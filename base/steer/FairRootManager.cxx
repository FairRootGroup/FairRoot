/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairRun.h"                    // for FairRun
#include "FairTSBufferFunctional.h"     // for FairTSBufferFunctional, etc
#include "FairWriteoutBuffer.h"         // for FairWriteoutBuffer
#include "FairLinkManager.h"			// for FairLinkManager
#include "Riosfwd.h"                    // for ostream
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

#include <stdlib.h>                     // for exit
#include <string.h>                     // for NULL, strcmp
#include <algorithm>                    // for find
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <list>                         // for _List_iterator, list, etc
#include <map>                          // for map, _Rb_tree_iterator, etc
#include <set>                          // for set, set<>::iterator
#include <utility>                      // for pair
#include <vector>                       // for vector

using std::flush;
using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;
using std::set;

TMCThreadLocal FairRootManager* FairRootManager::fgInstance = 0;
//_____________________________________________________________________________
FairRootManager* FairRootManager::Instance()
{
// Returns singleton instance.
// ---
  return fgInstance;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRootManager::FairRootManager()
  : TObject(),
    fOldEntryNr(-1),
    fCbmout(0),
    fCbmroot(0),
    fCurrentTime(0),
    fOutFile(NULL),
    fOutTree(NULL),
    fObj2(new TObject*[1000]),
    fNObj(-1),
    fMap(),
    fPtrTree(NULL),
    fCurrentEntries(0),
    fBranchSeqId(0),
    fBranchNameList(new TList()),
    fDataContainer(),
    fActiveContainer(),
    fTSBufferMap(),
    fWriteoutBufferMap(),
    fInputBranchMap(),
    fCompressData(kFALSE),
    fTimeStamps(kFALSE),
    fBranchPerMap(kFALSE),
    fBrPerMap(),
    fBrPerMapIter(),
    fFriendFileList(),
    fLogger(FairLogger::GetLogger()),
    fMixAllInputs(kFALSE),
    fMixedInput(kFALSE),
    fActualSignalIdentifier(0),
    fNoOfSignals(0),
    fSignalChainList(NULL),
    fBackgroundChain(NULL),
    fBackgroundFile(NULL),
    fSignalTypeList(),
    fEventTimeMin(0.),
    fEventTimeMax(0.),
    fEventTime(0.),
    fEventMeanTime(0.),
    fTimeProb(0),
    fMCHeader(0),
    fEvtHeader(0),
    fFileHeader(0),
    fSignalBGN(),
    fEventTimeInMCHeader(kTRUE),
    fSBRatiobyN(kFALSE),
    fSBRatiobyT(kFALSE),
    fCurrentEntryNo(0),
    fTimeforEntryNo(0),
    fNoOfBGEntries(0),
    fCurrentEntry(),
    fEvtHeaderIsNew(kFALSE),
    fFillLastData(kFALSE),
    fUseFairLinks(kFALSE), 
    fInitFairLinksOnce(kFALSE),
    fFairLinksBranchName("FairLinkBranch"),
    fEntryNr(0),
    fRootFileSource(0),
    fRootFileSourceSignal(0),
    fRootFileSourceBKG(0)
{
  if (fgInstance) {
    Fatal("FairRootManager", "Singleton instance already exists.");
    return;
  }
  fgInstance = this;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRootManager::~FairRootManager()
{
//
  fLogger->Debug(MESSAGE_ORIGIN,"Enter Destructor of FairRootManager");
  if(fOutTree) {
    delete fOutTree;
  }
  if(fOutFile) {
    fOutFile->cd();
    delete fOutFile;
  }
  //  fObj2->Delete();
  delete fObj2;
// if(fPtrTree)delete fPtrTree;
  fBranchNameList->Delete();
  delete fBranchNameList;
  fgInstance = 0;
  fLogger->Debug(MESSAGE_ORIGIN, "Leave Destructor of FairRootManager");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetSignalFile(TString name, UInt_t identifier )
{
  /**
   * Create a new source for signal
   */
    
    if(fSignalTypeList[identifier]==0) {
      /** The first file create a new source for signal*/
      fRootFileSourceSignal = new FairFileSource(&name, "SignalSource", identifier);
      /** we have to inialize it to check the file and get/ create the chain from the input tree(s)*/
      fRootFileSourceSignal->Init();
      fCurrentEntry[identifier]= 0;
      fNoOfSignals++;
      fActualSignalIdentifier= identifier;
      fSignalTypeList[identifier]=fRootFileSourceSignal;
      fFileHeader->AddInputFile(fRootFileSourceSignal->GetInFile(), identifier, 0);
      fLogger->Info(MESSAGE_ORIGIN, "Add new signal from file %s  with identifier %i and file number %i", name.Data(), identifier,fNoOfSignals);
    }else{
      FairFileSource *fRootFileSourceS=fSignalTypeList[identifier];
      fRootFileSourceS->AddFile(name);
      TChain* CurrentChain=fRootFileSourceS->GetInChain();
      TObjArray* fileElements=CurrentChain->GetListOfFiles();
      fFileHeader->AddInputFile(fRootFileSourceSignal->GetInFile(), identifier, fileElements->GetEntries());
      fLogger->Info(MESSAGE_ORIGIN, "Add existing signal from file %s  with identifier %i and file number %i", name.Data(), identifier,fNoOfSignals);
    
    }
    fMixedInput=kTRUE;
    
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::AddSignalFile(TString name, UInt_t identifier )
{
  SetSignalFile(name, identifier);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TChain* FairRootManager::GetSignalChainNo(UInt_t i)
{
  if(i<<fNoOfSignals) {
    FairFileSource *fRootFileSourceS=fSignalTypeList[i];
    return fRootFileSourceS->GetInChain();
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "Error signal identifier %i does not exist ", i);
    return 0;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetBackgroundFile(TString name)
{
  if (name.IsNull() ) {
    fLogger->Info(MESSAGE_ORIGIN, "No background file defined.");
  }else{
    fRootFileSourceBKG = new FairFileSource(&name, "Background");
    fRootFileSourceBKG->Init();
    fFileHeader->AddInputFile(fRootFileSourceBKG->GetInFile(),0,0 );
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::AddBackgroundFile(TString name)
{
  if (name.IsNull() ) {
    fLogger->Info(MESSAGE_ORIGIN, "No background file defined.");
  }
  if(fRootFileSourceBKG!=0) {
     fRootFileSourceBKG->AddFile(name.Data());
     TObjArray* fileElements=fRootFileSourceBKG->GetInChain()->GetListOfFiles();
     fFileHeader->AddInputFile(fRootFileSourceBKG->GetInFile(),0, fileElements->GetEntries());
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN, "Use SetBackGroundFile first, then add files to background");
  }
    
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetInputFile(TString name)
{
  if(!fMixedInput) {
    //fInputFileName=name;
    fRootFileSource = new FairFileSource(&name);
    // fRootFileSource->Init();
    // fCbmroot = fRootFileSource->GetBranchDescriptionFolder();
    
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::InitSource() {
    Bool_t retBool=kFALSE;
    if(!fMixedInput) {
      retBool = fRootFileSource->Init();
      fCbmroot = fRootFileSource->GetBranchDescriptionFolder();
      fRootFileSource->AddFriendsToChain();
    }else{
      // In the mixed input the source is initialized immediatly when it is added
      // We need only to check that the BK source exist and we can return true.
        
      if(fRootFileSourceBKG!=0) retBool=kTRUE;
    
    }
    return retBool;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::OpenBackgroundChain()
{
 /* // Get the folder structure from file which describes the input tree.
  // There are two different names possible, so check both.
  fCbmroot= dynamic_cast <TFolder*> (fBackgroundFile->Get("cbmroot"));
  if(!fCbmroot) {
    fCbmroot= dynamic_cast <TFolder*> (fBackgroundFile->Get("cbmout"));
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

  TList* list= dynamic_cast <TList*> (fBackgroundFile->Get("BranchList"));
  TString chainName = "BGInChain";
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

  gROOT->GetListOfBrowsables()->Add(fCbmroot);
  fListFolder.Add( fCbmroot );
  return kTRUE;
*/
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::OpenSignalChain()
{
  std::map<UInt_t, FairFileSource*>::const_iterator iter;
  for(iter = fSignalTypeList.begin(); iter != fSignalTypeList.end(); iter++) {
      
    FairFileSource *SignalFile=iter->second;
    TChain* currentChain=SignalFile->GetInChain();
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
Bool_t  FairRootManager::DataContainersEmpty()
{
  for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++) {
    if (it->second.empty() == false) {
      return kFALSE;
    }
  }
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t  FairRootManager::DataContainersFilled()
{
  for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++) {
    if (it->second.empty() == true) {
      return kFALSE;
    }
  }
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TFile* FairRootManager::OpenOutFile(TFile* f)
{

  fLogger->Debug(MESSAGE_ORIGIN,"Check the output file");
  fOutFile=f;
  /**Check the output file, if anything wronge with it exit!*/
  if (fOutFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN,"FairRootManager: Error opening output file ");
    exit(-1);
  }
  FairRun* fRun = FairRun::Instance();
  /**Check if a simulation run!*/
  if(!fRun->IsAna()) {
    fCbmroot= gROOT->GetRootFolder()->AddFolder("cbmroot", "Main Folder");
    gROOT->GetListOfBrowsables()->Add(fCbmroot);
  } else {
    fCbmout= gROOT->GetRootFolder()->AddFolder("cbmout", "Main Output Folder");
    gROOT->GetListOfBrowsables()->Add(fCbmout);
  }
  return fOutFile;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TFile* FairRootManager::OpenOutFile(const char* fname)
{
  fLogger->Debug(MESSAGE_ORIGIN,"Opening output file, %s", fname);
  if(fOutFile) {
    CloseOutFile();
  }
  LOG(INFO) << "FairRootManager::OpenOutFile(\"" << fname << "\")" << FairLogger::endl;
  fOutFile = new TFile(fname, "recreate");
  return OpenOutFile(fOutFile);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name, const char* folderName , TNamed* obj, Bool_t toFile)
{

  // Security check. If the the name is equal the folder name there are problems with reading
  // back the data. Instead of the object inside the folder the RootManger will return a pointer
  // to the folder. To avoid such problems we check here if both strings are equal and stop the
  // execution with some error message if this is the case.
  if (strcmp (name, folderName) == 0 ) {
    fLogger->Fatal(MESSAGE_ORIGIN,"The names for the object name %s and the folder name %s are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the name or the folder name.", name, folderName);
  }

  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=(TFolder*)fCbmroot->FindObjectAny(folderName);
      if(f==0) {
        folder= fCbmroot->AddFolder(folderName,folderName);
      } else {
        folder=f;
      }
    } else {
      f=(TFolder*)fCbmout->FindObjectAny(folderName);
      if(f==0) {
        folder= fCbmout->AddFolder(folderName,folderName);
      } else {
        folder=f;
      }
    }
    obj->SetName(name);
    folder->Add(obj);
  }
  AddMemoryBranch(name, obj );
  //cout << " FairRootManager::Register Adding branch:(Obj) " << name << " In folder : " << folderName << endl;
  if(fBranchNameList->FindObject(name)==0) {
    fBranchNameList->AddLast(new TObjString(name));
    fBranchSeqId++;
  }

  if (toFile == kFALSE) {
          FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
   }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name,const char* Foldername ,TCollection* obj, Bool_t toFile)
{
  /**
  * This method do exactly the same as the one before but for TCollection which is a TObject and not a TNamed (MT)
  */
  // Security check. If the the name is equal the folder name there are problems with reading
  // back the data. Instead of the object inside the folder the RootManger will return a pointer
  // to the folder. To avoid such problems we check here if both strings are equal and stop the
  // execution with some error message if this is the case.
  if (strcmp (name, Foldername) == 0 ) {
    fLogger->Fatal(MESSAGE_ORIGIN,"The names for the object name %s and the folder name %s are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the name or the folder name.", name, Foldername);
  }

  if (GetUseFairLinks() == kTRUE && fInitFairLinksOnce == kFALSE){
            fInitFairLinksOnce = kTRUE;
            Register(fFairLinksBranchName, "FairMultiLinkedData", "FairLinksBranch", kTRUE);
  }

  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=(TFolder*)fCbmroot->FindObjectAny(Foldername);
      if(f==0) {
        folder= fCbmroot->AddFolder(Foldername,Foldername);
      } else {
        folder=f;
      }
    } else {
      f=(TFolder*)fCbmout->FindObjectAny(Foldername);
      if(f==0) {
        folder= fCbmout->AddFolder(Foldername,Foldername);
      } else {
        folder=f;
      }
    }
    obj->SetName(name);
    folder->Add(obj);
  }
  /**Keep the Object in Memory, and do not write it to the tree*/
  AddMemoryBranch(name, obj );
  if(fBranchNameList->FindObject(name)==0) {
    fBranchNameList->AddLast(new TObjString(name));
    fBranchSeqId++;
  }
  if (toFile == kFALSE) {
	  FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
  }

}
//_____________________________________________________________________________

//_____________________________________________________________________________
TClonesArray* FairRootManager::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{

  TClonesArray* outputArray;
  if (fActiveContainer.find(branchName) == fActiveContainer.end()) {
    fActiveContainer[branchName] = new TClonesArray(className);
    if (fCompressData) {
      std::queue<TClonesArray*> myQueue;
      fDataContainer[branchName] = myQueue;
      outputArray = new TClonesArray(className);
    } else {
      outputArray = fActiveContainer[branchName];
    }
    Register(branchName, folderName, outputArray, toFile);
  }
  return fActiveContainer[branchName];
}
//_____________________________________________________________________________
TClonesArray* FairRootManager::GetEmptyTClonesArray(TString branchName)
{
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {          //if a TClonesArray is registered in the active container
    if (fActiveContainer[branchName] == 0) {                      //the address of the TClonesArray is still valid
      std::cout << "-E- FairRootManager::GetEmptyTClonesArray: Container deleted outside FairRootManager!" << std::endl;
    } else if (!fCompressData) {                          //if the data is not compressed the existing TClonesArray is just emptied
      fActiveContainer[branchName]->Delete();
    } else if (fActiveContainer[branchName]->GetEntries() > 0) {    //if the container is not empty push it into the DataContainer storage and create a new one
      fDataContainer[branchName].push(fActiveContainer[branchName]);
      fLogger->Info(MESSAGE_ORIGIN, "GetEmptyTClonesArray moved %s with  %i to data container ",
                    branchName.Data(),  fActiveContainer[branchName]->GetEntries());
      fActiveContainer[branchName] = new TClonesArray(fActiveContainer[branchName]->GetClass()->GetName());
    } else {
      fLogger->Info(MESSAGE_ORIGIN, "GetEmptyTClonesArray not moved %s  %s  with %i to data container ",
                    branchName.Data(),fActiveContainer[branchName]  , fActiveContainer[branchName]->GetEntries());
    }
    return fActiveContainer[branchName];                        // return the container
  } else {
    std::cout << "-E- Branch: " << branchName << " not registered!" << std::endl;  // error if the branch is not registered
  }
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetTClonesArray(TString branchName)
{
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {
    /**if a TClonesArray is registered in the active container*/
    if (fCompressData && fActiveContainer[branchName]->GetEntries() > 0) {
      /**if the container is not empty push it into the DataContainer storage and create a new one*/
      fDataContainer[branchName].push(fActiveContainer[branchName]);
      fActiveContainer[branchName] = new TClonesArray(fActiveContainer[branchName]->GetClass()->GetName());
    }
    return fActiveContainer[branchName]; // return the container
  } else {
    fLogger->Info(MESSAGE_ORIGIN,  "Branch: %s not registered!" , branchName.Data());
  }
  // error if the branch is not registered
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetDataContainer(TString branchName)
{
  if (DataContainersFilled()) {
    return fDataContainer[branchName].front();
  }
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TClonesArray* FairRootManager::ForceGetDataContainer(TString branchName)
{
  TClonesArray* result = 0;
  if (fDataContainer.find(branchName)!= fDataContainer.end()) {
    if (!fDataContainer[branchName].empty()) {
      result = fDataContainer[branchName].front();
      fDataContainer[branchName].pop();
    }
  }
  return result;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TString FairRootManager::GetBranchName(Int_t id)
{
  /**Return the branch name from the id*/
  if(id < fBranchSeqId) {
    TObjString* ObjStr= (TObjString*) fBranchNameList->At(id);
    return ObjStr->GetString();
  } else {
    TString NotFound("Branch not found");
    return NotFound;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairRootManager::GetBranchId(TString BrName)
{
  /**Return the branch id from the name*/
  TObjString* ObjStr;
  Int_t Id=-1;
  for(Int_t t=0; t<fBranchNameList->GetEntries(); t++) {
    ObjStr= (TObjString*) fBranchNameList->At(t);
    if(BrName==ObjStr->GetString()) {
      Id=t;
      break;
    }
  }
  return Id;

}
//_____________________________________________________________________________

//_____________________________________________________________________________
TClonesArray*    FairRootManager::GetData(TString branchName, BinaryFunctor* function, Double_t parameter)
{
  if (fTSBufferMap[branchName] == 0) {
    fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
  }
  fTSBufferMap[branchName]->SetStopFunction(function);
  return fTSBufferMap[branchName]->GetData(parameter);
}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void  FairRootManager::Fill()
{
// Fills the tree.
// ---
  if (fCompressData) {
    if (DataContainersFilled()) {
      AssignTClonesArrays();
      ForceFill();
    }
  } else {
    ForceFill();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::ForceFill()
{
  if (fOutTree != 0) {
    fOutTree->Fill();
  } else {
    fLogger->Info(MESSAGE_ORIGIN,  " No Output Tree");
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::LastFill()
{
  if (fFillLastData) {
    Fill();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairRootManager::Write(const char* name, Int_t option, Int_t bufsize)
{
  /** Writes the tree in the file.*/
  if (fCompressData) {
    SaveAllContainers();
  }
  if(fOutTree!=0) {
    /** Get the file handle to the current output file from the tree.
      * If ROOT splits the file (due to the size of the file) the file
      * handle fOutFile is lost and the program crash while writing the
      * last part of the last file.
    */
    fOutFile = fOutTree->GetCurrentFile();
    fOutFile->cd();
    fOutTree->Write();
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "No Output Tree" );
  }
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager:: WriteGeometry()
{
  /** Writes the geometry in the current output file.*/

  if(fOutTree!=0) {
    fOutFile = fOutTree->GetCurrentFile();
    fOutFile->cd();
    gGeoManager->Write();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::CreateGeometryFile(const char* geofile)
{
  /** Writes the geometry in a separate file.
   *  This is only to have a file which can be read without the
   *  framework. The geomanager used by the framework is still
   *  stored in the parameter file or database
  */
  TFile* oldfile=gFile;
  TFile* file=new TFile(geofile,"RECREATE");
  file->cd();
  gGeoManager->Write();
  file->Close();
  file->Delete();
  gFile=oldfile;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager:: WriteFolder()
{
  fOutFile->cd();
  if(fCbmroot!=0 && fRootFileSource==0) {
    fCbmroot->Write();
  }
  if(fCbmout!=0) {
    fCbmout->Write();
  }
  fBranchNameList->Write("BranchList", TObject::kSingleKey);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::ReadEvent(Int_t i)
{
    SetEntryNr(i);
    /**For mixed input use the ReadMixedEvent method */
    if(fMixedInput) {
        fLogger->Info(MESSAGE_ORIGIN,"Read mixed event number  %i", i);
        ReadMixedEvent(i);
    }else{
        /** Check if the source is not zero, it is zero if we use the mixed input (bk and sg) */
        if ( fRootFileSource!=0) {
            
            /**special action needed for the first entry */
            
            if(0==fCurrentEntryNo) {
                Int_t totEnt =  fRootFileSource->GetEntries();
                fLogger->Info(MESSAGE_ORIGIN,"The number of entries in the tree is %i",totEnt);
                LOG(INFO) << "FairRootManager::ReadEvent(" << i << "): The tree has " << totEnt << " entries" << FairLogger::endl;
                fEvtHeader = (FairEventHeader*) GetObject("EventHeader.");
                if(fEvtHeader ==0) {
                    fLogger->Info(MESSAGE_ORIGIN, " No event Header was found!!!");
                    return;
                }
                SetEventTime();
            }
            
            /**After the first entry we are here */
            fCurrentEntryNo=i;
            fRootFileSource->ReadEvent(i);
            fEvtHeader->SetMCEntryNumber(i);
            fEvtHeader->SetEventTime(GetEventTime());
            fEvtHeader->SetInputFileId(0);
        }
    }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::ReadMixedEvent(Int_t i)
{
  /**Privat method used for event mixing*/

  /**Check for fCurrentEntryNo because it always starts from Zero, i could have any value! */
  if(0==fCurrentEntryNo) {
    fEvtHeader = (FairEventHeader*) GetObject("EventHeader.");
    SetEventTime();
  }
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
        TChain* chain = fSignalTypeList[iterN->first]->GetInChain();
        UInt_t entry = fCurrentEntry[iterN->first];
        chain->GetEntry(entry);
        fEvtHeader->SetMCEntryNumber(entry);
        fEvtHeader->SetInputFileId(iterN->first);
        fEvtHeader->SetEventTime(GetEventTime());
        GetASignal=kTRUE;
        fCurrentEntry[iterN->first]=entry+1;
        fLogger->Debug(MESSAGE_ORIGIN,"---Get entry No. %i from signal chain number --- %i --- ",entry, iterN->first);
        break;
      }
    }
    if(!GetASignal) {
      fRootFileSourceBKG->ReadEvent(i);
      fEvtHeader->SetMCEntryNumber(i);
      fEvtHeader->SetInputFileId(0); //Background files has always 0 as Id
      fEvtHeader->SetEventTime(GetEventTime());
      fLogger->Debug(MESSAGE_ORIGIN,"---Get entry from background chain  --- ");
    }

  }
  fCurrentEntryNo=i;
  fEvtHeader->SetEventTime(GetEventTime());
  fLogger->Debug(MESSAGE_ORIGIN,"--Event number --- %i  with time ----%f",fCurrentEntryNo, GetEventTime());
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::ReadBKEvent(Int_t i)
{
  if(fMixedInput) {
    if(0==i) {
      Int_t totEnt = fRootFileSourceBKG->GetInChain()->GetEntries();
      fLogger->Info(MESSAGE_ORIGIN,"The number of entries in background chain is %i",totEnt);
    }
    fRootFileSourceBKG->ReadEvent(i);
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::ReadNextEvent(Double_t dt)
{
  Bool_t readentry=kFALSE;
  ///TODO
  return readentry;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairRootManager::GetObject(const char* BrName)
{
  /**Get Data object by name*/
  TObject* Obj =NULL;
  fLogger->Debug2(MESSAGE_ORIGIN, " Try to find if the object %s  already activated by other task or call", BrName);
  /**Try to find the object in the folder structure, object already activated by other task or call*/
  if(fCbmout) {
    Obj = fCbmout->FindObjectAny(BrName);
    if (Obj) {
      fLogger->Debug2(MESSAGE_ORIGIN, "object %s was already activated by another task", BrName);
    }
  }
  /**if the object does not exist then it could be a memory branch */
  if(!Obj) {
    fLogger->Debug2(MESSAGE_ORIGIN, " Try to find if the object %s  is a memory branch", BrName);
    Obj=GetMemoryBranch(BrName);
    if (Obj) {
      fLogger->Debug2(MESSAGE_ORIGIN, "Object  %s  is a memory branch", BrName);
    }
  }
  /**if the object does not exist then look in the input tree */
  if(fCbmroot && !Obj) {
    /** there is an input tree and the object was not in memory */
    fLogger->Debug2(MESSAGE_ORIGIN, " Object %s  is not a memory branch and not yet activated, try the Input Tree (Chain)", BrName);
    Obj=fCbmroot->FindObjectAny(BrName);
    Obj=ActivateBranch(BrName);
  }
  if(!Obj) {
    Obj=ActivateBranch(BrName);
  }
  return Obj;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairRootManager::GetObjectFromInTree(const char* BrName)
{
   TTree *fInTree =fRootFileSource->GetInTree();
  if ( !fInTree ) {
    return GetObject(BrName);
  }
  /**Get Data object by name*/
  TObject* Obj =NULL;
  fLogger->Debug2(MESSAGE_ORIGIN, " Try to find if the object %s  already activated by other task or call", BrName);

  /**Try to find the object in the folder structure, object already activated by other task or call*/
  /**if the object does not exist then look in the input tree */
  if(fCbmroot && !Obj) {
    /** there is an input tree and the object was not in memory */
    fLogger->Debug2(MESSAGE_ORIGIN, " Object %s  is not a memory branch and not yet activated, try the Input Tree (Chain)", BrName);
    Obj=fCbmroot->FindObjectAny(BrName);
    Obj=ActivateBranchInInTree(BrName);
  }
  if(!Obj) {
    Obj=ActivateBranch(BrName);
  }
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
    dataTree = GetBGChain();
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
    TClonesArray* dataArray = (TClonesArray*)GetObject(GetBranchName(type));

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
    dataTree = GetBGChain();
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
    result = (TClonesArray*) GetObject(GetBranchName(type))->Clone();
  }
  if (entryNr > -1) {
    dataBranch->GetEntry(oldEntryNr); //reset the dataBranch to the original entry
  }
  return result;

}

//_____________________________________________________________________________
void FairRootManager::TruncateBranchNames(TTree* fTree, const char* folderName)
{
  /** If a object is created in a folder the corresponding branch
  * in the tree is crated with a wrong name.
  * The name of the branch is created as follows
  * mainFolder.subFolder.nameOfStoredObject
  * e.g. cbmroot.Event.ExampleClass.
  * The name which is wanted is only nameOfStoredObject
  * e.g. ExampleClass.
  * This is corrected in this function
  * If the folder does not exist don't do anything
  */
  TFolder* cbm=(TFolder*)gROOT->FindObjectAny(folderName);
  if(cbm) {
    TCollection* lf=cbm->GetListOfFolders();
    TIterator* iter= lf->MakeIterator();
    TObjArray* Br= fTree->GetListOfBranches();
    TIterator* BrIter= Br->MakeIterator();
    TObject* obj;
    TObject* BrObj;

    /** correct branch names in all folders below the main output folder*/
    while((obj=iter->Next())) {

      /** Create TString with the part of the branch name which should be
      * removed. This is mainFolderName.folderName. e.g. cbmroot.Event.
      * This part of the branch name is obsolete, so it is removed from
      * the branch name.
      */
      TString ffn=cbm->GetName();
      ffn=ffn+".";
      ffn=ffn+obj->GetName();
      ffn=ffn+".";

      /** Correct name of all branches and leaves which correspond to
      * the subfolder. To do so loop over all branches and check
      * if the branch corresponds with the folder. If it corresponds
      * correct the branch names of all sub branches.
      * Only correct branch names for up to now uncorrected branches.
      */
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch* b=(TBranch*)BrObj;
        TruncateBranchNames(b, ffn);
      }
    }

    // Remove all occurence of FairMCEventHeader and   from
    // all branches containing that string.
    // This is not the correct way to do it, but up tonow we don't understand
    // why this part comes in when storing a derrived class from
    // FairMCEventHeader or FairEventHeader.

    iter->Reset();
    while((obj=iter->Next())) {

      TString ffn=".FairMCEventHeader";
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch* b=(TBranch*)BrObj;
        TruncateBranchNames(b, ffn);
      }
    }

    iter->Reset();
    while((obj=iter->Next())) {

      TString ffn=".FairEventHeader";
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch* b=(TBranch*)BrObj;
        TruncateBranchNames(b, ffn);
      }
    }

    delete  iter;
    delete  BrIter;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::TruncateBranchNames(TBranch* b, TString ffn)
{
  /** Get the branch name from the branch object, remove common
  *  and wrong part of the name and and set branch name to
  *  the new corrected name. This has to be done recursivly for
  *  all subbranches/leaves
  *  Remove wrong part of branch name
  */
  TObject* BrObj;
  TString nn= b->GetName();
  //  cout<<"nn.Data before: "<<nn.Data()<<endl;
  nn.ReplaceAll(ffn.Data(),"");
  //  cout<<"nn.Data after: "<<nn.Data()<<endl;
  //  cout <<"##################"<<endl;
  b->SetName(nn.Data());
  TObjArray* Br= b->GetListOfBranches();
  TIterator* BrIter= Br->MakeIterator();
  BrIter->Reset();

  while((BrObj=BrIter->Next())) {
    TBranch* bb=(TBranch*)BrObj;
    TruncateBranchNames(bb, ffn);
  }
  delete  BrIter;
}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void  FairRootManager::SetBranchNameList(TList* list)
{
  for(Int_t t=0; t<list->GetEntries(); t++) {
    fBranchNameList->AddAt(list->At(t),t);
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
  TObjArray *fListFolder;
  if(fRootFileSource){
      fListFolder = fRootFileSource->GetListOfFolders();
  }else{
      fListFolder = fRootFileSourceBKG->GetListOfFolders();
  }
  fNObj++;
  fObj2[fNObj]  =  GetMemoryBranch ( BrName );
  if ( fObj2[fNObj]   ) {
    return  fObj2[fNObj];
  }
  /**try to find the object decribing the branch in the folder structure in file*/
  fLogger->Debug2(MESSAGE_ORIGIN, " Try to find an object %s decribing the branch in the folder structure in file", BrName);
  for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
    TFolder* fold = (TFolder*) fListFolder->At(i);
    fObj2[fNObj] = fold->FindObjectAny(BrName);
    if (fObj2[fNObj] ) {
      fLogger->Debug(MESSAGE_ORIGIN, "object %s decribing the branch in the folder structure was found", BrName);
      break;
    }
  }

  if(!fObj2[fNObj]) {
    /** if we do not find an object corresponding to the branch in the folder structure
    *  then we have no idea about what type of object is this and we cannot set the branch address
    */
    fLogger->Info(MESSAGE_ORIGIN, " Branch: %s  not found in Tree ", BrName);
    //Fatal(" No Branch in the tree", BrName );
    return 0;
  } else {
    if(fMixedInput) {
      /** All branches has the same types in background and signal chains, thus
       * we can set the branch address to al of them with one TClonesarray and then we call the proper
       * fill in the read (event) entry
       */

      fLogger->Debug2(MESSAGE_ORIGIN, "Set the Branch address for background branch %s", BrName);
      fRootFileSourceBKG->GetInChain()->SetBranchStatus(BrName,1);
      fRootFileSourceBKG->GetInChain()->SetBranchAddress(BrName,&fObj2[fNObj]);

      std::map<UInt_t, FairFileSource*>::const_iterator iter;
      Int_t no=0;
    
      for(iter = fSignalTypeList.begin(); iter != fSignalTypeList.end(); iter++) {
        fLogger->Debug2(MESSAGE_ORIGIN, "Set the Branch address for signal file number %i  and  branch %s ", no++ , BrName);
        FairFileSource *signal=iter->second;
        cout << "------------------------------" << signal<< endl;
        TChain* currentChain=signal->GetInChain();
        currentChain->SetBranchStatus(BrName,1);
        currentChain->SetBranchAddress(BrName,&fObj2[fNObj]);
      }


    } else {
      
      TChain *fInChain=fRootFileSource->GetInChain();
      fInChain->SetBranchStatus(BrName,1);
      fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
    }
  }
  
  AddMemoryBranch( BrName , fObj2[fNObj] );
  return  fObj2[fNObj];
  
}

//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairRootManager::ActivateBranchInInTree(const char* BrName)
{
    
  TTree *fInTree =fRootFileSource->GetInTree();
  TObjArray *fListFolder=fRootFileSource->GetListOfFolders();
  fNObj++;

  for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
    TFolder* fold = (TFolder*) fListFolder->At(i);
    fObj2[fNObj] = fold->FindObjectAny(BrName);
    if (fObj2[fNObj] ) {
      break;
    }
  }

  if(!fObj2[fNObj]) {
    /** if we do not find an object corresponding to the branch in the folder structure
    *  then we have no idea about what type of object is this and we cannot set the branch address
    */
    fLogger->Info(MESSAGE_ORIGIN, " Branch: %s  not found in Tree ", BrName);
    //Fatal(" No Branch in the tree", BrName );
    return 0;
  } else {
    fInTree->SetBranchStatus (BrName,1);
    fInTree->SetBranchAddress(BrName,&fObj2[fNObj]);
  }

  AddMemoryBranch( BrName , fObj2[fNObj] );
  return  fObj2[fNObj];

}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void FairRootManager::AssignTClonesArrays()
{
  for(std::map<TString, std::queue<TClonesArray*> >::iterator it = fDataContainer.begin(); it != fDataContainer.end(); it++) {
    AssignTClonesArray(it->first);
  }
}
//_____________________________________________________________________________
void FairRootManager::AssignTClonesArray(TString branchName)
{
  TClonesArray* output = (TClonesArray*)GetObject(branchName);
  TClonesArray* input = ForceGetDataContainer(branchName);
  output->Clear();
  if (input != 0) {
    output->AbsorbObjects(input, 0, input->GetEntries() - 1);
  }
}
//_____________________________________________________________________________
Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
  cout <<"FairRootManager::CheckBranchSt  :  " << BrName << endl;
  Int_t returnvalue=0;
  TObject* Obj1 =NULL;
  TObjArray *fListFolder=0;
    
  if(fRootFileSource!=0){
    fListFolder=fRootFileSource->GetListOfFolders();
  }else{
    fListFolder = new TObjArray(16);
  }
    
  cout <<"FairRootManager::CheckBranchSt  :  " <<fCbmroot << endl;
  if (fCbmroot) {
    fListFolder->Add(fCbmroot);
    Obj1 = fCbmroot->FindObjectAny(BrName);
  }
  if(fCbmout && !Obj1) {
    fListFolder->Add(fCbmout);
    Obj1 = fCbmout->FindObjectAny(BrName);  //Branch in output folder
  }
  if(!Obj1) {
    for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
      cout << "Search in Folder: " << i << "  " <<  fListFolder->At(i) << endl;
      TFolder* fold = dynamic_cast<TFolder*> (fListFolder->At(i));
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

//_____________________________________________________________________________
void  FairRootManager::CreatePerMap()
{
//   cout << " FairRootManager::CreatePerMap() " << endl;
  fBranchPerMap=kTRUE;
  for (Int_t i=0; i<fBranchSeqId; i++) {
    TObjString* name= (TObjString*)(fBranchNameList->At(i));
    cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
    TString BrName=name->GetString();
    fBrPerMap.insert(pair<TString, Int_t> (BrName, CheckBranchSt(BrName.Data())));
  }

}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void FairRootManager::SaveAllContainers()
{
  while(!DataContainersEmpty()) {
    AssignTClonesArrays();
    ForceFill();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Double_t FairRootManager::GetEventTime()
{
  fLogger->Debug(MESSAGE_ORIGIN,"-- Get Event Time --");
  if(!fEvtHeaderIsNew && fEvtHeader!=0) {
    Double_t EvtTime=fEvtHeader->GetEventTime();
    if( !(EvtTime<0)) {
      return   EvtTime;
    }
  }

  if (fEventTimeInMCHeader && !fMCHeader) {
    fLogger->Debug(MESSAGE_ORIGIN," No MCEventHeader, time is set to 0");
    return 0;
  } else if(fEventTimeInMCHeader && fMCHeader) {
    fEventTime=fMCHeader->GetT();
    fLogger->Debug(MESSAGE_ORIGIN," Get event time from MCEventHeader : %f ns", fEventTime);
    return fEventTime;
  } else {

    if(fTimeforEntryNo!=fCurrentEntryNo) {
      SetEventTime();
    }
    fLogger->Debug(MESSAGE_ORIGIN," Calculate event time from user input : %f ns", fEventTime);
    return fEventTime;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::WriteFileHeader(FairFileHeader* f)
{
  fOutFile->cd();
  f->SetName(fOutFile->GetName());
  f->Write("FileHeader", TObject::kSingleKey);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetEventTimeInterval(Double_t min, Double_t max)
{
  fEventTimeMin=min;
  fEventTimeMax=max;
  fEventMeanTime=(fEventTimeMin+fEventTimeMax)/2;
  fEventTimeInMCHeader=kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::SetEventMeanTime(Double_t mean)
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
void FairRootManager::SetEventTime()
{
  fLogger->Debug(MESSAGE_ORIGIN, "Set event time for Entry = %i , where the current entry is %i",
                 fTimeforEntryNo, fCurrentEntryNo );
  if(fTimeProb!=0) {
    fLogger->Debug(MESSAGE_ORIGIN, "Time will be  set via sampling method : old time = %f ", fEventTime);
    fEventTime += fTimeProb->GetRandom();
    fLogger->Debug(MESSAGE_ORIGIN, "Time set via sampling method : %f ", fEventTime);
  } else {
    fEventTime += gRandom->Uniform( fEventTimeMin,  fEventTimeMax);
    fLogger->Debug(MESSAGE_ORIGIN, "Time set via Uniform Random : %f ", fEventTime);

  }
  fTimeforEntryNo=fCurrentEntryNo;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRootManager::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
  fLogger->Info(MESSAGE_ORIGIN, "SetSignal rate for signal %i  : %i ", Signalid , background );
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
void  FairRootManager::BGWindowWidthTime(Double_t background, UInt_t Signalid)
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
Int_t  FairRootManager::CheckMaxEventNo(Int_t EvtEnd)
{
  fLogger->Info(MESSAGE_ORIGIN, "Maximum No of Event was set manually to :  %i , we will check if there is enough entries for this!! ", EvtEnd);
  Int_t MaxEventNo=0;
  if(EvtEnd!=0) {
    MaxEventNo=EvtEnd;
  }
  Int_t localMax=0;
  if(!fMixedInput) {
    TChain *fInChain =fRootFileSource->GetInChain();
    MaxEventNo=fInChain->GetEntries();
  } else {
    Int_t MaxBG=fRootFileSourceBKG->GetInChain()->GetEntries();
    Int_t MaxS=0;
    Double_t ratio=0.;
    std::map<UInt_t, Double_t>::const_iterator iterN;
    for(iterN = fSignalBGN.begin(); iterN != fSignalBGN.end(); iterN++) {
      TChain* chain = fSignalTypeList[iterN->first]->GetInChain();
      MaxS=chain->GetEntries();
      fLogger->Info(MESSAGE_ORIGIN, "Signal chain  No %i  has  :  %i  entries ", iterN->first, MaxS);
      ratio=iterN->second;
      cout<< " ratio = "<< ratio <<  "floor(MaxS/ratio) "<<floor(MaxS/ratio) << "  MaxBG = " << MaxBG  << endl;
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
  }
  return MaxEventNo;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManager::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
  if (fWriteoutBufferMap[branchName] == 0) {
    fWriteoutBufferMap[branchName] = buffer;
  } else {
    fLogger->Warning(MESSAGE_ORIGIN, "Branch %s is already registered in WriteoutBufferMap", branchName.Data());
    delete buffer;
  }
  return fWriteoutBufferMap[branchName];
}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void FairRootManager::StoreWriteoutBufferData(Double_t eventTime)
{
  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {
    iter->second->WriteOutData(eventTime);
  }
}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
void FairRootManager::DeleteOldWriteoutBufferData()
{
  for(std::map<TString, FairWriteoutBuffer*>::const_iterator iter = fWriteoutBufferMap.begin(); iter != fWriteoutBufferMap.end(); iter++) {
    iter->second->DeleteOldData();
  }
}
//_____________________________________________________________________________


void FairRootManager::ReadBranchEvent(const char* BrName)
{
  /**fill the object with content if the other branches in this tree entry were already read**/
    TTree *fInTree =fRootFileSource->GetInTree();
    TChain *fInChain =fRootFileSource->GetInChain();

  if(fEvtHeader == 0) { return; } //No event header, Reading will start later
  if ( fInTree ) {
    fInTree->FindBranch(BrName)->GetEntry(fEntryNr);
    return;
  }
  if(!fMixedInput) {
    if(!fInChain) { return; }
    fInChain->FindBranch(BrName)->GetEntry(fEntryNr);
    return;
  } else {
    TChain* chain = fSignalTypeList[fEvtHeader->GetInputFileId()]->GetInChain();
    if(!chain) { return; }
    chain->FindBranch(BrName)->GetEntry(fEvtHeader->GetMCEntryNumber());
    return;
  }
  return;
}
//_____________________________________________________________________________



ClassImp(FairRootManager)








