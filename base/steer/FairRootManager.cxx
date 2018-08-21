/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRootManager source file                 -----
// -----            Created 06/01/04  by M. Al-Turany/D. Bertini       -----
// -------------------------------------------------------------------------

// Class FairRootManager
// ------------------
// Class that takes care of Root IO.
#include "FairRootManager.h"

#include "FairEventHeader.h"            // for FairEventHeader
#include "FairFileHeader.h"             // for FairFileHeader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairLink.h"                   // for FairLink
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMonitor.h"                // for FairMonitor
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairRun.h"                    // for FairRun
#include "FairTSBufferFunctional.h"     // for FairTSBufferFunctional, etc
#include "FairWriteoutBuffer.h"         // for FairWriteoutBuffer
#include "FairLinkManager.h"            // for FairLinkManager
#include <iosfwd>                       // for ostream
#include "TArrayI.h"                    // for TArrayI
#include "TBranch.h"                    // for TBranch
#include "TChainElement.h"              // for TChainElement
#include "TClass.h"                     // for TClass
#include "TClonesArray.h"               // for TClonesArray
#include "TCollection.h"                // for TCollection, TIter
#include "TF1.h"                        // for TF1
#include "TFolder.h"                    // for TFolder
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TIterator.h"                  // for TIterator
#include "TList.h"                      // for TList
#include "TMath.h"                      // for floor
#include "TNamed.h"                     // for TNamed
#include "TObjArray.h"                  // for TObjArray
#include "TObjString.h"                 // for TObjString
#include "TROOT.h"                      // for TROOT, gROOT
#include "TRandom.h"                    // for TRandom, gRandom
#include "TTree.h"                      // for TTree
#include "TRefArray.h"                  // for TRefArray
#include "TMCAutoLock.h"

#include "FairRootFileSink.h"           // to enable GetOutFile()

#include <stdlib.h>                     // for exit
#include <string.h>                     // for NULL, strcmp
#include <algorithm>                    // for find
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <list>                         // for _List_iterator, list, etc
#include <map>                          // for map, _Rb_tree_iterator, etc
#include <set>                          // for set, set<>::iterator
#include <utility>                      // for pair
#include <vector>                       // for vector
#include <type_traits>
#include <cassert>

using std::flush;
using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;
using std::set;

namespace {
  // Define mutexes per operation which modify shared data
  TMCMutex createMutex = TMCMUTEX_INITIALIZER;
  TMCMutex deleteMutex = TMCMUTEX_INITIALIZER;
}

//_____________________________________________________________________________
Int_t   FairRootManager::fgCounter = 0;

//_____________________________________________________________________________
FairRootManager* FairRootManager::Instance()
{
// Returns singleton instance.
// ---
    static thread_local FairRootManager instance;
    return &instance;
}

//_____________________________________________________________________________
FairRootManager::FairRootManager()
  : TObject(),
    fOldEntryNr(-1),
    fOutFolder(0),
    fRootFolder(0),
    fCurrentTime(0),
    fSink(NULL),
    fObj2(new TObject*[1000]),
    fNObj(-1),
    fMap(),
    fBranchSeqId(0),
    fBranchNameList(new TList()),
    fMCTrackBranchId(-1),
    fTimeBasedBranchNameList(new TList()),
    fActiveContainer(),
    fTSBufferMap(),
    fWriteoutBufferMap(),
    fInputBranchMap(),
    fTimeStamps(kFALSE),
    fBranchPerMap(kFALSE),
    fBrPerMap(),
    fBrPerMapIter(),
    fCurrentEntryNo(0),
    fTimeforEntryNo(0),
    fFillLastData(kFALSE),
    fEntryNr(0),
    fListFolder(0),
    fSource(0),
    fSourceChain(new TChain(GetTreeName(), Form("/%s", GetFolderName()))),
    fSignalChainList(),
    fEventHeader(new FairEventHeader()),
    fUseFairLinks(kFALSE),
    fFinishRun(kFALSE),
    fListOfBranchesFromInput(0),
    fListOfBranchesFromInputIter(0),
    fListOfNonTimebasedBranches(new TRefArray()),
    fListOfNonTimebasedBranchesIter(0),
    fId(0)
{
  LOG(debug) << "FairRootManager::FairRootManager: going to lock " << this;

  TMCAutoLock lk(&createMutex);

  // Set Id
  fId = fgCounter;

  // Increment counter
  ++fgCounter;

  lk.unlock();

  LOG(debug) << "Released lock and done FairRootManager::FairRootManager in "
    << fId << " " << this;
}

