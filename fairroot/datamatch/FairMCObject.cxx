/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCObject.cpp
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#include "FairMCObject.h"

FairMCObject::FairMCObject()
    : TObject()
    , fStage(0)
    , fStageId()
{}

FairMCObject::~FairMCObject() {}

void FairMCObject::SetEntry(FairMCEntry entry)
{
    if (entry.GetPos() < 0) {
        std::cout << "-E- FairMCObject::SetEntry(FairMCEntry): pos " << entry.GetPos() << std::endl;
        return;
    }
    AdoptSize(entry.GetPos());
    fStage[entry.GetPos()] = entry;
}

void FairMCObject::SetEntry(std::vector<Int_t> type, std::vector<Int_t> link, int index)
{
    FairMCEntry myEntry;
    myEntry.SetPos(index);
    myEntry.SetPersistanceCheck(kFALSE);
    for (unsigned int i = 0; i < type.size(); i++) {
        myEntry.AddLink(FairLink(type[i], link[i]));
    }
    SetEntry(myEntry);
}

void FairMCObject::SetEntry(FairMultiLinkedData* data, int index)
{
    AdoptSize(index);
    fStage[index].SetLinks(data->GetLinks());
}

void FairMCObject::SetLink(FairLink link, int index)
{
    if (index < static_cast<int>(fStage.size())) {
        fStage[index].ResetLinks();
    }
    AddLink(link, index);
}

void FairMCObject::AddLink(FairLink link, int index)
{
    AdoptSize(index);
    fStage[index].AddLink(link);
}

void FairMCObject::AdoptSize(int index)
{
    while (static_cast<int>(fStage.size()) < index + 1) {
        FairMCEntry myVec;
        myVec.SetPos(fStage.size());
        myVec.SetSource(GetStageId());
        myVec.SetPersistanceCheck(kFALSE);
        fStage.push_back(myVec);
    }
}

FairMultiLinkedData FairMCObject::PosInList(FairLink link)
{
    FairMultiLinkedData result;
    result.SetPersistanceCheck(kFALSE);
    for (unsigned int i = 0; i < fStage.size(); i++) {
        if (fStage[i].IsLinkInList(link.GetType(), link.GetIndex())) {
            result.AddLink(FairLink(GetStageId(), i));
        }
    }
    return result;
}

void FairMCObject::RemoveType(Int_t type)
{
    for (unsigned int i = 0; i < fStage.size(); i++) {
        fStage[i].RemoveType(type);
    }
}
