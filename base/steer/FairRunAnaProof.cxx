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
   fProofOutputStatus("copy"),
   fProofFileSource(0)
{
  if ( strcmp(proofName,"RunOnProofWorker") == 0 ) {
    fRunOnProofWorker = kTRUE;
  }
  else {
    LOG(INFO) << "+++++++ T P R O O F +++++++++++++++++++++++++++++++++" << FairLogger::endl;
    LOG(INFO) << "creating TProof* proof = TProof::Open(\"" << fProofServerName.Data()
	 << "\");" << FairLogger::endl;
    TProof::AddEnvVar("LOCALDATASERVER","file://");
    //    TProof* proof = TProof::Open("lite:///?workers=1");
    fProof = TProof::Open(fProofServerName.Data());
    LOG(INFO) << "+++++++ C R E A T E D +++++++++++++++++++++++++++++++" << FairLogger::endl;
  }

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
  fInFileIsOpen = fRootManager->InitSource();

  if (fIsInitialized) {
    LOG(FATAL) << "Error Init is already called before!"
	       << FairLogger::endl;
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }

  if ( !fRunOnProofWorker ) {
    // Open the input file and add other input files added by AddFile to the
    // input chain. Do a check if the added files are of the same type
    // as the the input file. Same type means check if they contain the
    // same branch.
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
        fProofFileSource->GetInTree()->GetCurrentFile()->Get("FAIRGeom");
      }
    } else {

      // Add all friend files defined by AddFriend to the correct chain
      if (fLoadGeo && gGeoManager==0) {
        // Check if the geometry in the first file of the Chain
        fProofFileSource->GetInTree()->GetCurrentFile()->Get("FAIRGeom");
      }
      //check that the geometry was loaded if not try all connected files!
      if (fLoadGeo && gGeoManager==0) {
        LOG(INFO) << "Geometry was not found in the input file we will look in the friends if any!" << FairLogger::endl;
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
    LOG(WARNING) << "QUITTING, CAUSE IT'S not running on proof worker" << FairLogger::endl;
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

    LOG(INFO) << "Parameter and input file are available, Assure that basic info is there for the run!" << FairLogger::endl;
    fRootManager->ReadEvent(0);

    fEvtHeader = (FairEventHeader*)fRootManager->GetObject("EventHeader.");

    if (fEvtHeader ==0) {
      fEvtHeader=GetEventHeader();
      fEvtHeader->SetRunId(fRunId);
      //      fRootManager->SetEvtHeaderNew(kTRUE);
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
    
  } else {
    LOG(INFO) << "Initializing without input file or Mixed input"
	      << FairLogger::endl;
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
void FairRunAnaProof::InitContainers()
{
  fRtdb= GetRuntimeDb();
  FairBaseParSet* par=dynamic_cast<FairBaseParSet*>
                      (fRtdb->getContainer("FairBaseParSet"));

  if (par && fInFileIsOpen) {
    fRootManager->ReadEvent(0);

    fEvtHeader = dynamic_cast<FairEventHeader*>(fRootManager->GetObject("EventHeader."));

    fRootManager->FillEventHeader(fEvtHeader);

    fRunId = fEvtHeader->GetRunId();

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    // Init the containers in Tasks
    fRtdb->initContainers(fRunId);
    fTask->ReInitTask();
    //    fTask->SetParTask();
    fRtdb->initContainers( fRunId );
    if (gGeoManager==0) {
      //   par->GetGeometry();
    }
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::SetSource(FairSource* tempSource) {
  // FairRunAnaProof should accept only FairFileSource
  if (strncmp(tempSource->GetName(), "FairFileSource", 14) != 0) {
    LOG(WARNING) << "FairRunAnaProof. Seems you are trying to set different source than FairFileSource" << FairLogger::endl;
  }
  fRootManager->SetSource(tempSource);
  fProofFileSource = (FairFileSource*)tempSource;
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

    fRootManager->FillEventHeader(fEvtHeader);

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
  fProofOutputStatus.ToLower();
  if ( !fProofOutputStatus.Contains("copy") && !fProofOutputStatus.Contains("merge") ) {
    LOG(WARNING) << "FairRunAnaProof::RunOnProof. Do not know how to create output \"" << fProofOutputStatus.Data() << "\"." << FairLogger::endl;
    LOG(WARNING) << "FairRunAnaProof::RunOnProof. Please use SetProofOutputStatus to either \"copy\" or \"merge\"." << FairLogger::endl;
    LOG(WARNING) << "FairRunAnaProof::RunOnProof. For the current run using the \"merge\" setting." << FairLogger::endl;
    fProofOutputStatus = "merge";
  }

//  TChain* inChain = (TChain*)fRootManager->GetInChain();
  TChain* inChain = (TChain*)fProofFileSource->GetInChain();
  TString par1File = "";
  TString par2File = "";
  if ( fRtdb->getFirstInput () ) {
    par1File = fRtdb->getFirstInput ()->getFilename();
  }
  if ( fRtdb->getSecondInput() ) {
    par2File = fRtdb->getSecondInput()->getFilename();
  }

  TString outDir = (fOutputDirectory.Length()>1?fOutputDirectory.Data():gSystem->WorkingDirectory());

  TString outFile = Form("%s",fOutname);

  fProof->AddInput(fTask);

  fProof->AddInput(new TNamed("FAIRRUNANA_fContainerStatic",(fStatic?"kTRUE":"kFALSE")));
  fProof->AddInput(new TNamed("FAIRRUNANA_fProofOutputStatus",fProofOutputStatus.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputDirectory",outDir.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputFileName",outFile.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput1FName",par1File.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput2FName",par2File.Data()));

  // uploading packages not needed, as the libraries are in the rootmap now
  // fProof->ClearPackages();
  // fProof->UploadPackage(fProofParName.Data());
  // fProof->EnablePackage(fProofParName.Data());

  Int_t nofChainEntries = inChain->GetEntries();
  LOG(INFO) << "FairRunAnaProof::RunOnProof(): The chain seems to have " << nofChainEntries << " entries." << FairLogger::endl;

  TObjArray* listOfFiles = inChain->GetListOfFiles();
  LOG(INFO) << "FairRunAnaProof::RunOnProof(): There are " << listOfFiles->GetEntries() << " files in the chain." << FairLogger::endl;

  inChain->SetProof();

  Int_t nofEventsToAnalyze = NStop-NStart;

  if ( nofEventsToAnalyze <= 0 ) {
    LOG(INFO) << "You requested to analyze events from " << NStart << " to " << NStop << " that is " << nofEventsToAnalyze << " events!!!" << FairLogger::endl;
    nofEventsToAnalyze = nofChainEntries-NStart;
    LOG(INFO) << "It will be changed to analyze all events from " << NStart << " to the end of chain (" << nofChainEntries << "), that is to analyze " << nofEventsToAnalyze << " events." << FairLogger::endl;
  }

  LOG(INFO) << "FairRunAnaProof::RunOnProof(): Starting inChain->Process(\"FairAnaSelector\",\"\","
       << nofEventsToAnalyze << "," << NStart << ")" << FairLogger::endl;
  inChain->Process("FairAnaSelector","",nofEventsToAnalyze,NStart);
  LOG(INFO) << "FairRunAnaProof::RunOnProof(): inChain->Process DONE" << FairLogger::endl;

  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::SetOutputFile(const char* fname)
{
  fOutname=fname;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAnaProof::SetOutputFile(TFile* f)
{
  if (! fRootManager) return;

  fOutname=f->GetName();
  fRootManager->OpenOutFile(f);
  fOutFile = f;

}
//_____________________________________________________________________________

ClassImp(FairRunAnaProof)


