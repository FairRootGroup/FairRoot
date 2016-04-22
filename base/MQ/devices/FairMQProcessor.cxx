/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQProcessor.cxx
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQProcessor.h"
#include "FairMQLogger.h"

FairMQProcessor::FairMQProcessor()
  : fProcessorTask(NULL)
{
}

FairMQProcessor::~FairMQProcessor()
{
    delete fProcessorTask;
}

void FairMQProcessor::SetTask(FairMQProcessorTask* task)
{
    fProcessorTask = task;
}

void FairMQProcessor::InitTask()
{
    fProcessorTask->InitTask();

    fProcessorTask->SetTransport(fTransportFactory);
}

void FairMQProcessor::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;

    // channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);
    FairMQChannel& dataOutChannel = fChannels.at("data-out").at(0);

    while (CheckCurrentState(RUNNING))
    {
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(fProcessorTask->GetPayload()) > 0)
        {
            ++receivedMsgs;
            fProcessorTask->Exec();

            dataOutChannel.Send(fProcessorTask->GetPayload());
            sentMsgs++;
        }

        fProcessorTask->ClearPayload();
    }

    LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}
