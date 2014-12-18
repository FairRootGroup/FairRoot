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
#include "FairFileHeader.h"
#include "FairLogger.h"
#include "TObjArray.h"
#include <map> 
#include <set> 
#include <algorithm>                    // for find
#include "TChainElement.h"
#include "TFolder.h"
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "TROOT.h"
#include <list>                         // for _List_iterator, list, etc
using std::map;
using std::set;

//_____________________________________________________________________________

FairFileSource::FairFileSource(TFile *f, const char* Title, UInt_t identifier)
 :FairSource(),
 fInputTitle(Title),
 fRootFile(f),
 fFileHeader(0),
 fCurrentEntryNr(0),
 fLogger(FairLogger::GetLogger()),
 fFriendFileList(),
 fInputChainList(),
 fFriendTypeList(),
 fCheckInputBranches(),
 fInputLevel(),
 fRunIdInfoAll(),
 fInChain(0),
 fInTree(0),
 fListFolder(new TObjArray(16)),
 fBranchSeqId(0),
 fBranchNameList(new TList()),
 fRtdb(FairRuntimeDb::instance()),
 fCbmout(0),
 fCbmroot(0),
 fSourceIdentifier(0),
 fNoOfEntries(-1),
 IsInitialized(kFALSE)
{
   if (fRootFile->IsZombie()) {
      fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
   }
  fLogger->Info(MESSAGE_ORIGIN, "FairFileSource created------------");
 
}
//_____________________________________________________________________________

FairFileSource::FairFileSource(const TString* RootFileName, const char* Title, UInt_t identifier)
:FairSource(),
 fInputTitle(Title),
 fRootFile(0),
 fFileHeader(0),
 fCurrentEntryNr(0),
 fLogger(FairLogger::GetLogger()),
 fFriendFileList(),
 fInputChainList(),
 fFriendTypeList(),
 fCheckInputBranches(),
 fInputLevel(),
 fRunIdInfoAll(),
 fInChain(0),
 fInTree(0),
 fListFolder(new TObjArray(16)),
 fBranchSeqId(0),
 fBranchNameList(new TList()),
 fRtdb(FairRuntimeDb::instance()),
 fCbmout(0),
 fCbmroot(0),
 fSourceIdentifier(0),
 fNoOfEntries(-1),
 IsInitialized(kFALSE)
{
    fRootFile = new TFile(RootFileName->Data());
    if (fRootFile->IsZombie()) {
       fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
    }
  fLogger->Info(MESSAGE_ORIGIN, "FairFileSource created------------");

}
//_____________________________________________________________________________

FairFileSource::~FairFileSource()
{
}
//_____________________________________________________________________________

