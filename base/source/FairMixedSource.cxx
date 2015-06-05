/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  FairMixedSource.cxx
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//
#include "FairMixedSource.h"
#include "TString.h"
#include "FairEventHeader.h"
#include "FairFileHeader.h"
#include "FairMCEventHeader.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "TObjArray.h"
#include <map> 
#include <set> 
#include <algorithm>                    // for find
#include "TChainElement.h"
#include "TFolder.h"
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "TRandom.h"                    // for TRandom, gRandom
#include "TROOT.h"
#include <list>                         // for _List_iterator, list, etc
using std::map;
using std::set;


FairMixedSource::FairMixedSource(TFile *f, const char* Title, UInt_t identifier)
  :FairSource(),
   fInputTitle(Title),
   fRootFile(f),
   fRootManager(0),
   fLogger(FairLogger::GetLogger()),
   fListFolder(new TObjArray(16)),
   fRtdb(FairRuntimeDb::instance()),
   fCbmout(0),
   fCbmroot(0),
   fSourceIdentifier(0),
   fActualSignalIdentifier(0),
   fNoOfSignals(0),
   fSignalChainList(NULL),
   fBackgroundChain(NULL),
   fSignalTypeList(),
    fMCHeader(0),
    fEvtHeader(0),
    fOutHeader(0),
    fFileHeader(0),
    fEvtHeaderIsNew(kFALSE),
   fEventTimeInMCHeader(kTRUE),
    fCurrentEntryNo(0),
    fTimeforEntryNo(0),
    fNoOfBGEntries(0),
  fCurrentEntry(),
    fEventTimeMin(0.),
    fEventTimeMax(0.),
    fEventTime(0.),
    fEventMeanTime(0.),
  fBeamTime(-1.),
  fGapTime(-1.),
    fTimeProb(0),
   fSignalBGN(),
   fSBRatiobyN(kFALSE),
  fSBRatiobyT(kFALSE),
  fNoOfEntries(-1),
  IsInitialized(kFALSE)
{
   if (fRootFile->IsZombie()) {
      fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
   }
  fLogger->Info(MESSAGE_ORIGIN, "FairMixedSource created------------");
  
  fRootManager = FairRootManager::Instance();

}
FairMixedSource::FairMixedSource(const TString* RootFileName, const char* Title, UInt_t identifier)
:FairSource(),
 fInputTitle(Title),
 fRootFile(0),
   fRootManager(0),
 fLogger(FairLogger::GetLogger()),
 fListFolder(new TObjArray(16)),
 fRtdb(FairRuntimeDb::instance()),
 fCbmout(0),
 fCbmroot(0),
 fSourceIdentifier(0),
    fActualSignalIdentifier(0),
    fNoOfSignals(0),
    fSignalChainList(NULL),
    fBackgroundChain(NULL),
    fSignalTypeList(),
    fMCHeader(0),
    fEvtHeader(0),
    fOutHeader(0),
    fFileHeader(0),
    fEvtHeaderIsNew(kFALSE),
   fEventTimeInMCHeader(kTRUE),
    fCurrentEntryNo(0),
    fTimeforEntryNo(0),
    fNoOfBGEntries(0),
  fCurrentEntry(),
    fEventTimeMin(0.),
    fEventTimeMax(0.),
    fEventTime(0.),
    fEventMeanTime(0.),
  fBeamTime(-1.),
  fGapTime(-1.),
    fTimeProb(0),
   fSignalBGN(),
   fSBRatiobyN(kFALSE),
  fSBRatiobyT(kFALSE),
 fNoOfEntries(-1),
 IsInitialized(kFALSE)
{
    fRootFile = new TFile(RootFileName->Data());
    if (fRootFile->IsZombie()) {
       fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
    }
    fRootManager = FairRootManager::Instance();
  fLogger->Info(MESSAGE_ORIGIN, "FairMixedSource created------------");

}

