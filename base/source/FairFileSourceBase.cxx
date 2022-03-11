/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairFileSourceBase.h"

#include <TObjString.h>
#include <algorithm>   // for std::for_each
#include <set>

using std::set;

ClassImp(FairFileSourceBase);

FairFileSourceBase::~FairFileSourceBase() {}

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
    set<TString>::iterator iter1;
    TList* list = dynamic_cast<TList*>(fileHandle->Get("BranchList"));
    if (list) {
        TObjString* Obj = 0;
        for (Int_t i = 0; i < list->GetEntries(); i++) {
            Obj = dynamic_cast<TObjString*>(list->At(i));
            iter1 = branches.find(Obj->GetString().Data());
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
    if (branches.size() != 0) {
        LOG(info) << "Compare Branch List will return kFALSE. The list has " << branches.size() << " branches:";
        for (auto branchName : branches)
            LOG(info) << "  -> " << branchName;
        return kFALSE;
    }

    return kTRUE;
}
