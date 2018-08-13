/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairRootFileSink                      -----
// -----                    Created 22.12.2017 by R. Karabowicz            -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#include "FairRootFileSink.h"
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
#include "FairRun.h"
#include "FairRootManager.h"            // to GetTreeName()
#include "TGeoManager.h"                // for TGeoManager, gGeoManager
#include "TRandom.h"                    // for TRandom, gRandom
#include "TROOT.h"
#include <list>                         // for _List_iterator, list, etc
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>

using std::map;
using std::set;

//_____________________________________________________________________________
FairRootFileSink::FairRootFileSink(TFile *f, const char* Title)
  :FairSink()
  , fOutputTitle(Title)
  , fRootFile(f)
  , fOutTree(0)
  , fListFolder(new TObjArray(16))
  , fCbmout(0)
  , fIsInitialized(kFALSE)
  , fFileHeader(0)
{
    if (fRootFile->IsZombie()) {
     LOG(FATAL) << "Error opening the Input file";
    }
    LOG(DEBUG) << "FairRootFileSink created------------";
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRootFileSink::FairRootFileSink(const TString* RootFileName, const char* Title)
  :FairSink()
  , fOutputTitle(Title)
  , fRootFile(0)
  , fOutTree(0)
  , fListFolder(new TObjArray(16))
  , fCbmout(0)
  , fIsInitialized(kFALSE)
  , fFileHeader(0)
{
    fRootFile = TFile::Open(RootFileName->Data(),"recreate");
    if (fRootFile->IsZombie()) {
      LOG(FATAL) << "Error opening the Output file";
    }
    LOG(DEBUG) << "FairRootFileSink created------------";
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRootFileSink::FairRootFileSink(const TString RootFileName, const char* Title)
  :FairSink()
  , fOutputTitle(Title)
  , fRootFile(0)
  , fOutTree(0)
  , fListFolder(new TObjArray(16))
  , fCbmout(0)
  , fIsInitialized(kFALSE)
  , fFileHeader(0)
{
    fRootFile = TFile::Open(RootFileName.Data(),"recreate");
    if (fRootFile->IsZombie()) {
      LOG(FATAL) << "Error opening the Input file";
    }
    LOG(DEBUG) << "FairRootFileSink created------------";
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRootFileSink::~FairRootFileSink()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
TFile* FairRootFileSink::OpenRootFile(TString fileName) {
  if ( fileName.Length() <= 5 ) return NULL;
  return TFile::Open(fileName.Data(),"recreate");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairRootFileSink::InitSink()
{
    if(fIsInitialized){
        LOG(INFO) << "FairRootFileSink already initialized";
        return kTRUE;
    }
    fIsInitialized = kTRUE;

    fRootFile->cd();

    //FairRun* fRun = FairRun::Instance();
    /**Check if a simulation run!*/
    fOutFolder= gROOT->GetRootFolder()->AddFolder(FairRootManager::GetFolderName(), "Main Folder");
    gROOT->GetListOfBrowsables()->Add(fOutFolder);
    
    LOG(INFO) << "FairRootFileSink initialized.";
    LOG(INFO) << " - " << fOutFolder->GetName();
    LOG(INFO) << "    - " << fRootFile->GetName();

    return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::TruncateBranchNames()
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
  TCollection* lf = fOutFolder->GetListOfFolders();
  TIterator* iter= lf->MakeIterator();
  TObjArray* Br= fOutTree->GetListOfBranches();
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
    TString ffn=(fOutFolder->GetName());
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
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::TruncateBranchNames(TBranch* b, TString ffn)
{
  /** Get the branch name from the branch object, remove common
  *  and wrong part of the name and and set branch name to
  *  the new corrected name. This has to be done recursivly for
  *  all subbranches/leaves
  *  Remove wrong part of branch name
  */
  TObject* BrObj;
  TString nn= b->GetName();
  LOG(DEBUG)<<"nn.Data before: "<<nn.Data();
  nn.ReplaceAll(ffn.Data(),"");
  LOG(DEBUG)<<"nn.Data after: "<<nn.Data();
  LOG(DEBUG) <<"##################";
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
void FairRootFileSink::Close()
{
    if(fRootFile)
      {
        fRootFile->Close();
      }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::Reset()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::FillEventHeader(FairEventHeader* feh)
{
  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::RegisterImpl(const char* name, const char *folderName, void* obj) {
  TFolder* folder=0;
  TFolder* f=0;
  f=static_cast<TFolder*>(fOutFolder->FindObjectAny(folderName));
  if(f==0) {
    folder= fOutFolder->AddFolder(folderName,folderName);
  } else {
    folder=f;
  }
    //  ((TNamed*)obj)->SetName(name);
  folder->Add((TNamed*)obj);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj) {
  fPersistentBranchesMap[brname]=std::unique_ptr<TypeAddressPair const> (new TypeAddressPair(oi, pi,obj));
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::WriteFolder() {
  fRootFile->cd();
  if(fOutFolder!=0) {
    fOutFolder->Write();

    //FairRun* fRun = FairRun::Instance();
    fOutTree =new TTree(FairRootManager::GetTreeName(), Form("/%s", FairRootManager::GetFolderName()), 99);
    TruncateBranchNames();
    CreatePersistentBranchesAny();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
namespace impl
{
  inline
  // a helper function to demangle a type_name
  std::string demangle(const char* name)
  {
    int status = -4; // some arbitrary value to eliminate the compiler warning
    std::unique_ptr<char, void (*)(void*)> res{ abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free };
    return (status == 0) ? res.get() : name;
  }
}

bool FairRootFileSink::CreatePersistentBranchesAny()
{
  for(auto& iter : fPersistentBranchesMap)
    {
      LOG(INFO) << "CREATING BRANCH " << iter.first;
      auto &tinfo = iter.second->persistenttypeinfo;
      auto tname = impl::demangle(tinfo.name());

      // for the branch creation we need a TClass describing the object
      // get it from ROOT via the type name
      auto cl = TClass::GetClass(tinfo);
      if(!cl) {
        LOG(FATAL) << "No TClass found for " << tname << "\n";
        return false;
      }

      if(!cl->HasDictionary()) {
        LOG(FATAL) << "No dictionary found for " << tname << "\n";
        return false;
      }

      // create the branch
      auto obj = iter.second->ptraddr;

      LOG(INFO) << "Creating branch for " << iter.first.c_str() << " with address " << obj;
      fOutTree->Branch(iter.first.c_str(), tname.c_str(), obj);
    }
  return true;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::WriteObject(TObject* f, const char* name, Int_t option) {
  fRootFile->cd();
  f->Write(name, option);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::WriteGeometry() {
  fRootFile->cd();
  gGeoManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRootFileSink::Fill() {
  if (fOutTree != 0) {
    fOutTree->Fill();
  } else {
    LOG(INFO) << " No Output Tree";
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t FairRootFileSink::Write(const char*, Int_t, Int_t)
{
  /** Writes the tree in the file.*/
  if(fOutTree!=0) {
    /** Get the file handle to the current output file from the tree.
      * If ROOT splits the file (due to the size of the file) the file
      * handle fOutFile is lost and the program crash while writing the
      * last part of the last file.
    */

    // fOutTree->Print();

    fRootFile = fOutTree->GetCurrentFile();
    LOG(DEBUG) << "FairRootFileSink::Write to file: "  << fRootFile->GetName();
    fRootFile->cd();
    fOutTree->Write();
  } else {
    LOG(INFO) << "No Output Tree";
  }
  return 0;
}

ClassImp(FairRootFileSink)
