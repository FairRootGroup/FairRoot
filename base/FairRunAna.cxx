// -------------------------------------------------------------------------
// -----                   FairRunAna source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunAna.h"

#include "FairRootManager.h"
#include "FairTask.h"
#include "FairBaseParSet.h"
#include "FairEventHeader.h"
#include "FairFieldFactory.h"
#include "FairRuntimeDb.h"
#include "TROOT.h"
#include "TTree.h"
#include "FairTrajFilter.h"
#include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
#include "FairRunIdGenerator.h"
#include "FairLogger.h"
#include "FairFileHeader.h"


#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;


//_____________________________________________________________________________
FairRunAna* FairRunAna::fgRinstance= 0;
//_____________________________________________________________________________
FairRunAna* FairRunAna::Instance()
{

  return fgRinstance;
}
//_____________________________________________________________________________
FairRunAna::FairRunAna()
  :FairRun(),
   //   fFriendFileList(new TObjArray()),
   fIsInitialized(kFALSE),
   //   fInputFile(0),
   fInputGeoFile(0),
   fLoadGeo( kFALSE),
   fEvtHeader(0),
   fStatic(kFALSE),
   fField(0),
   fTimeStamps(kFALSE),
   fInFileIsOpen(kFALSE)
{

  fgRinstance=this;
  fAna=kTRUE;
}
//_____________________________________________________________________________

FairRunAna::~FairRunAna()
{
  //  delete fFriendFileList;
  if(fField) { delete fField; }
  if(gGeoManager) { delete gGeoManager; }
}

//_____________________________________________________________________________

void  FairRunAna::SetGeomFile(const char* GeoFileName)
{
  if(fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN, "Geometry file has to be set before Run::Init !") ;
    exit(-1);
  } else {

    TFile* CurrentFile=gFile;
    fInputGeoFile= new TFile(GeoFileName);
    if (fInputGeoFile->IsZombie()) {
      fLogger->Error(MESSAGE_ORIGIN, "Error opening Geometry Input file");
      fInputGeoFile=0;
    }
    fLogger->Info(MESSAGE_ORIGIN, " Opening Geometry input file: %s ", GeoFileName);
    fLoadGeo=kTRUE;
    gFile=CurrentFile;
  }
}

//_____________________________________________________________________________

