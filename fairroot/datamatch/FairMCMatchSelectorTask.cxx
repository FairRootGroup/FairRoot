/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairMCMatchSelectorTask source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
#include "FairMCMatchSelectorTask.h"

#include "FairMCMatch.h"       // for FairMCMatch
#include "FairMCResult.h"      // for operator<<
#include "FairMCStage.h"       // for FairMCStage
#include "FairRootManager.h"   // for FairRootManager

#include <iostream>   // for operator<<, ostream, etc

// -----   Default constructor   -------------------------------------------
FairMCMatchSelectorTask::FairMCMatchSelectorTask()
    : FairTask("Creates FairMCMatch")
    , fMCMatch(nullptr)
    , fStart(-1)
    , fStop(-1)
    , fStartString("")
    , fStopString("")
    , fStageWeights()
    , fCommonWeight(0)
{}
// -------------------------------------------------------------------------

FairMCMatchSelectorTask::FairMCMatchSelectorTask(TString start, TString stop)
    : FairTask("Creates FairMCMatch")
    , fMCMatch(nullptr)
    , fStart(-1)
    , fStop(-1)
    , fStartString(start)
    , fStopString(stop)
    , fStageWeights()
    , fCommonWeight(0)
{}

FairMCMatchSelectorTask::FairMCMatchSelectorTask(Int_t start, Int_t stop)
    : FairTask("Creates FairMCMatch")
    , fMCMatch(nullptr)
    , fStart(start)
    , fStop(stop)
    , fStartString("")
    , fStopString("")
    , fStageWeights()
    , fCommonWeight(0)
{}

// -----   Destructor   ----------------------------------------------------
FairMCMatchSelectorTask::~FairMCMatchSelectorTask() {}

// -----   Public method Init   --------------------------------------------
InitStatus FairMCMatchSelectorTask::Init()
{

    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        std::cout << "-E- FairMCMatchSelectorTask::Init: "
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    fMCMatch = static_cast<FairMCMatch*>(ioman->GetObject("MCMatch"));
    if (fStart < 0 && fStop < 0) {
        fStart = ioman->GetBranchId(fStartString);
        fStop = ioman->GetBranchId(fStopString);
        std::cout << fStartString << ": " << fStart << " / " << fStopString << ": " << fStop << std::endl;
    }

    std::cout << "-I- FairMCMatchSelectorTask::Init: Initialization successfull" << std::endl;

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairMCMatchSelectorTask::Exec(Option_t* /*opt*/)
{
    std::cout << "Output Selector: " << std::endl;
    SetWeights();
    fMCMatch->CreateArtificialStage("MCTrack");
    std::cout << fMCMatch->GetMCInfo(fStart, fStop);
    std::cout << std::endl;
}

void FairMCMatchSelectorTask::SetWeights()
{
    fMCMatch->SetCommonWeightStages(fCommonWeight);
    for (unsigned int i = 0; i < fStageWeights.size(); i++) {
        fMCMatch->GetMCStageType(fStageWeights[i].first)->SetWeight(fStageWeights[i].second);
    }
}

void FairMCMatchSelectorTask::Finish() {}
