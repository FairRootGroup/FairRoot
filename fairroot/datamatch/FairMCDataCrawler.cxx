/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCDataCrawler.cpp
 *
 *  Created on: Jul 5, 2011
 *      Author: stockman
 */

#include "FairMCDataCrawler.h"

#include "FairLink.h"          // for FairLink, operator<<
#include "FairRootManager.h"   // for FairRootManager

#include <iostream>   // for operator<<, ostream, cout, etc

ClassImp(FairMCDataCrawler);

FairMCDataCrawler::FairMCDataCrawler()
    : fIoman(FairRootManager::Instance())
    , fFinalStage()
    , fUltimateStage(0)
    , fVerbose(0)
    , fStoreAllEndpoints(kTRUE)
    , fStoreIntermediate(kTRUE)
{}

FairMCDataCrawler::~FairMCDataCrawler() {}

void FairMCDataCrawler::Init()
{

    InitDataObjects();
    /*
  fIoman->GetObject("MVDPoint");
  fIoman->GetObject("MVDStripDigis");
  fIoman->GetObject("MVDPixelDigis");
  fIoman->GetObject("MVDHitsPixel");
  fIoman->GetObject("MVDHitsStrip");
  fIoman->GetObject("MVDPixelClusterCand");
  fIoman->GetObject("MVDStripClusterCand");
  fIoman->GetObject("MVDSortedStripDigis");
  fIoman->GetObject("MVDSortedPixelDigis");


  fIoman->GetObject("EmcCluster");
  fIoman->GetObject("EmcBump");
  fIoman->GetObject("EmcDigi");
  fIoman->GetObject("EmcHit");
  fIoman->GetObject("EmcPoint");
  fIoman->GetObject("EmcRecoHit");
  fIoman->GetObject("EmcSharedDigi");
  fIoman->GetObject("EmcWaveform");



  fIoman->GetObject("STTPoint");
  fIoman->GetObject("STTHit");
  fIoman->GetObject("SttHelixHit");
  fIoman->GetObject("STTTrack");
  fIoman->GetObject("STTTrackCand");

  fIoman->GetObject("FairTpcPoint");
  fIoman->GetObject("FairTpcPrimaryCluster");
  fIoman->GetObject("FairTpcDriftedElectron");
  fIoman->GetObject("FairTpcAvalanche");
  fIoman->GetObject("FairTpcSignal");
  fIoman->GetObject("FairTpcDigi");
  fIoman->GetObject("FairTpcCluster");


  fIoman->GetObject("GEMPoint");
  fIoman->GetObject("GEMDigi");
  fIoman->GetObject("GEMHit");

  fIoman->GetObject("FairDchPoint");
  fIoman->GetObject("FairDchDigi");
  fIoman->GetObject("PndDchCylinderHit");

  fIoman->GetObject("MdtPoint");
  fIoman->GetObject("MdtHit");
  fIoman->GetObject("MdtTrk");

  fIoman->GetObject("LheHit");
  fIoman->GetObject("LheCandidate");
  fIoman->GetObject("LheTrack");
  fIoman->GetObject("MVDIdealTrackCand");
  fIoman->GetObject("MVDRiemannTrackCand");
  fIoman->GetObject("PndTrack");
  fIoman->GetObject("LheGenTrack");
  fIoman->GetObject("PidChargedCand");
  fIoman->GetObject("PidNeutralCand");
  */
}

FairMultiLinkedData FairMCDataCrawler::GetInfo(FairMultiLinkedData startLink, TString stopStage)
{
    return GetInfo(startLink, fIoman->GetBranchId(stopStage));
}

FairMultiLinkedData FairMCDataCrawler::GetInfo(FairMultiLinkedData startLink, Int_t stopStageId)
{
    fFinalStage.ResetLinks();
    if (fVerbose > 1) {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "StartLink: " << startLink;
    }
    if (fVerbose > 1) {
        std::cout << "StopStageLink: " << fIoman->GetBranchName(stopStageId) << std::endl;
    }
    GetNextStage(startLink, stopStageId);
    if (fVerbose > 1) {
        std::cout << "FinalStage: " << fFinalStage << std::endl;
    }
    return fFinalStage;
}

FairMultiLinkedData* FairMCDataCrawler::GetEntry(FairLink link)
{
    return static_cast<FairMultiLinkedData*>(FairRootManager::Instance()->GetCloneOfLinkData(link));
}

FairMultiLinkedData* FairMCDataCrawler::GetEntry(Int_t fileId, Int_t eventNr, Int_t type, Int_t index)
{
    return GetEntry(FairLink(fileId, eventNr, type, index));
}

