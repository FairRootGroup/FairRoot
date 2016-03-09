/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample7Client.cpp
 *
 * @since 2015-10-26
 * @author A. Rybalchenko
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQLogger.h"
#include "FairMQExample7Client.h"
#include "FairMQExample7ParOne.h"

#include "TMessage.h"
#include "Rtypes.h"

using namespace std;

FairMQExample7Client::FairMQExample7Client() :
    fRunId(0),
    fParameterName()
{
}

FairMQExample7Client::~FairMQExample7Client()
{
}

void FairMQExample7Client::CustomCleanup(void* /*data*/, void* hint)
{
    delete static_cast<string*>(hint);
}

// special class to expose protected TMessage constructor
class FairMQExample7TMessage : public TMessage
{
  public:
    FairMQExample7TMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

void FairMQExample7Client::Run()
{
    int runId = 2000;

    while (CheckCurrentState(RUNNING))
    {
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

        string* reqStr = new string(fParameterName + "," + to_string(runId));

        LOG(INFO) << "Requesting parameter \"" << fParameterName << "\" for Run ID " << runId << ".";

        unique_ptr<FairMQMessage> req(NewMessage(const_cast<char*>(reqStr->c_str()), reqStr->length(), CustomCleanup, reqStr));
        unique_ptr<FairMQMessage> rep(NewMessage());

        if (Send(req, "data") > 0)
        {
            if (Receive(rep, "data") > 0)
            {
                FairMQExample7TMessage tmsg(rep->GetData(), rep->GetSize());
                FairMQExample7ParOne* par = static_cast<FairMQExample7ParOne*>(tmsg.ReadObject(tmsg.GetClass()));
                LOG(INFO) << "Received parameter from the server:";
                par->print();
            }
        }

        runId == 2099 ? runId = 2000 : runId++;
    }
}


void FairMQExample7Client::SetProperty(const int key, const string& value)
{
    switch (key)
    {
        case ParameterName:
            fParameterName = value;
            break;
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

string FairMQExample7Client::GetProperty(const int key, const string& default_ /*= ""*/)
{
    switch (key)
    {
        case ParameterName:
            return fParameterName;
            break;
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

void FairMQExample7Client::SetProperty(const int key, const int value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

int FairMQExample7Client::GetProperty(const int key, const int default_ /*= 0*/)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}
