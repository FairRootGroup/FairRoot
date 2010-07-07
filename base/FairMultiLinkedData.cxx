/*
 * FairMultiLinkedData.cxx
 *
 *  Created on: Dec 7, 2009
 *      Author: stockman
 */

#include "FairMultiLinkedData.h"
#include "TClonesArray.h"

#include<algorithm>

ClassImp(FairMultiLinkedData);

FairMultiLinkedData::FairMultiLinkedData()
:FairLinkedData(), fPersistanceCheck(kTRUE), fVerbose(2)
{
	// TODO Auto-generated constructor stub

}

FairMultiLinkedData::FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links, Bool_t persistanceCheck, Bool_t bypass, Float_t mult)
:FairLinkedData(), fPersistanceCheck(persistanceCheck), fVerbose(2)
{
	SimpleAddLinks(dataType, links, bypass, mult);
}


Bool_t FairMultiLinkedData::IsLinkInList(Int_t type, Int_t index)
{
	if (LinkPosInList(type, index) > -1)
		return kTRUE;
	return kFALSE;
}

Int_t FairMultiLinkedData::LinkPosInList(Int_t type, Int_t index){
	std::set<FairLink>::iterator it = std::find(fLinks.begin(), fLinks.end(), FairLink(type, index));
	if (it != fLinks.end())
		return std::distance(fLinks.begin(), it);
	return -1;
}

void FairMultiLinkedData::DeleteLink(Int_t type, Int_t index){
/*	Int_t pos = LinkPosInList(type, index);
	if (pos < 0) return;
	else{
		fLinks.erase(fLinks.begin()+pos);
	}*/
}

FairMultiLinkedData FairMultiLinkedData::GetLinksWithType(Int_t type) const
{
	FairMultiLinkedData result;
	for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++)
	{
		if (it->GetType() == type){
			FairLink myLink = *it;
			result.InsertLink(myLink);
		}
	}
	return result;
}

TObject* FairMultiLinkedData::GetData(FairLink& myLink)
{
	FairRootManager* ioman = FairRootManager::Instance();
	TString branchName = ioman->GetBranchName(myLink.GetType());
	if (ioman->CheckBranch(branchName) > 0){
		TClonesArray* myArray = (TClonesArray*)ioman->GetObject(branchName);
		if (myArray != 0){
			if (myArray->GetEntries() > myLink.GetIndex()){
				return myArray->At(myLink.GetIndex());
			}
			else std::cout << "-E- FairMultiLinkedData::GetData index out of bounds" << std::endl;
		}
		else std::cout << "-E- FairMultiLinkedData::GetData no TClonesArray" << std::endl;
	}
	else std::cout << "-E- FairMultiLinkedData::GetData Branch does not exist in Memory" << std::endl;

	return 0;
}
