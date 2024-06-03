/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------

#include "FairFileHeader.h"

#include "FairFileInfo.h"   // for FairFileInfo

#include <TCollection.h>   // for TRangeDynCast
#include <TList.h>
#include <TObjString.h>

FairFileHeader::FairFileHeader()
    : TNamed()
    , fRunId(0)
    , fTaskList(new TList())
    , fFileList(new TList())
{}

void FairFileHeader::AddTaskClassName(TString taskname) { fTaskList->AddLast(new TObjString(taskname)); }

void FairFileHeader::AddInputFile(TFile* f, UInt_t id, UInt_t ChId)
{
    fFileList->AddLast(new FairFileInfo(f, id, ChId));
}

FairFileInfo* FairFileHeader::GetFileInfo(UInt_t id, UInt_t ChId)
{
    for (auto info : TRangeDynCast<FairFileInfo>(fFileList)) {
        if (info && info->GetIdentifier() == id && info->GetOrderInChain() == ChId) {
            return info;
        }
    }
    return 0;
}

FairFileHeader::~FairFileHeader() {}