//_____________________________________________________________________________
FairRootManager::~FairRootManager()
{
//
  LOG(debug) << "Enter Destructor of FairRootManager";

  delete[] fObj2;
  fBranchNameList->Delete();
  delete fBranchNameList;
  LOG(debug) << "Leave Destructor of FairRootManager";
  delete fEventHeader;
  delete fSourceChain;

  // Global cleanup
  TMCAutoLock lk(&deleteMutex);

  LOG(debug) << "FairRootManager::~FairRootManager: going to lock "
    << fId << " " << this;

  --fgCounter;

  //
  lk.unlock();

  LOG(debug) << "Released lock and done FairRootManager::~FairRootManager in "
    << fId << " " << this;
}

//_____________________________________________________________________________
Bool_t FairRootManager::InitSource() {

  LOG(debug) << "Call the initialiazer for the FairSource in FairRootManager ";
  if ( fSource ) {
    Bool_t sourceInitBool = fSource->Init();
    fListOfBranchesFromInput=fSourceChain->GetListOfBranches();
    TObject *obj;
    if(fListOfBranchesFromInput){
      fListOfBranchesFromInputIter=fListOfBranchesFromInput->MakeIterator();
      while((obj=fListOfBranchesFromInputIter->Next())) {
         if((fTimeBasedBranchNameList->FindObject(obj->GetName()))==0)
         fListOfNonTimebasedBranches->Add(obj);
      }
    }
    LOG(debug) << "Source is intialized and the list of branches is created in FairRootManager ";
    fListOfNonTimebasedBranchesIter=fListOfNonTimebasedBranches->MakeIterator();
    return sourceInitBool;
  }
  return kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::InitSink() {
  if ( fSink ) {
    fSink->InitSink();
  }
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
template<typename T>
void FairRootManager::RegisterImpl(const char* name, const char *folderName, T* obj, Bool_t toFile)
{
/// a common implementation for Register
  FairMonitor::GetMonitor()->RecordRegister(name,folderName,toFile);

  // Security check. If the the name is equal the folder name there are problems with reading
  // back the data. Instead of the object inside the folder the RootManger will return a pointer
  // to the folder. To avoid such problems we check here if both strings are equal and stop the
  // execution with some error message if this is the case.
  if (strcmp (name, folderName) == 0 ) {
    LOG(fatal) << "The names for the object name "
               << name << " and the folder name "
               << folderName <<" are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the name or the folder name.";
  }

  if(toFile) { /**Write the Object to the Tree*/
    obj->SetName(name);
    if ( fSink )
      {
	fSink->RegisterImpl(name,folderName,obj);
      }
  }
  AddMemoryBranch(name, obj);
  AddBranchToList(name);

  if (toFile == kFALSE) {
    FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
  }
}

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name, const char* folderName , TNamed* obj, Bool_t toFile)
{
  RegisterImpl(name, folderName, obj, toFile);
}

//_____________________________________________________________________________
Int_t  FairRootManager::AddBranchToList(const char* name)
{
  if(fBranchNameList->FindObject(name)==0) {
    fBranchNameList->AddLast(new TObjString(name));
    // check if we are setting the MCTrack Branch
    if(strcmp(name, "MCTrack") == 0) {
      fMCTrackBranchId = fBranchSeqId;
    }
    fBranchSeqId++;
  }
  return fBranchSeqId;
}

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name,const char* foldername ,TCollection* obj, Bool_t toFile)
{
  RegisterImpl(name, foldername, obj, toFile);
}

//_____________________________________________________________________________
void FairRootManager::RegisterInputObject(const char* name, TObject* obj)
{
  AddMemoryBranch(name, obj);
  AddBranchToList(name);
}

