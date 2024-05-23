/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairMCMatchCreatorTask source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
#include "FairMCMatchCreatorTask.h"

#include "FairLink.h"              // for FairLink
#include "FairMCEntry.h"           // for FairMCEntry
#include "FairMCMatch.h"           // for FairMCMatch
#include "FairMCStage.h"           // for FairMCStage
#include "FairMultiLinkedData.h"   // for FairMultiLinkedData
#include "FairRootManager.h"       // for FairRootManager

#include <TClonesArray.h>   // for TClonesArray
#include <iostream>         // for operator<<, basic_ostream, etc

FairMCMatchCreatorTask::FairMCMatchCreatorTask()
    : FairTask("Creates FairMCMatch")
    , fMCMatch(nullptr)
    , fBranches()
    , fPersistance(kTRUE)
    , fMCLink(nullptr)
    , fEventNr(0)
{}

FairMCMatchCreatorTask::~FairMCMatchCreatorTask() {}

InitStatus FairMCMatchCreatorTask::Init()
{
    fMCMatch = new FairMCMatch("FairMCMatch", "FairMCMatch");

    InitDataStages();

    InitStatus status = InitBranches();

    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        std::cout << "-E- FairMCMatchCreatorTask::Init: "
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    fMCLink = new TClonesArray("FairMCEntry");
    ioman->Register("MCLink", "MCInfo", fMCLink, kTRUE);

    ioman->Register("MCMatch", "MCInfo", fMCMatch, kFALSE);

    std::cout << "-I- FairMCMatchCreatorTask::Init: Initialization successfull" << std::endl;

    return status;
}

InitStatus FairMCMatchCreatorTask::InitBranches()
{

    // Get RootManager
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        std::cout << "-E- FairMCMatchCreatorTask::Init: "
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    int NStages = fMCMatch->GetNMCStages();
    for (int i = NStages - 1; i > -1; i--) {
        TClonesArray* myBranch =
            static_cast<TClonesArray*>(ioman->GetObject(fMCMatch->GetMCStage(i)->GetBranchName().c_str()));
        if (!myBranch) {
            // std::cout << "NMCStages: " << fMCMatch->GetNMCStages() << std::endl;
            std::cout << "-W- FairMCMatchCreatorTask::Init: "
                      << "No " << fMCMatch->GetMCStage(i)->GetBranchName() << " array!" << std::endl;
            fMCMatch->GetMCStage(i)->SetFill(kFALSE);   // RemoveStage(fMCMatch->GetMCStage(i)->GetStageId());

            continue;
        } else {
            fMCMatch->GetMCStage(i)->SetFill(kTRUE);
        }
        fBranches[fMCMatch->GetMCStage(i)->GetBranchName()] = myBranch;
    }
    return kSUCCESS;
}

void FairMCMatchCreatorTask::Exec(Option_t* /*opt*/)
{
    if (!fMCLink) {
        Fatal("Exec", "No fMCLinkDet");
    }
    fMCLink->Delete();
    fMCMatch->ClearMCList();

    fMCMatch->LoadInMCLists(fMCLink);

    for (int i = 0; i < fMCMatch->GetNMCStages(); i++) {
        if (fMCMatch->GetMCStage(i)->GetFill() && !fMCMatch->GetMCStage(i)->GetLoaded()) {
            TClonesArray* clArray = fBranches[fMCMatch->GetMCStage(i)->GetBranchName()];
            for (int j = 0; j < clArray->GetEntries(); j++) {
                FairMultiLinkedData* myData = static_cast<FairMultiLinkedData*>(clArray->At(j));
                fMCMatch->SetElements(fMCMatch->GetMCStage(i)->GetStageId(), j, myData);
            }
            if (fMCMatch->GetMCStage(i)->GetNEntries() > 0) {
                fMCMatch->GetMCStage(i)->SetLoaded(kTRUE);
            }
        }
    }

    int i = 0;
    if (fPersistance) {
        for (int index = 0; index < fMCMatch->GetNMCStages(); index++) {
            FairMCStage myStage(*(fMCMatch->GetMCStage(index)));

            for (int indStage = 0; indStage < myStage.GetNEntries(); indStage++) {

                FairMCEntry myLink(myStage.GetMCLink(indStage));
                new ((*fMCLink)[i]) FairMCEntry(myLink.GetLinks(), myLink.GetSource(), myLink.GetPos());
                i++;
            }
        }
    }

    if (fVerbose > 0) {
        fMCMatch->Print();
        std::cout << std::endl;
    }
}

void FairMCMatchCreatorTask::Finish() {}
