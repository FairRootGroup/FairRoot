/**
 * FairMultiLinkedData.h
 *
 * \date Dec 7, 2009
 * \author T.Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef FAIRMULTILINKEDDATA_H_
#define FAIRMULTILINKEDDATA_H_

#include "FairLinkedData.h"
#include "FairLink.h"
#include "FairRootManager.h"
#include "TClonesArray.h"


class FairMultiLinkedData : public FairLinkedData {
public:
	FairMultiLinkedData();																					///< Default constructor
	virtual ~FairMultiLinkedData(){};
	FairMultiLinkedData(std::set<FairLink> links, Bool_t persistanceCheck = kTRUE):fLinks(links), fPersistanceCheck(persistanceCheck), fVerbose(2){}
	FairMultiLinkedData(TString dataType, std::vector<Int_t> links,Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0):
		fPersistanceCheck(persistanceCheck)
	{
		FairRootManager* ioman = FairRootManager::Instance();
		SimpleAddLinks(ioman->GetBranchId(dataType), links, bypass, mult);
	//	FairMultiLinkedData(ioman->GetBranchId(dataType), links, persistanceCheck, bypass, addup, mult);
	}
		///< Constructor
	FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links, Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0);
	virtual std::set<FairLink>	GetLinks() const {return fLinks;} 					///< returns stored links as FairLinks
	virtual Int_t 					GetNLinks() const {	return fLinks.size();	} 			///< returns the number of stored links
	virtual FairLink				GetLink(Int_t pos) const {
		if (pos < (Int_t)fLinks.size()){
			//return fLinks.at(pos);
			std::set<FairLink>::iterator it = fLinks.begin();
			for (int i = 0; i < pos; i++)it++;
			return *it;
		}
		else{
			std::cout << "-E- FairMultiLinkedData:GetLink(pos) pos " << pos << " outside range " << fLinks.size() << std::endl;
			return FairLink();
		}
	} 	///< returns the FairLink at the given position

	virtual FairMultiLinkedData		GetLinksWithType(Int_t type) const;   					///< Gives you a list of links which contain the given type

	virtual void SetLinks(FairMultiLinkedData links, Float_t mult = 1.0){
		fLinks = links.GetLinks();
		MultiplyAllWeights(mult);
	}																											///< Sets the links as vector of FairLink

	virtual void SetLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0); 																		///< Sets the Links with a single FairLink

	virtual void AddLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0);													///< Adds a FairLink link at the end of fLinks. If multi is kTRUE a link is allowed more than once otherwise it is stored only once

	virtual void InsertLink(FairLink link){
		std::set<FairLink>::iterator it = fLinks.find(link);
		if (it != fLinks.end()){
			FairLink myTempLink = *it;
			myTempLink.AddWeight(link.GetWeight());
			fLinks.erase(it);
			fLinks.insert(myTempLink);
		}
		else{
			fLinks.insert(link);
		}
		return;
	}

	virtual void AddLinks(FairMultiLinkedData links, Float_t mult = 1.0){
		std::set<FairLink> myLinks = links.GetLinks();
		for (std::set<FairLink>::iterator it = myLinks.begin(); it != myLinks.end(); it++){
			FairLink myLink = *it;
			myLink.SetWeight(myLink.GetWeight()*mult);
			AddLink(myLink);
		}
	}																											///< Adds a List of FairLinks (FairMultiLinkedData) to fLinks

	virtual void SetPersistanceCheck(Bool_t check){fPersistanceCheck = check;}
	//virtual void SetBypass(Bool_t bypass){fBypass = bypass;}
	virtual void SetVerboseLevel(Int_t level){fVerbose = level;}

	virtual void SetAllWeights(Double_t weight){
		std::set<FairLink> tempLinks;
		for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++){
			FairLink tempLink = *it;
			tempLink.SetWeight(weight);
			tempLinks.insert(tempLink);
		}
		fLinks = tempLinks;
	}

	virtual void AddAllWeights(Double_t weight){
		std::set<FairLink> tempLinks;
		for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++){
			FairLink tempLink = *it;
			tempLink.SetWeight(weight + tempLink.GetWeight());
			tempLinks.insert(tempLink);
		}
		fLinks = tempLinks;
	}

	virtual void MultiplyAllWeights(Double_t weight){
		std::set<FairLink> tempLinks;
		for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++){
			FairLink tempLink = *it;
			tempLink.SetWeight(weight * tempLink.GetWeight());
			tempLinks.insert(tempLink);
		}
		fLinks = tempLinks;
	}


	virtual Bool_t IsLinkInList(FairLink link)		{return IsLinkInList(link.GetType(), link.GetIndex());} 	///< Test if a given link is in fLinks
	virtual Bool_t IsLinkInList(Int_t type, Int_t index); 														///< Same as IsLinkInList(FairLink) just with type and index given separately
	virtual Int_t LinkPosInList(FairLink link)	{return LinkPosInList(link.GetType(), link.GetIndex());} 	///< returns position of link in fLinks. If it is not in the list -1 is returned
	virtual Int_t LinkPosInList(Int_t type, Int_t index);														///< Same as LinkPosInList(FairLink)

	virtual void DeleteLink(FairLink link)		{DeleteLink(link.GetType(), link.GetIndex());}				///< Deletes a link ouf of fLinks
	virtual void DeleteLink(Int_t type, Int_t index);															///< Deletes a link ouf of fLinks

	virtual void Reset(){fLinks.clear();}																		///< Clears fLinks


	TObject* GetData(FairLink& myLink);																			///< Get the TObject the Link is pointing to

	virtual void Print(std::ostream& out = std::cout){
		out << *this;
	}																											///< Output

	friend std::ostream& operator<< (std::ostream& out, const FairMultiLinkedData& data){
		for (Int_t i = 0; i < data.GetNLinks(); i++){
			data.GetLink(i).Print(out);
			out << " ";
		}
		out << std::endl;
		return out;
	}																											///< Output

private:
	std::set<FairLink> fLinks;
	Bool_t fPersistanceCheck;
	Bool_t fVerbose;

	virtual void SimpleAddLinks(Int_t dataType, std::vector<Int_t> links, Bool_t bypass, Float_t mult){
		for (UInt_t i = 0; i < links.size(); i++){
				AddLink(FairLink(dataType, links[i]), bypass, mult);
			}
	}



	ClassDef(FairMultiLinkedData, 2);
};




inline void FairMultiLinkedData::SetLink(FairLink link, Bool_t bypass, Float_t mult){
	fLinks.clear();
	Float_t weight = link.GetWeight() * mult;
	link.SetWeight(weight);
	AddLink(link, bypass);
}

inline void FairMultiLinkedData::AddLink(FairLink link, Bool_t bypass, Float_t mult){

	SetVerboseLevel(2);
	Float_t weight = link.GetWeight() * mult;
	link.SetWeight(weight);
	//std::cout << fVerbose << std::endl;

	FairRootManager* ioman = FairRootManager::Instance();

	if (fVerbose > 1)
		std::cout << "Add FairLink: " << link << std::endl;

	if (fPersistanceCheck == kFALSE || ioman->CheckBranch(ioman->GetBranchName(link.GetType())) == 0){
		InsertLink(link);
		return;
	}

	if (bypass == kFALSE){
		if (fVerbose > 1)
			std::cout << "BranchName " << ioman->GetBranchName(link.GetType()) << " checkStatus: " <<  ioman->CheckBranch(ioman->GetBranchName(link.GetType())) << std::endl;
		if (link.GetType() > ioman->GetBranchId("MCTrack") && ioman->CheckBranch(ioman->GetBranchName(link.GetType())) != 1){
			if (fVerbose > 1)
				std::cout << "BYPASS!" << std::endl;
			bypass = kTRUE;
		}
	}

	if (bypass == kTRUE){
		//FairRootManager* ioman = FairRootManager::Instance();
		if (link.GetType() > ioman->GetBranchId("MCTrack")){
			TClonesArray* array = (TClonesArray*)ioman->GetObject(ioman->GetBranchName(link.GetType()));
			if (fVerbose > 1)
				std::cout << "Entries in " << ioman->GetBranchName(link.GetType()) << " Array: " << array->GetEntries() << std::endl;
			FairMultiLinkedData* links = (FairMultiLinkedData*)array->At(link.GetIndex());
			if (fVerbose > 1){
				std::cout << "FairMultiLinkedData has " << links->GetNLinks() << " Entries: " << std::endl;
				std::cout << *links << std::endl;
			}
			AddLinks(*links, mult);
			return;
		}
		else {
			InsertLink(link);
		}
	}
	else {
		InsertLink(link);
	}

}

/**\fn virtual void FairMultiLinkedData::SetLinks(Int_t type, std::vector<Int_t> links)
 * \param type as Int_t gives one type of source data for all indices
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */

/**\fn virtual void FairMultiLinkedData::SetLinks(std::vector<Int_t> type, std::vector<Int_t> links)
 * \param type as vector<Int_t> gives the type of source data (TClonesArray)
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */

#endif /* FAIRMULTILinkedData_H_ */
