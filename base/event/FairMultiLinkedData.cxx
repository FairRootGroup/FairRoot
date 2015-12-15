/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMultiLinkedData.cxx
 *
 *  Created on: Dec 7, 2009
 *      Author: stockman
 */

#include "FairMultiLinkedData.h"
#include "FairMultiLinkedData_Interface.h"

#include "FairRootManager.h"            // for FairRootManager
#include "FairLinkManager.h"            // for FairLinkManager

#include "TClonesArray.h"               // for TClonesArray

#include <algorithm>                    // for find
#include <iterator>                     // for distance

ClassImp(FairMultiLinkedData);

FairMultiLinkedData::FairMultiLinkedData()
  :TObject(),
   fLinks(),
   fEntryNr(),
   fPersistanceCheck(kTRUE),
   fInsertHistory(kTRUE),
   fVerbose(0),
   fDefaultType(0)

{
}

FairMultiLinkedData::FairMultiLinkedData(std::set<FairLink> links, Bool_t persistanceCheck)
  :TObject(),
   fLinks(links),
   fEntryNr(),
   fPersistanceCheck(persistanceCheck),
   fInsertHistory(kTRUE),
   fVerbose(0),
   fDefaultType(0)
{
}

FairMultiLinkedData::FairMultiLinkedData(TString dataType, std::vector<Int_t> links, Int_t fileId, Int_t evtId, Bool_t persistanceCheck, Bool_t bypass, Float_t mult)
  :TObject(),
   fLinks(),
   fEntryNr(),
   fPersistanceCheck(persistanceCheck),
   fInsertHistory(kTRUE),
   fVerbose(0),
   fDefaultType(0)

{
  SimpleAddLinks(fileId, evtId, FairRootManager::Instance()->GetBranchId(dataType), links, bypass, mult);
//  FairMultiLinkedData(ioman->GetBranchId(dataType), links, persistanceCheck, bypass, addup, mult);
}

FairMultiLinkedData::FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links, Int_t fileId, Int_t evtId, Bool_t persistanceCheck, Bool_t bypass, Float_t mult)
  :TObject(),
   fLinks(),
   fEntryNr(),
   fPersistanceCheck(persistanceCheck),
   fInsertHistory(kTRUE),
   fVerbose(0),
   fDefaultType(0)

{
  SimpleAddLinks(fileId, evtId, dataType, links, bypass, mult);
}

FairLink FairMultiLinkedData::GetLink(Int_t pos) const
{
  if (pos < (Int_t)fLinks.size()) {
    std::set<FairLink>::iterator it = fLinks.begin();
    for (int i = 0; i < pos; i++) { it++; }
    return *it;
  } else {
    std::cout << "-E- FairMultiLinkedData:GetLink(pos) pos " << pos << " outside range " << fLinks.size() << std::endl;
    return FairLink();
  }
}

void FairMultiLinkedData::SetLinks(FairMultiLinkedData links, Float_t mult)
{
  fLinks.clear();
  AddLinks(links, mult);
}


void FairMultiLinkedData::SetLink(FairLink link, Bool_t bypass, Float_t mult)
{
  fLinks.clear();
  Float_t weight = link.GetWeight() * mult;
  link.SetWeight(weight);
  AddLink(link, bypass);
}


void FairMultiLinkedData::AddLinks(FairMultiLinkedData links, Float_t mult)
{
  std::set<FairLink> myLinks = links.GetLinks();
  for (std::set<FairLink>::iterator it = myLinks.begin(); it != myLinks.end(); it++) {
    FairLink myLink = *it;
    myLink.SetWeight(myLink.GetWeight()*mult);
    AddLink(myLink);
  }
}

