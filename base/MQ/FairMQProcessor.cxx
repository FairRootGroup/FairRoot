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

FairMQProcessor::FairMQProcessor() :
  fProcessorTask(NULL)
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

void FairMQProcessor::Init()
{
  FairMQDevice::Init();

  fProcessorTask->InitTask();

  fProcessorTask->SetSendPart(boost::bind(&FairMQProcessor::SendPart, this));
  fProcessorTask->SetReceivePart(boost::bind(&FairMQProcessor::ReceivePart, this));
}

void FairMQProcessor::Run()
{
  LOG(INFO) << ">>>>>>> Run <<<<<<<";

  boost::thread rateLogger(boost::bind(&FairMQDevice::LogSocketRates, this));

  int receivedMsgs = 0;
  int sentMsgs = 0;

  bool received = false;

  while ( fState == RUNNING ) {
    fProcessorTask->SetPayload(fTransportFactory->CreateMessage());

    received = fPayloadInputs->at(0)->Receive(fProcessorTask->GetPayload());
    receivedMsgs++;

    if (received) {
      fProcessorTask->Exec();

      fPayloadOutputs->at(0)->Send(fProcessorTask->GetPayload());
      sentMsgs++;
      received = false;
    }

    fProcessorTask->GetPayload()->CloseMessage();
  }

  LOG(INFO) << "I've received " << receivedMsgs << " and sent " << sentMsgs << " messages!";

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));

  try {
    rateLogger.interrupt();
    rateLogger.join();
  } catch(boost::thread_resource_error& e) {
    LOG(ERROR) << e.what();
  }
}

void FairMQProcessor::SendPart()
{
    fPayloadOutputs->at(0)->Send(fProcessorTask->GetPayload(), "snd-more");
    fProcessorTask->GetPayload()->CloseMessage();
}

bool FairMQProcessor::ReceivePart()
{
    int64_t more = 0;
    size_t more_size = sizeof(more);
    fPayloadInputs->at(0)->GetOption("rcv-more", &more, &more_size);
    if(more)
    {
        fProcessorTask->GetPayload()->CloseMessage();
        fProcessorTask->SetPayload(fTransportFactory->CreateMessage());
        return fPayloadInputs->at(0)->Receive(fProcessorTask->GetPayload());
    }
    else
    {
        return false;
    }
}


