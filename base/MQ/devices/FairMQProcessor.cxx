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

    fProcessorTask->SetSendPart(boost::bind(&FairMQProcessor::SendPart, this));
    fProcessorTask->SetReceivePart(boost::bind(&FairMQProcessor::ReceivePart, this));
}

void FairMQProcessor::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;

    // int inSize = 0;
    // int outSize = 0;

    // store the channel references to avoid traversing the map on every loop iteration
    FairMQChannel& dataInChannel = fChannels.at("data-in").at(0);
    FairMQChannel& dataOutChannel = fChannels.at("data-out").at(0);

    while (CheckCurrentState(RUNNING))
    {
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());

        if (dataInChannel.Receive(fProcessorTask->GetPayload()) > 0)
        {
            ++receivedMsgs;
            // inSize += fProcessorTask->GetPayload()->GetSize();
            fProcessorTask->Exec();

            // outSize += fProcessorTask->GetPayload()->GetSize();
            dataOutChannel.Send(fProcessorTask->GetPayload());
            sentMsgs++;
        }

        fProcessorTask->ClearPayload();
    }

    // LOG(INFO) << "Input size (" << receivedMsgs << "): " << inSize << ". Output size (" << sentMsgs << "): " << outSize;
    LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}

void FairMQProcessor::SendPart()
{
      fChannels.at("data-out").at(0).Send(fProcessorTask->GetPayload(), "snd-more");
      fProcessorTask->GetPayload()->CloseMessage();
}

bool FairMQProcessor::ReceivePart()
{
    if (fChannels.at("data-in").at(0).ExpectsAnotherPart())
    {
        fProcessorTask->GetPayload()->CloseMessage();
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());
        return fChannels.at("data-in").at(0).Receive(fProcessorTask->GetPayload());
    }
    else
    {
        return false;
    }
}
