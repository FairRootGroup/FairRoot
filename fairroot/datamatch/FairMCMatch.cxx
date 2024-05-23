/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCMatch.cxx
 *
 *  Created on: Nov 23, 2009
 *      Author: stockman
 */

#include "FairMCMatch.h"

#include "FairLink.h"          // for FairLink
#include "FairRootManager.h"   // for FairRootManager

#include <TClonesArray.h>   // for TClonesArray
#include <iostream>         // for operator<<, basic_ostream, etc

FairMCMatch::FairMCMatch()
    : TNamed()
    , fUltimateStage(0)
    , fList()
    , fFinalStageML()
    , fVerbose(0)
{
    fFinalStageML.SetPersistanceCheck(kFALSE);
}

FairMCMatch::~FairMCMatch()
{
    for (TListIterator iter = fList.begin(); iter != fList.end(); ++iter) {
        delete (iter->second);
    }
    fList.clear();
}

void FairMCMatch::AddElement(Int_t sourceType, int index, Int_t targetType, int link)
{
    FairLink myPair(targetType, link);
    AddElement(sourceType, index, myPair);
}

void FairMCMatch::AddElement(Int_t type, int index, FairLink link) { fList[type]->AddLink(link, index); }

void FairMCMatch::SetElements(Int_t sourceType, int index, FairMultiLinkedData* links)
{
    fList[sourceType]->SetEntry(links, index);
}

void FairMCMatch::InitStage(Int_t type, const std::string& fileName, const std::string& branchName)
{
    if (fList[type] == 0) {
        FairMCStage* newStage = new FairMCStage(type, fileName, branchName);
        fList[type] = newStage;
        if (fVerbose > 1) {
            std::cout << "InitStages: " << *newStage;
        }
    } else {
        std::cout << "-W- FairMCMatch::InitStage: Stage " << type << " exists already!" << std::endl;
    }
}

void FairMCMatch::InitStage(const std::string& branchName, const std::string& fileName)
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (ioman->CheckBranch(branchName.c_str()) == 1) {
        Int_t type = ioman->GetBranchId(branchName.c_str());
        if (type > -1) {
            InitStage(type, fileName, branchName);
        } else {
            std::cout << "-W- FairMCMatch::InitStage: Branch name " << branchName << " not registered!" << std::endl;
        }
    } else {
        std::cout << "-W- FairMCMatch::InitStage: Branch name " << branchName << " not persistant!" << std::endl;
    }
}

void FairMCMatch::RemoveStage(Int_t type) { fList.erase(type); }

void FairMCMatch::SetCommonWeightStages(Float_t weight)
{
    for (int i = 0; i < GetNMCStages(); ++i) {
        if (GetMCStage(i)) {
            GetMCStage(i)->SetWeight(weight);
        }
    }
}

FairMCResult FairMCMatch::GetMCInfo(TString start, TString stop)
{
    FairRootManager* ioman = FairRootManager::Instance();
    return GetMCInfo(ioman->GetBranchId(start), ioman->GetBranchId(stop));
}

FairMCResult FairMCMatch::GetMCInfo(Int_t start, Int_t stop)
{
    FairMCResult result(start, stop);
    if (!IsTypeInList(start)) {
        return result;
    }
    if (start < stop) {
        return GetMCInfoForward(start, stop);
    } else {
        return GetMCInfoBackward(start, stop);
    }
}

FairMCEntry FairMCMatch::GetMCInfoSingle(FairLink aLink, TString stop)
{
    FairRootManager* ioman = FairRootManager::Instance();
    return GetMCInfoSingle(aLink, ioman->GetBranchId(stop));
}

FairMCEntry FairMCMatch::GetMCInfoSingle(FairLink aLink, Int_t stop)
{
    FairMCEntry result;
    if (!IsTypeInList(static_cast<Int_t>(aLink.GetType()))) {
        return result;
    }
    if (!(fList[static_cast<Int_t>(aLink.GetType())]->GetNEntries() > aLink.GetIndex())) {
        return result;
    }

    if (aLink.GetType() < stop) {
        return GetMCInfoForwardSingle(aLink, stop);
    } else {
        return GetMCInfoBackwardSingle(aLink, stop);
    }
}

FairMCResult FairMCMatch::GetMCInfoForward(Int_t start, Int_t stop)
{
    FairMCResult result(start, stop);
    FairMCStage startVec = *(fList[start]);
    for (int i = 0; i < startVec.GetNEntries(); ++i) {
        FairLink tempLink(startVec.GetStageId(), i);

        FairMCEntry tempEntry(GetMCInfoForwardSingle(tempLink, stop));
        if (tempEntry.GetNLinks() > 0)
            if (tempEntry.GetLink(0).GetType() == start) {
                tempEntry.DeleteLink(tempEntry.GetLink(0));
            }
        tempEntry.SetSource(start);
        tempEntry.SetPos(i);
        result.SetEntry(tempEntry);
    }
    return result;
}

