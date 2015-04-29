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

    while (GetCurrentState() == RUNNING)
    {
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());

        ++receivedMsgs;

        if (fChannels["data-in"].at(0).Receive(fProcessorTask->GetPayload()) > 0)
        {
            fProcessorTask->Exec();

            fChannels["data-out"].at(0).Send(fProcessorTask->GetPayload());
            sentMsgs++;
        }

        fProcessorTask->GetPayload()->CloseMessage();
    }

    LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}

void FairMQProcessor::SendPart()
{
      fChannels["data-out"].at(0).Send(fProcessorTask->GetPayload(), "snd-more");
      fProcessorTask->GetPayload()->CloseMessage();
}

bool FairMQProcessor::ReceivePart()
{
    int64_t more = 0;
    size_t more_size = sizeof(more);
    fChannels["data-in"].at(0).fSocket->GetOption("rcv-more", &more, &more_size);
    if (more)
    {
        fProcessorTask->GetPayload()->CloseMessage();
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());
        return fChannels["data-in"].at(0).Receive(fProcessorTask->GetPayload());
    }
    else
    {
        return false;
    }
}
