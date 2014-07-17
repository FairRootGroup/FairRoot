/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunAnaProof source file                 -----
// -----            Created 30/04/13  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#include "FairRunAnaProof.h"

// #include "FairRootManager.h"
#include "FairTask.h"
#include "FairBaseParSet.h"
#include "FairGeoParSet.h"
#include "FairEventHeader.h"
#include "FairFieldFactory.h"
#include "FairRuntimeDb.h"
#include "FairTrajFilter.h"
#include "FairRunIdGenerator.h"
#include "FairLogger.h"
#include "FairFileHeader.h"
#include "FairMCEventHeader.h"
#include "FairParIo.h"
#include "FairAnaSelector.h"

#include "TROOT.h"
// #include "TTree.h"
// #include "TSeqCollection.h"
#include "TGeoManager.h"
#include "TKey.h"
// #include "TF1.h"
// #include "TSystem.h"
#include "TProof.h"
#include "TProofOutputFile.h"

#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::list;

//_____________________________________________________________________________
FairRunAnaProof* FairRunAnaProof::fRAPInstance= 0;
//_____________________________________________________________________________
FairRunAnaProof* FairRunAnaProof::Instance()
{

  return fRAPInstance;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunAnaProof::FairRunAnaProof(const char* proofName)
  :FairRunAna(),
   fProof(NULL),
   fRunOnProofWorker(kFALSE),
   fProofServerName(proofName),
   fProofParName("$VMCWORKDIR/gconfig/libFairRoot.par"),
   fOutputDirectory(""),
   fProofOutputStatus("copy")
{
  cout << "+++++++ T P R O O F +++++++++++++++++++++++++++++++++" << endl;
  cout << "creating TProof* proof = TProof::Open(\"" << fProofServerName.Data()
       << "\");" << endl;
  TProof::AddEnvVar("LOCALDATASERVER","file://");
  //    TProof* proof = TProof::Open("lite:///?workers=1");
  fProof = TProof::Open(fProofServerName.Data());
  cout << "+++++++ C R E A T E D +++++++++++++++++++++++++++++++" << endl;

  fRAPInstance=this;
  fAna=kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunAnaProof::~FairRunAnaProof()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::Init()
{

  if (fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Error Init is already called before!");
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }

  if ( fRunOnProofWorker ) {
    fInFileIsOpen = fRootManager->OpenInTree();
  } else {
    // Open the input file and add other input files added by AddFile to the
    // input chain. Do a check if the added files are of the same type
    // as the the input file. Same type means check if they contain the
    // same branch.
    if (!fMixedInput) {
      fInFileIsOpen = fRootManager->OpenInChain();
    } else {
      Bool_t openBKChain = fRootManager->OpenBackgroundChain();
      if (!openBKChain) {
        fLogger->Fatal(MESSAGE_ORIGIN, "Could not open background Chain!");
      }
      fRootManager->OpenSignalChain();
    }
  }
  //Load Geometry from user file

  if (fLoadGeo) {
    if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
      TIter next(fInputGeoFile->GetListOfKeys());
      TKey* key;
      while ((key = (TKey*)next())) {
        if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
          continue;
        }
        gGeoManager = (TGeoManager*)key->ReadObj();
        break;
      }
    }
  } else {
//    FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
    fRtdb->getContainer("FairGeoParSet");
  }

  if (fInFileIsOpen) {
    if ( fRunOnProofWorker ) {
      if (fLoadGeo && gGeoManager==0) {
        fRootManager->GetInFile()->Get("FAIRGeom");
      }
    } else {

      // Add all friend files defined by AddFriend to the correct chain
      fRootManager->AddFriendsToChain();
      if (fLoadGeo && gGeoManager==0) {
        // Check if the geometry in the first file of the Chain
        fRootManager->GetInChain()->GetFile()->Get("FAIRGeom");
      }
      //check that the geometry was loaded if not try all connected files!
      if (fLoadGeo && gGeoManager==0) {
        fLogger->Info(MESSAGE_ORIGIN, "Geometry was not found in the input file we will look in the friends if any!" );
        TFile* currentfile= gFile;
        TFile* nextfile=0;
        TSeqCollection* fileList=gROOT->GetListOfFiles();
        for (Int_t k=0; k<fileList->GetEntries(); k++) {
          nextfile=(TFile*)fileList->At(k);
          if (nextfile) {
            nextfile->Get("FAIRGeom");
          }
          if (gGeoManager) {
            break;
          }
        }
        gFile=currentfile;
      }
    }
  } else if (fMixedInput) {



  } else { //  if(fInputFile )
    // NO input file but there is a geometry file
    if (fLoadGeo) {
      if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
        TIter next(fInputGeoFile->GetListOfKeys());
        TKey* key;
        while ((key = (TKey*)next())) {
          if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
            continue;
          }
          gGeoManager = (TGeoManager*)key->ReadObj();
          break;
        }
      }
    }
  }
  //Init the Chain ptr
  //  fcurrent = fChainList.begin();
