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
#include "FairTrajFilter.h"
#include "FairRunIdGenerator.h"
#include "FairLogger.h"
#include "FairFileHeader.h"


#include "TROOT.h"
#include "TTree.h"
#include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
#include "TF1.h"


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
   fInFileIsOpen(kFALSE),
   fMixedInput(kFALSE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0)
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
  if(!fMixedInput) { fInFileIsOpen = fRootManager->OpenInChain(); }
  else {
    Bool_t openBKChain = fRootManager->OpenBackgroundChain();
    if(!openBKChain) { fLogger->Fatal(MESSAGE_ORIGIN, "Could not open background Chain!"); }
    fRootManager->OpenSignalChain();
  }
  //Load Geometry from user file

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
  if (fInFileIsOpen) {
    // Add all friend files defined by AddFriend to the correct chain
    fRootManager->AddFriendsToChain();
    if(fLoadGeo && gGeoManager==0) {
      // Check if the geometry in the first file of the Chain
      fRootManager->GetInChain()->GetFile()->Get("FAIRGeom");
    }
    //check that the geometry was loaded if not try all connected files!
    if(fLoadGeo && gGeoManager==0) {
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
  } else if(fMixedInput) {



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
// fOutFile = fRootManager->OpenOutFile(fOutname);

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

  } else if (fMixedInput) {
    fLogger->Info(MESSAGE_ORIGIN,"Initializing for Mixed input");

    //For mixed input we have to set containers to static becauser of the different run ids
    //fRtdb->setContainersStatic(kTRUE);

    fEvtHeader = (FairEventHeader*) fRootManager->GetObject("EventHeader.");
    if(fEvtHeader==0) { fEvtHeader=GetEventHeader(); }


    fRootManager->ReadBKEvent(0);

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    fRunId = fEvtHeader->GetRunId();
    // Init the containers in Tasks
    fRtdb->initContainers(fRunId);

    if(gGeoManager==0) {
      fLogger->Info(MESSAGE_ORIGIN,"Read the Geometry from Parameter file");
      par->GetGeometry();

    }
    if(gGeoManager==0) { fLogger->Fatal(MESSAGE_ORIGIN,"Could not Read the Geometry from Parameter file"); }
    fTask->SetParTask();
    fRtdb->initContainers( fRunId );

  } else {
    fLogger->Info(MESSAGE_ORIGIN,"Initializing without input file or Mixed input");
    FairEventHeader* evt = GetEventHeader();
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
  fOutFile->cd();
  TTree* outTree =new TTree("cbmsim", "/cbmout", 99);
  fRootManager->TruncateBranchNames(outTree, "cbmout");
  fRootManager->SetOutTree(outTree);
  fRootManager->WriteFolder();
  fRootManager->WriteFileHeader(fFileHeader);
}
//_____________________________________________________________________________
void FairRunAna::RunMixed(Int_t Ev_start, Int_t Ev_end)
{

  fLogger->Debug(MESSAGE_ORIGIN,"Running in mixed mode");
  Int_t MaxAllowed=fRootManager->CheckMaxEventNo(Ev_end);
  if(Ev_end==0) {
    if (Ev_start==0) {
      Ev_end=MaxAllowed;
    } else {
      Ev_end =  Ev_start;
      if ( Ev_end > MaxAllowed ) {
        Ev_end = MaxAllowed;
      }
      Ev_start=0;
    }
  } else {
    if(Ev_end > MaxAllowed) { Ev_end=MaxAllowed; }
  }

  for (int i=Ev_start; i< Ev_end; i++) {
    fRootManager->ReadEvent(i);
    fLogger->Debug(MESSAGE_ORIGIN,"------Event is read , now execute the tasks--------");
    fTask->ExecuteTask("");
    fLogger->Debug(MESSAGE_ORIGIN,"------ Tasks executed, now fill the tree  --------");
    fRootManager->Fill();
    fTask->FinishEvent();
    if(NULL !=  FairTrajFilter::Instance()) { FairTrajFilter::Instance()->Reset(); }
  }
  fTask->FinishTask();
  fRootManager->Fill();
  fRootManager->Write();

}
//_____________________________________________________________________________
void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{

  if(fTimeStamps) {
    RunTSBuffers();
  } else if(fMixedInput) {
    RunMixed(Ev_start,Ev_end);
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
    fRootManager->Fill();
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
    if(globalEvent < fRootManager->GetInTree()->GetEntriesFast()) { //this step is necessary to load in all data which is not read in via TSBuffers
      fRootManager->ReadEvent(globalEvent++);
    }
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fTask->FinishEvent();
    if(NULL !=  FairTrajFilter::Instance()) { FairTrajFilter::Instance()->Reset(); }
  }
  fTask->FinishTask();
  fRootManager->Fill();
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
  if(!fMixedInput) {
    fRootManager->SetInputFile(name);
  }
}
//_____________________________________________________________________________
void FairRunAna::SetSignalFile(TString name, UInt_t identifier )
{
  fMixedInput=kTRUE;
  if(identifier==0) { fLogger->Fatal(MESSAGE_ORIGIN," ----- Identifier 0 is reserved for background files! please use other value ------ "); }
  fRootManager->AddSignalFile(name, identifier);
  fLogger->Info(MESSAGE_ORIGIN," ----- Mixed input mode will be used ------ ");
}
//_____________________________________________________________________________
void FairRunAna::SetBackgroundFile(TString name)
{
  fMixedInput=kTRUE;
  fRootManager->SetBackgroundFile(name);
  fLogger->Info(MESSAGE_ORIGIN," ----- Mixed input mode will be used ------ ");

}//_____________________________________________________________________________
void FairRunAna::AddBackgroundFile(TString name)
{
  if(fMixedInput) {
    fRootManager->AddBackgroundFile(name);
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN," Background can be added only if mixed mode is used");
  }
}
//_____________________________________________________________________________
void FairRunAna::AddSignalFile(TString name, UInt_t identifier )
{
  if(fMixedInput) {
    if(identifier==0) { fLogger->Fatal(MESSAGE_ORIGIN," ----- Identifier 0 is reserved for background files! please use other value ------ "); }
    fRootManager->AddSignalFile(name, identifier);
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN," Signal can be added only if mixed mode is used");
  }
}
//_____________________________________________________________________________
void FairRunAna::AddFriend (TString Name)
{
  if(fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN, "AddFriend has to be set before Run::Init !");
  } else {
    fRootManager->AddFriend(Name);
  }
}
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
      fRootManager->RunWithTimeStamps();
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
//_____________________________________________________________________________
void FairRunAna::SetEventTimeInterval(Double_t min, Double_t max)
{
  fRootManager->SetEventTimeInterval(min,max);
}
//_____________________________________________________________________________
void  FairRunAna::SetEventMeanTime(Double_t mean)
{
  fRootManager->SetEventMeanTime(mean);
}
//_____________________________________________________________________________
void  FairRunAna::SetContainerStatic()
{
  fStatic=kTRUE;
  fLogger->Info(MESSAGE_ORIGIN, "Parameter Cont. initialisation is static");
}
//_____________________________________________________________________________
void  FairRunAna::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
  fRootManager->BGWindowWidthNo(background, Signalid);
}
//_____________________________________________________________________________
void  FairRunAna::BGWindowWidthTime(Double_t background, UInt_t Signalid)
{
  fRootManager->BGWindowWidthTime(background, Signalid);
}
//_____________________________________________________________________________

ClassImp(FairRunAna)