FairMixedSource::FairMixedSource(const TString RootFileName, const Int_t signalId, const char* Title, UInt_t identifier) 
  :FairSource(), 
   fInputTitle(Title),
   fRootFile(0),
   fRootManager(0),
   fLogger(FairLogger::GetLogger()),
   fListFolder(new TObjArray(16)),
   fRtdb(FairRuntimeDb::instance()),
   fCbmout(0),
   fCbmroot(0),
   fSourceIdentifier(0),
   fActualSignalIdentifier(0),
   fNoOfSignals(0),
   fSignalChainList(NULL),
   fBackgroundChain(NULL),
  fSignalTypeList(),
    fMCHeader(0),
    fEvtHeader(0),
  fOutHeader(0),
    fFileHeader(0),
    fEvtHeaderIsNew(kFALSE),
   fEventTimeInMCHeader(kTRUE),
    fCurrentEntryNo(0),
    fTimeforEntryNo(0),
    fNoOfBGEntries(0),
  fCurrentEntry(),
    fEventTimeMin(0.),
    fEventTimeMax(0.),
    fEventTime(0.),
    fEventMeanTime(0.),
  fBeamTime(-1.),
  fGapTime(-1.),
    fTimeProb(0),
   fSignalBGN(),
   fSBRatiobyN(kFALSE),
  fSBRatiobyT(kFALSE),
  fNoOfEntries(-1),
  IsInitialized(kFALSE) 
{
    fRootFile = new TFile(RootFileName.Data());

  if ( signalId == 0 ) {
    SetBackgroundFile(RootFileName);
  }
  else {
    SetSignalFile(RootFileName,signalId);
  }
    fRootManager = FairRootManager::Instance();
  // fBackgroundFile =  new TFile(name);
  // if (fBackgroundFile->IsZombie()) {
  //   fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Background file  %s ", name.Data());
  // } else {
  //   fBackgroundChain = new TChain("cbmsim", "/cbmroot");
  //   fBackgroundChain->AddFile(name.Data());
  // }
}

