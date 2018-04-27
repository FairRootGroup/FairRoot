/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9SamplerBin.cpp
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include "FairMQEx9SamplerBin.h"
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

#include "FairMQMessage.h"
#include "TMessage.h"

#include "TClonesArray.h"

#include "FairEventHeader.h"

#include "PixelDigi.h"
#include "PixelHit.h"
#include "PixelTrack.h"

#include "PixelPayload.h"

using namespace std;

FairMQEx9SamplerBin::FairMQEx9SamplerBin()
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

void FairMQEx9SamplerBin::InitTask() 
{
  fFileNames         = fConfig->GetValue<std::vector<std::string>>("file-name");
  fMaxIndex          = fConfig->GetValue<int64_t>                 ("max-index");
  fBranchNames       = fConfig->GetValue<std::vector<std::string>>("branch-name");
  fOutputChannelName = fConfig->GetValue<std::string>             ("out-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");

  fRunAna = new FairRunAna();
  if ( fFileNames.size() > 0 ) {
    fSource = new FairFileSource(fFileNames.at(0).c_str());
    for ( unsigned int ifile = 1 ; ifile < fFileNames.size() ; ifile++ ) 
      fSource->AddFile(fFileNames.at(ifile));
  }
  fSource->Init();
  LOG(info) << "Going to request " << fBranchNames.size() << "  branches:";
  for ( unsigned int ibrn = 0 ; ibrn < fBranchNames.size() ; ibrn++ ) {
    LOG(info) << " requesting branch \"" << fBranchNames[ibrn] << "\"";
    int branchStat = fSource->ActivateObject((TObject**)&fInputObjects[fNObjects],fBranchNames[ibrn].c_str()); // should check the status...
    if ( fInputObjects[fNObjects] ) {
      LOG(info) << "Activated object \"" << fInputObjects[fNObjects] << "\" with name \"" << fBranchNames[ibrn] << "\" (" << branchStat << ")";
      fNObjects++;
    }
  }
  if ( fMaxIndex < 0 )
    fMaxIndex = fSource->CheckMaxEventNo();
  LOG(info) << "Input source has " << fMaxIndex << " events.";
}

void FairMQEx9SamplerBin::PreRun()
{
  LOG(info) << "FairMQEx9Sampler::PreRun() started!";

  fAckListener = thread(&FairMQEx9SamplerBin::ListenForAcks, this);
}

bool FairMQEx9SamplerBin::ConditionalRun()
{
  if ( fEventCounter == fMaxIndex ) return false;
  
  int readEventReturn = 0;
  readEventReturn = fSource->ReadEvent(fEventCounter);
  
  if ( readEventReturn != 0 ) return false;
  
  FairMQParts parts;
  
  for ( int iobj = 0 ; iobj < fNObjects ; iobj++ ) {
    if ( strcmp(fInputObjects[iobj]->GetName(),"EventHeader.") == 0 ) {
      PixelPayload::EventHeader* header = new PixelPayload::EventHeader();
      header->fRunId     = ((FairEventHeader*)fInputObjects[iobj])->GetRunId();
      header->fMCEntryNo = ((FairEventHeader*)fInputObjects[iobj])->GetMCEntryNumber();
      header->fPartNo    = 0;
      FairMQMessagePtr msgHeader(NewMessage(header,
                                            sizeof(PixelPayload::EventHeader),
                                            [](void* data, void* /*hint*/) { delete static_cast<PixelPayload::EventHeader*>(data); }
                                            ));
      parts.AddPart(std::move(msgHeader));
      // LOG(debug) << "-----------------------------";
      // LOG(debug) << "first part has size = " << sizeof(PixelPayload::EventHeader);
    }
    else {
      Int_t nofEntries = ((TClonesArray*)fInputObjects[iobj])->GetEntries();
      size_t digisSize = nofEntries * sizeof(PixelPayload::Digi);
      
      FairMQMessagePtr  msgTCA(NewMessage(digisSize));
      
      PixelPayload::Digi* digiPayload = static_cast<PixelPayload::Digi*>(msgTCA->GetData());
      
      
      for ( int idigi = 0 ; idigi < nofEntries ; idigi++ ) {
	PixelDigi* digi = static_cast<PixelDigi*>(((TClonesArray*)fInputObjects[iobj])->At(idigi));
	if ( !digi ) {
	  continue;
	}
	new (&digiPayload[idigi]) PixelPayload::Digi();
	digiPayload[idigi].fDetectorID = digi->GetDetectorID();
	digiPayload[idigi].fFeID       = digi->GetFeID();
	digiPayload[idigi].fCharge     = digi->GetCharge();
	digiPayload[idigi].fCol        = digi->GetCol();
	digiPayload[idigi].fRow        = digi->GetRow();
      }
      // LOG(debug) << "second part has size = " << digisSize;
      parts.AddPart(std::move(msgTCA));
    }
  }
      
  // LOG(debug) << "sending data with " << parts.Size() << " parts";
  Send(parts, fOutputChannelName);
  
  fEventCounter++;

  return true;
}

void FairMQEx9SamplerBin::PostRun() 
{
  if (fAckChannelName != "") {
    fAckListener.join();
  }

  LOG(info) << "PostRun() finished!";
}

void FairMQEx9SamplerBin::ListenForAcks()
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

FairMQEx9SamplerBin::~FairMQEx9SamplerBin()
{
}