//_____________________________________________________________________________
TClonesArray* FairRootManager::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{
  FairMonitor::GetMonitor()->RecordRegister(branchName,folderName,toFile);

  TClonesArray* outputArray;
  if (fActiveContainer.find(branchName) == fActiveContainer.end()) {
    fActiveContainer[branchName] = new TClonesArray(className);
    outputArray = fActiveContainer[branchName];
    Register(branchName, folderName, outputArray, toFile);
  }

  return fActiveContainer[branchName];
}

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetEmptyTClonesArray(TString branchName)
{
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {//if a TClonesArray is registered in the active container
    if (fActiveContainer[branchName] == 0) {                      //the address of the TClonesArray is still valid
      std::cout << "-E- FairRootManager::GetEmptyTClonesArray: Container deleted outside FairRootManager!" << std::endl;
    } else {
      fActiveContainer[branchName]->Delete();
    }
    return fActiveContainer[branchName];                        // return the container
  } else {
    std::cout << "-E- Branch: " << branchName << " not registered!" << std::endl;  // error if the branch is not registered
  }
  return 0;
}

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetTClonesArray(TString branchName)
{
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {
    return fActiveContainer[branchName]; // return the container
  } else {
    LOG(info) << "Branch: " << branchName.Data()
              << " not registered!" ;
  }
  // error if the branch is not registered
  return 0;
}

//_____________________________________________________________________________
TString FairRootManager::GetBranchName(Int_t id)
{
  /**Return the branch name from the id*/
  if(id < fBranchSeqId) {
    TObjString* ObjStr= static_cast<TObjString*>(fBranchNameList->At(id));
    return ObjStr->GetString();
  } else {
    TString NotFound("Branch not found");
    return NotFound;
  }
}

//_____________________________________________________________________________
Int_t FairRootManager::GetBranchId(TString const &BrName)
{
  /**Return the branch id from the name*/
  TObjString* ObjStr;
  Int_t Id=-1;
  for(Int_t t=0; t<fBranchNameList->GetEntries(); t++) {
    ObjStr= static_cast<TObjString*>(fBranchNameList->TList::At(t));
    if(BrName==ObjStr->GetString()) {
      Id=t;
      break;
    }
  }
  return Id;
}

//_____________________________________________________________________________
void FairRootManager::InitTSBuffer(TString branchName, BinaryFunctor* function)
{
  fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
}

//_____________________________________________________________________________
TClonesArray*  FairRootManager::GetData(TString branchName, BinaryFunctor* function, Double_t parameter)
{
  if (fTSBufferMap[branchName] == 0) {
    fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
  }
  fTSBufferMap[branchName]->SetStopFunction(function);
  return fTSBufferMap[branchName]->GetData(parameter);
}

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetData(TString branchName, BinaryFunctor* startFunction, Double_t startParameter, BinaryFunctor* stopFunction, Double_t stopParameter)
{
  if (fTSBufferMap[branchName] == 0) {
    fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), stopFunction, startFunction);
  }
  fTSBufferMap[branchName]->SetStopFunction(stopFunction);
  fTSBufferMap[branchName]->SetStartFunction(startFunction);
  return fTSBufferMap[branchName]->GetData(startParameter, stopParameter);
}

//_____________________________________________________________________________
void FairRootManager::TerminateTSBuffer(TString branchName)
{
  if (fTSBufferMap.count(branchName) > 0){
    fTSBufferMap[branchName]->Terminate();
  }
}

//_____________________________________________________________________________
void FairRootManager::TerminateAllTSBuffer()
{
  for (std::map<TString, FairTSBufferFunctional*>::iterator iter = fTSBufferMap.begin(); iter != fTSBufferMap.end(); iter++)
  {
    iter->second->Terminate();
  }
}

//_____________________________________________________________________________
Bool_t FairRootManager::AllDataProcessed()
{
  for(std::map<TString, FairTSBufferFunctional*>::iterator it = fTSBufferMap.begin(); it != fTSBufferMap.end(); it++) {
    if (it->second->AllDataProcessed() == kFALSE && it->second->TimeOut() == kFALSE) {
      return kFALSE;
    }
  }
  return kTRUE;
}

//_____________________________________________________________________________
void FairRootManager::Fill()
{
  if ( fSink ) fSink->Fill();
}

//_____________________________________________________________________________
void FairRootManager::LastFill()
{
  FairMonitor::GetMonitor()->StoreHistograms();
  if (fFillLastData) {
      if ( fSink ) fSink->Fill();
  }
}

//_____________________________________________________________________________
Int_t FairRootManager::Write(const char*, Int_t, Int_t)
{
  /** Writes the tree in the file.*/

  LOG(debug) << "FairRootManager::Write "  << this;

  if ( fSink ) return (fSink->Write());

  return 0;
}

