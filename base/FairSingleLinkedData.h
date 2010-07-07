/**
 * FairSingleLinkedData.h
 *
 * \date Dec 7, 2009
 * \author T.Stockmanns <T.Stockmanns@fz-juelich.de>
 */

#ifndef FAIRSINGLELINKEDDATA_H_
#define FAIRSINGLELINKEDDATA_H_

#include "FairLinkedData.h"
#include "FairLink.h"
#include <iostream>

class FairSingleLinkedData : public FairLinkedData{
public:
	FairSingleLinkedData();
	virtual ~FairSingleLinkedData(){};

	virtual std::set<FairLink> GetLinks() const;

	virtual Int_t GetNLinks() const {return 1;}
	virtual FairLink GetLink(Int_t pos = 0) const {return fLink;}

	virtual void SetLink(FairLink link, Float_t mult = 1.0);
	virtual void AddLink(FairLink link, bool addup = true, Float_t mult = 1.0);

	virtual bool IsLinkInList(Int_t type, Int_t index);
	virtual Int_t LinkPosInList(Int_t type, Int_t index);

	virtual void DeleteLink(Int_t type, Int_t index);

	virtual void Print(){std::cout << *this;}

	friend std::ostream& operator<< (std::ostream& out, const FairSingleLinkedData& data){
		data.GetLink().Print(out);
		out << std::endl;
		return out;
	}


private:
	FairLink fLink;	///< single link
	//Int_t fLinksLink;	///< pos in TClonesArray
	ClassDef(FairSingleLinkedData, 0);
};

inline std::set<FairLink> FairSingleLinkedData::GetLinks() const{
	std::set<FairLink> result;
	if (GetNLinks() > 0)
		result.insert(GetLink());
	return result;
}


inline void FairSingleLinkedData::SetLink(FairLink link, Float_t mult){
	AddLink(link);
}

inline void FairSingleLinkedData::AddLink(FairLink link, bool addup, Float_t mult){
	Float_t weight = link.GetWeight() * mult;
	link.SetWeight(weight);
	fLink = link;
}

#endif /* PNDSINGLELINKEDDATA_H_ */
