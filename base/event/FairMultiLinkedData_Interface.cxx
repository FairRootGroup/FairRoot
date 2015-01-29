/*
 * FairMultiLinkedData_Interface.cxx
 *
 *  Created on: Dec 7, 2009
 *      Author: stockman
 */

#include "FairMultiLinkedData_Interface.h"

#include "FairRootManager.h"            // for FairRootManager

#include "TClonesArray.h"               // for TClonesArray

#include <algorithm>                    // for find
#include <iterator>                     // for distance

ClassImp(FairMultiLinkedData_Interface);

FairMultiLinkedData_Interface::FairMultiLinkedData_Interface()
  :TObject(),
   fVerbose(0),
   fRefToLinks(0),
   fLinkBranchName("FairLinkBranch")
{
}



FairMultiLinkedData_Interface::FairMultiLinkedData_Interface(FairMultiLinkedData& links, Bool_t persistanceCheck)
  :TObject(),
   fVerbose(0),
   fRefToLinks(),
   fLinkBranchName("FairLinkBranch")
{
	CreateFairMultiLinkedData();
	SetLinks(links);
}

FairMultiLinkedData_Interface::FairMultiLinkedData_Interface(TString dataType, std::vector<Int_t> links, Int_t fileId, Int_t evtId, Bool_t persistanceCheck, Bool_t bypass, Float_t mult)
  :TObject(),
   fVerbose(0),
   fRefToLinks(),
   fLinkBranchName("FairLinkBranch")
{

	CreateFairMultiLinkedData();
	FairMultiLinkedData data(dataType, links, fileId, evtId, persistanceCheck, bypass, mult);
	SetLinks(data);
}

FairMultiLinkedData_Interface::FairMultiLinkedData_Interface( Int_t dataType, std::vector<Int_t> links, Int_t fileId, Int_t evtId, Bool_t persistanceCheck, Bool_t bypass, Float_t mult)
  :TObject(),
   fVerbose(0),
   fRefToLinks(),
   fLinkBranchName("FairLinkBranch")
{
	CreateFairMultiLinkedData();
	FairMultiLinkedData data(dataType, links, fileId, evtId, persistanceCheck, bypass, mult);
	SetLinks(data);
}

FairMultiLinkedData* FairMultiLinkedData_Interface::CreateFairMultiLinkedData()
{
	if (FairRootManager::Instance()->GetUseFairLinks()){
		fLinkBranchName = FairRootManager::Instance()->GetFairLinksBranchName();
		if (fLinkBranchName != "" && !fRefToLinks.IsValid()){
			FairRootManager* ioman = FairRootManager::Instance();
			TClonesArray* container = ioman->GetTClonesArray(fLinkBranchName);
			fRefToLinks = new ((*container)[container->GetEntriesFast()]) FairMultiLinkedData();
		}
		return (FairMultiLinkedData*)fRefToLinks.GetObject();
	} else {
		fRefToLinks = 0;
		return 0;
	}
}

std::set<FairLink>    FairMultiLinkedData_Interface::GetLinks() const
{
	if (GetPointerToData() != 0){
		return GetPointerToData()->GetLinks();
	} else {
		std::set<FairLink> emptySet;
		return emptySet;
	}
}

Int_t           FairMultiLinkedData_Interface::GetNLinks() const
{
	if (GetPointerToData() != 0){
		return GetPointerToData()->GetNLinks();
	} else {
		return 0;
	}
}

FairLink        FairMultiLinkedData_Interface::GetLink(Int_t pos) const
{
	if (GetPointerToData() != 0){
		return GetPointerToData()->GetLink(pos);
	} else {
		FairLink emptyLink;
		return emptyLink;
	}
}

FairMultiLinkedData   FairMultiLinkedData_Interface::GetLinksWithType(Int_t type) const
{
	if (GetPointerToData() != 0){
		return GetPointerToData()->GetLinksWithType(type);
	} else {
		FairMultiLinkedData emptyLinks;
		return emptyLinks;
	}
}

void FairMultiLinkedData_Interface::SetLinks(FairMultiLinkedData links)
{
	CreateFairMultiLinkedData();
	if (GetPointerToData() != 0){
		GetPointerToData()->SetLinks(links);
	}
}

void FairMultiLinkedData_Interface::SetLink(FairLink link)
{
	CreateFairMultiLinkedData();
	if (GetPointerToData() != 0){
		GetPointerToData()->SetLink(link);
	}
}

void FairMultiLinkedData_Interface::AddLinks(FairMultiLinkedData links, Float_t mult)
{
	CreateFairMultiLinkedData();
	if (GetPointerToData() != 0){
		GetPointerToData()->AddLinks(links, mult);
	}
}

void FairMultiLinkedData_Interface::AddLink(FairLink link)
{
	CreateFairMultiLinkedData();
	if (GetPointerToData() != 0){
		GetPointerToData()->AddLink(link);
	}

}

void FairMultiLinkedData_Interface::ResetLinks()
{
	if (GetPointerToData() != 0){
		GetPointerToData()->ResetLinks();
	}
}
