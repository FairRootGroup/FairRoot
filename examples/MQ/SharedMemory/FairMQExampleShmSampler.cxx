/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExampleShmSampler.cpp
 *
 * @since 2016-04-08
 * @author A. Rybalchenko
 */

#include <boost/timer/timer.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>

#include "FairMQExampleShmSampler.h"
#include "FairMQLogger.h"

using namespace std;
using namespace boost::interprocess;

FairMQExampleShmSampler::FairMQExampleShmSampler()
    : fMsgSize(10000)
    , fMsgCounter(0)
    , fMsgRate(1)
    , fBytesOut(0)
    , fMsgOut(0)
    , fBytesOutNew(0)
    , fMsgOutNew(0)
{
    if (shared_memory_object::remove("FairMQSharedMemory"))
    {
        LOG(INFO) << "Successfully removed shared memory upon device start.";
    }
    else
    {
        LOG(INFO) << "Did not remove shared memory upon device start.";
    }
}

FairMQExampleShmSampler::~FairMQExampleShmSampler()
{
    if (shared_memory_object::remove("FairMQSharedMemory"))
    {
        LOG(INFO) << "Successfully removed shared memory after the device has stopped.";
    }
    else
    {
        LOG(INFO) << "Did not remove shared memory after the device stopped. Still in use?";
    }
}

void FairMQExampleShmSampler::Init()
{
    SegmentManager::Instance().InitializeSegment("open_or_create", "FairMQSharedMemory", 2000000000);
    LOG(INFO) << "Created/Opened shared memory segment of 2,000,000,000 bytes. Available are "
              << SegmentManager::Instance().Segment()->get_free_memory() << " bytes.";
}

void FairMQExampleShmSampler::Run()
{
    static uint64_t numSentMsgs = 0;

    LOG(INFO) << "Starting the benchmark with message size of " << fMsgSize;
    boost::timer::auto_cpu_timer timer;

    boost::thread rateLogger(boost::bind(&FairMQExampleShmSampler::Log, this, 1000));
    boost::thread ackListener(boost::bind(&FairMQExampleShmSampler::ListenForAcks, this));
    boost::thread resetMsgCounter(boost::bind(&FairMQExampleShmSampler::ResetMsgCounter, this));

    // int charnum = 97;

    while (CheckCurrentState(RUNNING))
    {
        string* ownerStr = new string("o" + to_string(numSentMsgs));
        string chunkStr = "c" + to_string(numSentMsgs);

        while (SegmentManager::Instance().Segment()->get_free_memory() < fMsgSize + 50000000)
        {
            LOG(TRACE) << "Not enough free memory for new message ("
                       << SegmentManager::Instance().Segment()->get_free_memory()
                       << " < "
                       << fMsgSize
                       << ")...";
            unique_lock<mutex> lock(fAckMutex);
            fAckCV.wait_for(lock, chrono::milliseconds(500));
        }

        SharedPtrType localPtr = make_managed_shared_ptr(SegmentManager::Instance().Segment()->construct<ShmChunk>(chunkStr.c_str())(fMsgSize),
                                                         *(SegmentManager::Instance().Segment()));

        SharedPtrOwner* owner = SegmentManager::Instance().Segment()->construct<SharedPtrOwner>(ownerStr->c_str())(localPtr);

        {
            unique_lock<mutex> containerLock(fContainerMutex);
            fLocalPtrs.insert(make_pair(*ownerStr, move(localPtr)));
        }

        LOG(TRACE) << "Shared pointer constructed at: " << *ownerStr;
        LOG(TRACE) << "Chunk constructed at: " << chunkStr;

        void* ptr = SegmentManager::Instance().Segment()->get_address_from_handle(owner->fSharedPtr.get()->Handle());

        // write something to memory, otherwise only allocation will be measured
        memset(ptr, 0, fMsgSize);

        // static_cast<char*>(ptr)[3] = charnum++;

        // if (charnum == 123)
        // {
        //     charnum = 97;
        // }

        LOG(TRACE) << "chunk handle: " << owner->fSharedPtr.get()->Handle();
        LOG(TRACE) << "chunk size: " << owner->fSharedPtr.get()->Size();
        LOG(TRACE) << "owner use count: " << owner->fSharedPtr.use_count();

        char* cptr = static_cast<char*>(ptr);

        // LOG(TRACE) << "check: " << cptr[3];

        unique_ptr<FairMQMessage> msg(NewMessage(const_cast<char*>(ownerStr->c_str()),
                                                                   ownerStr->length(),
                                                                   [](void* data, void* hint){ delete static_cast<string*>(hint); },
                                                                   ownerStr));

        if (Send(msg, "meta") >= 0)
        {
            LOG(TRACE) << "Sent meta.";
            fBytesOutNew += fMsgSize;
            ++fMsgOutNew;
            ++numSentMsgs;
        }
        else
        {
            fLocalPtrs.erase(*ownerStr);
            SegmentManager::Instance().Segment()->destroy_ptr(owner);
        }

        --fMsgCounter;

        while (fMsgCounter == 0) {
          boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        }
    }

    LOG(INFO) << "Sent " << numSentMsgs << " messages, leaving RUNNING state.";
    LOG(INFO) << "Sending time: ";

    try
    {
        ackListener.join();
        rateLogger.interrupt();
        rateLogger.join();
        resetMsgCounter.interrupt();
        resetMsgCounter.join();
    }
    catch(boost::thread_resource_error& e)
    {
        LOG(ERROR) << e.what();
        exit(EXIT_FAILURE);
    }
}

