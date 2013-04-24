/*
 * FairLink.cpp
 *
 *  Created on: Dec 23, 2009
 *      Author: stockman
 */

#include "FairLink.h"
#include "FairRootManager.h"

ClassImp(FairLink);

FairLink::FairLink()
  :TObject(),
   fFile(-1),
   fEntry(-1),
   fType(-1),
   fIndex(-1),
   fWeight(1.0)
{
}

FairLink::FairLink(Int_t type, Int_t index, Float_t weight)
  :TObject(),
   fFile(-1),
   fEntry(-1),
   fType(type),
   fIndex(index),
   fWeight(weight)
{
}


FairLink::FairLink(TString branchName, Int_t index, Float_t weight)
  :TObject(),
   fFile(-1),
   fEntry(-1),
   fType(FairRootManager::Instance()->GetBranchId(branchName)),
   fIndex(index),
   fWeight(weight)
{
}


FairLink::FairLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight)
  :TObject(),
   fFile(file),
   fEntry(entry),
   fType(type),
   fIndex(index),
   fWeight(weight)
{
}

FairLink::FairLink(Int_t file, Int_t entry, TString branchName, Int_t index, Float_t weight)
  :TObject(),
   fFile(file),
   fEntry(entry),
   fType(FairRootManager::Instance()->GetBranchId(branchName)),
   fIndex(index),
   fWeight(weight)
{
}

void FairLink::Print(std::ostream& out) const
{
  out << "(" << GetFile() << "/" << GetEntry() << "/";
  out << GetType() << "/" << GetIndex() << "/" << GetWeight() << ")";
}

FairLink::~FairLink()
{
  // TODO Auto-generated destructor stub
}