FairMCEntry FairMCMatch::GetMCInfoForwardSingle(FairLink link, Int_t stop)
{
    FairMCEntry result;
    ClearFinalStage();

    FairMultiLinkedData tempStage;
    tempStage.SetPersistanceCheck(kFALSE);
    tempStage.AddLink(link, true);
    FindStagesPointingToLinks(tempStage, stop);
    result.SetLinks(fFinalStageML);
    return result;
}

FairMCResult FairMCMatch::GetMCInfoBackward(Int_t start, Int_t stop)
{
    FairMCResult result(start, stop);
    FairMCStage startVec = *(fList[start]);
    for (int i = 0; i < startVec.GetNEntries(); ++i) {
        FairLink tempLink(start, i);
        GetMCInfoBackwardSingle(tempLink, stop, startVec.GetWeight());
        result.SetEntry(&fFinalStageML, result.GetNEntries());
    }
    return result;
}

FairMCEntry FairMCMatch::GetMCInfoBackwardSingle(FairLink aLink, Int_t stop, Double_t weight)
{
    FairMCEntry result;
    FairMultiLinkedData multiLink = fList[static_cast<Int_t>(aLink.GetType())]->GetEntry(aLink.GetIndex());

    ClearFinalStage();
    multiLink.MultiplyAllWeights(weight);
    GetNextStage(multiLink, stop);
    result.SetLinks(fFinalStageML);

    return result;
}

void FairMCMatch::FindStagesPointingToLinks(FairMultiLinkedData links, Int_t stop)
{
    FairMultiLinkedData tempLinks;
    tempLinks.SetPersistanceCheck(kFALSE);
    for (int i = 0; i < links.GetNLinks(); ++i) {
        FairLink myLink = links.GetLink(i);
        FairMultiLinkedData myNewLinks = FindStagesPointingToLink(myLink);
        myNewLinks.SetPersistanceCheck(kFALSE);
        if (myNewLinks.GetNLinks() == 0) {
            fFinalStageML.AddLink(myLink, true);
        } else {
            for (int j = 0; j < myNewLinks.GetNLinks(); ++j) {
                if (myNewLinks.GetLink(j).GetType() == static_cast<Int_t>(stop)) {
                    fFinalStageML.AddLink(myNewLinks.GetLink(j), true);
                } else if (myNewLinks.GetLink(j).GetType() > static_cast<Int_t>(stop)) {
                    fFinalStageML.AddLink(myLink, true);
                } else {
                    tempLinks.AddLink(myNewLinks.GetLink(j), true);
                }
            }
        }
    }
    if (tempLinks.GetNLinks() != 0) {
        FindStagesPointingToLinks(tempLinks, stop);
    }
}

FairMultiLinkedData FairMCMatch::FindStagesPointingToLink(FairLink link)
{
    FairMultiLinkedData result;
    result.SetPersistanceCheck(kFALSE);
    TListIteratorConst iter = fList.find(static_cast<Int_t>(link.GetType()));
    for (; iter != fList.end(); ++iter) {
        if (iter->second->PosInList(link).GetNLinks() > 0) {
            result.AddLinks(iter->second->PosInList(link), true);
        }
    }
    return result;
}

FairMultiLinkedData FairMCMatch::FindLinksToStage(Int_t stage)
{
    FairMultiLinkedData result;
    result.SetPersistanceCheck(kFALSE);
    for (int i = 0; i < GetNMCStages(); ++i) {
        result.AddLinks(GetMCStage(i)->GetLinksWithType(stage), true);
    }
    return result;
}

void FairMCMatch::CreateArtificialStage(const TString& branchName, const std::string& fileName)
{
    FairRootManager* ioman = FairRootManager::Instance();
    std::cout << "Create Artificial Stage for " << branchName;
    std::cout << " with ID " << ioman->GetBranchId(branchName) << std::endl;
    if (ioman->GetBranchId(branchName) > -1) {
        CreateArtificialStage(ioman->GetBranchId(branchName), fileName, branchName.Data());
    } else {
        std::cout << "-E- FairMCMatch::CreateArtificialStage: Branch does not exist: " << branchName << std::endl;
    }
}

