/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9Merger.cxx
 *
 * @since 2016-03-21
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQEx9Merger.h"
#include "FairMQLogger.h"

#include "TMessage.h"

using namespace std;

// special class to expose protected TMessage constructor
class Ex9TMessage : public TMessage
{
  public:
  Ex9TMessage(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

FairMQEx9Merger::FairMQEx9Merger()
  : FairMQDevice()
  , fInputChannelName("data-in")
  , fOutputChannelName("data-out")
  , fNofPartsPerEventMap()
  , fObjectMap()
  , fEvRIPair()
  , fEvRIPartTrio()
  , fRet()
  , fNofReceivedMessages(0)
  , fNofSentMessages(0)
  , fNofParts(3)
  , fEventHeader(NULL)
{
}

void FairMQEx9Merger::Init()
{
  OnData(fInputChannelName, &FairMQEx9Merger::MergeData);
}

bool FairMQEx9Merger::MergeData(FairMQParts& parts, int /*index*/)
{

  bool printInfo = false;
  int nofReceivedParts = 0; // if set to -1, the data seems to be duplicated

  fNofReceivedMessages++;
  //	  dataDuplicationFlag = false;
  TObject*      tempObject;
  TClonesArray* tempArrays[10];
  int nofArrays = 0;
  // LOG(TRACE) << "******************************************************************************************************";
  for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
  {
    Ex9TMessage tm(parts.At(ipart)->GetData(), parts.At(ipart)->GetSize());
    tempObject = (TObject*)tm.ReadObject(tm.GetClass());
    if ( strcmp(tempObject->GetName(),"EventHeader.") == 0 )
    {
      fEventHeader = (PixelEventHeader*)tempObject;
      // LOG(TRACE) << "GOT PART [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "]";

      // setting how many parts were received...
      fEvRIPair    .first  = fEventHeader->GetMCEntryNumber();
      fEvRIPair    .second = fEventHeader->GetRunId();
      fEvRIPartTrio.first  = fEvRIPair;
      fEvRIPartTrio.second = fEventHeader->GetPartNo();

      MultiMapDef::iterator it3;
      it3 = fObjectMap.find(fEvRIPartTrio);
      if ( it3 != fObjectMap.end() ) {
        LOG(INFO) << "FairMQEx9Merger::Run(), shouldn't happen, already got objects for part " << fEvRIPartTrio.second 
                  << ", event " << fEvRIPair.first << ", run " << fEvRIPair.second << ". Skipping this message!!!";
        nofReceivedParts = -1;
        break; // break the for(ipart) loop, as nothing else is left to do
      }
      
      std::map<std::pair<int,int>,int>::iterator it2;
      it2 = fNofPartsPerEventMap.find(fEvRIPair);
      if ( it2 == fNofPartsPerEventMap.end() ) {
        // LOG(TRACE) << "FIRST PART OF event " << fEvRIPair.first;
        fNofPartsPerEventMap[fEvRIPair] = 1;
        nofReceivedParts = 1;
      }
      else {
        it2->second+=1;
        nofReceivedParts = it2->second;
      }
      // LOG(TRACE) << " got " << nofReceivedParts << " parts of event " << fEvRIPair.first;
    }
    else { 
      tempArrays[nofArrays] = (TClonesArray*)tempObject;
      nofArrays++;
    }
  } // end the for(ipart) loop, should have received TCAs in tempArrays and PixelEventHeader
  if ( nofReceivedParts == -1 ) return true;

  // not all parts are there yet, have to put them in buffer
  if ( nofReceivedParts != fNofParts )
    { 
      // LOG(TRACE) << "not all parts are yet here... adding to (size = " << fObjectMap.size() << ")";
      // LOG(TRACE) << "+" << fEventHeader->GetName() << "[" << fEvRIPartTrio.first.second << "][" << fEvRIPartTrio.first.first << "][" << fEvRIPartTrio.second << "]";
      fObjectMap.insert(std::pair<std::pair<std::pair<int,int>,int>,TObject*>(fEvRIPartTrio,(TObject*)fEventHeader));
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ )
      {
        // LOG(TRACE) << "+" << tempArrays[iarray]->GetName() << "[" << fEvRIPartTrio.first.second << "][" << fEvRIPartTrio.first.first << "][" << fEvRIPartTrio.second << "]";
        fObjectMap.insert(std::pair<std::pair<std::pair<int,int>,int>,TObject*>(fEvRIPartTrio,(TObject*)tempArrays[iarray]));
      }
      // LOG(TRACE) << "                 now we have fObjectMap (size = " << fObjectMap.size() << ")";
      if ( printInfo) 
        LOG(INFO) << ">> [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "] Received: " << fNofReceivedMessages << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    }
  // got all the parts of the event, have to combine and send message, consisting of objects from tempArrays
  else
    {
      int currentEventPart = fEventHeader->GetPartNo();
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ ) 
      {
        // LOG(TRACE) << "BEFORE ADDING, TCA \"" << tempArrays[iarray]->GetName() << "\" has " << tempArrays[iarray]->GetEntries() << " entries.";
        TClonesArray* arrayToAdd;

        for ( int ieventpart = 0 ; ieventpart < fNofParts ; ieventpart++ ) {
          if ( ieventpart == currentEventPart ) continue;
          fEvRIPartTrio.second = ieventpart;
          fRet = fObjectMap.equal_range(fEvRIPartTrio);
          for ( MultiMapDef::iterator it = fRet.first ; it != fRet.second ; ++it ) {
            if ( tempArrays[iarray]->GetName() == it->second->GetName() ) {
              arrayToAdd = (TClonesArray*)it->second;
              tempArrays[iarray]->AbsorbObjects(arrayToAdd);
              // LOG(TRACE) << "FOUND ONE!, TCA has now " << tempArrays[iarray]->GetEntries() << " entries.";
            }
          }
        }
      }
      for ( int ieventpart = 0 ; ieventpart < fNofParts ; ieventpart++ ) {
        if ( ieventpart == currentEventPart ) continue;
        fEvRIPartTrio.second = ieventpart;
        fRet = fObjectMap.equal_range(fEvRIPartTrio);
        fObjectMap.erase(fRet.first,fRet.second);
      }

      TMessage* messageFEH;
      TMessage* messageTCA[10];
      FairMQParts partsOut;

      messageFEH = new TMessage(kMESS_OBJECT);
      messageFEH->WriteObject(fEventHeader);
      partsOut.AddPart(NewMessage(messageFEH->Buffer(),
                       messageFEH->BufferSize(), 
                       [](void* /*data*/, void* hint) { delete (TMessage*)hint;},
                       messageFEH));
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ ) {
        messageTCA[iarray] = new TMessage(kMESS_OBJECT);
        messageTCA[iarray]->WriteObject(tempArrays[iarray]);
        partsOut.AddPart(NewMessage(messageTCA[iarray]->Buffer(), 
                         messageTCA[iarray]->BufferSize(), 
                         [](void* /*data*/, void* hint) { delete (TMessage*)hint;},
                         messageTCA[iarray]));
      }
      Send(partsOut, fOutputChannelName);
      fNofSentMessages++;
      if ( printInfo )
        LOG(INFO) << ">> [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "] Received: " << fNofReceivedMessages << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    }

  return true;
}

FairMQEx9Merger::~FairMQEx9Merger()
{ 
}