//_____________________________________________________________________________
void FairRootManager:: WriteGeometry()
{
  /** Writes the geometry in the current output file.*/
  if ( fSink ) fSink->WriteGeometry();
}

//_____________________________________________________________________________
void FairRootManager::CreateGeometryFile(const char* geofile)
{
  /** Writes the geometry in a separate file.
   *  This is only to have a file which can be read without the
   *  framework. The geomanager used by the framework is still
   *  stored in the parameter file or database
  */
  TFile* oldfile=gFile;
  TFile* file=TFile::Open(geofile,"RECREATE");
  file->cd();
  gGeoManager->Write();
  file->Close();
  file->Delete();
  gFile=oldfile;
}

//_____________________________________________________________________________
void FairRootManager:: WriteFolder()
{
  if ( fSink ) {
    fSink->WriteFolder();
    fSink->WriteObject(fBranchNameList,          "BranchList",          TObject::kSingleKey);
    fSink->WriteObject(fTimeBasedBranchNameList, "TimeBasedBranchList", TObject::kSingleKey);
  }
}

//_____________________________________________________________________________
Int_t  FairRootManager::ReadEvent(Int_t i)
{
  if ( !fSource ) return 0;

  fSource->Reset();

  SetEntryNr(i);

  if ( !fSource ) {
    LOG(fatal) << "No Source available";
    return -1;
  }

  fCurrentEntryNo=i;

  Int_t readEventResult = fSource->ReadEvent(i);

  fSource->FillEventHeader(fEventHeader);
  fCurrentTime = fEventHeader->GetEventTime();

  LOG(debug) << "--Event number --- "
             << fCurrentEntryNo << " with time ---- "
             << fCurrentTime;

  return readEventResult;
}

//_____________________________________________________________________________
void FairRootManager::ReadBranchEvent(const char* BrName, Int_t entry)
{
  if ( !fSource) return;
  fSource->Reset();
  SetEntryNr(entry);

  fSource->ReadBranchEvent(BrName, entry);
  fSource->FillEventHeader(fEventHeader);
  fCurrentTime = fEventHeader->GetEventTime();
}

//_____________________________________________________________________________
Int_t FairRootManager::GetRunId()
{
  if ( fSource ) {
    fSource->FillEventHeader(fEventHeader);
    return fEventHeader->GetRunId();
  }
  return -1;
}

//_____________________________________________________________________________
void FairRootManager::ReadBranchEvent(const char* BrName)
{
  if ( fSource ) {
    fSource->ReadBranchEvent(BrName);
    fSource->FillEventHeader(fEventHeader);
    fCurrentTime = fEventHeader->GetEventTime();
  }
}

//_____________________________________________________________________________
Int_t FairRootManager::ReadNonTimeBasedEventFromBranches(Int_t Entry)
{
  if ( fSource ){
    TObject *Obj;
    fListOfNonTimebasedBranchesIter->Reset();
    while ( (Obj=fListOfNonTimebasedBranchesIter->Next())) {
        fSource->ReadBranchEvent(Obj->GetName(),Entry);
        fSource->FillEventHeader(fEventHeader);
        fCurrentTime = fEventHeader->GetEventTime();
    }
  } else{
    return 0;
  }
  return 1;
}

//_____________________________________________________________________________
Bool_t FairRootManager::ReadNextEvent(Double_t)
{
  Bool_t readentry=kFALSE;
  ///TODO
  return readentry;
}

//_____________________________________________________________________________
TObject* FairRootManager::GetObject(const char* BrName)
{
  fReqBrNames.emplace_back(BrName);
  /**Get Data object by name*/
  TObject* Obj =NULL;
  LOG(debug2) << " Try to find if the object "
              << BrName << " is already activated by another task or call";
  /**Try to find the object in the folder structure, object already activated by other task or call*/
  if(fOutFolder) {
    Obj = fOutFolder->FindObjectAny(BrName);
    if (Obj) {
      LOG(debug2) <<"Object "
                  << BrName << " was already activated by another task";
    }
  }
  /**if the object does not exist then it could be a memory branch */
  if(!Obj) {
    LOG(debug2) << "Try to find if the object "
                << BrName << " is a memory branch";
    Obj=GetMemoryBranch(BrName);
    if (Obj) {
      LOG(debug2) << "Object "
                  << BrName << " is a memory branch";
    }
  }
  /**if the object does not exist then look in the input tree */
  if(fRootFolder && !Obj) {
    /** there is an input tree and the object was not in memory */
    LOG(debug2) << "Object "
                << BrName << " is not a memory branch and not yet activated, try the Input Tree (Chain)";
    Obj=fRootFolder->FindObjectAny(BrName);
    Obj=ActivateBranch(BrName);
  }
  if(!Obj) {
    Obj=ActivateBranch(BrName);
  }
  if ( Obj!=NULL )
    FairMonitor::GetMonitor()->RecordGetting(BrName);
  return Obj;
}

