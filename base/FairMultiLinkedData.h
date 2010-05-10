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

class FairMultiLinkedData : public FairLinkedData {
public:
	FairMultiLinkedData();																					///< Default constructor
	virtual ~FairMultiLinkedData(){};
	FairMultiLinkedData(std::vector<FairLink> links):fLinks(links){}	 										///< Constructor
	FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links);
	virtual std::vector<FairLink>	GetLinks() const {return fLinks;} 					///< returns stored links as FairLinks
	virtual Int_t 					GetNLinks() const {	return fLinks.size();	} 			///< returns the number of stored links
	virtual FairLink				GetLink(Int_t pos) const {
		if (pos < (Int_t)fLinks.size())
			return fLinks.at(pos);
		else{
			std::cout << "-E- FairMultiLinkedData:GetLink(pos) pos " << pos << " outside range " << fLinks.size() << std::endl;
			return FairLink();
		}
	} 	///< returns the FairLink at the given position

	virtual FairMultiLinkedData		GetLinksWithType(Int_t type) const;   					///< Gives you a list of links which contain the given type

	virtual void SetLinks(FairMultiLinkedData links, Bool_t addup = kTRUE, Float_t mult = 1.0){
		fLinks.clear();
		AddLinks(links, addup, mult);
	}																											///< Sets the links as vector of FairLink

	virtual void SetLink(FairLink link, Float_t mult = 1.0); 																		///< Sets the Links with a single FairLink

	virtual void AddLink(FairLink link, Bool_t addup = kTRUE, Float_t mult = 1.0);													///< Adds a FairLink link at the end of fLinks. If multi is kTRUE a link is allowed more than once otherwise it is stored only once
	virtual void AddLinks(FairMultiLinkedData links, Bool_t addup = kTRUE, Float_t mult = 1.0){
		for (UInt_t i = 0; i < links.GetNLinks(); i++){
			AddLink(links.GetLink(i), addup, mult);
		}
	}																											///< Adds a List of FairLinks (FairMultiLinkedData) to fLinks

	virtual void SetAllWeights(Double_t weight){
		for (UInt_t i = 0; i < GetNLinks(); i++){
			fLinks[i].SetWeight(weight);
		}
	}

	virtual void AddAllWeights(Double_t weight){
		for (UInt_t i = 0; i < GetNLinks(); i++){
			fLinks[i].SetWeight(weight+fLinks[i].GetWeight());
		}
	}

	virtual void MultiplyAllWeights(Double_t weight){
		for (UInt_t i = 0; i < GetNLinks(); i++){
			fLinks[i].SetWeight(weight*fLinks[i].GetWeight());
		}
	}


	virtual Bool_t IsLinkInList(FairLink link)		{return IsLinkInList(link.GetType(), link.GetIndex());} 	///< Test if a given link is in fLinks
	virtual Bool_t IsLinkInList(Int_t type, Int_t index); 														///< Same as IsLinkInList(FairLink) just with type and index given separately
	virtual Int_t LinkPosInList(FairLink link)	{return LinkPosInList(link.GetType(), link.GetIndex());} 	///< returns position of link in fLinks. If it is not in the list -1 is returned
	virtual Int_t LinkPosInList(Int_t type, Int_t index);														///< Same as LinkPosInList(FairLink)

	virtual void DeleteLink(FairLink link)		{DeleteLink(link.GetType(), link.GetIndex());}				///< Deletes a link ouf of fLinks
	virtual void DeleteLink(Int_t type, Int_t index);															///< Deletes a link ouf of fLinks

	virtual void Reset(){fLinks.clear();}																		///< Clears fLinks

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
	std::vector<FairLink> fLinks;

	ClassDef(FairMultiLinkedData, 2);
};




inline void FairMultiLinkedData::SetLink(FairLink link, Float_t mult){
	fLinks.clear();
	Float_t weight = link.GetWeight() * mult;
	link.SetWeight(weight);
	AddLink(link);
}

inline void FairMultiLinkedData::AddLink(FairLink link, Bool_t addup, Float_t mult){

	Float_t weight = link.GetWeight() * mult;

	if (addup == kTRUE)
		if (IsLinkInList(link) == kTRUE){
			fLinks[LinkPosInList(link)].AddWeight(weight);
			return;
		}
	link.SetWeight(weight);
	fLinks.push_back(link);
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
