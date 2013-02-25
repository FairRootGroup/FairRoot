// -------------------------------------------------------------------------
// -----                   FairRootManager source file                 -----
// -----            Created 06/01/04  by M. Al-Turany/D. Bertini       -----
// -------------------------------------------------------------------------

// Class FairRootManager
// ------------------
// Class that takes care of Root IO.
#include "FairRootManager.h"
#include "FairDetector.h"
#include "FairRunAna.h"
#include "FairRun.h"
#include "FairMCApplication.h"
#include "FairGeoNode.h"
#include "FairTSBufferFunctional.h"
#include "FairLogger.h"
#include "FairMCEventHeader.h"
#include "FairEventHeader.h"
#include "FairFileHeader.h"
#include "FairEventHeader.h"
#include "FairWriteoutBuffer.h"
#include "FairLink.h"
#include "TFriendElement.h"
#include "TObjArray.h"
#include "TFolder.h"
#include "TCollection.h"
#include "TParticle.h"
#include "TList.h"
#include "TGeoManager.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TList.h"
#include "TChainElement.h"
#include "TPRegexp.h"
#include "TArray.h"
#include "TF1.h"
#include "TRandom.h"

#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>

using std::flush;
using std::cout;
using std::endl;
using std::map;
using std::list;
using std::pair;
using std::set;