void FairRunAna::Init()
{

  if(fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Error Init is already called before!");
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }

  // Open the input file and add other input files added by AddFile to the
  // input chain. Do a check if the added files are of the same type
  // as the the input file. Same type means check if they contain the
  // same branch.
  fInFileIsOpen = fRootManager->OpenInChain();

  if (fInFileIsOpen) {

    // Add all friend files defined by AddFriend to the correct chain
    fRootManager->AddFriendsToChain();

    //Load geometry
    if(fLoadGeo) {
      if(fInputGeoFile!=0) { //First check if the user has a separate Geo file!
        TIter next(fInputGeoFile->GetListOfKeys());
        TKey* key;
        while ((key = (TKey*)next())) {
          if (strcmp(key->GetClassName(),"TGeoManager") != 0) { continue; }
          gGeoManager = (TGeoManager*)key->ReadObj();
          break;
        }
      } else { //try the input file
        //  fInputFile->Get("FAIRGeom");
        // The geometry must be in the first file
        fRootManager->GetInChain()->GetFile()->Get("FAIRGeom");
      }
    }
    //check that the geometry was loaded if not try all connected files!
    if(gGeoManager==0) {
      fLogger->Info(MESSAGE_ORIGIN, "Geometry was not found in the input file we will look in the friends if any!" );
      TFile* currentfile= gFile;
      TFile* nextfile=0;
      TSeqCollection* fileList=gROOT->GetListOfFiles();
      for (Int_t k=0; k<fileList->GetEntries(); k++) {
        nextfile=(TFile*)fileList->At(k);
        if(nextfile) { nextfile->Get("FAIRGeom"); }
        if(gGeoManager) { break; }
      }
      gFile=currentfile;
    }
  } else { //  if(fInputFile )
    // NO input file but there is a geometry file
    if(fLoadGeo) {
      if(fInputGeoFile!=0) { //First check if the user has a separate Geo file!
        TIter next(fInputGeoFile->GetListOfKeys());
        TKey* key;
        while ((key = (TKey*)next())) {
          if (strcmp(key->GetClassName(),"TGeoManager") != 0) { continue; }
          gGeoManager = (TGeoManager*)key->ReadObj();
          break;
        }
      }
    }
  }
  //Init the Chain ptr
  //  fcurrent = fChainList.begin();
  TFile* Output = fRootManager->OpenOutFile(Outfname);
  // <DB> forwarding ptr
  fOutFile= Output;
  gROOT->GetListOfBrowsables()->Add(fTask);
  // Init the RTDB containers
  fRtdb= GetRuntimeDb();
  FairBaseParSet* par=(FairBaseParSet*)
                      (fRtdb->getContainer("FairBaseParSet"));

  /**Set the IO Manager to run with time stamps*/
  if(fTimeStamps) { fRootManager->RunWithTimeStamps(); }

  // Assure that basic info is there for the run
  //  if(par && fInputFile) {
  if(par && fInFileIsOpen) {
    fRootManager->ReadEvent(0);
    fEvtHeader = (FairEventHeader*)
                 fRootManager->GetObject("EventHeader.");
    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    fRunId = fEvtHeader->GetRunId();
    // Init the containers in Tasks
    fRtdb->initContainers(fRunId);
    fTask->SetParTask();
    fRtdb->initContainers( fRunId );
    if(gGeoManager==0) { par->GetGeometry(); }
    //  fRootManager->SetBranchNameList(par->GetBranchNameList());
  } else {

    FairEventHeader* evt = this->GetEventHeader();
    evt->Register();

    FairRunIdGenerator genid;
    fRunId = genid.generateId();
    fRtdb->addRun(fRunId);
    evt->SetRunId( fRunId);
    fTask->SetParTask();
    fRtdb->initContainers( fRunId );

  }
  FairFieldFactory* fieldfact= FairFieldFactory::Instance();
  if(fieldfact) { fieldfact->SetParm(); }

  fRtdb->initContainers(fRunId);
  fFileHeader->SetRunId(fRunId);
  // create a field
  // <DB>
  // Add test for external FairField settings
  if(fieldfact && !fField) { fField= fieldfact->createFairField(); }
  // Now call the User initialize for Tasks
  fTask->InitTask();
  // if the vis manager is available then initialize it!
  FairTrajFilter* fTrajFilter = FairTrajFilter::Instance();
  if(fTrajFilter) { fTrajFilter->Init(); }
  // create the output tree after tasks initialisation
  Output->cd();
  TTree* outTree =new TTree("cbmsim", "/cbmout", 99);
  fRootManager->TruncateBranchNames(outTree, "cbmout");
  fRootManager->SetOutTree(outTree);
  fRootManager->WriteFolder();
  fRootManager->WriteFileHeader(fFileHeader);
}
//_____________________________________________________________________________
void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{

  if(fTimeStamps) {
    RunTSBuffers();
  } else {

    UInt_t tmpId =0;
    //  if (fInputFile==0) {
    if (!fInFileIsOpen) {
      DummyRun(Ev_start,Ev_end);
      return;
    }
    if(Ev_end==0) {
      if (Ev_start==0) {
        Ev_end=Int_t((fRootManager->GetInChain())->GetEntries());
      } else {
        Ev_end =  Ev_start;
        if ( Ev_end > ((fRootManager->GetInChain())->GetEntries()) ) {
          Ev_end = (Int_t) (fRootManager->GetInChain())->GetEntries();
        }
        Ev_start=0;
      }
    } else {
      Int_t fileEnd=(fRootManager->GetInChain())->GetEntries();
      if(Ev_end > fileEnd) {
        cout << "-------------------Warning---------------------------" << endl;
        cout << " -W FairRunAna : File has less events than requested!!" << endl;
        cout << " File contains : " << fileEnd  << " Events" << endl;
        cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
        cout << " The number of events is set to " << fileEnd << " Events"<< endl;
        cout << "-----------------------------------------------------" << endl;
        Ev_end = fileEnd;
      }

    }

    for (int i=Ev_start; i< Ev_end; i++) {
      fRootManager->ReadEvent(i);
      tmpId = fEvtHeader->GetRunId();
      if ( tmpId != fRunId ) {
        fRunId = tmpId;
        if( !fStatic ) {
          cout << " -I FairRunAna : reinitialization done for RunID: "
               << fRunId << endl;

          Reinit( fRunId );
          fTask->ReInitTask();
        }
      }

      fTask->ExecuteTask("");
      fRootManager->Fill();
      fTask->FinishEvent();

      if(NULL !=  FairTrajFilter::Instance()) { FairTrajFilter::Instance()->Reset(); }

    }
    fTask->FinishTask();
    fRootManager->Write();
  }
}
//_____________________________________________________________________________

