/*
 * FairMCEntry.cpp
 *
 *  Created on: Dec 22, 2009
 *      Author: stockman
 */

#include "FairMCEntry.h"

ClassImp(FairMCEntry);

FairMCEntry::FairMCEntry()
  : FairMultiLinkedData(),
    fPos(-1),
    fSource(-1)
{
  SetPersistanceCheck(kFALSE);
}

FairMCEntry::~FairMCEntry()
{
}

void FairMCEntry::RemoveType(Int_t type)
{
  std::set<FairLink>::iterator endIter = fLinks.end();
  std::set<FairLink>::iterator it = fLinks.begin();
  for (; it!=fLinks.end();) {
    if (it->GetType() == type) {
      fLinks.erase(it);
      it = fLinks.begin();
    } else {
      it++;
    }
  }
}