void FairMultiLinkedData::AddLink(FairLink link, Bool_t bypass, Float_t mult)
{

  Float_t weight = link.GetWeight() * mult;
  link.SetWeight(weight);
  //std::cout << fVerbose << std::endl;

  FairRootManager* ioman = FairRootManager::Instance();

  if (ioman == 0) {
    std::cout << "-W- no IOManager present!" << std::endl;
    fPersistanceCheck = kFALSE;
  }
  if (fVerbose > 1) {
    std::cout << "Add FairLink: " << link << std::endl;
  }

  if (fPersistanceCheck == kFALSE ||
      link.GetIndex() < 0 ||
      ioman->CheckBranch(ioman->GetBranchName(link.GetType())) == 0) {
    InsertLink(link);
    if (fInsertHistory == kTRUE)
    	InsertHistory(link);
    return;
  }

  if (bypass == kFALSE) {
    if (fVerbose > 1) {
      std::cout << "BranchName " << ioman->GetBranchName(link.GetType()) << " checkStatus: " <<  ioman->CheckBranch(ioman->GetBranchName(link.GetType())) << std::endl;
    }
    if (link.GetType() > ioman->GetBranchId("MCTrack") && ioman->CheckBranch(ioman->GetBranchName(link.GetType())) != 1) {
      if (fVerbose > 1) {
        std::cout << "BYPASS!" << std::endl;
      }
//      bypass = kTRUE;
    }
  }

  if (bypass == kTRUE) {
    //FairRootManager* ioman = FairRootManager::Instance();
    if (link.GetType() > ioman->GetBranchId("MCTrack")) {
      TClonesArray* array = (TClonesArray*)ioman->GetObject(ioman->GetBranchName(link.GetType()));
      if (fVerbose > 1) {
        std::cout << "Entries in " << ioman->GetBranchName(link.GetType()) << " Array: " << array->GetEntries() << std::endl;
      }
      FairMultiLinkedData* links = (FairMultiLinkedData*)array->At(link.GetIndex());
      if (fVerbose > 1) {
        std::cout << "FairMultiLinkedData has " << links->GetNLinks() << " Entries: " << std::endl;
        std::cout << *links << std::endl;
      }
      AddLinks(*links, mult);
      return;
    } else {
      InsertLink(link);
      if (fInsertHistory == kTRUE)
    	  InsertHistory(link);
    }
  } else {
    InsertLink(link);
    if (fInsertHistory == kTRUE)
    	InsertHistory(link);
  }

}

void FairMultiLinkedData::InsertLink(FairLink link)
{
  if (FairLinkManager::Instance()->IsIgnoreType(link.GetType())){
	return;
  }

  std::set<FairLink>::iterator it = fLinks.find(link);
  if (it != fLinks.end()) {
    FairLink myTempLink = *it;
    myTempLink.AddWeight(link.GetWeight());
    fLinks.erase(it);
    fLinks.insert(myTempLink);
  } else {
    fLinks.insert(link);
  }
  return;
}

void FairMultiLinkedData::InsertHistory(FairLink link)
{
        FairRootManager* ioman = FairRootManager::Instance();
        FairMultiLinkedData* pointerToLinks = 0;

        if (fVerbose > 1)
        	std::cout << "FairMultiLinkedData::InsertHistory for Link " << link << " Type: " << ioman->GetBranchName(link.GetType()) << std::endl;

        if (link.GetType() < 0)
                return;
        if (link.GetType() == ioman->GetBranchId("MCTrack"))
                return;
        if(ioman->GetBranchName(link.GetType()).Contains("."))
        	return;
        if(link.GetEntry() != -1 && link.GetEntry() != ioman->GetEntryNr())
        	return;

        if (link.GetIndex() < 0) { //if index is -1 then this is not a TClonesArray so only the Object is returned
                FairMultiLinkedData_Interface* interface = (FairMultiLinkedData_Interface*) ioman->GetObject(ioman->GetBranchName(link.GetType()));
                pointerToLinks = interface->GetPointerToLinks();
        } else {
                TClonesArray* dataArray = (TClonesArray*) ioman->GetObject(ioman->GetBranchName(link.GetType()));
                if (dataArray != 0 && link.GetIndex() < dataArray->GetEntriesFast()) {
                        FairMultiLinkedData_Interface* interface = (FairMultiLinkedData_Interface*) dataArray->At(link.GetIndex());
                        pointerToLinks = interface->GetPointerToLinks();

                }
        }
        if (pointerToLinks != 0){
                std::set<FairLink> linkSet = pointerToLinks->GetLinks();
                for (std::set<FairLink>::const_iterator iter = linkSet.begin(); iter!= linkSet.end(); iter++){
                	if (fVerbose > 1)
                		std::cout << "FairMultiLinkedData::InsertHistory inserting " << *iter << std::endl;
                    InsertLink(*iter);
                }
        }

}

