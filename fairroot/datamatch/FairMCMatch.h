/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCMatch.h
 *
 *  Created on: Nov 23, 2009
 *      Author: stockman
 */

#ifndef FAIRMCMATCH_H_
#define FAIRMCMATCH_H_

#ifndef FAIR_SILENCE_DATAMATCH_DEPRECATION
#warning "FairRoot::DataMatch is deprecated and will be removed in a future major release"
#endif

#include "FairMCEntry.h"           // for FairMCEntry
#include "FairMCResult.h"          // for FairMCResult
#include "FairMCStage.h"           // for FairMCStage
#include "FairMultiLinkedData.h"   // for FairMultiLinkedData
#include "FairRootManager.h"       // for FairRootManager

#include <Rtypes.h>    // for Int_t, FairMCMatch::Class, etc
#include <TNamed.h>    // for TNamed
#include <TString.h>   // for TString
#include <iostream>    // for ostream, cout, endl
#include <map>         // for map, etc
#include <string>      // for string
#include <utility>     // for pair

class FairLink;
class TClonesArray;

typedef std::map<Int_t, FairMCStage*>::iterator TListIterator;
typedef std::map<Int_t, FairMCStage*>::const_iterator TListIteratorConst;

class FairMCMatch : public TNamed
{
  public:
    FairMCMatch();
    FairMCMatch(const char* name, const char* title)
        : TNamed(name, title)
        , fUltimateStage(0)
        , fList()
        , fFinalStageML()
        , fVerbose(0)
    {
        fFinalStageML.SetPersistanceCheck(kFALSE);
    }

    virtual ~FairMCMatch();

    void AddElement(Int_t type, int index, FairLink link);
    void AddElement(Int_t sourceType, int index, Int_t targetType, int link);
    void SetElements(Int_t sourceType, int index, FairMultiLinkedData* links);
    void InitStage(Int_t type, const std::string& fileName, const std::string& branchName);
    void InitStage(const std::string& fileName, const std::string& branchName = "");
    void RemoveStage(Int_t type);
    void LoadInMCLists(TClonesArray* myLinkArray);
    void ClearMCList();

    void SetCommonWeightStages(Float_t weight);

    FairMCEntry GetEntry(Int_t type, int index);
    FairMCEntry GetEntry(FairLink link);

    FairMCResult GetMCInfo(Int_t start, Int_t stop);
    FairMCResult GetMCInfo(TString start, TString stop);
    FairMCEntry GetMCInfoSingle(FairLink aLink, Int_t stop);
    FairMCEntry GetMCInfoSingle(FairLink aLink, TString stop);

    int GetNMCStages() const { return fList.size(); }

    FairMCStage* GetMCStage(int index) const
    {
        TListIteratorConst iter = fList.begin();
        for (int i = 0; i < index; i++) {
            iter++;
        }
        return (iter->second);
    }

    FairMCStage* GetMCStageType(TString branch)
    {
        FairRootManager* ioman = FairRootManager::Instance();
        if (ioman->GetBranchId(branch) > 0) {
            return fList[ioman->GetBranchId(branch)];
        } else {
            return 0;
        }
    }

    FairMCStage* GetMCStageType(Int_t type) { return fList[type]; }

    void CreateArtificialStage(const TString& branchName, const std::string& fileName = "");
    void CreateArtificialStage(Int_t stage, const std::string& fileName = "", const std::string& branchName = "");

    FairMultiLinkedData FindLinksToStage(Int_t stage);

    bool IsTypeInList(Int_t type);

    void PrintInfo(std::ostream& out = std::cout) { out << *this; }

    friend std::ostream& operator<<(std::ostream& out, const FairMCMatch& match)
    {
        for (int i = 0; i < match.GetNMCStages(); i++) {
            if (match.GetMCStage(i)->GetLoaded()) {
                match.GetMCStage(i)->PrintInfo(out);
                out << std::endl;
            }
        }
        return out;
    }

  private:
    Int_t fUltimateStage;   ///< last stage in link chain. Here all recursive operations must stop.
    std::map<Int_t, FairMCStage*> fList;
    FairMultiLinkedData fFinalStageML;
    Int_t fVerbose;

    void FindStagesPointingToLinks(FairMultiLinkedData links, Int_t stop);
    FairMultiLinkedData FindStagesPointingToLink(FairLink link);

    FairMCResult GetMCInfoForward(Int_t start, Int_t stop);
    FairMCResult GetMCInfoBackward(Int_t start, Int_t stop);
    FairMCEntry GetMCInfoForwardSingle(FairLink link, Int_t stop);
    FairMCEntry GetMCInfoBackwardSingle(FairLink link, Int_t stop, Double_t weight = 1.);

    void GetNextStage(FairMultiLinkedData& startEntry, Int_t stopStage);
    void AddToFinalStage(FairLink link, Float_t mult);
    void ClearFinalStage();

    ClassDef(FairMCMatch, 1);
};

#endif /* FAIRMCMATCH_H_ */
