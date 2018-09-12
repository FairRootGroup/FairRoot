/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelMerger.cxx
 *
 * @since 2016-03-21
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQPixelMerger.h"
#include "FairMQLogger.h"

#include "RootSerializer.h"

using namespace std;

FairMQPixelMerger::FairMQPixelMerger()
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

void FairMQPixelMerger::Init()
{
  OnData(fInputChannelName, &FairMQPixelMerger::MergeData);
}

bool FairMQPixelMerger::MergeData(FairMQParts& parts, int /*index*/)
{

  bool printInfo = false;
  int nofReceivedParts = 0; // if set to -1, the data seems to be duplicated

  fNofReceivedMessages++;
  //	  dataDuplicationFlag = false;
  TObject*      tempObject;
  TClonesArray* tempArrays[10];
  int nofArrays = 0;
  // LOG(debug) << "******************************************************************************************************";
  for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
  {
    tempObject = nullptr;
    Deserialize<RootSerializer>(*parts.At(ipart),tempObject);
    if ( strcmp(tempObject->GetName(),"EventHeader.") == 0 )
    {
      fEventHeader = (PixelEventHeader*)tempObject;
      // LOG(debug) << "GOT PART [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "]";

      // setting how many parts were received...
      fEvRIPair    .first  = fEventHeader->GetMCEntryNumber();
      fEvRIPair    .second = fEventHeader->GetRunId();
      fEvRIPartTrio.first  = fEvRIPair;
      fEvRIPartTrio.second = fEventHeader->GetPartNo();

      MultiMapDef::iterator it3;
      it3 = fObjectMap.find(fEvRIPartTrio);
      if ( it3 != fObjectMap.end() ) {
        LOG(info) << "FairMQPixelMerger::Run(), shouldn't happen, already got objects for part " << fEvRIPartTrio.second 
                  << ", event " << fEvRIPair.first << ", run " << fEvRIPair.second << ". Skipping this message!!!";
        nofReceivedParts = -1;
        break; // break the for(ipart) loop, as nothing else is left to do
      }
      
      std::map<std::pair<int,int>,int>::iterator it2;
      it2 = fNofPartsPerEventMap.find(fEvRIPair);
      if ( it2 == fNofPartsPerEventMap.end() ) {
        // LOG(debug) << "FIRST PART OF event " << fEvRIPair.first;
        fNofPartsPerEventMap[fEvRIPair] = 1;
        nofReceivedParts = 1;
      }
      else {
        it2->second+=1;
        nofReceivedParts = it2->second;
      }
      // LOG(debug) << " got " << nofReceivedParts << " parts of event " << fEvRIPair.first;
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
      // LOG(debug) << "not all parts are yet here... adding to (size = " << fObjectMap.size() << ")";
      // LOG(debug) << "+" << fEventHeader->GetName() << "[" << fEvRIPartTrio.first.second << "][" << fEvRIPartTrio.first.first << "][" << fEvRIPartTrio.second << "]";
      fObjectMap.insert(std::pair<std::pair<std::pair<int,int>,int>,TObject*>(fEvRIPartTrio,(TObject*)fEventHeader));
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ )
      {
        // LOG(debug) << "+" << tempArrays[iarray]->GetName() << "[" << fEvRIPartTrio.first.second << "][" << fEvRIPartTrio.first.first << "][" << fEvRIPartTrio.second << "]";
        fObjectMap.insert(std::pair<std::pair<std::pair<int,int>,int>,TObject*>(fEvRIPartTrio,(TObject*)tempArrays[iarray]));
      }
      // LOG(debug) << "                 now we have fObjectMap (size = " << fObjectMap.size() << ")";
      if ( printInfo) 
        LOG(info) << ">> [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "] Received: " << fNofReceivedMessages << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    }
  // got all the parts of the event, have to combine and send message, consisting of objects from tempArrays
  else
    {
      int currentEventPart = fEventHeader->GetPartNo();
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ ) 
      {
        // LOG(debug) << "BEFORE ADDING, TCA \"" << tempArrays[iarray]->GetName() << "\" has " << tempArrays[iarray]->GetEntries() << " entries.";
        TClonesArray* arrayToAdd;

        for ( int ieventpart = 0 ; ieventpart < fNofParts ; ieventpart++ ) {
          if ( ieventpart == currentEventPart ) continue;
          fEvRIPartTrio.second = ieventpart;
          fRet = fObjectMap.equal_range(fEvRIPartTrio);
          for ( MultiMapDef::iterator it = fRet.first ; it != fRet.second ; ++it ) {
            if ( tempArrays[iarray]->GetName() == it->second->GetName() ) {
              arrayToAdd = (TClonesArray*)it->second;
              tempArrays[iarray]->AbsorbObjects(arrayToAdd);
              // LOG(debug) << "FOUND ONE!, TCA has now " << tempArrays[iarray]->GetEntries() << " entries.";
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

      FairMQMessagePtr messageTCA[10];
      FairMQParts partsOut;

      FairMQMessagePtr messFEH(NewMessage());
      Serialize<RootSerializer>(*messFEH,fEventHeader);
      partsOut.AddPart(std::move(messFEH));
      for ( int iarray = 0 ; iarray < nofArrays ; iarray++ ) {
        messageTCA[iarray] = NewMessage();
        Serialize<RootSerializer>(*messageTCA[iarray],tempArrays[iarray]);
        partsOut.AddPart(std::move(messageTCA[iarray]));
      }
      Send(partsOut, fOutputChannelName);
      fNofSentMessages++;
      if ( printInfo )
        LOG(info) << ">> [" << fEventHeader->GetRunId() << "][" << fEventHeader->GetMCEntryNumber() << "][" << fEventHeader->GetPartNo() << "] Received: " << fNofReceivedMessages << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    }

  return true;
}

FairMQPixelMerger::~FairMQPixelMerger()
{ 
}
