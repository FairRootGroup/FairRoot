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
  fBranch(""),
  fOutput(NULL)
{
}

FairMQSamplerTask::FairMQSamplerTask() :
  FairTask( "Abstract base task used for loading a branch from a root file into memory"),
  fInput(NULL),
  fBranch(""),
  fOutput(NULL)
{
}

FairMQSamplerTask::~FairMQSamplerTask()
{
  delete fInput;
  fOutput->CloseMessage();
  //delete fOutput; // leave fOutput in memory, because it is needed even after FairMQSamplerTask is terminated. ClearOutput will clean it when it is no longer needed.
}

InitStatus FairMQSamplerTask::Init()
{
  FairRootManager* ioman = FairRootManager::Instance();
  fInput = (TClonesArray*) ioman->GetObject(fBranch.c_str());

  return kSUCCESS;
}



void FairMQSamplerTask::Exec(Option_t* opt)
{
  
}


void FairMQSamplerTask::SetBranch(string branch)
{
  fBranch = branch;
}

FairMQMessage* FairMQSamplerTask::GetOutput()
{
  return fOutput;
}

void FairMQSamplerTask::SetTransport(FairMQTransportFactory* factory)
{
  fTransportFactory = factory;
}
