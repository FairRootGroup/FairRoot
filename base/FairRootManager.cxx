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
#include "FairLogger.h"
#include "FairMCEventHeader.h"
#include "FairEventHeader.h"

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

#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>

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
FairRootManager::FairRootManager()
  : TObject(),
    fCbmout(NULL),
    fCbmroot(NULL),
    fCurrentTime(0),
    fInFile(NULL),
    fInChain( new TChain("cbmsim", "/cbmroot")),
    fOutFile(NULL),
    fOutTree(NULL),
    fListFolder(0),
    fObj2(new TObject*[100]),
    fNObj(-1),
    fMap(),
    fPtrTree(NULL),
    fCurrentEntries(0),
    fBranchSeqId(0),
    fBranchNameList(new TList()),
    fDataContainer(),
    fActiveContainer(),
    fCompressData(kFALSE),
    fFriendTypeList(),
    fTimeStamps(kFALSE),
    fBranchPerMap(kFALSE),
    fBrPerMap(),
    fFriendFileList(),
    fBrPerMapIter(),
    fInputFileName(""),
    fLogger(FairLogger::GetLogger())
{
  if (fgInstance) {
    Fatal("FairRootManager", "Singleton instance already exists.");
    return;
  }
  fgInstance = this;
}
//_____________________________________________________________________________
FairRootManager::~FairRootManager()
{
//
  cout<<"Enter Destructor of FairRootManager"<<endl;
// if(fCbmout) delete fCbmout;
// if(fCbmroot) delete fCbmroot;
  if(fInFile) { delete fInFile; }
  if(fInChain) { delete fInChain; }
  if(fOutTree) { delete fOutTree; }
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
  cout<<"Leave Destructor of FairRootManager"<<endl;
}
//_____________________________________________________________________________

