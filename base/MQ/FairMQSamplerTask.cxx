/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSamplerTask.cxx
 *
 * @since 2012-11-22
 * @author D. Klein, A. Rybalchenko
 */

#include "FairMQSamplerTask.h"

FairMQSamplerTask::FairMQSamplerTask(const Text_t* name, int iVerbose) :
  FairTask(name, iVerbose),
  fInput(NULL),
  fOutput(NULL),
  fTransportFactory(NULL),
  fEventIndex(0)
{
}

FairMQSamplerTask::FairMQSamplerTask() :
  FairTask("Abstract base task used for loading a branch from a root file into memory"),
  fInput(NULL),
  fOutput(NULL),
  fTransportFactory(NULL),
  fEventIndex(0),
  fEvtHeader(NULL)
{
}

FairMQSamplerTask::~FairMQSamplerTask()
{
  delete fInput;
  // fOutput->CloseMessage();
}

InitStatus FairMQSamplerTask::Init()
{
  FairRootManager* ioman = FairRootManager::Instance();
  fEvtHeader = (FairEventHeader *)ioman->GetObject("EventHeader.");
  fInput = (TClonesArray*) ioman->GetObject(fBranch.c_str());

  return kSUCCESS;
}

void FairMQSamplerTask::Exec(Option_t *opt)
{
}

// initialize a callback to the Sampler for sending multipart messages.
void FairMQSamplerTask::SetSendPart(boost::function<void()> callback)
{
  SendPart = callback;
}

void FairMQSamplerTask::SetBranch(string branch)
{
  fBranch = branch;
}

void FairMQSamplerTask::SetEventIndex(Long64_t EventIndex)
{
  fEventIndex = EventIndex;
}

FairMQMessage* FairMQSamplerTask::GetOutput()
{
  return fOutput;
}

void FairMQSamplerTask::SetTransport(FairMQTransportFactory* factory)
{
  fTransportFactory = factory;
}
