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
  fType(0),
  fIndex(0),
  fWeight(1.0)
  
{}

FairLink::FairLink(Int_t type, Int_t index, Float_t weight)
:TObject(),
 fType(0),
 fIndex(index),
 fWeight(weight)

 {}


FairLink::FairLink(TString branchName, Int_t index, Float_t weight)
:TObject(),
fType(0),
fIndex(index),
fWeight(weight)
{
	FairRootManager* ioman = FairRootManager::Instance();
	if (0==ioman)
		std::cout << "-E- FairLink: No iomanager" << std::endl;
	SetLink(ioman->GetBranchId(branchName), index, weight);
}

FairLink::~FairLink() {
	// TODO Auto-generated destructor stub
}
