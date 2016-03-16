/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9Sampler.cpp
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQEx9Sampler.h"
#include "FairMQLogger.h"

#include "FairMQMessage.h"
#include "TMessage.h"

using namespace std;

FairMQEx9Sampler::FairMQEx9Sampler()
  : FairMQDevice()
  , fInputObjects()
  , fRunAna(NULL)
  , fSource(NULL)
  , fNObjects(0)
  , fMaxIndex(-1)
  , fBranchNames()
  , fFileNames()
{
}

void FairMQEx9Sampler::InitTask() 
{
  fRunAna = new FairRunAna();
  if ( fFileNames.size() > 0 ) {
    fSource = new FairFileSource(fFileNames.at(0).c_str());
    for ( int ifile = 1 ; ifile < fFileNames.size() ; ifile++ ) 
      fSource->AddFile(fFileNames.at(ifile));
  }
  fSource->Init();
  LOG(INFO) << "Going to request " << fBranchNames.size() << "  branches:";
  for ( int ibrn = 0 ; ibrn < fBranchNames.size() ; ibrn++ ) {
    LOG(INFO) << " requesting branch \"" << fBranchNames[ibrn] << "\"";
    int branchStat = fSource->ActivateObject((TObject**)&fInputObjects[fNObjects],fBranchNames[ibrn].c_str()); // should check the status...
    if ( fInputObjects[fNObjects] ) {
      LOG(INFO) << "Activated object \"" << fInputObjects[fNObjects] << "\" with name \"" << fBranchNames[ibrn] << "\" (" << branchStat << ")";
      fNObjects++;
    }
  }
  if ( fMaxIndex < 0 )
    fMaxIndex = fSource->CheckMaxEventNo();
  LOG(INFO) << "Input source has " << fMaxIndex << " events.";
}

// helper function to clean up the object holding the data after it is transported.
void free_tmessage2(void *data, void *hint)
{
    delete (TMessage*)hint;
}

void FairMQEx9Sampler::Run()
{
  int eventCounter = 0;

  // Check if we are still in the RUNNING state.
  while (CheckCurrentState(RUNNING))
    {
      if ( eventCounter == fMaxIndex ) break;

      Int_t readEventReturn = fSource->ReadEvent(eventCounter);

      if ( readEventReturn != 0 ) break;

      TMessage* message[1000];
      FairMQParts parts;
      
      for ( int iobj = 0 ; iobj < fNObjects ; iobj++ ) {
	message[iobj] = new TMessage(kMESS_OBJECT);
	message[iobj]->WriteObject(fInputObjects[iobj]);
	parts.AddPart(NewMessage(message[iobj]->Buffer(), message[iobj]->BufferSize(), free_tmessage2, message[iobj]));
      }
      
      Send(parts, "data-out");
      
      eventCounter++;
    }
  
  LOG(INFO) << "Going out of RUNNING state.";
}

FairMQEx9Sampler::~FairMQEx9Sampler()
{
}