Bool_t FairRootManager::OpenInChain()
{
  if ( fInputFileName.IsNull() ) {
    FairLogger* logger = FairLogger::GetLogger();
    logger->Info(MESSAGE_ORIGIN, "No input file defined.");
    return kFALSE;
  }

  // Temporarily open the input file to extract information which
  // is needed to bring the friend trees in the correct order
  fInFile = new TFile(fInputFileName);
  if (fInFile->IsZombie()) {
    FairLogger* logger = FairLogger::GetLogger();
    logger->Fatal(MESSAGE_ORIGIN, "Error opening the Input file");
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
  GetRunIdInfo(fInFile->GetName(), chainName);

  // Add all additional input files to the input chain and do a
  // consitency check
  std::list<TString>::const_iterator iter;
  for(iter = fInputChainList.begin(); iter != fInputChainList.end(); iter++) {
    // Store global gFile pointer for safety reasons.
    // Set gFile to old value at the end of the routine.
    TFile* temp = gFile;

    // Temporarily open the input file to extract information which
    // is needed to bring the friend trees in the correct order
    TFile* inputFile = new TFile((*iter));
    if (inputFile->IsZombie()) {
      FairLogger* logger = FairLogger::GetLogger();
      logger->Fatal(MESSAGE_ORIGIN, "Error opening the file %s which should be added to the input chain or as friend chain", (const char*)(*iter));
    }

    // Check if the branchlist is the same as for the first input file.
    Bool_t isOk = CompareBranchList(inputFile, chainName);
    if ( !isOk ) {
      FairLogger* logger = FairLogger::GetLogger();
      logger->Fatal(MESSAGE_ORIGIN, "Branch structure of the input file %s and the file to be added %s are different.", (const char*)fInputFileName, (const char*)(*iter));
    }

    // Add the runid information for all files in the chain.
    GetRunIdInfo(inputFile->GetName(), chainName);
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

void FairRootManager::AddFile(TString name)
{
  fInputChainList.push_back(name);
}

void FairRootManager::PrintFriendList( )
{
  // Print information about the input structure
  // List files from the input chain together with all files of
  // all friend chains

  fLogger->Info(MESSAGE_ORIGIN,
                "The input consists out of the following trees and files:");
  fLogger->Info(MESSAGE_ORIGIN," - %s",(const char*)fInChain->GetName());
  TObjArray* fileElements=fInChain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement* chEl=0;
  while (( chEl=(TChainElement*)next() )) {
    fLogger->Info(MESSAGE_ORIGIN,"    - %s",(const char*)chEl->GetTitle());
  }

  map< TString, TChain* >::iterator mapIterator;
  for (mapIterator = fFriendTypeList.begin();
       mapIterator != fFriendTypeList.end(); mapIterator++ ) {
    TChain* chain = (TChain*)mapIterator->second;
    fLogger->Info(MESSAGE_ORIGIN," - %s",(const char*)chain->GetName());
    fileElements=chain->GetListOfFiles();
    TIter next1(fileElements);
    chEl=0;
    while (( chEl=(TChainElement*)next1() )) {
      fLogger->Info(MESSAGE_ORIGIN,"    - %s",(const char*)chEl->GetTitle());
    }
  }

}

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
error_label:
  if (errorFlag>0) {
    fLogger->Error(MESSAGE_ORIGIN,"The input chain and the friend chain %s have a different structure:", (const char*)inputLevel);
    if (errorFlag == 1) {
      fLogger->Error(MESSAGE_ORIGIN,"The input chain has the following runids and event numbers:");
      for ( Int_t i=0; i<runid.size(); i++) {
        fLogger->Error(MESSAGE_ORIGIN," - Runid %i with %i events", runid[i], events[i]);
      }
      fLogger->Error(MESSAGE_ORIGIN,"The %s chain has the following runids and event numbers:", (const char*)inputLevel);
      for ( it=map1.begin() ; it != map1.end(); it++ ) {
        TArrayI bla = (*it).second;
        fLogger->Error(MESSAGE_ORIGIN," - Runid %i with %i events", bla[0], bla[1]);
      }
    }
    if (errorFlag == 2) {
      Int_t counter = 0;
      for ( it=map1.begin() ; it != map1.end(); it++ ) {
        TArrayI bla = (*it).second;
        fLogger->Error(MESSAGE_ORIGIN,"Runid Input Chain, %s chain: %i, %i", (const char*)inputLevel, bla[0], runid[counter]);
        fLogger->Error(MESSAGE_ORIGIN,"Event number Input Chain, %s chain: %i, %i", (const char*)inputLevel, bla[1], events[counter]);
        counter++;
      }
    }
    fLogger->Fatal(MESSAGE_ORIGIN,"Event structure mismatch");
  }
}

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
TFile* FairRootManager::OpenOutFile(TFile* f)
{
  fOutFile=f;
  /**Check the output file, if anything wronge with it exit!*/
  if (fOutFile->IsZombie()) {
    cout << "-E- FairRootManager: Error opening output file " << endl;
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
TFile* FairRootManager::OpenOutFile(const char* fname)
{
  if(fOutFile) { CloseOutFile(); }
  fOutFile = new TFile(fname, "recreate");
  return OpenOutFile(fOutFile);
}
//_____________________________________________________________________________
void  FairRootManager::Register(const char* name, const char* folderName , TNamed* obj, Bool_t toFile)
{
  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=(TFolder*)fCbmroot->FindObjectAny(folderName);
      if(f==0) { folder= fCbmroot->AddFolder(folderName,folderName); }
      else { folder=f; }
    } else {
      f=(TFolder*)fCbmout->FindObjectAny(folderName);
      if(f==0) { folder= fCbmout->AddFolder(folderName,folderName); }
      else { folder=f; }
    }
    obj->SetName(name);
    folder->Add(obj);
  }
  AddMemoryBranch(name, obj );
  //cout << " FairRootManager::Register Adding branch:(Obj) " << name << " In folder : " << folderName << endl;
  if(fBranchNameList->FindObject(name)==0) {
    ;
    fBranchNameList->AddLast(new TObjString(name));
    fBranchSeqId++;
  }
}

//_____________________________________________________________________________
void  FairRootManager::Register(const char* name,const char* Foldername ,TCollection* obj, Bool_t toFile)
{
  /**
  * This method do exactly the same as the one before but for TCollection which is a TObject and not a TNamed (MT)
  */
  if(toFile) { /**Write the Object to the Tree*/
    TFolder* folder=0;
    TFolder* f=0;
    if(fCbmout==0) {
      f=(TFolder*)fCbmroot->FindObjectAny(Foldername);
      if(f==0) { folder= fCbmroot->AddFolder(Foldername,Foldername); }
      else { folder=f; }
    } else {
      f=(TFolder*)fCbmout->FindObjectAny(Foldername);
      if(f==0) { folder= fCbmout->AddFolder(Foldername,Foldername); }
      else { folder=f; }
    }
    obj->SetName(name);
    folder->Add(obj);
  }
  /**Keep the Object in Memory, and do not write it to the tree*/
  AddMemoryBranch(name, obj );
  if(fBranchNameList->FindObject(name)==0) {
    ;
    fBranchNameList->AddLast(new TObjString(name));
    fBranchSeqId++;
  }
}
//_____________________________________________________________________________
TClonesArray* FairRootManager::Register(TString branchName, TString className, TString folderName, Bool_t toFile)
{

  TClonesArray* outputArray;
  fActiveContainer[branchName] = new TClonesArray(className);
  if (fCompressData) {
    std::queue<TClonesArray*> myQueue;
    fDataContainer[branchName] = myQueue;
    outputArray = new TClonesArray(className);
  } else { outputArray = fActiveContainer[branchName]; }
  Register(branchName, folderName, outputArray, toFile);
  return fActiveContainer[branchName];
}
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
  } else { std::cout << "-E- Branch: " << branchName << " not registered!" << std::endl; }
  // error if the branch is not registered
  return 0;
}


