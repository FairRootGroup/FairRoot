/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExample7Client.cpp
 *
 * @since 2015-10-26
 * @author A. Rybalchenko
 */

#include <thread> // this_thread::sleep_for
#include <chrono>

#include "FairMQLogger.h"
#include "FairMQExample7Client.h"
#include "FairMQExample7ParOne.h"
#include "FairMQProgOptions.h"

#include "TMessage.h"
#include "Rtypes.h"

using namespace std;

FairMQExample7Client::FairMQExample7Client()
    : fRunId(0)
    , fParameterName()
    , fMaxIterations(0)
    , fNumIterations(0)
{
}

FairMQExample7Client::~FairMQExample7Client()
{
}

void FairMQExample7Client::InitTask()
{
    fParameterName = fConfig->GetValue<string>("parameter-name");
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
    fRunId = 2000;
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

bool FairMQExample7Client::ConditionalRun()
{
    LOG(info) << "Requesting parameter \"" << fParameterName << "\" for Run ID " << fRunId << ".";

    // NewSimpleMessage creates a copy of the data and takes care of its destruction (after the transfer takes place).
    // Should only be used for small data because of the cost of an additional copy
    FairMQMessagePtr req(NewSimpleMessage(fParameterName + "," + to_string(fRunId)));
    FairMQMessagePtr rep(NewMessage());

    if (Send(req, "data") > 0)
    {
        if (Receive(rep, "data") >= 0)
        {
            if (rep->GetSize() != 0)
            {
                FairMQExample7TMessage tmsg(rep->GetData(), rep->GetSize());
                FairMQExample7ParOne* par = static_cast<FairMQExample7ParOne*>(tmsg.ReadObject(tmsg.GetClass()));
                LOG(info) << "Received parameter from the server:";
                par->print();
            }
            else
            {
                LOG(error) << "Received empty reply. Parameter not available";
            }
        }
    }

    fRunId == 2099 ? fRunId = 2000 : fRunId++;

    if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations)
    {
        LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
        return false;
    }

    this_thread::sleep_for(chrono::seconds(1));

    return true;
}