void FairMCMatch::CreateArtificialStage(Int_t stage, const std::string& fileName, const std::string& branchName)
{
    FairMultiLinkedData stageLinks = FindLinksToStage(stage);
    stageLinks.SetPersistanceCheck(kFALSE);
    if (stageLinks.GetNLinks() > 0) {
        InitStage(stage, fileName, branchName);
        FairMultiLinkedData artData;
        artData.SetLink(FairLink(static_cast<Int_t>(-1), -1));
        for (int i = 0; i < stageLinks.GetNLinks(); ++i) {
            if (stageLinks.GetLink(i).GetIndex() > -1) {
                fList[stage]->SetEntry(&artData, stageLinks.GetLink(i).GetIndex());
            }
        }
        fList[stage]->SetLoaded(kTRUE);
    }
}

void FairMCMatch::GetNextStage(FairMultiLinkedData& startStage, Int_t stopStage)
{

    FairMCEntry tempStage;

    for (int i = 0; i < startStage.GetNLinks(); ++i) {
        if (startStage.GetLink(i).GetType() == stopStage) {
            AddToFinalStage(startStage.GetLink(i), 1);
            if (fVerbose > 0) {
                std::cout << "FinalStage: " << fFinalStageML << std::endl;
                std::cout << "---------------------" << std::endl;
            }
        } else if (startStage.GetLink(i).GetType() == fUltimateStage) {
        } else {
            tempStage = GetEntry(startStage.GetLink(i));
            if (fVerbose > 0) {
                std::cout << "TempStage Start";
                startStage.GetLink(i).PrintLinkInfo();
                std::cout << " --> " << tempStage << std::endl;
            }
            if (tempStage.GetNLinks() == 0) {
                AddToFinalStage(startStage.GetLink(i), 1);
                if (fVerbose > 0) {
                    std::cout << "FinalStage: " << fFinalStageML << std::endl;
                    std::cout << "---------------------" << std::endl;
                }
            } else {
                double tempStageWeight = GetMCStageType(static_cast<Int_t>(tempStage.GetSource()))->GetWeight();
                double startLinkWeight = startStage.GetLink(i).GetWeight();

                if (fVerbose > 0) {
                    std::cout << "Tempstage " << tempStage.GetSource() << ": weight " << tempStageWeight << std::endl;
                    std::cout << "StartLinkWeight " << startLinkWeight << std::endl;
                }
                tempStage.MultiplyAllWeights(tempStageWeight);

                if ((tempStageWeight * startLinkWeight) == 0) {
                    tempStage.MultiplyAllWeights(tempStageWeight);
                    tempStage.AddAllWeights(startLinkWeight / startStage.GetNLinks());
                    if (fVerbose > 0) {
                        std::cout << " NLinks: " << tempStage.GetNLinks() << " ";
                        std::cout << "AddAllWeights: " << startLinkWeight / startStage.GetNLinks() << std::endl;
                    }
                } else {
                    tempStage.MultiplyAllWeights(startLinkWeight);
                    if (fVerbose > 0) {
                        std::cout << "MultiplyAllWeights: " << startLinkWeight << std::endl;
                    }
                }
            }
            if (fVerbose > 0) {
                std::cout << "TempStage Stop: " << tempStage << std::endl;
            }

            GetNextStage(tempStage, stopStage);
        }
    }
}

FairMCEntry FairMCMatch::GetEntry(Int_t type, int index)
{

    FairMCEntry empty;
    if (index < 0) {
        return empty;
    }
    if (fList[type] == 0) {
        return empty;
    }
    if (fList[type]->GetNEntries() > index) {
        return fList[type]->GetEntry(index);
    }
    return empty;
}

FairMCEntry FairMCMatch::GetEntry(FairLink link)
{
    return GetEntry(static_cast<Int_t>(link.GetType()), link.GetIndex());
}

void FairMCMatch::AddToFinalStage(FairLink hitPair, Float_t mult) { fFinalStageML.AddLink(hitPair, true, mult); }

void FairMCMatch::ClearFinalStage() { fFinalStageML.Reset(); }

void FairMCMatch::ClearMCList()
{
    for (TListIterator iter = fList.begin(); iter != fList.end(); ++iter) {
        if (iter->second != 0) {
            iter->second->ClearEntries();
        }
    }
    fList.clear();
}

bool FairMCMatch::IsTypeInList(Int_t type)
{
    for (TListIterator iter = fList.begin(); iter != fList.end(); ++iter) {
        if (iter->first == type) {
            return true;
        }
    }
    return false;
}

void FairMCMatch::LoadInMCLists(TClonesArray* myLinkArray)
{
    for (int i = 0; i < myLinkArray->GetEntriesFast(); ++i) {
        FairMCEntry* myLink = static_cast<FairMCEntry*>(myLinkArray->At(i));
        if (IsTypeInList(static_cast<Int_t>(myLink->GetSource()))) {
            fList[static_cast<Int_t>(myLink->GetSource())]->SetEntry(*myLink);
            fList[static_cast<Int_t>(myLink->GetSource())]->SetLoaded(kTRUE);
        }
    }
}