//_____________________________________________________________________________
TClonesArray* FairRootManager::GetDataContainer(TString branchName)
{
  if (DataContainersFilled()) {
    return fDataContainer[branchName].front();
  }
  return 0;
}
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
void  FairRootManager::Fill()
{
// Fills the tree.
// ---
  if (fCompressData) {
    if (DataContainersFilled()) {
      AssignTClonesArrays();
      ForceFill();
    }
  } else { ForceFill(); }
}
void FairRootManager::ForceFill()
{
  if (fOutTree != 0) {
    fOutTree->Fill();
  } else {
    cout << "-E- FairRootManager::Fill()  No Output Tree" << endl;
  }
}
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
    cout << "-E- FairRootManager::Write()  No Output Tree"  << endl;
  }
}
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
void  FairRootManager::ReadEvent(Int_t i)
{

  if(0==i) {
    Int_t totEnt = fInChain->GetEntries();
    fLogger->Info(MESSAGE_ORIGIN,"The number of entries in chain is %i",totEnt);
  }

  fInChain->GetEntry(i);

}
//_____________________________________________________________________________
Bool_t FairRootManager::ReadNextEvent(Double_t dt)
{
  Bool_t readentry=kFALSE;
  ///TODO
  return readentry;
}


//_____________________________________________________________________________
TObject* FairRootManager::GetObject(const char* BrName)
{
  /**Get Data object by name*/
  TObject* Obj =NULL;
  /**Try to fine the object in the folder structure, object already activated by other task or call*/
  if(fCbmout) { Obj = fCbmout->FindObjectAny(BrName); }
  /**if the object does not exist then it could be a memory branch */
  if(!Obj) {  Obj=GetMemoryBranch(BrName); }
  /**if the object does not exist then look in the input tree */
  if(fCbmroot && !Obj) {
    /** there is an input tree and the object was not in memory */
    Obj=fCbmroot->FindObjectAny(BrName);
    Obj=ActivateBranch(BrName);
  }
  if(!Obj) {  Obj=ActivateBranch(BrName); }
  return Obj;
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
  if ( froot ) { detf = dynamic_cast<TFolder*> (froot->FindObjectAny( detname )); }
  else { cout << "-E- GetGeoParameter() Main Folder not found ! " << endl; }
  if ( detf    ) { lgeo = dynamic_cast<TList*> (detf->FindObjectAny( lname.Data() )); }
  else { cout << "-E- GetGeoParameter() GeoPar: " << lname << endl; }
  if ( lgeo    ) { node = dynamic_cast<FairGeoNode*> (lgeo->FindObject(gname)); }
  else { cout << "-E- GetGeoParameter() GeoList not found " << endl; }
  return node;
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

Int_t FairRootManager::CheckBranch(const char* BrName)
{
  /**The first time this method is called the map is generated and then used*/
  if(!fBranchPerMap) {
    CreatePerMap();
    return CheckBranchSt(BrName);
  } else {
    fBrPerMapIter=fBrPerMap.find(BrName);
    if(fBrPerMapIter!=fBrPerMap.end()) { return fBrPerMapIter->second; }
    else { return 0; }
  }
}

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
  for(Int_t i=0; i<fListFolder.GetEntriesFast(); i++) {
    TFolder* fold = (TFolder*) fListFolder.At(i);
    fObj2[fNObj] = fold->FindObjectAny(BrName);
    if (fObj2[fNObj] ) { break; }
  }

  if(!fObj2[fNObj]) {
    /** if we do not find an object corresponding to the branch in the folder structure
    *  then we have no idea about what type of object is this and we cannot set the branch address
    */
    cout << "-E- FairRootManager Branch: "  << BrName  << " not found in Tree" << endl;
    //Fatal(" No Branch in the tree", BrName );
    return 0;
  } else {
    fInChain->SetBranchStatus(BrName,1);
    fInChain->SetBranchAddress(BrName,&fObj2[fNObj]);
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
    //  cout << " -E- FairRootManager::AddMemoryBranch " << BrName << " is already inserted " << endl;
  } else {
    //  cout << " -E- FairRootManager::AddMemoryBranch " << BrName << " isAdded " << endl;
    fMap.insert(pair<TString, TObject*> (BrName, pObj));
  }
}
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
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,27,4)
  if (input != 0) {
    output->AbsorbObjects(input);
  }
