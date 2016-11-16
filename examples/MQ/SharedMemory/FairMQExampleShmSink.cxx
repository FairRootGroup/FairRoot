/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExampleShmSink.cxx
 *
 * @since 2016-04-08
 * @author A. Rybalchenko
 */

#include <boost/thread.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>

#include "FairMQExampleShmSink.h"
#include "FairMQLogger.h"
#include "ShmChunk.h"

using namespace std;
using namespace boost::interprocess;

FairMQExampleShmSink::FairMQExampleShmSink()
    : fBytesIn(0)
    , fMsgIn(0)
    , fBytesInNew(0)
    , fMsgInNew(0)
{
}

FairMQExampleShmSink::~FairMQExampleShmSink()
{
}

void FairMQExampleShmSink::Init()
{
    SegmentManager::Instance().InitializeSegment("open_only", "FairMQSharedMemory");
    LOG(INFO) << "Opened shared memory segment 'FairMQSharedMemory'. Available are "
              << SegmentManager::Instance().Segment()->get_free_memory() << " bytes.";
}

void FairMQExampleShmSink::Run()
{
    uint64_t numReceivedMsgs = 0;

    boost::thread rateLogger(boost::bind(&FairMQExampleShmSink::Log, this, 1000));

    while (CheckCurrentState(RUNNING))
    {
        unique_ptr<FairMQMessage> msg(NewMessage());

        if (Receive(msg, "meta") >= 0)
        {
            string ownerStr(static_cast<char*>(msg->GetData()), msg->GetSize());
            LOG(TRACE) << "Received message: " << ownerStr;

            SharedPtrType* owner = SegmentManager::Instance().Segment()->find<SharedPtrType>(ownerStr.c_str()).first;
            LOG(TRACE) << "owner use count: " << owner->use_count();

            // reply with the string as a confirmation
            if (Send(msg, "ack") >= 0)
            {
                LOG(TRACE) << "Sent acknowledgement.";
            }

            if (owner)
            {
                // void* ptr = SegmentManager::Instance().Segment()->get_address_from_handle(owner->get()->Handle());
                LOG(TRACE) << "chunk handle: " << owner->get()->Handle();
                LOG(TRACE) << "chunk size: " << owner->get()->Size();
                fBytesInNew += owner->get()->Size();
                ++fMsgInNew;

                // char* cptr = static_cast<char*>(ptr);

                // LOG(TRACE) << "check: " << cptr[3];
            }
            else
            {
                LOG(WARN) << "shared pointer is zero :-(";
            }

            SegmentManager::Instance().Segment()->destroy_ptr(owner);

            LOG(TRACE) << "deallocated memory & destroyed shared pointer";
            LOG(TRACE) << "owner use count: " << owner->use_count();

            ++numReceivedMsgs;
        }
    }

    LOG(INFO) << "Received " << numReceivedMsgs << " messages, leaving RUNNING state.";

    try
    {
        rateLogger.interrupt();
        rateLogger.join();
    }
    catch(boost::thread_resource_error& e)
    {
        LOG(ERROR) << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQExampleShmSink::Log(const int intervalInMs)
{
    timestamp_t t0 = get_timestamp();
    timestamp_t t1;
    timestamp_t msSinceLastLog;

    double mbPerSecIn = 0;
    double msgPerSecIn = 0;

    while (true)
    {
        try
        {
            t1 = get_timestamp();

            msSinceLastLog = (t1 - t0) / 1000.0L;

            mbPerSecIn = (static_cast<double>(fBytesInNew - fBytesIn) / (1024. * 1024.)) / static_cast<double>(msSinceLastLog) * 1000.;
            fBytesIn = fBytesInNew;

            msgPerSecIn = static_cast<double>(fMsgInNew - fMsgIn) / static_cast<double>(msSinceLastLog) * 1000.;
            fMsgIn = fMsgInNew;

            LOG(DEBUG) << fixed
                       << setprecision(0) << "in: " << msgPerSecIn << " msg ("
                       << setprecision(2) << mbPerSecIn << " MB)\t("
                       << SegmentManager::Instance().Segment()->get_free_memory() / (1024. * 1024.) << " MB free)";

            t0 = t1;
            boost::this_thread::sleep(boost::posix_time::milliseconds(intervalInMs));
        }
        catch (boost::thread_interrupted&)
        {
            break;
        }
    }
}