FairMixedSource::~FairMixedSource()
{
}
Bool_t FairMixedSource::Init()
{
  fOutHeader = new FairEventHeader();
  LOG(INFO) << "fSBRatiobyN = " << (fSBRatiobyN?"true":"false") << " / fSBRatiobyT = " << (fSBRatiobyT?"true":"false") << FairLogger::endl;

  //  LOG(INFO) << "*********** CHAIN HAS " << fBackgroundChain->GetEntries() << " entries" << FairLogger::endl;
  if(IsInitialized){
    fLogger->Info(MESSAGE_ORIGIN, "FairMixedSource already initialized");
    return kTRUE;
  }
  if (!fBackgroundChain ) {
    fBackgroundChain = new TChain("cbmsim", "/cbmroot");
    fLogger->Info(MESSAGE_ORIGIN, "FairMixedSource::Init() chain created");
  }

    fBackgroundChain->Add( fRootFile->GetName() );
    LOG(INFO) << "*********** CHAIN HAS " << fBackgroundChain->GetEntries() << " entries" << FairLogger::endl;
    
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
                
                FairRootManager::Instance()->AddBranchToList(ObjName.Data());
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
        fBackgroundChain->Add( (*iter) );
        
        // Close the temporarly file and restore the gFile pointer.
        inputFile->Close();
        gFile = temp;

    }
    fNoOfEntries = fBackgroundChain->GetEntries();

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
    
    fBackgroundChain->GetEntry(0);
    if ( fEvtHeader ) {
      fOutHeader->SetRunId      (fEvtHeader->GetRunId());
    }
    if ( fMCHeader ) {
      fOutHeader->SetRunId      (fMCHeader->GetRunID());
    }


    fLogger->Info(MESSAGE_ORIGIN, "Entries in this Source %i------------",  fNoOfEntries);
    return kTRUE;

  
}
Int_t FairMixedSource::ReadEvent(UInt_t i)
{
  SetEventTime();

  Double_t SBratio=gRandom->Uniform(0,1);
  Bool_t GetASignal=kFALSE;

  if(fSBRatiobyN || fSBRatiobyT ) {
    std::map<UInt_t, Double_t>::const_iterator iterN;
    Double_t ratio=0;
    if(fCurrentEntryNo==0) {
      for(iterN = fSignalBGN.begin(); iterN != fSignalBGN.end(); iterN++) {
        ratio+=iterN->second;
        fSignalBGN[iterN->first]=ratio;
        fLogger->Debug(MESSAGE_ORIGIN,"--------------Set signal no. %i  weight  %f   ", iterN->first, ratio);
      }
    }
    ratio=0;
    for(iterN = fSignalBGN.begin(); iterN != fSignalBGN.end(); iterN++) {
      ratio=iterN->second;
      fLogger->Debug(MESSAGE_ORIGIN,"---Check signal no. %i  SBratio %f  :  ratio %f ", iterN->first , SBratio, ratio);
      if(SBratio <=ratio) {
        TChain* chain = fSignalTypeList[iterN->first];
        UInt_t entry = fCurrentEntry[iterN->first];
        chain->GetEntry(entry);
        fOutHeader->SetMCEntryNumber(entry);
        fOutHeader->SetInputFileId(iterN->first);
        fOutHeader->SetEventTime(GetEventTime());
        GetASignal=kTRUE;
        fCurrentEntry[iterN->first]=entry+1;
        fLogger->Debug(MESSAGE_ORIGIN,"---Get entry No. %i from signal chain number --- %i --- ",entry, iterN->first);
        break;
      }
    }
    if(!GetASignal) {
      UInt_t entry = fCurrentEntry[0];
      fBackgroundChain->GetEntry(entry);
      fOutHeader->SetMCEntryNumber(entry);
      fOutHeader->SetInputFileId(0); //Background files has always 0 as Id
      fOutHeader->SetEventTime(GetEventTime());
      fCurrentEntry[0]=entry+1;
      fLogger->Debug(MESSAGE_ORIGIN,"---Get entry from background chain  --- ");
    }
    
  }

  fCurrentEntryNo=i;
  fOutHeader->SetEventTime(GetEventTime());
  fLogger->Debug(MESSAGE_ORIGIN,"--Event number --- %i  with time ----%f",fCurrentEntryNo, GetEventTime());

  return 0;
}
void FairMixedSource::Close()
{
}
void FairMixedSource::Reset()
{
}