#else
  cout <<"FairRootManager::AssignTClonesArray(TString branchName) "<<endl;
  cout <<"Is only available in ROOT 5.27-04 "<<endl;
#endif
}
//_____________________________________________________________________________
Int_t FairRootManager::CheckBranchSt(const char* BrName)
{
  Int_t returnvalue=0;
  TObject* Obj1 =NULL;
  if (fCbmroot) { Obj1 = fCbmroot->FindObjectAny(BrName); }
  if(fCbmout && !Obj1) { Obj1 = fCbmout->FindObjectAny(BrName); }  //Branch in output folder
  if(!Obj1) {
    for(Int_t i=0; i<fListFolder.GetEntriesFast(); i++) {
//      cout << "Search in Folder: " << i << "  " <<  listFolder.At(i) << endl;
      TFolder* fold = dynamic_cast<TFolder*> (fListFolder.At(i));
      if(fold!=0) { Obj1= fold->FindObjectAny(BrName); }
      if (Obj1) { break; }
    }
  }
  TObject* Obj2 =NULL;
  Obj2=GetMemoryBranch(BrName);  // Branch in Memory
  if (Obj1!=0) { returnvalue=1; }
  else if(Obj2!=0) { returnvalue=2; }
  else { returnvalue= 0; }

  /**  1 : Branch is Persistance
       2 : Memory Branch
       0 : Branch does not exist
  */
  return returnvalue;
}
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
TObject*  FairRootManager::GetMemoryBranch( const char* fName )
{

//return fMap[BrName];
  TString BrName=fName;
  map < TString, TObject*>::iterator p;
  p=fMap.find(BrName);

  if(p!=fMap.end()) {
    return p->second;
    //    cout << " -E- FairRootManager::GetMemoryBranch " << BrName << " is found " << endl;
  } else {
    // cout << " -E- FairRootManager::GetMemoryBranch " << BrName << " Not found " << endl;
    return 0;
  }
}
//_____________________________________________________________________________
void FairRootManager::SaveAllContainers()
{
  while(!DataContainersEmpty()) {
    AssignTClonesArrays();
    ForceFill();
  }
}
//_____________________________________________________________________________

void FairRootManager::AddFriend(TString Name)
{
  fFriendFileList.push_back(Name);
}
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
        FairLogger* logger = FairLogger::GetLogger();
        logger->Fatal(MESSAGE_ORIGIN, "Error opening the file %s which should be added to the input chain or as friend chain", (const char*)(*iter));
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

    GetRunIdInfo((*iter1), inputLevel);
    TChain* chain = (TChain*) fFriendTypeList[inputLevel];
    chain->AddFile((*iter1), 1234567890, "cbmsim");
  }
  gFile=temp;

  // Check if all friend chains have the same runids and the same
  // number of event numbers as the corresponding input chain
  CheckFriendChains();

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

ClassImp(FairRootManager)