//_____________________________________________________________________________
TObject* FairRootManager::GetCloneOfLinkData(const FairLink link)
{
  TObject* result = 0;

//  std::cout << "GetCloneOfLinkData: Link " << link << std::endl;
  Int_t fileId = link.GetFile();
  Int_t entryNr = link.GetEntry();
  Int_t type = link.GetType();
  Int_t index = link.GetIndex();

  Int_t oldEntryNr = GetEntryNr();

//  std::cout << "OldEntryNr: " << GetEntryNr();

//  std::cout << "GetLinkData: " << link << std::endl;

  TTree* dataTree;          //get the correct Tree
  if (fileId < 0) {
    dataTree = GetInTree();
  } else if (fileId == 0) {
    dataTree = GetInChain();
  } else {
    dataTree = GetSignalChainNo(fileId);
  }

  if (dataTree == 0) {
    dataTree = GetInTree();
  }

  if (type < 0) {
    return 0;
  }

  TBranch* dataBranch = 0;

//  std::cout << "DataType: " << GetBranchName(type) << std::endl;

  if (fileId < 0 && fInputBranchMap[type] != 0) {
    dataBranch = fInputBranchMap[type];
  } else if (fileId < 0) {
    fInputBranchMap[type] = dataTree->GetBranch(GetBranchName(type));
    dataBranch = fInputBranchMap[type];
  } else {
    dataBranch = dataTree->GetBranch(GetBranchName(type));
  }

  if (dataBranch == 0) {
    return 0;
  }

  if (entryNr > -1) {         //get the right entry (if entryNr < 0 then the current entry is taken
    if (entryNr < dataBranch->GetEntries()) {
      dataBranch->GetEntry(entryNr);
    } else {
      return 0;
    }
  } else {        //the link entry nr is negative --> take the actual one

//    std::cout << "EntryNr: " << GetEntryNr() << std::endl;
//    dataBranch->GetEntry(GetEntryNr());
  }

  if (index < 0) {                //if index is -1 then this is not a TClonesArray so only the Object is returned
    result = GetObject(GetBranchName(type))->Clone();
  } else {
    TClonesArray* dataArray = static_cast<TClonesArray*>(GetObject(GetBranchName(type)));

//    std::cout << "dataArray size: " << dataArray->GetEntriesFast() << std::endl;
    if (index < dataArray->GetEntriesFast()) {
//      std::cout << "DataArray at index " << index << " has Link: " << ((FairMultiLinkedData*)dataArray->At(index))->GetNLinks() << std::cout;
      result = dataArray->At(index)->Clone();
//      std::cout << "Result: " << *((FairMultiLinkedData*)result) << std::endl;
    }
  }
  if (entryNr > -1) {
    dataBranch->GetEntry(oldEntryNr);  //reset the dataBranch to the original entry
  }
  return result;
}

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetCloneOfTClonesArray(const FairLink link)
{
  TClonesArray* result = 0;

  //  std::cout << "GetCloneOfLinkData: Link " << link << std::endl;
  Int_t fileId = link.GetFile();
  Int_t entryNr = link.GetEntry();
  Int_t type = link.GetType();
  Int_t index = link.GetIndex();

  Int_t oldEntryNr = GetEntryNr();

  //  std::cout << "OldEntryNr: " << GetEntryNr();

  //  std::cout << "GetLinkData: " << link << std::endl;

  TTree* dataTree;          //get the correct Tree
  if (fileId < 0) {
    dataTree = GetInTree();
  } else if (fileId == 0) {
    dataTree = GetInChain();
  } else {
    dataTree = GetSignalChainNo(fileId);
  }

  if (dataTree == 0) {
    dataTree = GetInTree();
  }

  if (type < 0) {
    return 0;
  }

  TBranch* dataBranch = 0;

  //  std::cout << "DataType: " << GetBranchName(type) << std::endl;

  if (fileId < 0 && fInputBranchMap[type] != 0) {
    dataBranch = fInputBranchMap[type];
  } else if (fileId < 0) {
    fInputBranchMap[type] = dataTree->GetBranch(GetBranchName(type));
    dataBranch = fInputBranchMap[type];
  } else {
    dataBranch = dataTree->GetBranch(GetBranchName(type));
  }

  if (dataBranch == 0) {
    return 0;
  }

  if (entryNr > -1) { //get the right entry (if entryNr < 0 then the current entry is taken
    if (entryNr < dataBranch->GetEntries()) {
      dataBranch->GetEntry(entryNr);
    } else {
      return 0;
    }
  } else {        //the link entry nr is negative --> take the actual one

    //    std::cout << "EntryNr: " << GetEntryNr() << std::endl;
    //    dataBranch->GetEntry(GetEntryNr());
  }

  if (index < 0) { //if index is -1 then this is not a TClonesArray so only the Object is returned
    result = 0;
  } else {
    result = static_cast<TClonesArray*>( GetObject(GetBranchName(type))->Clone() );
  }
  if (entryNr > -1) {
    dataBranch->GetEntry(oldEntryNr); //reset the dataBranch to the original entry
  }
  return result;

}

