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
   fType(0),
   fIndex(0),
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
   fEntry(-1)
{
  //FairRootManager* ioman = FairRootManager::Instance();
  //if (0==ioman) std::cout << "-E- FairLink: No iomanager" << std::endl;
  SetLink(FairRootManager::Instance()->GetBranchId(branchName), index, weight);
}


FairLink::FairLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight)
{
  SetLink(file, entry, type, index, weight);
}

FairLink::FairLink(Int_t file, Int_t entry, TString branchName, Int_t index, Float_t weight)
  :TObject()
{
  //FairRootManager* ioman = FairRootManager::Instance();
  //if (0==ioman) std::cout << "-E- FairLink: No iomanager" << std::endl;
  SetLink(file, entry, FairRootManager::Instance()->GetBranchId(branchName), index, weight);
}


FairLink::~FairLink()
{
  // TODO Auto-generated destructor stub
}