void FairMCDataCrawler::GetNextStage(FairMultiLinkedData& startStage, Int_t stopStage)
{
    FairMultiLinkedData* tempStage;
    for (int i = 0; i < startStage.GetNLinks(); i++) {
        FairLink actualLink = startStage.GetLink(i);
        //    if (fVerbose > 0) { std::cout << "Actual Link: " << actualLink << std::endl; }
        if (actualLink.GetType() < 0) {
            if (fStoreAllEndpoints) {
                AddToFinalStage(actualLink, 1);
            }
            if (fVerbose > 2) {
                std::cout << "ActualLink.Type < 0" << std::endl;
                std::cout << "FinalStage: " << fFinalStage << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            if (fVerbose > 1) {
                std::cout << std::endl;
            }
        } else if (actualLink.GetType() == stopStage) {
            AddToFinalStage(actualLink, 1);
            if (fVerbose > 2) {
                std::cout << "ActualLink.Type == stopStage" << std::endl;
                std::cout << "FinalStage: " << fFinalStage << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            if (fVerbose > 1) {
                std::cout << std::endl;
            }
        } else if (actualLink.GetType() == fUltimateStage) {
            if (fStoreAllEndpoints) {
                AddToFinalStage(actualLink, 1);
            }
            if (fVerbose > 2) {
                std::cout << "ActualLink.Type == UltimateStage" << std::endl;
                std::cout << "FinalStage: " << fFinalStage << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            if (fVerbose > 1) {
                std::cout << std::endl;
            }
        } else if (actualLink.GetType() == FairRootManager::Instance()->GetBranchId("EventHeader.")) {
            if (fStoreAllEndpoints) {
                AddToFinalStage(actualLink, 1);
            }
            if (fVerbose > 2) {
                std::cout << "ActualLink.Type == EventHeader" << std::endl;
                std::cout << "FinalStage: " << fFinalStage << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            if (fVerbose > 1) {
                std::cout << std::endl;
            }
        } else {
            tempStage = GetEntry(actualLink);
            if (tempStage == 0) {
                if (fStoreAllEndpoints) {
                    AddToFinalStage(actualLink, 1);
                }
                if (fVerbose > 2) {
                    std::cout << "TempStage == 0" << std::endl;
                    std::cout << "FinalStage: " << fFinalStage << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
                if (fVerbose > 1) {
                    std::cout << std::endl;
                }
                continue;
            }
            if (fVerbose > 0) {
                //        std::cout << "TempStage Start";
                std::cout << " // ";
                std::cout << actualLink;
                std::cout << " --> " << *tempStage;
            }
            if (tempStage->GetNLinks() == 0) {
                if (fStoreAllEndpoints) {
                    AddToFinalStage(actualLink, 1);
                }
                if (fVerbose > 0) {
                    std::cout << "tempStage->GetNLinks == 0" << std::endl;
                    std::cout << "FinalStage: " << fFinalStage << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
            } else {
                if (fStoreIntermediate) {
                    AddToFinalStage(actualLink, 1);
                }
                double tempStageWeight = 1;
                double startLinkWeight = startStage.GetLink(i).GetWeight();

                if (fVerbose > 2) {
                    // std::cout << "Tempstage " << tempStage.GetSource() << ": weight " << tempStageWeight <<
                    // std::endl;
                    std::cout << "StartLinkWeight " << startLinkWeight << std::endl;
                }
                // std::cout << " StageWeight: " << tempStageWeight << " startLinkWeight: " << startLinkWeight;
                tempStage->MultiplyAllWeights(tempStageWeight);

                if ((tempStageWeight * startLinkWeight) == 0) {
                    tempStage->MultiplyAllWeights(tempStageWeight);
                    tempStage->AddAllWeights(startLinkWeight / startStage.GetNLinks());
                    if (fVerbose > 2) {
                        std::cout << " NLinks: " << tempStage->GetNLinks() << " ";
                        std::cout << "AddAllWeights: " << startLinkWeight / startStage.GetNLinks() << std::endl;
                    }
                } else {
                    tempStage->MultiplyAllWeights(startLinkWeight);
                    if (fVerbose > 2) {
                        std::cout << "MultiplyAllWeights: " << startLinkWeight << std::endl;
                    }
                }
            }
            //      if (fVerbose > 0)
            //        std::cout<< "TempStage Stop: " << *tempStage << std::endl;

            GetNextStage(*tempStage, stopStage);
        }
    }
}

void FairMCDataCrawler::AddToFinalStage(FairLink hitPair, Float_t mult) { fFinalStage.AddLink(hitPair, false, mult); }