//_____________________________________________________________________________
Int_t FairRootManager::CheckBranch(const char* BrName)
{
  /**The first time this method is called the map is generated and then used*/
  if(!fBranchPerMap) {
    CreatePerMap();
    return CheckBranchSt(BrName);
  } else {
    fBrPerMapIter=fBrPerMap.find(BrName);
    if(fBrPerMapIter!=fBrPerMap.end()) {
      return fBrPerMapIter->second;
    } else {
      return 0;
    }
  }
}

//_____________________________________________________________________________
void  FairRootManager::SetBranchNameList(TList* list)
{
  if ( list == NULL ) return;
  // otherwise clear existing and add via the standard interface
  fBranchNameList->Clear();
  fMCTrackBranchId = -1;
  for (Int_t t=0; t<list->GetEntries(); t++) {
    AddBranchToList(static_cast<TObjString*>(list->At(t))->GetString().Data());
  }
}

//_____________________________________________________________________________
void FairRootManager::SetInChain(TChain* tempChain, Int_t ident)
{
  if ( ident <= 0 )
    fSourceChain = tempChain;
  else
    fSignalChainList[ident] = tempChain;
}

//_____________________________________________________________________________
Double_t FairRootManager::GetEventTime() {
  return fCurrentTime;
}

//_____________________________________________________________________________
void FairRootManager::UpdateBranches() {
  for ( Int_t iobj = 0 ; iobj <= fNObj ; iobj++ ) {
    if ( fObj2[iobj] ) {
      LOG(info) << "FairRootManager::UpdateBranches \"" << fObj2[iobj]->GetName()
                << "\" (\"" << fObj2[iobj]->GetTitle() << "\")";
      TString tempBranchName = fObj2[iobj]->GetName();
      fSource->ActivateObject(&fObj2[fNObj],tempBranchName.Data());
    }
  }

}

//_____________________________________________________________________________
/** Private functions*/
//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairRootManager::ActivateBranch(const char* BrName)
{
  /** Set the branch address for a given branch name and return a TObject pointer,
   the user have to cast this pointer to the right type.
   The function has been revisited ! Now it test if in the task init() mutilple
   calls to activate branch is done , and then just forward the pointer.
   <DB>
   **/
  fNObj++;
  fObj2[fNObj]  =  GetMemoryBranch ( BrName );
  if ( fObj2[fNObj]   ) {
    return  fObj2[fNObj];
  }
  /**try to find the object decribing the branch in the folder structure in file*/
  LOG(debug) << "Try to find an object "
              << BrName << " describing the branch in the folder structure in file";
  if ( fListFolder ) {
    for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
      TFolder* fold = static_cast<TFolder*>(fListFolder->At(i));
      fObj2[fNObj] = fold->FindObjectAny(BrName);
      if (fObj2[fNObj] ) {
        LOG(info) << "Object "
                  << BrName << " describing the branch in the folder structure was found";
        break;
      }
    }
  }

  if(!fObj2[fNObj]) {
    /** if we do not find an object corresponding to the branch in the folder structure
    *  then we have no idea about what type of object is this and we cannot set the branch address
    */
    LOG(info) << " Branch: " << BrName << " not found in Tree.";
    //Fatal(" No Branch in the tree", BrName );
    return 0;
  } else {
    if ( fSource )
      fSource->ActivateObject(&fObj2[fNObj],BrName);
  }

  AddMemoryBranch( BrName , fObj2[fNObj] );
  return  fObj2[fNObj];
}

