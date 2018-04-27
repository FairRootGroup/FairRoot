/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9Sampler.cpp
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include "FairMQEx9Sampler.h"

#include "TMessage.h"
#include "TClonesArray.h"

#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "FairSource.h"
#include "FairFileSource.h"

using namespace std;

FairMQEx9Sampler::FairMQEx9Sampler()
  : FairMQDevice()
  , fOutputChannelName("data-out")
  , fAckChannelName("")
  , fRunAna(NULL)
  , fSource(NULL)
  , fInputObjects()
  , fNObjects(0)
  , fMaxIndex(-1)
  , fEventCounter(0)
  , fBranchNames()
  , fFileNames()
  , fAckListener()
{
}

void FairMQEx9Sampler::InitTask() 
{
  fFileNames         = fConfig->GetValue<std::vector<std::string>>("file-name");
  fMaxIndex          = fConfig->GetValue<int64_t>                 ("max-index");
  fBranchNames       = fConfig->GetValue<std::vector<std::string>>("branch-name");
  fOutputChannelName = fConfig->GetValue<std::string>             ("out-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");
  
  fRunAna = new FairRunAna();

  if ( fSource == NULL ) 
    {
      fSource = new FairFileSource(fFileNames.at(0).c_str());
      for ( unsigned int ifile = 1 ; ifile < fFileNames.size() ; ifile++ ) 
	((FairFileSource*)fSource)->AddFile(fFileNames.at(ifile));
    }

  fSource->Init();
  LOG(info) << "Going to request " << fBranchNames.size() << "  branches:";
  for ( unsigned int ibrn = 0 ; ibrn < fBranchNames.size() ; ibrn++ ) {
    LOG(info) << " requesting branch \"" << fBranchNames[ibrn] << "\"";
    int branchStat = fSource->ActivateObject((TObject**)&fInputObjects[fNObjects],fBranchNames[ibrn].c_str()); // should check the status...
    if ( fInputObjects[fNObjects] ) {
      LOG(info) << "Activated object \"" << fInputObjects[fNObjects] << "\" with name \"" << fBranchNames[ibrn] << "\" (" << branchStat << "), it got name: \"" << fInputObjects[fNObjects]->GetName() << "\"";
      if ( strcmp(fInputObjects[fNObjects]->GetName(),fBranchNames[ibrn].c_str()) )
	if ( strcmp(fInputObjects[fNObjects]->ClassName(),"TClonesArray") == 0 ) 
	  ((TClonesArray*)fInputObjects[fNObjects])->SetName(fBranchNames[ibrn].c_str());
      fNObjects++;
    }
  }
  if ( fMaxIndex < 0 )
    fMaxIndex = fSource->CheckMaxEventNo();
  LOG(info) << "Input source has " << fMaxIndex << " events.";
}

// helper function to clean up the object holding the data after it is transported.
void free_tmessage2(void* /*data*/, void *hint)
{
    delete (TMessage*)hint;
}

void FairMQEx9Sampler::PreRun()
{
  if (fAckChannelName != "") {
    fAckListener = thread(&FairMQEx9Sampler::ListenForAcks, this);
  }

  LOG(info) << "FairMQEx9Sampler::PreRun() finished!";
}

bool FairMQEx9Sampler::ConditionalRun()
{
  if ( fEventCounter == fMaxIndex ) return false;
  
  Int_t readEventReturn = fSource->ReadEvent(fEventCounter);

  if ( readEventReturn != 0 ) return false;
  
  TMessage* message[1000];
  FairMQParts parts;
  
  for ( int iobj = 0 ; iobj < fNObjects ; iobj++ ) {
    message[iobj] = new TMessage(kMESS_OBJECT);
    message[iobj]->WriteObject(fInputObjects[iobj]);
    parts.AddPart(NewMessage(message[iobj]->Buffer(), message[iobj]->BufferSize(), free_tmessage2, message[iobj]));
  }
  
  Send(parts, fOutputChannelName);
  
  fEventCounter++;

  return true;
}

void FairMQEx9Sampler::PostRun()
{
  if (fAckChannelName != "") {
    fAckListener.join();
  }

  LOG(info) << "PostRun() finished!";
}

void FairMQEx9Sampler::ListenForAcks()
{
  if (fAckChannelName != "")
      {
          Long64_t numAcks = 0;
          do
              {
                  unique_ptr<FairMQMessage> ack(NewMessage());
                  if (Receive(ack, fAckChannelName) >= 0)
                      {
                          numAcks++;
                      }
              }
          while (numAcks < fMaxIndex);
          
          LOG(info) << "Acknowledged " << numAcks << " messages.";
      }
}

FairMQEx9Sampler::~FairMQEx9Sampler()
{
}
