/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  FairFileSource.cxx
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//
#include "FairFileSource.h"
#include "TString.h"
#include "FairEventHeader.h"
#include "FairFileHeader.h"
#include "FairMCEventHeader.h"
#include "FairLogger.h"
#include "TObjArray.h"
#include <map> 
#include <set> 
#include <algorithm>                    // for find
#include "TChainElement.h"
#include "TFolder.h"
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairRootManager.h"
#include "TRandom.h"                    // for TRandom, gRandom
#include "TROOT.h"
#include <list>                         // for _List_iterator, list, etc
using std::map;
using std::set;

//_____________________________________________________________________________

FairFileSource::FairFileSource(TFile *f, const char* Title, UInt_t identifier)
  :FairSource()
  , fInputTitle(Title)
  , fRootFile(f)
  , fFileHeader(0)
  , fCurrentEntryNr(0)
  , fLogger(FairLogger::GetLogger())
  , fFriendFileList()
  , fFriendTypeList()
  , fInputChainList()
  , fCheckInputBranches()
  , fInputLevel()
  , fRunIdInfoAll()
  , fInChain(0)
  , fInTree(0)
  , fListFolder(new TObjArray(16))
  , fRtdb(FairRuntimeDb::instance())
  , fCbmout(0)
  , fCbmroot(0)
  , fSourceIdentifier(0)
  , fNoOfEntries(-1)
  , IsInitialized(kFALSE)
  , fMCHeader(0)
  , fEvtHeader(0)
  , fEvtHeaderIsNew(kFALSE)
  , fEventTimeInMCHeader(kTRUE)
  , fCurrentEntryNo(0)
  , fTimeforEntryNo(-1)
  , fEventTimeMin(0.)
  , fEventTimeMax(0.)
  , fEventTime(0.)
  , fEventMeanTime(0.)
  , fBeamTime(-1.)
  , fGapTime(-1.)
  , fTimeProb(0)
{
    if (fRootFile->IsZombie()) {
     LOG(FATAL) << "Error opening the Input file" << FairLogger::endl;
  }
  LOG(DEBUG) << "FairFileSource created------------" << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairFileSource::FairFileSource(const TString* RootFileName, const char* Title, UInt_t identifier)
  :FairSource()
  , fInputTitle(Title)
  , fRootFile(0)
  , fFileHeader(0)
  , fCurrentEntryNr(0)
  , fLogger(FairLogger::GetLogger())
  , fFriendFileList()
  , fFriendTypeList()
  , fInputChainList()
  , fCheckInputBranches()
  , fInputLevel()
  , fRunIdInfoAll()
  , fInChain(0)
  , fInTree(0)
  , fListFolder(new TObjArray(16))
  , fRtdb(FairRuntimeDb::instance())
  , fCbmout(0)
  , fCbmroot(0)
  , fSourceIdentifier(0)
  , fNoOfEntries(-1)
  , IsInitialized(kFALSE)
  , fMCHeader(0)
  , fEvtHeader(0)
  , fEvtHeaderIsNew(kFALSE)
  , fEventTimeInMCHeader(kTRUE)
  , fCurrentEntryNo(0)
  , fTimeforEntryNo(-1)
  , fEventTimeMin(0.)
  , fEventTimeMax(0.)
  , fEventTime(0.)
  , fEventMeanTime(0.)
  , fBeamTime(-1.)
  , fGapTime(-1.)
  , fTimeProb(0)
{
  fRootFile = new TFile(RootFileName->Data());
  if (fRootFile->IsZombie()) {
    LOG(FATAL) << "Error opening the Input file" << FairLogger::endl;
  }
  LOG(DEBUG) << "FairFileSource created------------" << FairLogger::endl;
  }
//_____________________________________________________________________________

//_____________________________________________________________________________
FairFileSource::FairFileSource(const TString RootFileName, const char* Title, UInt_t identifier)
  :FairSource()
  , fInputTitle(Title)
  , fRootFile(0)
  , fFileHeader(0)
  , fCurrentEntryNr(0)
  , fLogger(FairLogger::GetLogger())
  , fFriendFileList()
  , fFriendTypeList()
  , fInputChainList()
  , fCheckInputBranches()
  , fInputLevel()
  , fRunIdInfoAll()
  , fInChain(0)
  , fInTree(0)
  , fListFolder(new TObjArray(16))
  , fRtdb(FairRuntimeDb::instance())
  , fCbmout(0)
  , fCbmroot(0)
  , fSourceIdentifier(0)
  , fNoOfEntries(-1)
  , IsInitialized(kFALSE)
  , fMCHeader(0)
  , fEvtHeader(0)
  , fEvtHeaderIsNew(kFALSE)
  , fEventTimeInMCHeader(kTRUE)
  , fCurrentEntryNo(0)
  , fTimeforEntryNo(-1)
  , fEventTimeMin(0.)
  , fEventTimeMax(0.)
  , fEventTime(0.)
  , fEventMeanTime(0.)
  , fBeamTime(-1.)
  , fGapTime(-1.)
  , fTimeProb(0)
{
    fRootFile = new TFile(RootFileName.Data());
    if (fRootFile->IsZombie()) {
       fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
    }
    fLogger->Debug(MESSAGE_ORIGIN, "FairFileSource created------------");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairFileSource::~FairFileSource()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairFileSource::Init()
{
    if(IsInitialized){
      LOG(INFO) << "FairFileSource already initialized" << FairLogger::endl;
       return kTRUE;
    }
    if (!fInChain ) {
        fInChain = new TChain("cbmsim", "/cbmroot");
        LOG(DEBUG) << "FairFileSource::Init() chain created"
		   << FairLogger::endl;
    }
    fInChain->Add( fRootFile->GetName() );
    
    // Get the folder structure from file which describes the input tree.
    // There are two different names possible, so check both.
    fCbmroot= dynamic_cast <TFolder*> (fRootFile->Get("cbmroot"));
    if(!fCbmroot) {
        fCbmroot= dynamic_cast <TFolder*> (fRootFile->Get("cbmout"));
        if(!fCbmroot) {
            fCbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");
        } else {
            fCbmroot->SetName("cbmroot");
        }
    }
    // Get The list of branches from the input file and add it to the
    // actual list of existing branches.
    // Add this list of branches also to the map of input trees, which
    // stores the information which branches belong to which input tree.
    // There is at least one primary input tree, but there can be many
    // additional friend trees.
    // This information is needed to add new files to the correct friend
    // tree. With this information it is also possible to check if the
    // input files which are added to the input chain all have the same
    // branch structure. Without this check it is possible to add trees
    // with a different branch structure but the same tree name. ROOT
    // probably only checks if the name of the tree is the same.
    TList* list= dynamic_cast <TList*> (fRootFile->Get("BranchList"));
    if(list==0) {
      LOG(FATAL) << "No Branch list in input file" << FairLogger::endl;
    }
    TString chainName = fInputTitle;
    TString ObjName;
    fInputLevel.push_back(chainName);
    fCheckInputBranches[chainName] = new std::list<TString>;
    if(list) {
      TObjString* Obj=0;
      LOG(DEBUG) << "Enteries in the list " 
		 << list->GetEntries() << FairLogger::endl;
      for(Int_t i =0; i< list->GetEntries(); i++) {
	Obj=dynamic_cast <TObjString*> (list->At(i));
	if(Obj!=0){
	  ObjName=Obj->GetString();
	  LOG(DEBUG) << "Branch name " << ObjName.Data()
		     << FairLogger::endl;
	  fCheckInputBranches[chainName]->push_back(ObjName.Data());
	  
	  FairRootManager::Instance()->AddBranchToList(ObjName.Data());
	}
      }
    }
    
    LOG(DEBUG) << "Entries in this Source " << fNoOfEntries << FairLogger::endl;
    
    for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
       TFolder* fold = (TFolder*) fListFolder->At(i);
       fEvtHeader = (FairEventHeader*)   fold->FindObjectAny("EventHeader.");
       fMCHeader  = (FairMCEventHeader*) fold->FindObjectAny("MCEventHeader.");
       if ( fEvtHeader ) {
	  ActivateObject((TObject**)&fEvtHeader,"EventHeader.");
       }
       if ( fMCHeader  ) {
	  ActivateObject((TObject**)&fMCHeader ,"MCEventHeader.");
       }
    }

    AddFriendsToChain();

    return kTRUE;
   
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairFileSource::ReadEvent(UInt_t i)
{
    fCurrentEntryNo = i;
    SetEventTime();
    if ( fInChain->GetEntry(i) ) return 0;

    return 1;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::Close()
{
    CloseInFile();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::Reset()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::AddFriend(TString fName)
{
    fFriendFileList.push_back(fName);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::AddFile(TString FileName)
{
    fInputChainList.push_back(FileName);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::AddFriendsToChain()
{
    // Loop over all Friend files and extract the type. The type is defined by
    // the tree which is stored in the file. If there is already a chain of with
    // this type of tree then the file will be added to this chain.
    // If there is no such chain it will be created.
    //
    // Check if the order of runids and the event numbers per runid for all
    // friend chains is the same as the one defined by the input chain.
    // TODO: Should the order be corrected or should the execution be stopped.
    // The order in the input tree defined by the order in which the files have
    // been added. A file is defined by the runid.
    
    // In the old way it was needed sometimes to add a freind file more
    // than once. This is not needed any longer, so we remove deuplicates
    // from the list and display a warning.
    std::list<TString> friendList;
    std::list<TString>::iterator iter1;
    for(iter1 = fFriendFileList.begin();
        iter1 != fFriendFileList.end(); iter1++) {
        if (find(friendList.begin(), friendList.end(), (*iter1))
            == friendList.end()) {
            friendList.push_back(*iter1);
        }
    }
    // TODO: print a warning if it was neccessary to remove a filname from the
    // list. This can be chacked by comparing the size of both list
    
    TFile* temp = gFile;
    
    Int_t friendType = 1;
    // Loop over all files which have been added as friends
    for(iter1 = friendList.begin();
        iter1 != friendList.end(); iter1++) {
        std::list<TString>::iterator iter;
        TString inputLevel;
        // Loop over all already defined input levels to check if this type
        // of friend tree is already added.
        // If this type of friend tree already exist add the file to the
        // then already existing friend chain. If this type of friend tree
        // does not exist already create a new friend chain and add the file.
        Bool_t inputLevelFound = kFALSE;
        TFile* inputFile;
        for ( iter = fInputLevel.begin(); iter !=fInputLevel.end(); iter++ ) {
            inputLevel = (*iter);
            
            inputFile = new TFile((*iter1));
            if (inputFile->IsZombie()) {
	      LOG(FATAL) << "Error opening the file " << (*iter).Data()
			 << " which should be added to the input chain or as friend chain" << FairLogger::endl;
            }
            
            // Check if the branchlist is already stored in the map. If it is
            // already stored add the file to the chain.
            Bool_t isOk = CompareBranchList(inputFile, inputLevel);
            if ( isOk ) {
                inputLevelFound = kTRUE;
                inputFile->Close();
                continue;
            }
            inputFile->Close();
        }
        if (!inputLevelFound) {
            inputLevel= Form("FriendTree_%i",friendType);
            CreateNewFriendChain((*iter1), inputLevel);
            friendType++;
        }
        
        TChain* chain = (TChain*) fFriendTypeList[inputLevel];
        chain->AddFile((*iter1), 1234567890, "cbmsim");
    }
    gFile=temp;
    
    // Check if all friend chains have the same runids and the same
    // number of event numbers as the corresponding input chain
    // CheckFriendChains();
    
    // Add all the friend chains which have been created to the
    // main input chain.
    std::map< TString, TChain* >::iterator mapIterator;
    for (mapIterator = fFriendTypeList.begin();
         mapIterator != fFriendTypeList.end(); mapIterator++ ) {
        
        TChain* chain = (TChain*)mapIterator->second;
        fInChain->AddFriend(chain);
    }
    
    // Print some output about the input structure
    PrintFriendList();
    
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::PrintFriendList( )
{
    // Print information about the input structure
    // List files from the input chain together with all files of
    // all friend chains
    
  LOG(INFO) << "The input consists out of the following trees and files: "
	    <<FairLogger::endl;
  LOG(INFO) << " - " << fInChain->GetName() << FairLogger::endl;
    TObjArray* fileElements=fInChain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    while (( chEl=(TChainElement*)next() )) {
      LOG(INFO) << "    - " << chEl->GetTitle() << FairLogger::endl;
    }
    
    map< TString, TChain* >::iterator mapIterator;
    for (mapIterator = fFriendTypeList.begin();
         mapIterator != fFriendTypeList.end(); mapIterator++ ) {
        TChain* chain = (TChain*) mapIterator->second;
        LOG(INFO) << " - " << chain->GetName() << FairLogger::endl;
        fileElements=chain->GetListOfFiles();
        TIter next1(fileElements);
        chEl=0;
        while (( chEl=(TChainElement*)next1() )) {
	  LOG(INFO) << "    - " << chEl->GetTitle() << FairLogger::endl;
        }
    }
    
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::CheckFriendChains()
{
    std::multimap< TString, std::multimap<TString,TArrayI> >::iterator it1;
    std::multimap<TString,TArrayI> map1;
    
    // Get the structure from the input chain
    it1=fRunIdInfoAll.find("InputChain");
    map1 = it1->second;
    std::vector<Int_t> runid;
    std::vector<Int_t> events;
    std::multimap<TString,TArrayI>::iterator it;
    for ( it=map1.begin() ; it != map1.end(); it++ ) {
        TArrayI bla = (*it).second;
        runid.push_back(bla[0]);
        events.push_back(bla[1]);
    }
    
    // Now loop over all chains except the input chain and comapare the
    // runids and event numbers.
    // If there is a mismatch stop the execution.
    Int_t errorFlag = 0;
    TString inputLevel;
    std::list<TString>::iterator listit;
    for ( listit=fInputLevel.begin() ; listit != fInputLevel.end(); listit++ ) {
        inputLevel = (*listit);
        if ( !inputLevel.Contains("InputChain") ) {
            it1=fRunIdInfoAll.find(inputLevel);
            map1 = it1->second;
            if ( runid.size() != map1.size()) {
                errorFlag = 1;
                //        goto error_label;
                break;
            }
            Int_t counter = 0;
            for ( it=map1.begin() ; it != map1.end(); it++ ) {
                TArrayI bla = (*it).second;
                if ( (bla[0] != runid[counter]) || (bla[1] != events[counter]) ) {
                    errorFlag = 2;
                    //          goto error_label;
                    break;
                }
                counter++;
            }
            if (errorFlag>0) {
                break;
            }
        }
    }
    
    // Use goto to leave double loop at once in case of error
    // error_label:
    if (errorFlag>0) {
      LOG(ERROR) << "The input chain and the friend chain " << inputLevel.Data() 
		 << " have a different structure:" << FairLogger::endl;
        if (errorFlag == 1) {
	  LOG(ERROR) << "The input chain has the following runids and event numbers:" << FairLogger::endl;
            for ( Int_t i=0; i<runid.size(); i++) {
	      LOG(ERROR) << " - Runid " << runid[i] << " with " << events[i] 
			 << " events" << FairLogger::endl;
            }
            LOG(ERROR) << "The " << inputLevel.Data() 
		       << " chain has the following runids and event numbers:"
		       << FairLogger::endl;
            for ( it=map1.begin() ; it != map1.end(); it++ ) {
                TArrayI bla = (*it).second;
                LOG(ERROR) << " - Runid " << bla[0] << " with " << bla[1] 
			   << " events" << FairLogger::endl;
            }
        }
        if (errorFlag == 2) {
            Int_t counter = 0;
            for ( it=map1.begin() ; it != map1.end(); it++ ) {
                TArrayI bla = (*it).second;
                LOG(ERROR) << "Runid Input Chain, " << inputLevel.Data() 
			   << " chain: " << bla[0] << ", " << runid[counter]
			   << FairLogger::endl;
                LOG(ERROR) << "Event number Input Chain, " << inputLevel.Data()
			   << " chain: " << bla[1] 
			   << ", " << events[counter] << FairLogger::endl;
                counter++;
            }
        }
        LOG(FATAL) << "Event structure mismatch" << FairLogger::endl;
    }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::CreateNewFriendChain(TString inputFile, TString inputLevel)
{
    
    TFile* temp = gFile;
    TFile* f = new TFile(inputFile);
    
    TFolder* added=NULL;
    TString folderName = "/cbmout";
    TString folderName1 = "cbmout";
    added = dynamic_cast <TFolder*> (f->Get("cbmout"));
    if(!added) {
        folderName = "/cbmroot";
        folderName1 = "cbmroot";
        added = dynamic_cast <TFolder*> (f->Get("cbmroot"));
	if (!added) {
	  LOG(FATAL) << "Could not find folder cbmout nor cbmroot." 
		     <<FairLogger::endl;
	  exit(-1);
	}
    }
    folderName1=folderName1+"_"+inputLevel;
    added->SetName(folderName1);
    fListFolder->Add( added );
    
    /**Get The list of branches from the friend file and add it to the actual list*/
    TList* list= dynamic_cast <TList*> (f->Get("BranchList"));
    TString chainName = inputLevel;
    fInputLevel.push_back(chainName);
    fCheckInputBranches[chainName] = new std::list<TString>;
    if(list) {
        TObjString* Obj=0;
        for(Int_t i =0; i< list->GetEntries(); i++) {
            Obj=dynamic_cast <TObjString*> (list->At(i));
            fCheckInputBranches[chainName]->push_back(Obj->GetString().Data());
	    FairRootManager::Instance()->AddBranchToList(Obj->GetString().Data());
        }
    }
    
    TChain* chain = new TChain(inputLevel,folderName);
    fFriendTypeList[inputLevel]=chain;
    
    f->Close();
    gFile = temp;
    
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairFileSource::CompareBranchList(TFile* fileHandle, TString inputLevel)
{
  // fill a set with the original branch structure
  // This allows to use functions find and erase
  std::set<TString> branches;
  std::list<TString>::const_iterator iter;
  for(iter = fCheckInputBranches[inputLevel]->begin();
      iter != fCheckInputBranches[inputLevel]->end(); iter++) {
    branches.insert(*iter);
  }

  // To do so we have to loop over the branches in the file and to compare
  // the branches in the file with the information stored in
  // fCheckInputBranches["InputChain"]. If both lists are equal everything
  // is okay

  // Get The list of branches from the input file one by one and compare
  // it to the reference list of branches which is defined for this tree.
  // If a branch with the same name is found, this branch is removed from
  // the list. If in the end no branch is left in the list everything is
  // fine.
  set<TString>::iterator iter1;
  TList* list= dynamic_cast <TList*> (fileHandle->Get("BranchList"));
  if(list) {
    TObjString* Obj=0;
    for(Int_t i =0; i< list->GetEntries(); i++) {
      Obj=dynamic_cast <TObjString*> (list->At(i));
      iter1=branches.find(Obj->GetString().Data());
      if (iter1 != branches.end() ) {
        branches.erase (iter1);
      } else {
        // Not found is an error because branch structure is
        // different. It is impossible to add to tree with a
        // different branch structure
        return kFALSE;
      }
    }
  }
  // If the size of branches is !=0 after removing all branches also in the
  // reference list, this is also a sign that both branch list are not the
  // same
  if (branches.size() != 0 ) {
    LOG(INFO) << "Compare Branch List will return kFALSE. The list has " << branches.size() << " branches:" << FairLogger::endl;
    for (std::set<TString>::iterator it=branches.begin(); it!=branches.end(); ++it)
      LOG(INFO) << "  -> " << *it << FairLogger::endl;
    return kFALSE;
  }

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairFileSource::GetObject(const char* ObjName, const char* ObjType) {
  if ( ObjType == "GetListOfFolders" ) {
    return GetListOfFolders();
  }
  if ( ObjType == "GetInTree" ) {
    return GetInTree();
  }
    
    TObject* temp = new TObject();
    return temp;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t   FairFileSource::ActivateObject(TObject** obj, const char* BrName) {
    if ( fInTree ) {
        fInTree->SetBranchStatus(BrName,1);
        fInTree->SetBranchAddress(BrName,obj);
    }
    if ( fInChain ) {
        fInChain->SetBranchStatus(BrName,1);
        fInChain->SetBranchAddress(BrName,obj);
    }
    
    return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::SetInputFile(TString name) {
  fRootFile = new TFile(name.Data());
  if (fRootFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
  }
  fLogger->Info(MESSAGE_ORIGIN, "FairFileSource set------------");

}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  FairFileSource::CheckMaxEventNo(Int_t EvtEnd)
{
  Int_t MaxEventNo=0;
  if(EvtEnd!=0) {
    MaxEventNo=EvtEnd;
  }
  MaxEventNo=fInChain->GetEntries();
  return MaxEventNo;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairFileSource::SetEventMeanTime(Double_t mean)
{
  fEventMeanTime =mean;
  TString form="(1/";
  form+= mean;
  form+=")*exp(-x/";
  form+=mean;
  form+=")";
  fTimeProb= new TF1("TimeProb.", form.Data(), 0., mean*10);
  fTimeProb->GetRandom();
  fEventTimeInMCHeader=kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::SetEventTimeInterval(Double_t min, Double_t max)
{
  fEventTimeMin=min;
  fEventTimeMax=max;
  fEventMeanTime=(fEventTimeMin+fEventTimeMax)/2;
  fEventTimeInMCHeader=kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::SetBeamTime(Double_t beamTime, Double_t gapTime)
{
  fBeamTime = beamTime;
  fGapTime = gapTime;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::SetEventTime()
{
  LOG(DEBUG) << "Set event time for Entry = "
	     << fTimeforEntryNo << " , where the current entry is "
	     << fCurrentEntryNo << " and eventTime is "
	     << fEventTime << FairLogger::endl;
  if (fBeamTime < 0){
	  fEventTime += GetDeltaEventTime();
  } else {
	  do {
		  fEventTime += GetDeltaEventTime();
	  } while( fmod(fEventTime, fBeamTime + fGapTime) > fBeamTime );
  }
  LOG(DEBUG) << "New time = " << fEventTime << FairLogger::endl;
  fTimeforEntryNo=fCurrentEntryNo;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Double_t FairFileSource::GetDeltaEventTime()
{
  Double_t deltaTime = 0;
  if (fTimeProb != 0) {
    deltaTime = fTimeProb->GetRandom();
    LOG(DEBUG) << "Time set via sampling method : " <<  deltaTime
	       << FairLogger::endl;
  } else {
    deltaTime = gRandom->Uniform(fEventTimeMin, fEventTimeMax);
    LOG(DEBUG) << "Time set via Uniform Random : "
	       << deltaTime << FairLogger::endl;
  }
  return deltaTime;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Double_t FairFileSource::GetEventTime()
{
 LOG(DEBUG) << "-- Get Event Time --" << FairLogger::endl;
  if(!fEvtHeaderIsNew && fEvtHeader!=0) {
    Double_t EvtTime=fEvtHeader->GetEventTime();
    if( !(EvtTime<0)) {
      return   EvtTime;
    }
  }

  if (fEventTimeInMCHeader && !fMCHeader) {
    LOG(DEBUG) << "No MCEventHeader, time is set to 0" << FairLogger::endl;
    return 0;
  } else if(fEventTimeInMCHeader && fMCHeader) {
    fEventTime=fMCHeader->GetT();
    LOG(DEBUG) << "Get event time from MCEventHeader : "
	       << fEventTime << " ns" << FairLogger::endl;
    return fEventTime;
  } else {

    if(fTimeforEntryNo!=fCurrentEntryNo) {
      SetEventTime();
    }
    LOG(DEBUG) << "Calculate event time from user input : " 
	       << fEventTime << " ns" << FairLogger::endl;
    return fEventTime;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::ReadBranchEvent(const char* BrName)
{
  /**fill the object with content if the other branches in this tree entry were already read**/
  if(fEvtHeader == 0) { return; } //No event header, Reading will start later
  if ( fInTree ) {
    fInTree->FindBranch(BrName)->GetEntry(fEvtHeader->GetMCEntryNumber());
    return;
  }
  if ( fInChain ) { 
    fInChain->FindBranch(BrName)->GetEntry(fEvtHeader->GetMCEntryNumber());
    return;
  } 
  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairFileSource::FillEventHeader(FairEventHeader* feh) 
{
  feh->SetEventTime(fEventTime);
  if ( fEvtHeader ) {
    feh->SetRunId(fEvtHeader->GetRunId());
    feh->SetMCEntryNumber(fEvtHeader->GetMCEntryNumber());
  }
  if ( fMCHeader ) {
    feh->SetRunId(fMCHeader->GetRunID());
    feh->SetMCEntryNumber(fMCHeader->GetEventID());
  }
  feh->SetInputFileId(0);
  return;
}
//_____________________________________________________________________________

ClassImp(FairFileSource)