void FairMQExampleShmSampler::ListenForAcks()
{
    while (CheckCurrentState(RUNNING))
    {
        unique_ptr<FairMQMessage> msg(NewMessage());

        if (Receive(msg, "ack") >= 0)
        {
            string key(static_cast<char*>(msg->GetData()), msg->GetSize());
            LOG(TRACE) << "Received ack for: " << key;
            {
                unique_lock<mutex> containerLock(fContainerMutex);
                if (fLocalPtrs.find(key) != fLocalPtrs.end())
                {
                    fLocalPtrs.erase(key);
                }
                else
                {
                    LOG(WARN) << "Received ack for a key not contained in the container";
                }
                LOG(TRACE) << fLocalPtrs.size();
            }
            fAckCV.notify_all();
        }
    }
}

void FairMQExampleShmSampler::Log(const int intervalInMs)
{
    timestamp_t t0 = get_timestamp();
    timestamp_t t1;
    timestamp_t msSinceLastLog;

    double mbPerSecOut = 0;
    double msgPerSecOut = 0;

    while (true)
    {
        try
        {
            t1 = get_timestamp();

            msSinceLastLog = (t1 - t0) / 1000.0L;

            mbPerSecOut = (static_cast<double>(fBytesOutNew - fBytesOut) / (1024. * 1024.)) / static_cast<double>(msSinceLastLog) * 1000.;
            fBytesOut = fBytesOutNew;

            msgPerSecOut = static_cast<double>(fMsgOutNew - fMsgOut) / static_cast<double>(msSinceLastLog) * 1000.;
            fMsgOut = fMsgOutNew;

            LOG(DEBUG) << fixed
                       << setprecision(0) << "out: " << msgPerSecOut << " msg ("
                       << setprecision(2) << mbPerSecOut << " MB)\t("
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

void FairMQExampleShmSampler::ResetMsgCounter()
{
  while (true) {
    try {
      fMsgCounter = fMsgRate / 100;
      boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    } catch (boost::thread_interrupted&) {
      LOG(DEBUG) << "Event rate limiter thread interrupted";
      break;
    }
  }
}

void FairMQExampleShmSampler::SetProperty(const int key, const string& value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

string FairMQExampleShmSampler::GetProperty(const int key, const string& default_ /*= ""*/)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

void FairMQExampleShmSampler::SetProperty(const int key, const int value)
{
    switch (key)
    {
        case MsgSize:
            fMsgSize = value;
            break;
        case MsgRate:
            fMsgRate = value;
            break;
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

int FairMQExampleShmSampler::GetProperty(const int key, const int default_ /*= 0*/)
{
    switch (key)
    {
        case MsgSize:
            return fMsgSize;
        case MsgRate:
            return fMsgRate;
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

string FairMQExampleShmSampler::GetPropertyDescription(const int key)
{
    switch (key)
    {
        case MsgSize:
            return "MsgSize: Size of the transfered message buffer.";
        case MsgRate:
            return "MsgRate: Maximum msg rate.";
        default:
            return FairMQDevice::GetPropertyDescription(key);
    }
}

void FairMQExampleShmSampler::ListProperties()
{
    LOG(INFO) << "Properties of FairMQExampleShmSampler:";
    for (int p = FairMQConfigurable::Last; p < FairMQExampleShmSampler::Last; ++p)
    {
        LOG(INFO) << " " << GetPropertyDescription(p);
    }
    LOG(INFO) << "---------------------------";
}
