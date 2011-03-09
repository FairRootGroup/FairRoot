/*
 * FairSingleLinkedData.cxx
 *
 *  Created on: Dec 7, 2009
 *      Author: stockman
 */

#include "FairSingleLinkedData.h"

ClassImp(FairSingleLinkedData);

FairSingleLinkedData::FairSingleLinkedData()
  :FairLinkedData(),
   fLink(-1, -1)
{
  // TODO Auto-generated constructor stub

}

bool FairSingleLinkedData::IsLinkInList(Int_t type, Int_t index)
{
  if (LinkPosInList(type, index) == 0) {
    return true;
  }
  return false;
}
Int_t FairSingleLinkedData::LinkPosInList(Int_t type, Int_t index)
{
  if (index == fLink.GetIndex() && type == fLink.GetType()) {
    return 0;
  } else { return -1; }
}

void FairSingleLinkedData::DeleteLink(Int_t type, Int_t index)
{
  fLink.SetLink(-1, -1);
}