Bool_t FairMultiLinkedData::IsLinkInList(Int_t type, Int_t index)
{
  if (LinkPosInList(type, index) > -1) {
    return kTRUE;
  }
  return kFALSE;
}

Int_t FairMultiLinkedData::LinkPosInList(Int_t type, Int_t index)
{
  std::set<FairLink>::iterator it = std::find(fLinks.begin(), fLinks.end(), FairLink(type, index));
  if (it != fLinks.end()) {
    return std::distance(fLinks.begin(), it);
  }
  return -1;
}

void FairMultiLinkedData::DeleteLink(Int_t /*type*/, Int_t /*index*/)
{
  /*  Int_t pos = LinkPosInList(type, index);
    if (pos < 0) return;
    else{
      fLinks.erase(fLinks.begin()+pos);
    }*/
}

FairMultiLinkedData FairMultiLinkedData::GetLinksWithType(Int_t type) const
{
  FairMultiLinkedData result;
  for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++) {
    if (it->GetType() == type) {
      FairLink myLink = *it;
      result.InsertLink(myLink);
    }
  }
  return result;
}

bool LargerWeight(FairLink val1, FairLink val2){
	return val1.GetWeight() > val2.GetWeight();
}

std::vector<FairLink> FairMultiLinkedData::GetSortedMCTracks(){
	FairMultiLinkedData mcLinks = GetLinksWithType(FairRootManager::Instance()->GetBranchId("MCTrack"));
	std::set<FairLink> mcSet = mcLinks.GetLinks();
	std::vector<FairLink> mcVector(mcSet.begin(), mcSet.end());
	//std::sort(begin(mcVector), end(mcVector), [](FairLink& val1, FairLink& val2){ return val1.GetWeight() > val2.GetWeight();});
	std::sort(begin(mcVector), end(mcVector), LargerWeight);
	return mcVector;
}

TObject* FairMultiLinkedData::GetData(FairLink& myLink)
{
  FairRootManager* ioman = FairRootManager::Instance();
  TString branchName = ioman->GetBranchName(myLink.GetType());
  if (ioman->CheckBranch(branchName) > 0) {
    TClonesArray* myArray = (TClonesArray*)ioman->GetObject(branchName);
    if (myArray != 0) {
      if (myArray->GetEntries() > myLink.GetIndex()) {
        return myArray->At(myLink.GetIndex());
      } else { std::cout << "-E- FairMultiLinkedData::GetData index out of bounds" << std::endl; }
    } else { std::cout << "-E- FairMultiLinkedData::GetData no TClonesArray" << std::endl; }
  } else { std::cout << "-E- FairMultiLinkedData::GetData Branch does not exist in Memory" << std::endl; }

  return 0;
}

void FairMultiLinkedData::SetAllWeights(Double_t weight)
{
  std::set<FairLink> tempLinks;
  for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++) {
    FairLink tempLink = *it;
    tempLink.SetWeight(weight);
    tempLinks.insert(tempLink);
  }
  fLinks = tempLinks;
}

void FairMultiLinkedData::AddAllWeights(Double_t weight)
{
  std::set<FairLink> tempLinks;
  for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++) {
    FairLink tempLink = *it;
    tempLink.SetWeight(weight + tempLink.GetWeight());
    tempLinks.insert(tempLink);
  }
  fLinks = tempLinks;
}

void FairMultiLinkedData::MultiplyAllWeights(Double_t weight)
{
  std::set<FairLink> tempLinks;
  for (std::set<FairLink>::iterator it = fLinks.begin(); it != fLinks.end(); it++) {
    FairLink tempLink = *it;
    tempLink.SetWeight(weight * tempLink.GetWeight());
    tempLinks.insert(tempLink);
  }
  fLinks = tempLinks;
}
