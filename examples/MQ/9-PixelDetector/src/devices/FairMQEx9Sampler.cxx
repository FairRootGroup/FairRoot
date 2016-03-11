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
  , fSourceName()
{
}

void FairMQEx9Sampler::InitTask() 
{
  //  fSourceName = "/Users/karabowi/fairroot/pixel9_dev/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root";
  //  fBranchNames.push_back("EventHeader.");
  //  fBranchNames.push_back("PixelDigis");

  fRunAna = new FairRunAna();
  fSource = new FairFileSource(fSourceName.c_str());
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

void FairMQEx9Sampler::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        case InputFileName :
	  SetInputFileName(value);
            break;

        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

void FairMQEx9Sampler::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

std::string FairMQEx9Sampler::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        case InputFileName :
	  return GetInputFileName();

        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

int FairMQEx9Sampler::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}

FairMQEx9Sampler::~FairMQEx9Sampler()
{
}
