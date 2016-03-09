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
#include "FairMonitor.h"                // for FairMonitor
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairRun.h"                    // for FairRun
#include "FairTSBufferFunctional.h"     // for FairTSBufferFunctional, etc
#include "FairWriteoutBuffer.h"         // for FairWriteoutBuffer
#include "FairLinkManager.h"            // for FairLinkManager
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
#include "TRefArray.h"                  // for TRefArray

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
    fBranchSeqId(0),
    fBranchNameList(new TList()),
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
    fSourceChain( new TChain("cbmsim", "/cbmroot")),
    fSignalChainList(),
    fUseFairLinks(kFALSE),
    fFinishRun(kFALSE),
    fListOfBranchesFromInput(0),
    fListOfBranchesFromInputIter(0),
    fListOfNonTimebasedBranches(new TRefArray()),
    fListOfNonTimebasedBranchesIter(0)
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
  LOG(DEBUG) << "Enter Destructor of FairRootManager" << FairLogger::endl;
  if(fOutTree) {
    delete fOutTree;
  }
  if(fOutFile) {
    fOutFile->cd();
    delete fOutFile;
  }
  delete fObj2;
  fBranchNameList->Delete();
  delete fBranchNameList;
  fgInstance = 0;
  LOG(DEBUG) << "Leave Destructor of FairRootManager" << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::InitSource() {
  
  LOG(DEBUG) << "Call the initialiazer for the FairSource in FairRootManager " << FairLogger::endl;
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
    LOG(DEBUG) << "Source is intialized and the list of branches is created in FairRootManager " << FairLogger::endl;
    fListOfNonTimebasedBranchesIter=fListOfNonTimebasedBranches->MakeIterator();
    return sourceInitBool;
  }
  return kFALSE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TFile* FairRootManager::OpenOutFile(TFile* f)
{

  LOG(DEBUG) << "Check the output file" << FairLogger::endl;
  fOutFile=f;
  /**Check the output file, if anything wronge with it exit!*/
  if (fOutFile->IsZombie()) {
    LOG(FATAL) << "FairRootManager: Error opening output file " 
	       << FairLogger::endl;
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
  LOG(DEBUG) << "Opening output file, " << fname << FairLogger::endl;
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
  FairMonitor::GetMonitor()->RecordRegister(name,folderName,toFile);

  // Security check. If the the name is equal the folder name there are problems with reading
  // back the data. Instead of the object inside the folder the RootManger will return a pointer
  // to the folder. To avoid such problems we check here if both strings are equal and stop the
  // execution with some error message if this is the case.
  if (strcmp (name, folderName) == 0 ) {
    LOG(FATAL) << "The names for the object name "
	       << name << " and the folder name "
	       << folderName <<" are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the name or the folder name."
	       << FairLogger::endl;
  }

  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=static_cast<TFolder*>(fCbmroot->FindObjectAny(folderName));
      if(f==0) {
        folder= fCbmroot->AddFolder(folderName,folderName);
      } else {
        folder=f;
      }
    } else {
      f=static_cast<TFolder*>(fCbmout->FindObjectAny(folderName));
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
 
  AddBranchToList(name);
    
  if (toFile == kFALSE) {
          FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
   }
}
//_____________________________________________________________________________

Int_t  FairRootManager::AddBranchToList(const char* name)
{
    if(fBranchNameList->FindObject(name)==0) {
        fBranchNameList->AddLast(new TObjString(name));
        fBranchSeqId++;
    }
    return fBranchSeqId;
}


//_____________________________________________________________________________
void  FairRootManager::Register(const char* name,const char* Foldername ,TCollection* obj, Bool_t toFile)
{
  FairMonitor::GetMonitor()->RecordRegister(name,Foldername,toFile);

  /**
  * This method do exactly the same as the one before but for TCollection which is a TObject and not a TNamed (MT)
  */
  // Security check. If the the name is equal the folder name there are problems with reading
  // back the data. Instead of the object inside the folder the RootManger will return a pointer
  // to the folder. To avoid such problems we check here if both strings are equal and stop the
  // execution with some error message if this is the case.
  if (strcmp (name, Foldername) == 0 ) {
    LOG(FATAL) << "The names for the object name "
	       << name << " and the folder name "
	       << Foldername << " are equal. This isn't allowed. So we stop the execution at this point. Pleae change either the name or the folder name."

	       <<FairLogger::endl;
  }

  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=static_cast<TFolder*>(fCbmroot->FindObjectAny(Foldername));
      if(f==0) {
        folder= fCbmroot->AddFolder(Foldername,Foldername);
      } else {
        folder=f;
      }
    } else {
      f=static_cast<TFolder*>(fCbmout->FindObjectAny(Foldername));
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
  AddBranchToList(name);
  
  if (toFile == kFALSE) {
	  FairLinkManager::Instance()->AddIgnoreType(GetBranchId(name));
  }
}
//_____________________________________________________________________________

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
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {          //if a TClonesArray is registered in the active container
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

//_____________________________________________________________________________
TClonesArray* FairRootManager::GetTClonesArray(TString branchName)
{
  if (fActiveContainer.find(branchName) != fActiveContainer.end()) {
    return fActiveContainer[branchName]; // return the container
  } else {
    LOG(INFO) << "Branch: " << branchName.Data()
	      << " not registered!" << FairLogger::endl ;
  }
  // error if the branch is not registered
  return 0;
}
//_____________________________________________________________________________

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

//_____________________________________________________________________________
Int_t FairRootManager::GetBranchId(TString BrName)
{
  /**Return the branch id from the name*/
  TObjString* ObjStr;
  Int_t Id=-1;
  for(Int_t t=0; t<fBranchNameList->GetEntries(); t++) {
    ObjStr= static_cast<TObjString*>(fBranchNameList->At(t));
    if(BrName==ObjStr->GetString()) {
      Id=t;
      break;
    }
  }
  return Id;

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::InitTSBuffer(TString branchName, BinaryFunctor* function)
{
	fTSBufferMap[branchName] = new FairTSBufferFunctional(branchName, GetInTree(), function);
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
void FairRootManager::TerminateTSBuffer(TString branchName)
{
	if (fTSBufferMap.count(branchName) > 0){
		fTSBufferMap[branchName]->Terminate();
	}
}
//_____________________________________________________________________________

//_____________________________________________________________________________

void FairRootManager::TerminateAllTSBuffer()
{
	for (std::map<TString, FairTSBufferFunctional*>::iterator iter = fTSBufferMap.begin(); iter != fTSBufferMap.end(); iter++)
	{
		iter->second->Terminate();
	}
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
void FairRootManager::Fill()
{
  if (fOutTree != 0) {
    fOutTree->Fill();
  } else {
    LOG(INFO) << " No Output Tree" << FairLogger::endl;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::LastFill()
{
  FairMonitor::GetMonitor()->StoreHistograms(fOutFile);
  if (fFillLastData) {
    Fill();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairRootManager::Write(const char*, Int_t, Int_t)
{
  /** Writes the tree in the file.*/

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
    LOG(INFO) << "No Output Tree" << FairLogger::endl;
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
  if(fCbmroot!=0 && fSource==0) {
    fCbmroot->Write();
  }
  if(fCbmout!=0) {
    fCbmout->Write();
  }
  fBranchNameList->Write("BranchList", TObject::kSingleKey);
  fTimeBasedBranchNameList->Write("TimeBasedBranchList", TObject::kSingleKey);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  FairRootManager::ReadEvent(Int_t i)
{
  if ( !fSource ) return 0;
  
  fSource->Reset();

  SetEntryNr(i);

  if ( !fSource ) {
    LOG(FATAL) << "No Source available" << FairLogger::endl;
    return -1;
  }

  fCurrentEntryNo=i;

  Int_t readEventResult = fSource->ReadEvent(i);

  FairEventHeader* tempEH = new FairEventHeader();
  fSource->FillEventHeader(tempEH);
  fCurrentTime = tempEH->GetEventTime();
  tempEH->Delete();

  LOG(DEBUG) << "--Event number --- "
	     << fCurrentEntryNo << " with time ---- " 
	     << fCurrentTime << FairLogger::endl;

  return readEventResult;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairRootManager::GetRunId() 
{
  FairEventHeader* tempEH = new FairEventHeader();
  if ( fSource ) {
    fSource->FillEventHeader(tempEH);
    return tempEH->GetRunId();
  }
  return -1;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::ReadBranchEvent(const char* BrName)
{
    if ( fSource )
    fSource->ReadBranchEvent(BrName);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
//_____________________________________________________________________________
Int_t FairRootManager::ReadNonTimeBasedEventFromBranches(Int_t Entry)
{
    if ( fSource ){
        TObject *Obj;
        fListOfNonTimebasedBranchesIter->Reset();
        while ( (Obj=fListOfNonTimebasedBranchesIter->Next())) {
            fSource->ReadBranchEvent(Obj->GetName(),Entry);
        }
    }else{
      return 0;
    }
    return 1;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::ReadNextEvent(Double_t)
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
  LOG(DEBUG2) << " Try to find if the object "
	      << BrName << " is already activated by another task or call"
	      << FairLogger::endl;
  /**Try to find the object in the folder structure, object already activated by other task or call*/
  if(fCbmout) {
    Obj = fCbmout->FindObjectAny(BrName);
    if (Obj) {
      LOG(DEBUG2) <<"Object "  
		  << BrName << " was already activated by another task"
		  << FairLogger::endl;
    }
  }
  /**if the object does not exist then it could be a memory branch */
  if(!Obj) {
    LOG(DEBUG2) << "Try to find if the object "
		<< BrName << " is a memory branch" << FairLogger::endl;
    Obj=GetMemoryBranch(BrName);
    if (Obj) {
      LOG(DEBUG2) << "Object "
		  << BrName << " is a memory branch" << FairLogger::endl;
    }
  }
  /**if the object does not exist then look in the input tree */
  if(fCbmroot && !Obj) {
    /** there is an input tree and the object was not in memory */
    LOG(DEBUG2) << "Object "
		<< BrName << " is not a memory branch and not yet activated, try the Input Tree (Chain)" << FairLogger::endl;
    Obj=fCbmroot->FindObjectAny(BrName);
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
  TFolder* cbm=static_cast<TFolder*>(gROOT->FindObjectAny(folderName));
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
        TBranch* b=static_cast<TBranch*>(BrObj);
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
        TBranch* b=static_cast<TBranch*>(BrObj);
        TruncateBranchNames(b, ffn);
      }
    }

    iter->Reset();
    while((obj=iter->Next())) {

      TString ffn=".FairEventHeader";
      BrIter->Reset();

      while((BrObj=BrIter->Next())) {
        TBranch* b=static_cast<TBranch*>(BrObj);
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
    TBranch* bb=static_cast<TBranch*>(BrObj);
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
  if ( list == NULL ) return;
  for(Int_t t=0; t<list->GetEntries(); t++) {
    fBranchNameList->AddAt(list->At(t),t);
    fBranchSeqId++;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetInChain(TChain* tempChain, Int_t ident)
{ 
  if ( ident <= 0 ) 
    fSourceChain = tempChain;
  else
    fSignalChainList[ident] = tempChain;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Double_t FairRootManager::GetEventTime() {
  return fCurrentTime;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::UpdateBranches() { 
  for ( Int_t iobj = 0 ; iobj <= fNObj ; iobj++ ) {
    if ( fObj2[iobj] ) {
      LOG(INFO) << "FairRootManager::UpdateBranches \"" << fObj2[iobj]->GetName()
		<< "\" (\"" << fObj2[iobj]->GetTitle() << "\")" << FairLogger::endl;
      TString tempBranchName = fObj2[iobj]->GetName();
      fSource->ActivateObject(&fObj2[fNObj],tempBranchName.Data());
    }
  }

}
//_____________________________________________________________________________


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
  LOG(DEBUG) << "Try to find an object "
	      << BrName << " describing the branch in the folder structure in file"
	      << FairLogger::endl;
  if ( fListFolder ) {
    for(Int_t i=0; i<fListFolder->GetEntriesFast(); i++) {
      TFolder* fold = static_cast<TFolder*>(fListFolder->At(i));
      fObj2[fNObj] = fold->FindObjectAny(BrName);
      if (fObj2[fNObj] ) {
	LOG(INFO) << "Object "
		  << BrName << " describing the branch in the folder structure was found" << FairLogger::endl;
	break;
      }
    }
  }

  if(!fObj2[fNObj]) {
    /** if we do not find an object corresponding to the branch in the folder structure
    *  then we have no idea about what type of object is this and we cannot set the branch address
    */
    LOG(INFO) << " Branch: " << BrName << " not found in Tree."
	      << FairLogger::endl;
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

Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
 // cout <<"FairRootManager::CheckBranchSt  :  " << BrName << endl;
  Int_t returnvalue=0;
  TObject* Obj1 =NULL;
    
  if(fListFolder==0){
    fListFolder = new TObjArray(16);
  }
  
  //cout <<"FairRootManager::CheckBranchSt  :  " <<fCbmroot << endl;
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

//_____________________________________________________________________________
void  FairRootManager::CreatePerMap()
{
//   cout << " FairRootManager::CreatePerMap() " << endl;
  fBranchPerMap=kTRUE;
  for (Int_t i=0; i<fBranchSeqId; i++) {
    TObjString* name= static_cast<TObjString*>(fBranchNameList->At(i));
//    cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
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
void FairRootManager::WriteFileHeader(FairFileHeader* f)
{
  fOutFile->cd();
  f->SetName(fOutFile->GetName());
  f->Write("FileHeader", TObject::kSingleKey);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  FairRootManager::CheckMaxEventNo(Int_t EvtEnd)
{
  if ( fSource ) 
    return fSource->CheckMaxEventNo(EvtEnd);
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairWriteoutBuffer* FairRootManager::RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer)
{
  if (fWriteoutBufferMap[branchName] == 0) {
    fWriteoutBufferMap[branchName] = buffer;
  } else {
    LOG(WARNING) << "Branch "
		 << branchName.Data() 
		 << " is already registered in WriteoutBufferMap"
		 << FairLogger::endl;
    delete buffer;
  }
  return fWriteoutBufferMap[branchName];
}
//_____________________________________________________________________________

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

ClassImp(FairRootManager)