// fOutFile = fRootManager->OpenOutFile(fOutname);

  if ( !fRunOnProofWorker ) {
    std::cout << "QUITTING, CAUSE IT'S not running on proof worker" << std::endl;
    return;
  }
  gROOT->GetListOfBrowsables()->Add(fTask);

  // Init the RTDB containers
  fRtdb= GetRuntimeDb();
  FairBaseParSet* par=(FairBaseParSet*)
                      (fRtdb->getContainer("FairBaseParSet"));

  /**Set the IO Manager to run with time stamps*/
  if (fTimeStamps) {
    fRootManager->RunWithTimeStamps();
  }



  // Assure that basic info is there for the run

  if (par && fInFileIsOpen) {

    fLogger->Info(MESSAGE_ORIGIN,"Parameter and input file are available, Assure that basic info is there for the run!");
    fRootManager->ReadEvent(0);

    fEvtHeader = (FairEventHeader*)fRootManager->GetObject("EventHeader.");
    fMCHeader = (FairMCEventHeader*)fRootManager->GetObject("MCEventHeader.");

    if (fEvtHeader ==0) {
      fEvtHeader=GetEventHeader();
      fRunId = fMCHeader->GetRunID();
      fEvtHeader->SetRunId(fRunId);
      fRootManager->SetEvtHeaderNew(kTRUE);
    } else {
      fRunId = fEvtHeader->GetRunId();
    }

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    // Init the containers in Tasks

    fRtdb->initContainers(fRunId);
    fTask->SetParTask();

    fRtdb->initContainers( fRunId );
    if (gGeoManager==0) {



    }
    //  fRootManager->SetBranchNameList(par->GetBranchNameList());

  } else if (fMixedInput) {
    fLogger->Info(MESSAGE_ORIGIN,"Initializing for Mixed input");

    //For mixed input we have to set containers to static becauser of the different run ids
    //fRtdb->setContainersStatic(kTRUE);

    fEvtHeader = (FairEventHeader*)fRootManager->GetObject("EventHeader.");
    fMCHeader = (FairMCEventHeader*)fRootManager->GetObject("MCEventHeader.");

    if (fEvtHeader ==0) {
      fEvtHeader=GetEventHeader();
      fRunId = fMCHeader->GetRunID();
      fEvtHeader->SetRunId(fRunId);
      fRootManager->SetEvtHeaderNew(kTRUE);
    }


    fRootManager->ReadBKEvent(0);

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    fRunId = fEvtHeader->GetRunId();
    // Init the containers in Tasks
    fRtdb->initContainers(fRunId);

    /*   if (gGeoManager==0) {
         fLogger->Info(MESSAGE_ORIGIN,"Read the Geometry from Parameter file");
          FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));

       }
       if (gGeoManager==0) {
         fLogger->Fatal(MESSAGE_ORIGIN,"Could not Read the Geometry from Parameter file");
       }

     */
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
  if (fieldfact) {
    fieldfact->SetParm();
  }

  fRtdb->initContainers(fRunId);
  fFileHeader->SetRunId(fRunId);

  // create a field
  // <DB>
  // Add test for external FairField settings
  if (fieldfact && !fField) {
    fField= fieldfact->createFairField();
  }
  // Now call the User initialize for Tasks
  fTask->InitTask();
  // if the vis manager is available then initialize it!
  FairTrajFilter* fTrajFilter = FairTrajFilter::Instance();
  if (fTrajFilter) {
    fTrajFilter->Init();
  }

  // create the output tree after tasks initialisation
  fOutFile->cd();
  TTree* outTree =new TTree("cbmsim", "/cbmout", 99);
  fRootManager->TruncateBranchNames(outTree, "cbmout");
  fRootManager->SetOutTree(outTree);
  fRootManager->WriteFolder();
  fRootManager->WriteFileHeader(fFileHeader);
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::Run(Int_t Ev_start, Int_t Ev_end)
{
  RunOnProof(Ev_start,Ev_end);
  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::RunOneEvent(Long64_t entry)
{
  if (fTimeStamps) {
    RunTSBuffers();
  } else {
    UInt_t tmpId =0;
    fRootManager->ReadEvent(entry);
    tmpId = fEvtHeader->GetRunId();
    if ( tmpId != fRunId ) {
      fRunId = tmpId;
      if ( !fStatic ) {
        Reinit( fRunId );
        fTask->ReInitTask();
      }
    }
    fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());

    fTask->ExecuteTask("");
    fRootManager->Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fTask->FinishEvent();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::RunOnProof(Int_t NStart,Int_t NStop)
{
//  FairAnaSelector* proofSelector = new FairAnaSelector();


  TChain* inChain = (TChain*)fRootManager->GetInChain();
  TString par1File = "";
  TString par2File = "";
  if ( fRtdb->getFirstInput () ) {
    par1File = fRtdb->getFirstInput ()->getFilename();
  }
  if ( fRtdb->getSecondInput() ) {
    par2File = fRtdb->getSecondInput()->getFilename();
  }

  TString outDir = (fOutputDirectory.Length()>1?fOutputDirectory.Data():gSystem->WorkingDirectory());

  TString outFile = fRootManager->GetOutFile()->GetName();
  fRootManager->CloseOutFile();

  fProof->AddInput(fTask);

  fProof->AddInput(new TNamed("FAIRRUNANA_fContainerStatic",(fStatic?"kTRUE":"kFALSE")));
  fProof->AddInput(new TNamed("FAIRRUNANA_fProofOutputStatus",fProofOutputStatus.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputDirectory",outDir.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputFileName",outFile.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput1FName",par1File.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput2FName",par2File.Data()));

  if ( 1 == 0 ) { // uploading packages not needed, as the libraries are in the rootmap now
    if ( 1==0 ) { cout << "+++++++ ClearPackages" << endl; }
    fProof->ClearPackages();
    if ( 1==0 ) { cout << "+++++++ UploadPackages" << endl; }
    fProof->UploadPackage(fProofParName.Data());
    if ( 1==0 ) { cout << "+++++++ EnablePackages" << endl; }
    fProof->EnablePackage(fProofParName.Data());
    if ( 1==0 ) { cout << "+++++++ ShowPackages" << endl; }
    if ( 1==0 ) { fProof->ShowPackages(); }
    if ( 1==0 ) { cout << "+++++++ Done" << endl; }
  }

  Int_t nofChainEntries = inChain->GetEntries();
  cout << "FairRunAnaProof::RunOnProof(): The chain seems to have " << nofChainEntries << " entries." << endl;

  TObjArray* listOfFiles = inChain->GetListOfFiles();
  cout << "FairRunAnaProof::RunOnProof(): There are " << listOfFiles->GetEntries() << " files in the chain." << endl;

  inChain->SetProof();

  Int_t nofEventsToAnalyze = NStop-NStart;

  if ( nofEventsToAnalyze <= 0 ) {
    cout << "You requested to analyze events from " << NStart << " to " << NStop << " that is " << nofEventsToAnalyze << " events!!!" << endl;
    nofEventsToAnalyze = nofChainEntries-NStart;
    cout << "It will be changed to analyze all events from " << NStart << " to the end of chain (" << nofChainEntries << "), that is to analyze " << nofEventsToAnalyze << " events." << endl;
  }

  cout << "FairRunAnaProof::RunOnProof(): Starting inChain->Process(\"FairAnaSelector\",\"\","
       << nofEventsToAnalyze << "," << NStart << ")" << endl;
  inChain->Process("FairAnaSelector","",nofEventsToAnalyze,NStart);
  cout << "FairRunAnaProof::RunOnProof(): inChain->Process DONE" << endl;

  return;
}
//_____________________________________________________________________________

ClassImp(FairRunAnaProof)