//_____________________________________________________________________________
void  FairRootManager::AddMemoryBranch( const char* fName, TObject* pObj )
{
  /**branch will be available ionly in Memory, will not be written to disk */
  map < TString, TObject*>::iterator p;
  TString BrName=fName;
  p=fMap.find(BrName);
  if(p!=fMap.end()) {
  } else {
    fMap.insert(pair<TString, TObject*> (BrName, pObj));
  }
}

//_____________________________________________________________________________
Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
 // cout <<"FairRootManager::CheckBranchSt  :  " << BrName << endl;
  Int_t returnvalue=0;
  TObject* Obj1 =NULL;

  if(fListFolder==0){
    fListFolder = new TObjArray(16);
  }

  //cout <<"FairRootManager::CheckBranchSt  :  " <<fRootFolder << endl;
  if (fRootFolder) {
    fListFolder->Add(fRootFolder);
    Obj1 = fRootFolder->FindObjectAny(BrName);
  }
  if(fOutFolder && !Obj1) {
    fListFolder->Add(fOutFolder);
    Obj1 = fOutFolder->FindObjectAny(BrName);  //Branch in output folder
  }
  if(!Obj1) {
    for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
     // cout << "Search in Folder: " << i << "  " <<  fListFolder->At(i) << endl;
      TFolder* fold = dynamic_cast<TFolder*>(fListFolder->At(i));
      if(fold!=0) {
        Obj1= fold->FindObjectAny(BrName);
      }
      if (Obj1) {
        break;
      }
    }
  }
  TObject* Obj2 =NULL;
  Obj2=GetMemoryBranch(BrName);  // Branch in Memory
  if (Obj1!=0) {
    returnvalue=1;
  } else if(Obj2!=0) {
    returnvalue=2;
  } else {
    returnvalue= 0;
  }

  /**  1 : Branch is Persistance
       2 : Memory Branch
       0 : Branch does not exist
  */
  return returnvalue;
}

//_____________________________________________________________________________
void  FairRootManager::CreatePerMap()
{
  // cout << " FairRootManager::CreatePerMap() " << endl;
  fBranchPerMap=kTRUE;
  for (Int_t i=0; i<fBranchSeqId; i++) {
    TObjString* name= static_cast<TObjString*>(fBranchNameList->At(i));
    // cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
    TString BrName=name->GetString();
    fBrPerMap.insert(pair<TString, Int_t> (BrName, CheckBranchSt(BrName.Data())));
  }

}

//_____________________________________________________________________________
TObject*  FairRootManager::GetMemoryBranch( const char* fName )
{

  //return fMap[BrName];
  TString BrName=fName;
  map < TString, TObject*>::iterator p;
  p=fMap.find(BrName);

  if(p!=fMap.end()) {
    return p->second;
  } else {
    return 0;
  }
}

//_____________________________________________________________________________
void FairRootManager::WriteFileHeader(FairFileHeader* f)
{
  if ( fSink ) fSink->WriteObject(f,"FileHeader", TObject::kSingleKey);
}

//_____________________________________________________________________________
Int_t  FairRootManager::CheckMaxEventNo(Int_t EvtEnd)
{
  if ( fSource )
    return fSource->CheckMaxEventNo(EvtEnd);
  return 0;
}

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManager::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
  if (fWriteoutBufferMap[branchName] == 0) {
    fWriteoutBufferMap[branchName] = buffer;
  } else {
    LOG(warn) << "Branch "
                 << branchName.Data()
                 << " is already registered in WriteoutBufferMap";
    delete buffer;
  }

  return fWriteoutBufferMap[branchName];
}

//_____________________________________________________________________________
void FairRootManager::UpdateListOfTimebasedBranches()
{
  /**
   * Add branches that are time based to the proper list
   */

  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {

    if(iter->second->IsBufferingActivated()) fTimeBasedBranchNameList->AddLast(new TObjString(iter->first.Data()));

  }

}

