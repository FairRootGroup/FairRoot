/********************************************************************************
 * Copyright (C) 2022-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairFileSourceBase.h"

#include "FairRootManager.h"

#include <TObjString.h>
#include <fairlogger/Logger.h>
#include <set>

FairFileSourceBase::~FairFileSourceBase()
{
    FairRootManager::Instance()->SetListOfFolders(nullptr);
}

Bool_t FairFileSourceBase::CompareBranchList(TFile* fileHandle, TString inputLevel)
{
    // fill a set with the original branch structure
    // This allows to use functions find and erase
    std::set<TString> branches;
    for (auto li : (fCheckInputBranches[inputLevel])) {
        branches.insert(li);
    }

    // To do so we have to loop over the branches in the file and to compare
    // the branches in the file with the information stored in
    // fCheckInputBranches["InputChain"]. If both lists are equal everything
    // is okay

    // Get The list of branches from the input file one by one and compare
    // it to the reference list of branches which is defined for this tree.
    // If a branch with the same name is found, this branch is removed from
    // the list. If in the end no branch is left in the list everything is
    // fine.
    auto list = fileHandle->Get<TList>("BranchList");
    if (list) {
        for (Int_t i = 0; i < list->GetEntries(); i++) {
            auto Obj = dynamic_cast<TObjString*>(list->At(i));
            auto iter1 = branches.find(Obj->GetString());
            if (iter1 != branches.end()) {
                branches.erase(iter1);
            } else {
                // Not found is an error because branch structure is
                // different. It is impossible to add to tree with a
                // different branch structure
                return kFALSE;
            }
        }
    }
    // If the size of branches is !=0 after removing all branches also in the
    // reference list, this is also a sign that both branch list are not the
    // same
    if (!branches.empty()) {
        LOG(info) << "Compare Branch List will return kFALSE. The list has " << branches.size() << " branches:";
        for (auto const& branchName : branches) {
            LOG(info) << "  -> " << branchName;
        }
        return kFALSE;
    }

    return kTRUE;
}

bool FairFileSourceBase::ActivateObjectAnyImpl(TTree* source,
                                               void** obj,
                                               const std::type_info& info,
                                               const char* brname)
{
    if (!source) {
        return false;
    }
    // we check if the types match at all
    auto br = source->GetBranch(brname);
    if (!br) {
        // branch not found in source
        return false;
    }

    // look up the TClass and resulting typeid stored in this branch
    auto cl = TClass::GetClass(br->GetClassName());
    if (!cl) {
        // class not found
        return false;
    }

    auto storedtype = cl->GetTypeInfo();

    // check consistency of types
    if (info != *storedtype) {
        LOG(info) << "Trying to read from branch " << brname << " with wrong type " << info.name()
                  << " (expected: " << storedtype->name() << ")\n";
        return false;
    }
    source->SetBranchStatus(brname, true);
    // force to use the (void*) interface which is non-checking
    source->SetBranchAddress(brname, (void*)obj);
    return true;
}