FairRootManager* FairRootManager::fgInstance = 0;
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
    fCbmout(NULL),
    fCbmroot(NULL),
    fCurrentTime(0),
    fInFile(NULL),
    fInChain( new TChain("cbmsim", "/cbmroot")),
    fInTree(NULL),
    fOutFile(NULL),
    fOutTree(NULL),
    fListFolder(0),
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
    fInputFileName(""),
    fInputChainList(),
    fFriendTypeList(),
    fCheckInputBranches(),
    fInputLevel(),
    fRunIdInfoAll(),
    fLogger(FairLogger::GetLogger()),
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
    fEntryNr(0)
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
// if(fCbmout) delete fCbmout;
// if(fCbmroot) delete fCbmroot;
  if(fInFile) {
    delete fInFile;
  }
  if(fInChain) {
    delete fInChain;
  }
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
      fFileHeader->AddInputFile(SignalInFile, identifier, 0); //First file in the Chain
    } else {
      TChain* CurrentChain=fSignalTypeList[identifier];
      CurrentChain->AddFile(name.Data());
      TObjArray* fileElements=CurrentChain->GetListOfFiles();
      fFileHeader->AddInputFile(SignalInFile, identifier, fileElements->GetEntries());
    }
    fMixedInput=kTRUE;

  }
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
    return fSignalTypeList[i];
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
  }
  fBackgroundFile =  new TFile(name);
  if (fBackgroundFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Background file  %s ", name.Data());
  } else {
    fBackgroundChain = new TChain("cbmsim", "/cbmroot");
    fBackgroundChain->AddFile(name.Data());
    fFileHeader->AddInputFile(fBackgroundFile,0,0 );
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::AddBackgroundFile(TString name)
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
      fFileHeader->AddInputFile(BGFile,0, fileElements->GetEntries());
    } else {
      fLogger->Fatal(MESSAGE_ORIGIN, "Use SetBackGroundFile first, then add files to background");
    }

  }

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::SetInputFile(TString name)
{
  if(!fMixedInput) {
    fInputFileName=name;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::OpenBackgroundChain()
{
  // Get the folder structure from file which describes the input tree.
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

}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::OpenSignalChain()
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
Bool_t FairRootManager::OpenInChain()
{
  if(fMixedInput) {
    return OpenBackgroundChain();
  }
  if ( fInputFileName.IsNull() ) {
    fLogger->Info(MESSAGE_ORIGIN, "No input file defined.");
    return kFALSE;
  }

  // Temporarily open the input file to extract information which
  // is needed to bring the friend trees in the correct order
  fInFile = new TFile(fInputFileName);
  if (fInFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
  }

  if (!fInChain ) {
    fInChain = new TChain("cbmsim", "/cbmroot");
  }
  fInChain->Add( fInFile->GetName() );



  // Get the folder structure from file which describes the input tree.
  // There are two different names possible, so check both.
  fCbmroot= dynamic_cast <TFolder*> (fInFile->Get("cbmroot"));
  if(!fCbmroot) {
    fCbmroot= dynamic_cast <TFolder*> (fInFile->Get("cbmout"));
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
  TList* list= dynamic_cast <TList*> (fInFile->Get("BranchList"));
  TString chainName = "InputChain";
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
      fLogger->Fatal(MESSAGE_ORIGIN, "Branch structure of the input file %s and the file to be added %s are different.", fInputFileName.Data(), (*iter).Data());
    }

    // Add the runid information for all files in the chain.
    //GetRunIdInfo(inputFile->GetName(), chainName);
    // Add the file to the input chain
    fInChain->Add( (*iter) );

    // Close the temporarly file and restore the gFile pointer.
    inputFile->Close();
    gFile = temp;

  }

//  fCurrentEntries =  (Int_t) fInChain->GetTree()->GetEntries();
//  cout<<"Input Chain has "<<fCurrentEntries<<" entries"<<endl;

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootManager::OpenInTree()
{
  cout << "-I- FairRootManager::OpenInTree() Opening fInTree: \"" << fInTree->GetCurrentFile()->GetName() << "\"" << endl;
  // Temporarily open the input file to extract information which
  // is needed to bring the friend trees in the correct order
  fInputFileName = fInTree->GetCurrentFile()->GetName();
  fInFile        = fInTree->GetCurrentFile();
  if (fInFile->IsZombie()) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
  }

  // Get the folder structure from file which describes the input tree.
  // There are two different names possible, so check both.
  fCbmroot= dynamic_cast <TFolder*> (fInFile->Get("cbmroot"));
  if(!fCbmroot) {
    fCbmroot= dynamic_cast <TFolder*> (fInFile->Get("cbmout"));
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
  TList* list= dynamic_cast <TList*> (fInFile->Get("BranchList"));
  TString chainName = "InputChain";
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

  // Store the information about the unique runids in the input file
  // together with the filename and the number of events for each runid
  // this information is needed later to check if inconsitencies exist
  // between the main input chain and any of the friend chains.

  //  GetRunIdInfo(fInFile->GetName(), chainName);

  for ( Int_t iobj = 0 ; iobj <= fNObj ; iobj++ ) {
    if ( fObj2[iobj] ) {
      cout << "-I- FairRootManager::OpenInTree(): Updating branch \"" << fObj2[iobj]->GetName()
           << "\" (\"" << fObj2[iobj]->GetTitle() << "\") in the new fInTree \"" << fInTree << "\"" << endl;
      TString tempBranchName = fObj2[iobj]->GetName();
      fInTree->SetBranchStatus (tempBranchName.Data(),1);
      fInTree->SetBranchAddress(tempBranchName.Data(),&fObj2[iobj]);
    }
  }

  Int_t nofEnt =  (Int_t) fInTree->GetEntries();

  cout << "-I- FairRootManager::OpenInTree() Input TREE has " << nofEnt << " entries." << endl;

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::AddFile(TString name)
{
  if(!fMixedInput) {
    fInputChainList.push_back(name);
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN, "You cannot use this method with mixed input!");
  }

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::PrintFriendList( )
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
    TChain* chain = (TChain*)mapIterator->second;
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

//_____________________________________________________________________________
void FairRootManager::CheckFriendChains()
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
  cout << "FairRootManager::OpenOutFile(\"" << fname << "\")" << endl;
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
void FairRootManager:: Write()
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
  if(fCbmroot!=0 && fInFile==0) {
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
  if ( fInTree ) {
    cout << "FairRootManager::ReadEvent(" << i << "): FROM THE TREE " << fInTree << endl;
    if(0==fCurrentEntryNo) {
      Int_t totEnt = fInTree->GetEntries();
      fLogger->Info(MESSAGE_ORIGIN,"The number of entries in the tree is %i",totEnt);
      cout << "FairRootManager::ReadEvent(" << i << "): The tree has " << totEnt << " entries" << endl;

      fEvtHeader = (FairEventHeader*) GetObject("EventHeader.");

      SetEventTime();
    }
    fCurrentEntryNo=i;
    fInTree->GetEntry(i);

    if(fEvtHeader !=0) {
      fEvtHeader->SetMCEntryNumber(i);
      fEvtHeader->SetEventTime(GetEventTime());
      fEvtHeader->SetInputFileId(0);
    } else { fLogger->Info(MESSAGE_ORIGIN, " No event Header was found!!!"); }
    return;
  }

  if(!fMixedInput) {
    /**Check for fCurrentEntryNo because it always starts from Zero, i could have any value! */
    if(0==fCurrentEntryNo) {
      Int_t totEnt = fInChain->GetEntries();
      fLogger->Info(MESSAGE_ORIGIN,"The number of entries in chain is %i",totEnt);

      fEvtHeader = (FairEventHeader*) GetObject("EventHeader.");

      SetEventTime();
    }
    fCurrentEntryNo=i;
    fInChain->GetEntry(i);

    if(fEvtHeader !=0) {
      fEvtHeader->SetMCEntryNumber(i);
      fEvtHeader->SetEventTime(GetEventTime());
      fEvtHeader->SetInputFileId(0);
    } else {
      fLogger->Info(MESSAGE_ORIGIN, " No event Header was found!!!");
    }

  } else {
    fLogger->Info(MESSAGE_ORIGIN,"Read mixed event number  %i", i);
    ReadMixedEvent(i);

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
        TChain* chain = fSignalTypeList[iterN->first];
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
      fBackgroundChain->GetEntry(i);
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
      Int_t totEnt = fBackgroundChain->GetEntries();
      fLogger->Info(MESSAGE_ORIGIN,"The number of entries in background chain is %i",totEnt);
    }
    fBackgroundChain->GetEntry(i);
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
FairGeoNode*  FairRootManager::GetGeoParameter(const char* detname, const char* gname)
{
  TFolder* detf= NULL;
  FairGeoNode* node = NULL;
  TList* lgeo=NULL;
  TString lname(detname);
  lname+="GeoPar";
  TFolder* froot =  dynamic_cast<TFolder*> (gROOT->FindObject("cbmroot"));
  if ( froot ) {
    detf = dynamic_cast<TFolder*> (froot->FindObjectAny( detname ));
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "GetGeoParameter() Main Folder not found ! ");
  }
  if ( detf    ) {
    lgeo = dynamic_cast<TList*> (detf->FindObjectAny( lname.Data() ));
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "GetGeoParameter() GeoPar: %s " , lname.Data() );
  }
  if ( lgeo    ) {
    node = dynamic_cast<FairGeoNode*> (lgeo->FindObject(gname));
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "GetGeoParameter() GeoList not found " );
  }
  return node;
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

    // Remove all occurence of FairMCEventHeader and FairEventHeader from
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
  fNObj++;
  fObj2[fNObj]  =  GetMemoryBranch ( BrName );
  if ( fObj2[fNObj]   ) {
    return  fObj2[fNObj];
  }
  /**try to find the object decribing the branch in the folder structure in file*/
  fLogger->Debug2(MESSAGE_ORIGIN, " Try to find an object %s decribing the branch in the folder structure in file", BrName);
  for(Int_t i=0; i<fListFolder.GetEntriesFast(); i++) {
    TFolder* fold = (TFolder*) fListFolder.At(i);
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
       * we can set the branch address to aal of them with one TClonesarray and then we call the proper
       * fill in the read (event) entry
       */

      fLogger->Debug2(MESSAGE_ORIGIN, "Set the Branch address for background branch %s", BrName);
      fBackgroundChain->SetBranchStatus(BrName,1);
      fBackgroundChain->SetBranchAddress(BrName,&fObj2[fNObj]);

      std::map<UInt_t, TChain*>::const_iterator iter;
      Int_t no=0;
      for(iter = fSignalTypeList.begin(); iter != fSignalTypeList.end(); iter++) {
        TChain* currentChain=iter->second;
        fLogger->Debug2(MESSAGE_ORIGIN, "Set the Branch address for signal file number %i  and  branch %s ", no++ , BrName);
        currentChain->SetBranchStatus(BrName,1);
        currentChain->SetBranchAddress(BrName,&fObj2[fNObj]);
      }


    } else {

      if ( fInTree ) {
        fInTree->SetBranchStatus (BrName,1);
        fInTree->SetBranchAddress(BrName,&fObj2[fNObj]);
      } else {
        fInChain->SetBranchStatus(BrName,1);
        fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
      }
    }
  }

  AddMemoryBranch( BrName , fObj2[fNObj] );
  return  fObj2[fNObj];

}

