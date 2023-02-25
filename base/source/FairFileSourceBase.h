/********************************************************************************
 * Copyright (C) 2022-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef __FAIRROOT__FairFileSourceBase__
#define __FAIRROOT__FairFileSourceBase__

#include "FairSource.h"

#include <TFile.h>
#include <TTree.h>
#include <list>
#include <map>

/**
 * \brief Internal base class for FairFileSource and FairMixedSource
 */
class FairFileSourceBase : public FairSource
{
  public:
    ~FairFileSourceBase() override = default;
    void Reset() override {}
    Source_Type GetSourceType() override { return kFILE; }
    void SetParUnpackers() override {}
    Bool_t InitUnpackers() override { return kTRUE; }
    Bool_t ReInitUnpackers() override { return kTRUE; }

    Bool_t CompareBranchList(TFile* fileHandle, TString inputLevel);

  protected:
    FairFileSourceBase()
        : FairSource(){};

    std::map<TString, std::list<TString>> fCheckInputBranches{};   //!

    static bool ActivateObjectAnyImpl(TTree* source, void** obj, const std::type_info& info, const char* brname);

    ClassDefOverride(FairFileSourceBase, 0);
};

#endif
