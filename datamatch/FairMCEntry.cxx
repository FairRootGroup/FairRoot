/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCEntry.cpp
 *
 *  Created on: Dec 22, 2009
 *      Author: stockman
 */

#include "FairMCEntry.h"

ClassImp(FairMCEntry);

FairMCEntry::FairMCEntry()
    : FairMultiLinkedData()
    , fSource(-1)
    , fPos(-1)
{
    SetPersistanceCheck(kFALSE);
}

FairMCEntry::~FairMCEntry() {}

void FairMCEntry::RemoveType(Int_t type)
{
    // std::set<FairLink>::iterator endIter = fLinks.end();
    std::set<FairLink>::iterator it = fLinks.begin();
    for (; it != fLinks.end();) {
        if (it->GetType() == type) {
            fLinks.erase(it);
            it = fLinks.begin();
        } else {
            ++it;
        }
    }
}