//_____________________________________________________________________________

//_____________________________________________________________________________
TObject* FairRootManager::ActivateBranchInInTree(const char* BrName)
{
  fNObj++;

  for(Int_t i=0; i<fListFolder.GetEntriesFast(); i++) {
    TFolder* fold = (TFolder*) fListFolder.At(i);
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
  Int_t returnvalue=0;
  TObject* Obj1 =NULL;
  if (fCbmroot) {
    Obj1 = fCbmroot->FindObjectAny(BrName);
  }
  if(fCbmout && !Obj1) {
    Obj1 = fCbmout->FindObjectAny(BrName);  //Branch in output folder
  }
  if(!Obj1) {
    for(Int_t i=0; i<fListFolder.GetEntriesFast(); i++) {
//      cout << "Search in Folder: " << i << "  " <<  listFolder.At(i) << endl;
      TFolder* fold = dynamic_cast<TFolder*> (fListFolder.At(i));
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
//      cout << " FairRootManager::CreatePerMap() Obj At " << i << "  is "  << name->GetString() << endl;
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
void FairRootManager::AddFriend(TString Name)
{
  fFriendFileList.push_back(Name);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootManager::AddFriendsToChain()
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
  map< TString, TChain* >::iterator mapIterator;
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
void FairRootManager::CreateNewFriendChain(TString inputFile, TString inputLevel)
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
  fListFolder.Add( added );

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

//_____________________________________________________________________________
Bool_t FairRootManager::CompareBranchList(TFile* fileHandle, TString inputLevel)
{
  // fill a set with the original branch structure
  // This allows to use functions find and erase
  std::set<TString> branches;
  list<TString>::const_iterator iter;
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
//void FairRootManager::GetRunIdInfo(TFile* fileHandle, TString inputLevel)
void FairRootManager::GetRunIdInfo(TString fileName, TString inputLevel)
{
  TFile* temp=gFile;
  TFile* fileHandle = new TFile(fileName);

  TTree* testTree = dynamic_cast<TTree*>(fileHandle->Get("cbmsim"));
  TFolder* folder = dynamic_cast<TFolder*>(fileHandle->Get("cbmroot"));
  if (!folder) {
    folder = dynamic_cast<TFolder*>(fileHandle->Get("cbmout"));
  }

  // Get the information about runid and start and stop event number
  // If there is a branch with this information use this information
  // directly. If not loop over all events and read the MCEventHeader
  // information to extract all different runids and start/stop event
  // numbers.

  FairEventHeader* header =
    (FairEventHeader*)folder->FindObjectAny("EventHeader.");
  // With the follwing two lines the MCEventHeader is not filled
  // correctely. The runid is correct but the event numbers are
  // zero all the time. This must be a bug.
  // TODO: Create example and submit a bug report to the ROOT team
  //   testTree->SetBranchStatus("*",0); //disable all branches
  //   testTree->SetBranchStatus("MCEventHeader.",1);
  testTree->SetBranchAddress("EventHeader.", &header);

  Int_t entries =  (Int_t) testTree->GetEntriesFast();


  TArrayI runidInfo(2);

  testTree->GetEntry(0);

  Int_t runid;
  Int_t counter = 1;
  runid = header->GetRunId();
  runidInfo.AddAt(runid,0);

  std::map<TString, std::multimap<TString,TArrayI> >::iterator it;

  std::multimap<TString, TArrayI>  myRunIdInfo;
  it=fRunIdInfoAll.find(inputLevel);
  if ( it != fRunIdInfoAll.end()) {
    myRunIdInfo=it->second;
  }

  for (Int_t i=1; i<entries ; i++) {
    testTree->GetEntry(i);
    runid = header->GetRunId();
    if ( runid != runidInfo[0] ) {
      runidInfo.AddAt(counter,1);
      // Fill info to structure
      myRunIdInfo.insert(pair<TString,TArrayI>(fileName,runidInfo));
      runidInfo.Reset();
      runid = header->GetRunId();
      runidInfo.AddAt(runid,0);
      counter = 0;
    }
    counter++;
  }

  runidInfo.AddAt(counter,1);
  myRunIdInfo.insert(pair<TString,TArrayI>(fileName,runidInfo));
  fRunIdInfoAll.erase(inputLevel);
  fRunIdInfoAll.insert(pair<TString, std::multimap<TString,TArrayI> >
                       (inputLevel, myRunIdInfo));

  fileHandle->Close();
  gFile=temp;
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
    MaxEventNo=fInChain->GetEntries();
  } else {
    Int_t MaxBG=fBackgroundChain->GetEntries();
    Int_t MaxS=0;
    Double_t ratio=0.;
    std::map<UInt_t, Double_t>::const_iterator iterN;
    for(iterN = fSignalBGN.begin(); iterN != fSignalBGN.end(); iterN++) {
      TChain* chain = fSignalTypeList[iterN->first];
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

ClassImp(FairRootManager)








