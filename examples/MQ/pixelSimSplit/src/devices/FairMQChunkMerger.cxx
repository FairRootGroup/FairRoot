/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQChunkMerger.cxx
 *
 * @since 2016-03-21
 * @author R. Karabowicz
 */

#include "FairMQChunkMerger.h"

#include "FairMCPoint.h"
#include "FairMCSplitEventHeader.h"
#include "FairMCTrack.h"
#include "RootSerializer.h"

#include <FairMQLogger.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

FairMQChunkMerger::FairMQChunkMerger()
    : FairMQDevice()
    , fInputChannelName("data-in")
    , fOutputChannelName("data-out")
    , fNofPartsPerEventMap()
    , fObjectMap()
    , fEvRIPair()
    , fEvCOPair()
    , fRet()
    , fNofReceivedMessages(0)
    , fNofSentMessages(0)
    , fNofParts(3)
    , fMCSplitEventHeader(nullptr)
{}

void FairMQChunkMerger::Init()
{
    fInputChannelName = fConfig->GetValue<std::string>("in-channel");
    fOutputChannelName = fConfig->GetValue<std::string>("out-channel");

    OnData(fInputChannelName, &FairMQChunkMerger::MergeData);
}

bool FairMQChunkMerger::MergeData(FairMQParts& parts, int /*index*/)
{
    bool printInfo = false;
    int nofReceivedParts = 0;   // if set to -1, the data seems to be duplicated
    int nofExpectedParts = 1;

    fNofReceivedMessages++;
    // dataDuplicationFlag = false;

    std::vector<TClonesArray*> tcaVector;
    for (int ipart = 0; ipart < parts.Size(); ++ipart) {
        TObject* tempObject = nullptr;
        RootSerializer().Deserialize(*parts.At(ipart), tempObject);

        //        LOG(INFO) << "Got object " << tempObject->ClassName() << " named " << tempObject->GetName();
        if (strcmp(tempObject->GetName(), "MCEventHeader.") == 0) {
            fMCSplitEventHeader = dynamic_cast<FairMCSplitEventHeader*>(tempObject);
            //            LOG(info) << "GOT PART [" << fMCSplitEventHeader->GetRunID() << "][" <<
            //            fMCSplitEventHeader->GetEventID() << "][" << fMCSplitEventHeader->GetChunkStart() << "]";
            fEvRIPair.first = fMCSplitEventHeader->GetEventID();
            fEvRIPair.second = fMCSplitEventHeader->GetRunID();
            fEvCOPair.first = fMCSplitEventHeader->GetChunkStart();
            nofExpectedParts = fMCSplitEventHeader->GetNofChunks();

            fRet = fObjectMap.equal_range(fEvRIPair);
            for (auto& it = fRet.first; it != fRet.second; ++it) {
                //              LOG(info) << "comparing " << it->second.first << " and " << fEvCOPair.first;
                if (it->second.first == fMCSplitEventHeader->GetChunkStart())
                    LOG(fatal) << "got part starting at " << fEvCOPair.first << " again!!!";
            }

            auto it2 = fNofPartsPerEventMap.find(fEvRIPair);
            if (it2 == fNofPartsPerEventMap.end()) {
                fNofPartsPerEventMap[fEvRIPair] = 1;
                nofReceivedParts = 1;
            } else {
                it2->second += 1;
                nofReceivedParts = it2->second;
            }
        } else {
            tcaVector.push_back(dynamic_cast<TClonesArray*>(tempObject));
        }
    }

    // not all parts are there yet, have to put them in buffer
    if (nofReceivedParts != nofExpectedParts) {
        // LOG(info) << "not all parts are yet here (got " << nofReceivedParts << " out of " << nofExpectedParts <<
        // ")... adding to (size = " << fObjectMap.size() << ")"; LOG(info) << "+" << fMCSplitEventHeader->GetName() <<
        // "[" << fEvRIPair.second << "][" << fEvRIPair.first << "][" << fEvCOPair.first << "]";
        for (int iarray = 0; iarray < tcaVector.size(); ++iarray) {
            LOG(debug) << "+ [" << fEvRIPair.second << "][" << fEvRIPair.first << "][" << fEvCOPair.first << "] "
                       << tcaVector[iarray]->GetName();
            fEvCOPair.second = (dynamic_cast<TObject*>(tcaVector[iarray]));
            fObjectMap.insert(std::pair<std::pair<int, int>, std::pair<int, TObject*>>(fEvRIPair, fEvCOPair));
        }
        //        LOG(info) << "                 now we have fObjectMap (size = " << fObjectMap.size() << ")";
        if (printInfo)
            LOG(info) << ">> [" << fMCSplitEventHeader->GetRunID() << "][" << fMCSplitEventHeader->GetEventID() << "]["
                      << fMCSplitEventHeader->GetChunkStart() << "] Received: " << fNofReceivedMessages
                      << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    } else {
        // got all the parts of the event, have to combine and send message, consisting of objects from fObjectMap
        [[gnu::unused]] int currentEventPart = fMCSplitEventHeader->GetChunkStart();
        fRet = fObjectMap.equal_range(fEvRIPair);
        std::vector<int> trackShift;
        LOG(debug) << "- [" << fEvRIPair.second << "][" << fEvRIPair.first << "][ALL]";
        for (int iarray = 0; iarray < tcaVector.size(); ++iarray) {
            if (strcmp(tcaVector[iarray]->GetName(), "MCTrack") != 0)
                continue;   //  want only MCTrack array to renumber tracks and get track shifts...
            //  LOG(info) << "BEFORE ADDING, TCA \"" << tcaVector[iarray]->GetName() << "\" has " <<
            //  tcaVector[iarray]->GetEntries() << " entries.";
            TClonesArray* arrayToAdd;
            for (auto& it = fRet.first; it != fRet.second; ++it) {
                if (it->second.first == fMCSplitEventHeader->GetChunkStart())
                    continue;
                if (strcmp(tcaVector[iarray]->GetName(), it->second.second->GetName()) == 0) {
                    trackShift.push_back(tcaVector[iarray]->GetEntries());
                    arrayToAdd = dynamic_cast<TClonesArray*>(it->second.second);
                    for (int iobj = 0; iobj < arrayToAdd->GetEntries(); ++iobj) {
                        FairMCTrack* temp = dynamic_cast<FairMCTrack*>(arrayToAdd->At(iobj));
                        if (temp->GetMotherId() >= 0) {
                            temp->SetMotherId(temp->GetMotherId() + trackShift.back());
                        }
                    }
                    tcaVector[iarray]->AbsorbObjects(arrayToAdd);
                    //      LOG(info) << "FOUND ONE!, TCA has now " << tcaVector[iarray]->GetEntries() << " entries.";
                }
            }
        }

        for (int iarray = 0; iarray < tcaVector.size(); ++iarray) {
            if (strcmp(tcaVector[iarray]->GetName(), "MCTrack") == 0)
                continue;   // MCTrack already done, renumber all _other_ arrays...
            //            LOG(info) << "BEFORE ADDING, TCA \"" << tcaVector[iarray]->GetName() << "\" has " <<
            //            tcaVector[iarray]->GetEntries() << " entries.";
            int addedArray = 0;
            TClonesArray* arrayToAdd;

            for (auto& it = fRet.first; it != fRet.second; ++it) {
                if (it->second.first == fMCSplitEventHeader->GetChunkStart())
                    continue;
                if (strcmp(tcaVector[iarray]->GetName(), it->second.second->GetName()) == 0) {
                    int objShift = trackShift[addedArray++];
                    //     LOG(INFO) << "trying to add " << tcaVector[iarray]->GetName() << " and " <<
                    //     it->second.second->GetName() << "(shift = " << objShift << ")";
                    arrayToAdd = dynamic_cast<TClonesArray*>(it->second.second);
                    for (int iobj = 0; iobj < arrayToAdd->GetEntries(); ++iobj) {
                        FairMCPoint* temp = dynamic_cast<FairMCPoint*>(arrayToAdd->At(iobj));
                        temp->SetTrackID(temp->GetTrackID() + objShift);
                    }
                }
                tcaVector[iarray]->AbsorbObjects(arrayToAdd);
                //                LOG(info) << "FOUND ONE!, TCA has now " << tcaVector[iarray]->GetEntries() << "
                //                entries.";
            }
        }
        fObjectMap.erase(fRet.first, fRet.second);

        FairMQParts partsOut;

        fMCSplitEventHeader->SetNofChunks(1);
        fMCSplitEventHeader->SetChunkStart(0);

        FairMQMessagePtr messEH(NewMessage());
        RootSerializer().Serialize(*messEH, fMCSplitEventHeader);
        partsOut.AddPart(std::move(messEH));

        for (int iarray = 0; iarray < tcaVector.size(); ++iarray) {
            FairMQMessagePtr mess(NewMessage());
            RootSerializer().Serialize(*mess, tcaVector[iarray]);
            partsOut.AddPart(std::move(mess));
        }
        // LOG(info) << "created output message with " << partsOut.Size() << " parts.";
        Send(partsOut, fOutputChannelName);
        fNofSentMessages++;
        if (printInfo)
            LOG(info) << ">> [" << fMCSplitEventHeader->GetRunID() << "][" << fMCSplitEventHeader->GetEventID() << "]["
                      << fMCSplitEventHeader->GetChunkStart() << "] Received: " << fNofReceivedMessages
                      << " // Buffered: " << fObjectMap.size() << " // Sent: " << fNofSentMessages << " <<";
    }

    for (auto it = fObjectMap.begin(); it != fObjectMap.end(); ++it) {
        LOG(debug) << "= [" << it->first.second << "][" << it->first.first << "][" << it->second.first << "] "
                   << it->second.second->GetName();
    }
    return true;
}

FairMQChunkMerger::~FairMQChunkMerger() {}