//_____________________________________________________________________________
void FairRootManager::SetTimeBasedBranchNameList(TList *list)
{
  /**
   * Replace the list
   */

  if(list!=0){
    fTimeBasedBranchNameList->Delete();
    delete fTimeBasedBranchNameList;
    fTimeBasedBranchNameList=list;
  }

}

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManager::GetWriteoutBuffer(TString branchName)
{
  if (fWriteoutBufferMap.count(branchName) > 0) {
    return fWriteoutBufferMap[branchName];
  } else {
    return 0;
  }
}

//_____________________________________________________________________________
void FairRootManager::StoreWriteoutBufferData(Double_t eventTime)
{
  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {
    iter->second->WriteOutData(eventTime);
  }
}

//_____________________________________________________________________________
void FairRootManager::StoreAllWriteoutBufferData()
{
  Bool_t dataInBuffer = kFALSE;
  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {
    if (iter->second->GetNData() > 0) {
      dataInBuffer = kTRUE;
    }
    iter->second->WriteOutAllData();
  }
  fFillLastData = dataInBuffer;
}

//_____________________________________________________________________________
void FairRootManager::DeleteOldWriteoutBufferData()
{
  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {
    iter->second->DeleteOldData();
  }
}

//_____________________________________________________________________________
char* FairRootManager::GetTreeName()
{
  char* default_name = (char*)"cbmsim";
  char* workdir = getenv("VMCWORKDIR");
  if(NULL == workdir)
  {
      return default_name;
  }

  // Open file with output tree name
  FILE* file = fopen(Form("%s/config/rootmanager.dat",workdir), "r");
  // If file does not exist -> default
  if(NULL == file)
  {
      return default_name;
  }

  char str[100];
  while(NULL != fgets(str, 100, file))
  {
    if(TString(str).Contains("treename"))
    {
      char* treename = new char[100];
      if(1 == sscanf(str, "treename=%s", treename))
      {
        fclose(file);
        return treename;
      }
      delete [] treename;
    }
  }

  // Key "treename" was not found in file: return default
  fclose(file);
  return default_name;
}

//_____________________________________________________________________________
char* FairRootManager::GetFolderName()
{
  char* default_name = (char*)"cbmout";
  if(! FairRun::Instance()->IsAna())
  {
    default_name = (char*)"cbmroot";
  }
  char* workdir = getenv("VMCWORKDIR");
  if(NULL == workdir)
  {
      return default_name;
  }

  // Open file with output tree name
  FILE* file = fopen(Form("%s/config/rootmanager.dat",workdir), "r");
  // If file does not exist -> default
  if(NULL == file)
  {
      return default_name;
  }

  char str[100];
  while(NULL != fgets(str, 100, file))
  {
    if(TString(str).Contains("foldername"))
    {
      char* foldername = new char[100];
      if(1 == sscanf(str, "foldername=%s", foldername))
      {
        fclose(file);
        return foldername;
      }
      delete [] foldername;
    }
  }

  // Key "foldername" was not found in file: return default
  fclose(file);
  return default_name;
}

//_____________________________________________________________________________
void FairRootManager::EmitMemoryBranchWrongTypeWarning(const char* brname, const char *type1, const char *type2) const {
  LOG(warn) << "Trying to read from memory branch " << brname
               << " with wrong type " << type1
               << " (expexted: " << type2 << " )";
}

//_____________________________________________________________________________
void FairRootManager::UpdateFileName(TString& fileName)
{
  TString tid = "_t";
  tid += GetInstanceId();
  fileName.Insert(fileName.Index(".root"), tid);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TFile* FairRootManager::GetOutFile()
{
  LOG(WARNING) << "FairRootManager::GetOutFile() deprecated. Use separate file to store additional data.";
  auto sink = GetSink();
  assert(sink->GetSinkType() == kFILESINK);
  auto rootFileSink = static_cast<FairRootFileSink*>(sink);
  return rootFileSink->GetRootFile();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TTree* FairRootManager::GetOutTree()
{
  LOG(WARNING) << "FairRootManager::GetOutTree() deprecated. Use separate file to store additional data.";
  auto sink = GetSink();
  assert(sink->GetSinkType() == kFILESINK);
  auto rootFileSink = static_cast<FairRootFileSink*>(sink);
  return rootFileSink->GetOutTree();
}
//_____________________________________________________________________________

ClassImp(FairRootManager)