void FairRunAna::Run(Double_t delta_t)
{
  while (fRootManager->ReadNextEvent(delta_t)==kTRUE) {
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fTask->FinishEvent();
    if(NULL !=  FairTrajFilter::Instance()) { FairTrajFilter::Instance()->Reset(); }
  }
  fTask->FinishTask();
  fRootManager->Write();

}

//_____________________________________________________________________________
void FairRunAna::Run(Long64_t entry)
{


  if(fTimeStamps) {
    RunTSBuffers();
  } else {
    UInt_t tmpId =0;
    fRootManager->ReadEvent(entry);
    tmpId = fEvtHeader->GetRunId();
    if ( tmpId != fRunId ) {
      fRunId = tmpId;
      if( !fStatic ) {
        cout << " -I FairRunAna : reinitialization done for RunID: "
             << fRunId << endl;

        Reinit( fRunId );
        fTask->ReInitTask();
      }
    }
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fTask->FinishTask();
    fRootManager->Write();
  }
}
//_____________________________________________________________________________
void FairRunAna::RunTSBuffers()
{
  Int_t globalEvent = 0;

  bool firstRun = true;
  while (firstRun || fRootManager->AllDataProcessed() == kFALSE) {
    firstRun = false;
    if(globalEvent + 1 < fRootManager->GetInTree()->GetEntriesFast()) { //this step is necessary to load in all data which is not read in via TSBuffers
      fRootManager->ReadEvent(globalEvent++);
    }
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fTask->FinishEvent();
    if(NULL !=  FairTrajFilter::Instance()) { FairTrajFilter::Instance()->Reset(); }
  }
  fTask->FinishTask();
  fRootManager->Write();
}
//_____________________________________________________________________________
void FairRunAna::DummyRun(Int_t Ev_start, Int_t Ev_end)
{

  /** This methode is just for testing, if you are not sure about what you do, don't use it */
  for (int i=Ev_start; i< Ev_end; i++) {
    fTask->ExecuteTask("");
    fRootManager->Fill();
  }
  fTask->FinishTask();
  fRootManager->Write();

}
//_____________________________________________________________________________

void FairRunAna::SetInputFile(TString name)
{
  fRootManager->SetInputFile(name);
  fFileHeader->AddInputFileName(name);
}
//_____________________________________________________________________________
/*
void FairRunAna::SetInputFile(TFile* f)
{
  if (f->IsZombie()) {
    cout << "-E- FairRunAna: Error opening Input file" << endl;
    exit(-1);
  } else {
    fInputFile=f;
  }
  fCurrentFileName = TString( f->GetName());
}
*/
//_____________________________________________________________________________
void FairRunAna::AddFriend (TString Name)
{
  if(fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN, "AddFriend has to be set before Run::Init !");
  } else {
    fRootManager->AddFriend(Name);
    fFileHeader->AddInputFileName(Name);
  }
}
//_____________________________________________________________________________
/*
void FairRunAna::AddFriend (TString Name, Int_t friendType)
{
  if(fIsInitialized) {
    cout << "-E- FairRunAna: Error, AddFriend has to be set before Run::Init !" << endl;
    exit(-1);
  } else {
    fRootManager->AddFriend(Name, 1);
  }
}
*/
//_____________________________________________________________________________

void FairRunAna::Reinit(UInt_t runId)
{
  // reinit procedure
  fRtdb->initContainers( runId );
}
//_____________________________________________________________________________

void FairRunAna::AddFile(TString name)
{
  fRootManager->AddFile(name);
  fFileHeader->AddInputFileName(name);

}
//_____________________________________________________________________________

void  FairRunAna::RunWithTimeStamps()
{
  if(ROOT_VERSION_CODE >= ROOT_VERSION(5,29,1)) {
    if(fIsInitialized) {
      fLogger->Warning(MESSAGE_ORIGIN, "RunWithTimeStamps has to be set before Run::Init !");
      exit(-1);
    } else {
      fTimeStamps=kTRUE;
    }
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN, "RunWithTimeStamps need at least ROOT version 5.29.1") ;
  }
}
//_____________________________________________________________________________

void FairRunAna::CompressData()
{
  fRootManager->SetCompressData(kTRUE);
}


ClassImp(FairRunAna)