Bool_t FairFileSource::Init()
{
    if(IsInitialized){
       fLogger->Info(MESSAGE_ORIGIN, "FairFileSource already initialized");
       return kTRUE;
    }
    if (!fInChain ) {
        fInChain = new TChain("cbmsim", "/cbmroot");
        fLogger->Info(MESSAGE_ORIGIN, "FairFileSource::Init() chain created");
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
    if(list==0)fLogger->Fatal(MESSAGE_ORIGIN, "No Branch list in input file");
    TString chainName = fInputTitle;
    TString ObjName;
    fInputLevel.push_back(chainName);
    fCheckInputBranches[chainName] = new std::list<TString>;
    if(list) {
        TObjString* Obj=0;
        fLogger->Info(MESSAGE_ORIGIN, "Enteries in the list  %i", list->GetEntries());
        for(Int_t i =0; i< list->GetEntries(); i++) {
            Obj=dynamic_cast <TObjString*> (list->At(i));
            if(Obj!=0){
                ObjName=Obj->GetString();
                fLogger->Info(MESSAGE_ORIGIN, "Branch name %s", ObjName.Data());
                fCheckInputBranches[chainName]->push_back(ObjName.Data());
                
                if(fBranchNameList->FindObject(ObjName.Data())==0) {
                    fBranchNameList->AddLast(Obj);
                    fBranchSeqId++;
                 }
            }
        }
    }
    
    gROOT->GetListOfBrowsables()->Add(fCbmroot);
    fListFolder->Add( fCbmroot );

    // Store the information about the unique runids in the input file
    // together with the filename and the number of events for each runid
    // this information is needed later to check if inconsitencies exist
    // between the main input chain and any of the friend chains.
    
    //  GetRunIdInfo(fInFile->GetName(), chainName);
    
    // Add all additional input files to the input chain and do a
    // consitency check
    std::list<TString>::const_iterator iter;
    for(iter = fInputChainList.begin(); iter != fInputChainList.end(); iter++) {
        // Store global gFile pointer for safety reasons.
        // Set gFile to old value at the end of the routine.R
        TFile* temp = gFile;
        
        // Temporarily open the input file to extract information which
        // is needed to bring the friend trees in the correct order
        TFile* inputFile = new TFile((*iter));
        if (inputFile->IsZombie()) {
            fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the file %s which should be added to the input chain or as friend chain", (*iter).Data());
        }
        
        // Check if the branchlist is the same as for the first input file.
        Bool_t isOk = CompareBranchList(inputFile, chainName);
        if ( !isOk ) {
            fLogger->Fatal(MESSAGE_ORIGIN, "Branch structure of the input file %s and the file to be added %s are different.", fRootFile->GetName(), (*iter).Data());
            return kFALSE;
        }
        
        // Add the runid information for all files in the chain.
        //GetRunIdInfo(inputFile->GetName(), chainName);
        // Add the file to the input chain
        fInChain->Add( (*iter) );
        
        // Close the temporarly file and restore the gFile pointer.
        inputFile->Close();
        gFile = temp;

    }
    fNoOfEntries = fInChain->GetEntries();
    fLogger->Info(MESSAGE_ORIGIN, "Entries in this Source %i------------",  fNoOfEntries);
    return kTRUE;

  
}
//_____________________________________________________________________________

Int_t FairFileSource::ReadEvent(UInt_t i)
{
   return fInChain->GetEntry(i);
}
//_____________________________________________________________________________

void FairFileSource::Close()
{
}
//_____________________________________________________________________________

void FairFileSource::Reset()
{
}
//_____________________________________________________________________________

void FairFileSource::AddFriend(TString fName)
{
    fFriendFileList.push_back(fName);
}
//_____________________________________________________________________________

void FairFileSource::AddFile(TString FileName)
{
     fInputChainList.push_back(FileName);
}
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
                fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the file %s which should be added to the input chain or as friend chain", (*iter).Data());
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

void FairFileSource::PrintFriendList( )
{
    // Print information about the input structure
    // List files from the input chain together with all files of
    // all friend chains
    
    fLogger->Info(MESSAGE_ORIGIN,
                  "The input consists out of the following trees and files:");
    fLogger->Info(MESSAGE_ORIGIN," - %s",fInChain->GetName());
    TObjArray* fileElements=fInChain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    while (( chEl=(TChainElement*)next() )) {
        fLogger->Info(MESSAGE_ORIGIN,"    - %s",chEl->GetTitle());
    }
    
    map< TString, TChain* >::iterator mapIterator;
    for (mapIterator = fFriendTypeList.begin();
         mapIterator != fFriendTypeList.end(); mapIterator++ ) {
        TChain* chain = (TChain*) mapIterator->second;
        fLogger->Info(MESSAGE_ORIGIN," - %s",chain->GetName());
        fileElements=chain->GetListOfFiles();
        TIter next1(fileElements);
        chEl=0;
        while (( chEl=(TChainElement*)next1() )) {
            fLogger->Info(MESSAGE_ORIGIN,"    - %s",chEl->GetTitle());
        }
    }
    
}
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
        fLogger->Error(MESSAGE_ORIGIN,"The input chain and the friend chain %s have a different structure:", inputLevel.Data());
        if (errorFlag == 1) {
            fLogger->Error(MESSAGE_ORIGIN,"The input chain has the following runids and event numbers:");
            for ( Int_t i=0; i<runid.size(); i++) {
                fLogger->Error(MESSAGE_ORIGIN," - Runid %i with %i events", runid[i], events[i]);
            }
            fLogger->Error(MESSAGE_ORIGIN,"The %s chain has the following runids and event numbers:", inputLevel.Data());
            for ( it=map1.begin() ; it != map1.end(); it++ ) {
                TArrayI bla = (*it).second;
                fLogger->Error(MESSAGE_ORIGIN," - Runid %i with %i events", bla[0], bla[1]);
            }
        }
        if (errorFlag == 2) {
            Int_t counter = 0;
            for ( it=map1.begin() ; it != map1.end(); it++ ) {
                TArrayI bla = (*it).second;
                fLogger->Error(MESSAGE_ORIGIN,"Runid Input Chain, %s chain: %i, %i", inputLevel.Data(), bla[0], runid[counter]);
                fLogger->Error(MESSAGE_ORIGIN,"Event number Input Chain, %s chain: %i, %i", inputLevel.Data(), bla[1], events[counter]);
                counter++;
            }
        }
        fLogger->Fatal(MESSAGE_ORIGIN,"Event structure mismatch");
    }
}
//_____________________________________________________________________________


void FairFileSource::CreateNewFriendChain(TString inputFile, TString inputLevel)
{
    
    TFile* temp = gFile;
    TFile* f = new TFile(inputFile);
    
    TFolder* added=NULL;
    TString folderName = "/cbmout";
    TString folderName1 = "cbmout";
    added = dynamic_cast <TFolder*> (f->Get("cbmout"));
    if(added==0) {
        folderName = "/cbmroot";
        folderName1 = "cbmroot";
        added = dynamic_cast <TFolder*> (f->Get("cbmroot"));
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
            if(fBranchNameList->FindObject(Obj->GetString().Data())==0) {
                fBranchNameList->AddLast(Obj);
                fBranchSeqId++;
            }
        }
    }
    
    TChain* chain = new TChain(inputLevel,folderName);
    fFriendTypeList[inputLevel]=chain;
    
    f->Close();
    gFile = temp;
    
}

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
    return kFALSE;
  }

  return kTRUE;
}
//_____________________________________________________________________________

ClassImp(FairFileSource)

