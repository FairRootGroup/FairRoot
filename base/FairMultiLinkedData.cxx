/*
 * FairMultiLinkedData.cxx
 *
 *  Created on: Dec 7, 2009
 *      Author: stockman
 */

#include "FairMultiLinkedData.h"

ClassImp(FairMultiLinkedData);

FairMultiLinkedData::FairMultiLinkedData()
:FairLinkedData()
{
	// TODO Auto-generated constructor stub

}

FairMultiLinkedData::FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links)
:FairLinkedData()
{
	for (UInt_t i = 0; i < links.size(); i++){
		AddLink(FairLink(dataType, links[i], 1.0));
	}
}


Bool_t FairMultiLinkedData::IsLinkInList(Int_t type, Int_t index)
{
	if (LinkPosInList(type, index) > -1)
		return kFALSE;
	return kFALSE;
}

Int_t FairMultiLinkedData::LinkPosInList(Int_t type, Int_t index){
	for (UInt_t i = 0; i < fLinks.size(); i++){
		if (index == fLinks[i].GetIndex() && type == fLinks[i].GetType())
				return i;
	}
	return -1;
}

void FairMultiLinkedData::DeleteLink(Int_t type, Int_t index){
	Int_t pos = LinkPosInList(type, index);
	if (pos < 0) return;
	else{
		fLinks.erase(fLinks.begin()+pos);
	}
}

FairMultiLinkedData FairMultiLinkedData::GetLinksWithType(Int_t type) const
{
	FairMultiLinkedData result;
	for (Int_t i = 0; i < GetNLinks(); i++)
	{
		if (GetLink(i).GetType() == type)
			result.AddLink(GetLink(i), kFALSE);
	}
	return result;
}