//_____________________________________________________________________________
void FairMixedSource::FillEventHeader(FairEventHeader* feh) 
{
  feh->SetEventTime    (fOutHeader->GetEventTime());
  feh->SetMCEntryNumber(fOutHeader->GetMCEntryNumber());
  feh->SetInputFileId  (fOutHeader->GetInputFileId());
  feh->SetRunId        (fOutHeader->GetRunId());
  LOG(DEBUG) << "FairMixedSource::FillEventHeader() Event " << fCurrentEntryNo << " at " << feh->GetEventTime() << " -> Run id = " << fOutHeader->GetRunId() << " event#" << feh->GetMCEntryNumber() << " from file#" << fOutHeader->GetInputFileId() << FairLogger::endl;
  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairMixedSource::CompareBranchList(TFile* fileHandle, TString inputLevel)
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

//_____________________________________________________________________________
void FairMixedSource::SetSignalFile(TString name, UInt_t identifier )
{
  TFile* SignalInFile = new TFile(name.Data());
  if (SignalInFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Signal file");
  } else {
    /** Set a signal file of certain type (identifier) if already exist add the file to the chain*/
    if(fSignalTypeList[identifier]==0) {
      TChain* chain = new TChain("cbmsim", "/cbmroot");
      fSignalTypeList[identifier]=chain;
      fCurrentEntry[identifier]= 0;
     fNoOfSignals++;
      fActualSignalIdentifier= identifier;
      chain->AddFile(name.Data());
    } else {
      TChain* CurrentChain=fSignalTypeList[identifier];
      CurrentChain->AddFile(name.Data());
      TObjArray* fileElements=CurrentChain->GetListOfFiles();
    }

  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMixedSource::AddSignalFile(TString name, UInt_t identifier )
{
  SetSignalFile(name, identifier);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TChain* FairMixedSource::GetSignalChainNo(UInt_t i)
{
  if(i<<fNoOfSignals) {
    return fSignalTypeList[i];
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "Error signal identifier %i does not exist ", i);
    return 0;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMixedSource::SetBackgroundFile(TString name)
{
  fCurrentEntry[0]= 0;
  if (name.IsNull() ) {
    fLogger->Info(MESSAGE_ORIGIN, "No background file defined.");
  }
  fRootFile =  new TFile(name);
  if (fRootFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Background file  %s ", name.Data());
  }
}
//_____________________________________________________________________________


//_____________________________________________________________________________
void FairMixedSource::AddBackgroundFile(TString name)
{
  if (name.IsNull() ) {
    fLogger->Info(MESSAGE_ORIGIN, "No background file defined.");
  }
  TFile* BGFile =  new TFile(name);
  if (BGFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Background file  %s ", name.Data());
  } else {
    if(fBackgroundChain!=0) {
      fBackgroundChain->AddFile(name.Data());
      TObjArray* fileElements=fBackgroundChain->GetListOfFiles();
    } else {
      fLogger->Fatal(MESSAGE_ORIGIN, "Use SetBackGroundFile first, then add files to background");
    }

  }

}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairMixedSource::OpenBackgroundChain()
{
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
  TString chainName = "BGInChain";
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

  gROOT->GetListOfBrowsables()->Add(fCbmroot);
  fListFolder->Add( fCbmroot );
  return kTRUE;

}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairMixedSource::OpenSignalChain()
{
  std::map<UInt_t, TChain*>::const_iterator iter;
  for(iter = fSignalTypeList.begin(); iter != fSignalTypeList.end(); iter++) {
    TChain* currentChain=iter->second;
    // cout << "Signal chain is : " << currentChain->GetName()<< endl;
    //   currentChain->Dump();
    TFile* ChainFirstFile = currentChain->GetFile();
    //cout << "First file in signal chain is : " << ChainFirstFile << endl;
    // Check if the branchlist is the same as for the first input file.
    Bool_t isOk = CompareBranchList(ChainFirstFile,"BGInChain");
    if ( !isOk ) {
      fLogger->Fatal(MESSAGE_ORIGIN, "Branch structure of the signal chain is different than the back ground one");
    }
  }
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairMixedSource::GetObject(const char* ObjName, const char* ObjType) {

  if ( ObjType == "GetListOfFolders" ) {
    return GetListOfFolders();
  }

  TObject* temp = new TObject();
  return temp;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t   FairMixedSource::ActivateObject(TObject** obj, const char* BrName) {
  fBackgroundChain->SetBranchStatus(BrName,1);
  fBackgroundChain->SetBranchAddress(BrName,obj);

  std::map<UInt_t, TChain*>::const_iterator iter;
  Int_t no=0;
  for(iter = fSignalTypeList.begin(); iter != fSignalTypeList.end(); iter++) {
    TChain* currentChain=iter->second;
    fLogger->Debug2(MESSAGE_ORIGIN, "Set the Branch address for signal file number %i  and  branch %s ", no++ , BrName);
    currentChain->SetBranchStatus(BrName,1);
    currentChain->SetBranchAddress(BrName,obj);
  }

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairMixedSource::ReadBKEvent(UInt_t i)
{
  if(0==i) {
    Int_t totEnt = fBackgroundChain->GetEntries();
    fLogger->Info(MESSAGE_ORIGIN,"The number of entries in background chain is %i",totEnt);
  }
  fBackgroundChain->GetEntry(i);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairMixedSource::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
  fSBRatiobyN=kTRUE;
  if(fSBRatiobyT) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Signal rate already set by TIME!!");
  }
  Double_t value=1.0/background;
  if(background!=0) {
    fSignalBGN[Signalid]=value;
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN, "Background cannot be Zero when setting the signal rate!!");
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairMixedSource::BGWindowWidthTime(Double_t background, UInt_t Signalid)
{
  fSBRatiobyT=kTRUE;
  if(fSBRatiobyN) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Signal rate already set by NUMBER!!");
  }
  if(fEventTimeInMCHeader) {
    fLogger->Fatal(MESSAGE_ORIGIN, "You have to Set the Event mean time before using SetSignalRateTime!");
  }
  if(fEventMeanTime==0) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Event mean time cannot be zero when using signal rate with time ");
  }
  /**convert to number of event by dividing by the mean time */
  Double_t value=fEventMeanTime/background;
  if(background!=0) {
    fSignalBGN[Signalid]=value;
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN, "Background cannot be Zero when setting the signal rate!!");
  }
  
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  FairMixedSource::CheckMaxEventNo(Int_t EvtEnd)
{
  Int_t MaxEventNo=0;
  if(EvtEnd!=0) {
    MaxEventNo=EvtEnd;
  }
  Int_t localMax=0;
  Int_t MaxBG=fBackgroundChain->GetEntries();
  Int_t MaxS=0;
  Double_t ratio=0.;
  std::map<UInt_t, Double_t>::const_iterator iterN;
  for(iterN = fSignalBGN.begin(); iterN != fSignalBGN.end(); iterN++) {
    TChain* chain = fSignalTypeList[iterN->first];
    MaxS=chain->GetEntries();
    fLogger->Info(MESSAGE_ORIGIN, "Signal chain  No %i  has  :  %i  entries ", iterN->first, MaxS);
    ratio=iterN->second;
    if(floor(MaxS/ratio) > MaxBG) {
      localMax=MaxBG+(Int_t)floor(MaxBG*ratio);
      fLogger->Warning(MESSAGE_ORIGIN, "No of Event in Background chain is not enough for all signals in chain  %i ", iterN->first);
    } else {
      localMax=(Int_t)floor(MaxS/ratio);
      fLogger->Warning(MESSAGE_ORIGIN, "No of Event in signal chain %i is not enough, the maximum event number will be reduced to : %i ", iterN->first,localMax );
    }
    if(MaxEventNo==0 || MaxEventNo > localMax) {
      MaxEventNo=localMax;
    }
  }
  fLogger->Info(MESSAGE_ORIGIN, "Maximum No of Event will be set to :  %i ", MaxEventNo);
  return MaxEventNo;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairMixedSource::SetEventMeanTime(Double_t mean)
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
void FairMixedSource::SetEventTimeInterval(Double_t min, Double_t max)
{
  fEventTimeMin=min;
  fEventTimeMax=max;
  fEventMeanTime=(fEventTimeMin+fEventTimeMax)/2;
  fEventTimeInMCHeader=kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMixedSource::SetBeamTime(Double_t beamTime, Double_t gapTime)
{
  fBeamTime = beamTime;
  fGapTime = gapTime;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairMixedSource::SetEventTime()
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
Double_t FairMixedSource::GetDeltaEventTime()
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
Double_t FairMixedSource::GetEventTime()
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

void FairMixedSource::ReadBranchEvent(const char* BrName)
{
  /**fill the object with content if the other branches in this tree entry were already read**/
  if(fEvtHeader == 0) { return; } //No event header, Reading will start later
  TChain* chain = fSignalTypeList[fEvtHeader->GetInputFileId()];
  if(!chain) { return; }
  chain->FindBranch(BrName)->GetEntry(fEvtHeader->GetMCEntryNumber());
  return;
}
//_____________________________________________________________________________

ClassImp(FairMixedSource)
