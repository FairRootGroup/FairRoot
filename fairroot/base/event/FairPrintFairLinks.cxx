/********************************************************************************
 * Copyright (C) 2018-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairPrintFairLinks source file             -----
// -----                  Created 18/07/08  by T.Stockmanns        -----
// -------------------------------------------------------------------------
#include "FairPrintFairLinks.h"

// framework includes
#include "FairMultiLinkedData_Interface.h"
#include "FairRootManager.h"

#include <fairlogger/Logger.h>

FairPrintFairLinks::FairPrintFairLinks()
    : FairTask("FairPrintFairLinks")
{}

InitStatus FairPrintFairLinks::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(error) << "-E- FairPrintFairLinks::Init: "
                   << "RootManager not instantiated!";
        return kFATAL;
    }

    TList* branchNames;
    if (fSelectedBranches.GetEntries() > 0) {
        branchNames = &fSelectedBranches;
    } else {
        branchNames = ioman->GetBranchNameList();
    }

    InitBranchList(branchNames);

    PrintBranchNameList(ioman->GetBranchNameList());

    return kSUCCESS;
}

void FairPrintFairLinks::InitBranchList(TList* branches)
{
    FairRootManager* ioman = FairRootManager::Instance();
    for (int i = 0; i < branches->GetEntries();
         ++i) {   // removes branches which do not contain objects derived from FairMultiLinkedData_Interface
        TObjString* branchName = (TObjString*)branches->At(i);
        if (branchName->String().Contains("_link"))
            continue;
        if (branchName->String().Contains("MCTrack"))
            continue;
        if (branchName->String().Contains("."))
            continue;
        if (branchName->String().Contains("GeoTracks"))
            continue;
        if (branchName->String().Contains("Header"))
            continue;
        if (branchName->String().Contains("Info"))
            continue;
        if (branchName->String().Contains("ID"))
            continue;
        if (branchName->String().Contains("PidAlgo"))
            continue;
        if (branchName->String().Contains("Riemann"))
            continue;

        LOG(debug) << "FairPrintFairLinks::Init() branches: " << branchName->String();
        if ((TClonesArray*)ioman->GetObject(branchName->String()) != 0) {
            fBranches[ioman->GetBranchId(branchName->String())] = (TClonesArray*)ioman->GetObject(branchName->String());
        } else {
            LOG(warning) << "-E- FairPrintFairLinks " << branchName->String().Data() << " is not a valid branch name!";
        }
    }
}

void FairPrintFairLinks::PrintBranchNameList(TList* branches)
{
    LOG(info) << "-I- FairPrintFairLinks Branches:";

    for (int i = 0; i < branches->GetEntries(); ++i) {
        TObjString* branchName = (TObjString*)branches->At(i);
        LOG(info) << i << " : " << branchName->String().Data() << "\n";
    }
    LOG(info) << "\n";
}

void FairPrintFairLinks::Exec(Option_t*)
{
    LOG(info) << "\n--------------------- Event " << FairRootManager::Instance()->GetEntryNr() << " at "
              << FairRootManager::Instance()->GetEventTime() << " ns ----------------------";
    for (std::map<Int_t, TClonesArray*>::iterator iter = fBranches.begin(); iter != fBranches.end(); ++iter) {
        LOG(info) << "\n"
                  << iter->first << " : " << FairRootManager::Instance()->GetBranchName(iter->first)
                  << " Entries: " << iter->second->GetEntriesFast();
        for (int i = 0; i < iter->second->GetEntriesFast(); ++i) {
            FairMultiLinkedData_Interface* myLinks = (FairMultiLinkedData_Interface*)iter->second->At(i);
            if (myLinks->GetPointerToLinks() != 0) {
                LOG(info) << i << " : " << *myLinks << "\n";
            }
        }
    }
}
