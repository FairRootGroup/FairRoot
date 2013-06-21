// -------------------------------------------------------------------------
// -----                   FairRunOnline source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunOnline.h"

#include "FairAnaSelector.h"            // for FairAnaSelector
#include "FairBaseParSet.h"             // for FairBaseParSet
#include "FairGeoParSet.h"              // for FairGeoParSet
#include "FairEventHeader.h"            // for FairEventHeader
#include "FairField.h"                  // for FairField
#include "FairFieldFactory.h"           // for FairFieldFactory
#include "FairFileHeader.h"             // for FairFileHeader
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairParIo.h"                  // for FairParIo
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunIdGenerator.h"         // for FairRunIdGenerator
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairSource.h"                 // for FairSource
#include "FairTask.h"                   // for FairTask
#include "FairTrajFilter.h"             // for FairTrajFilter

#include "RVersion.h"                   // for ROOT_VERSION, etc
#include "Riosfwd.h"                    // for ostream
#include "TCanvas.h"                    // for TCanvas
#include "TChain.h"                     // for TChain
#include "TCollection.h"                // for TIter
#include "TDirectory.h"                 // for TDirectory, gDirectory
#include "TFile.h"                      // for TFile, gFile
#include "TFolder.h"                    // for TFolder
#include "TGeoManager.h"                // for gGeoManager, TGeoManager
#include "TH1.h"                        // for TH1F
#include "TH2.h"                        // for TH2F
#include "TKey.h"                       // for TKey
#include "TList.h"                      // for TList
#include "TNamed.h"                     // for TNamed
#include "TObjArray.h"                  // for TObjArray
#include "TObject.h"                    // for TObject
#include "TProof.h"                     // for TProof
#include "TROOT.h"                      // for TROOT, gROOT
#include "TSeqCollection.h"             // for TSeqCollection
#include "TSystem.h"                    // for TSystem, gSystem
#include "TTree.h"                      // for TTree

#include <stdio.h>                      // for sprintf
#include <stdlib.h>                     // for NULL, exit, system
#include <string.h>                     // for strcmp
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <list>                         // for list

using std::cout;
using std::endl;
using std::list;


//_____________________________________________________________________________
FairRunOnline* FairRunOnline::fgRinstance= 0;
//_____________________________________________________________________________
FairRunOnline* FairRunOnline::Instance()
{

  return fgRinstance;
}
//_____________________________________________________________________________
FairRunOnline::FairRunOnline(FairSource* source)
  :FairRun(),
   fRunInfo(),
   fIsInitialized(kFALSE),
   fInputGeoFile(0),
   fLoadGeo( kFALSE),
   fEvtHeader(0),
   fMCHeader(0),
   fStatic(kFALSE),
   fField(0),
   fTimeStamps(kFALSE),
   fInFileIsOpen(kFALSE),
   fMixedInput(kFALSE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0),
   fProof(NULL),
   fProofAnalysis(kFALSE),
   fRunOnProofWorker(kFALSE),
   fProofServerName(""),
   fProofParName("$VMCWORKDIR/gconfig/libFairRoot.par"),
   fOutputDirectory(""),
   fProofOutputStatus("copy"),
   fFinishProcessingLMDFile(kFALSE),
   fSource(source),
   fFolder(new TFolder("HISTO", "HISTO"))
{

  fgRinstance=this;
  fAna=kTRUE;

//  fSource = source;

//  fFolder = new TFolder("HISTO", "HISTO");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunOnline::FairRunOnline(const char* type, const char* proofName)
  :FairRun(),
   fRunInfo(),
   fIsInitialized(kFALSE),
   //   fInputFile(0),
   fInputGeoFile(0),
   fLoadGeo( kFALSE),
   fEvtHeader(0),
   fMCHeader(0),
   fStatic(kFALSE),
   fField(0),
   fTimeStamps(kFALSE),
   fInFileIsOpen(kFALSE),
   fMixedInput(kFALSE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0),
   fProof(NULL),
   fProofAnalysis(kFALSE),
   fRunOnProofWorker(kFALSE),
   fProofServerName(proofName),
   fProofParName("$VMCWORKDIR/gconfig/libFairRoot.par"),
   fOutputDirectory(""),
   fProofOutputStatus("copy"),
   fFinishProcessingLMDFile(kFALSE),
   fSource(NULL),
   fFolder(NULL)
{
  TString anaType = type;
  anaType.ToLower();

  fProof = NULL;
  fProofAnalysis = kFALSE;
  fProofServerName = proofName;

  if ( anaType.Contains("proof") ) {
    fProofAnalysis = kTRUE;
    fProofServerName = proofName;

    cout << "+++++++ T P R O O F +++++++++++++++++++++++++++++++++" << endl;
    cout << "creating TProof* proof = TProof::Open(\"" << fProofServerName.Data()
         << "\");" << endl;
    TProof::AddEnvVar("LOCALDATASERVER","file://");
    //    TProof* proof = TProof::Open("lite:///?workers=1");
    fProof = TProof::Open(fProofServerName.Data());
    cout << "+++++++ C R E A T E D +++++++++++++++++++++++++++++++" << endl;
    //    fStatic = kTRUE;
  }

  fgRinstance=this;
  fAna=kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunOnline::~FairRunOnline()
{
  //  delete fFriendFileList;
  if (fField) {
    delete fField;
  }
  if (gGeoManager) {
    delete gGeoManager;
  }

  if(fSource) {
    delete fSource;
  }

  if(fFolder) {
    delete fFolder;
  }
}

//_____________________________________________________________________________

void  FairRunOnline::SetGeomFile(const char* GeoFileName)
{
  if (fIsInitialized) {
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

void FairRunOnline::Init()
{

  if (fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN,"Error Init is already called before!");
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }
  fRtdb= GetRuntimeDb();
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
    FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
  }



  if (fInFileIsOpen) {
    if ( fRunOnProofWorker ) {
      if (fLoadGeo && gGeoManager==0) {
        fRootManager->GetInFile()->Get("FAIRGeom");
      }
      if (fLoadGeo && gGeoManager==0) {
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

  if ( fProofAnalysis ) {
    return;
  }

  gROOT->GetListOfBrowsables()->Add(fTask);

  // Init the RTDB containers
  fRtdb= GetRuntimeDb();
  FairBaseParSet* par=NULL;//(FairBaseParSet*)
  //(fRtdb->getContainer("FairBaseParSet"));

  /**Set the IO Manager to run with time stamps*/
  if (fTimeStamps) {
    fRootManager->RunWithTimeStamps();
  }



  // Assure that basic info is there for the run
  //  if(par && fInputFile) {
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

//    fRtdb->initContainers( fRunId );
//    if (gGeoManager==0) {
//      par->GetGeometry();
//    }
    //  fRootManager->SetBranchNameList(par->GetBranchNameList());

  } else if (fMixedInput) {
    fLogger->Info(MESSAGE_ORIGIN,"Initializing for Mixed input");

    //For mixed input we have to set containers to static becauser of the different run ids
    //fRtdb->setContainersStatic(kTRUE);

    fEvtHeader = (FairEventHeader*) fRootManager->GetObject("EventHeader.");


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

    // if (gGeoManager==0) {
    //  fLogger->Info(MESSAGE_ORIGIN,"Read the Geometry from Parameter file");
    //  FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));

    // }
    // if (gGeoManager==0) {
    //   fLogger->Fatal(MESSAGE_ORIGIN,"Could not Read the Geometry from Parameter file");
    // }
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
//   if (fieldfact) {
//     fieldfact->SetParm();
//   }

//   fRtdb->initContainers(fRunId);
  fFileHeader->SetRunId(fRunId);

  // create a field
  // <DB>
  // Add test for external FairField settings
  if (fieldfact && !fField) {
    fField= fieldfact->createFairField();
  }

  fSource->Init();

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
void FairRunOnline::InitContainers()
{
  fRtdb= GetRuntimeDb();
  FairBaseParSet* par=(FairBaseParSet*)
                      (fRtdb->getContainer("FairBaseParSet"));

  if (par && fInFileIsOpen) {
    fRootManager->ReadEvent(0);

    fEvtHeader = (FairEventHeader*)fRootManager->GetObjectFromInTree("EventHeader.");
    fMCHeader  = (FairMCEventHeader*)fRootManager->GetObjectFromInTree("MCEventHeader.");

    if ( fMCHeader != 0 ) {
      fRunId = fMCHeader->GetRunID();
      fEvtHeader->SetRunId(fRunId); // should i do it?
      fRootManager->SetEvtHeaderNew(kTRUE);
    } else {
      fRunId = fEvtHeader->GetRunId();
    }

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
void FairRunOnline::RunMixed(Int_t Ev_start, Int_t Ev_end)
{

  fLogger->Debug(MESSAGE_ORIGIN,"Running in mixed mode");
  Int_t MaxAllowed=fRootManager->CheckMaxEventNo(Ev_end);
  if (Ev_end==0) {
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
    if (Ev_end > MaxAllowed) {
      Ev_end=MaxAllowed;
    }
  }

  for (int i=Ev_start; i< Ev_end; i++) {
    fRootManager->ReadEvent(i);
    fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
    fLogger->Debug(MESSAGE_ORIGIN,"------Event is read , now execute the tasks--------");
    fTask->ExecuteTask("");
    fLogger->Debug(MESSAGE_ORIGIN,"------ Tasks executed, now fill the tree  --------");
    fRootManager->Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fTask->FinishEvent();
    if (NULL !=  FairTrajFilter::Instance()) {
      FairTrajFilter::Instance()->Reset();
    }
  }
  fTask->FinishTask();
  fRootManager->StoreAllWriteoutBufferData();
  fRootManager->LastFill();
  fRootManager->Write();

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::Run(Int_t Ev_start, Int_t Ev_end)
{
//   if ( fProofAnalysis ) {
//     RunOnProof(Ev_start,Ev_end);
//     return;
//   }

//   if (fTimeStamps) {
//     RunTSBuffers();
//   } else if (fMixedInput) {
//     RunMixed(Ev_start,Ev_end);
//   } else {
//     UInt_t tmpId =0;
//     //  if (fInputFile==0) {
//     if (!fInFileIsOpen) {
//       DummyRun(Ev_start,Ev_end);
//       return;
//     }
//     if (Ev_end==0) {
//       if (Ev_start==0) {
//         Ev_end=Int_t((fRootManager->GetInChain())->GetEntries());
//       } else {
//         Ev_end =  Ev_start;
//         if ( Ev_end > ((fRootManager->GetInChain())->GetEntries()) ) {
//           Ev_end = (Int_t) (fRootManager->GetInChain())->GetEntries();
//         }
//         Ev_start=0;
//       }
//     } else {
//       Int_t fileEnd=(fRootManager->GetInChain())->GetEntries();
//       if (Ev_end > fileEnd) {
//         cout << "-------------------Warning---------------------------" << endl;
//         cout << " -W FairRunOnline : File has less events than requested!!" << endl;
//         cout << " File contains : " << fileEnd  << " Events" << endl;
//         cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
//         cout << " The number of events is set to " << fileEnd << " Events"<< endl;
//         cout << "-----------------------------------------------------" << endl;
//         Ev_end = fileEnd;
//       }

//     }

//     fRunInfo.Reset();


  if(Ev_start < 0) {
    return;
  } else {
    for (Int_t i = 0; i < Ev_start; i++) {
      if(! fSource->ReadEvent()) {
        continue;
      }
      /**
       * if we have simulation files then they have MC Event Header and the Run Id is in it, any way it
       * would be better to make FairMCEventHeader a subclass of FairEvtHeader.
       */
//       if (fRootManager->IsEvtHeaderNew()) {
//         tmpId = fMCHeader->GetRunID();
//       } else {
//         tmpId = fEvtHeader->GetRunId();
//       }
//       if ( tmpId != fRunId ) {
//         fRunId = tmpId;
//         if ( !fStatic ) {
//           Reinit( fRunId );
//           fTask->ReInitTask();
//         }
//       }
      //FairMCEventHeader* header = (FairMCEventHeader*)fRootManager->GetObject("MCEventHeader.");
      //std::cout << "WriteoutBufferData with time: " << fRootManager->GetEventTime();
      fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
      fTask->ExecuteTask("");
      fRootManager->Fill();
      fRootManager->DeleteOldWriteoutBufferData();
      fTask->FinishEvent();
    }
  }

  fRootManager->StoreAllWriteoutBufferData();
  fTask->FinishTask();
  if (fWriteRunInfo) {
//     fRunInfo.WriteInfo();
  }
  fRootManager->LastFill();
  fRootManager->Write();

  fSource->Close();

  TString path = TString("./") + fFolder->GetName();
  ProcessFolder(fFolder, path);
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::ProcessFolder(TFolder* folder, TString path)
{
  // Create iterator with the folder content
  TIter iter(folder->GetListOfFolders());

  // Pointer to an object
  TObject* object;

  // Class name of the object
  TString className;

  // Subfolder
  TFolder* subFolder;

  // Histogram pointers
  TH1F* h1;
  TH2F* h2;

  // Create folder with current path
  char strCmd[1000];
  sprintf(strCmd, "mkdir -p %s", path.Data());
  system(strCmd);

  // Loop over objects in the folder
  while((object = iter())) {

    // Get class name
    className = object->ClassName();

    // Recognise objects
    if(0 == className.CompareTo("TFolder")) {
      // If a subfolder - recursive call
      subFolder = (TFolder*) object;
      ProcessFolder(subFolder, path + "/" + subFolder->GetName());
    } else if(0 == className.CompareTo("TH1F")) {
      // If a histogram - plot it and save canvas
      h1 = (TH1F*) object;
      TCanvas* c1 = new TCanvas("c1", "", 10, 10, 450, 450);
      h1->Draw();
      sprintf(strCmd, "%s/%s.jpg", path.Data(), h1->GetName());
      c1->SaveAs(strCmd);
      delete c1;
    } else if(0 == className.CompareTo("TH2F")) {
      // If a histogram - plot it and save canvas
      h2 = (TH2F*) object;
      TCanvas* c1 = new TCanvas("c1", "", 10, 10, 450, 450);
      h2->Draw("col");
      sprintf(strCmd, "%s/%s.jpg", path.Data(), h2->GetName());
      c1->SaveAs(strCmd);
      delete c1;
    }
  }
}
//_____________________________________________________________________________



//_____________________________________________________________________________
void FairRunOnline::Run(Double_t delta_t)
{
  while (fRootManager->ReadNextEvent(delta_t)==kTRUE) {
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fTask->FinishEvent();
    if (NULL !=  FairTrajFilter::Instance()) {
      FairTrajFilter::Instance()->Reset();
    }
  }

  fRootManager->StoreAllWriteoutBufferData();
  fTask->FinishTask();
  fRootManager->LastFill();
  fRootManager->Write();

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::Run(Long64_t entry)
{
//  if (fTimeStamps) {
//    RunTSBuffers();
//  } else {
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
  fTask->ExecuteTask("");
  fTask->FinishTask();
  fRootManager->Fill();
  fRootManager->DeleteOldWriteoutBufferData();
  fRootManager->LastFill();
  fRootManager->Write();
//  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::RunOneEvent(Long64_t entry)
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
void FairRunOnline::RunTSBuffers()
{
  Int_t globalEvent = 0;

  bool firstRun = true;
  while (firstRun || fRootManager->AllDataProcessed() == kFALSE) {
    firstRun = false;
    if (globalEvent < fRootManager->GetInTree()->GetEntriesFast()) { //this step is necessary to load in all data which is not read in via TSBuffers
      fRootManager->ReadEvent(globalEvent++);
    }
    fTask->ExecuteTask("");
    fRootManager->Fill();
    fRootManager->DeleteOldWriteoutBufferData();
    fTask->FinishEvent();
    if (NULL !=  FairTrajFilter::Instance()) {
      FairTrajFilter::Instance()->Reset();
    }
  }
  fRootManager->StoreAllWriteoutBufferData();
  fTask->FinishTask();
  fRootManager->LastFill();
  fRootManager->Write();
}
//_____________________________________________________________________________
//_____________________________________________________________________________

void FairRunOnline::RunOnLmdFiles(UInt_t NStart, UInt_t NStop)
{
  if(NStart==0 && NStop==0) {
    NStart=0;
    NStop=1000000000;
    fLogger->Info(MESSAGE_ORIGIN," Maximum number of event is set to 1E9");
  }
  for (UInt_t i=NStart; i< NStop; i++) {
    if ( fFinishProcessingLMDFile ) {
      i = NStop; ///Same result like break

    }

    fTask->ExecuteTask("");
    fRootManager->Fill();
  }

  fTask->FinishTask();
  fRootManager->Write();

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::DummyRun(Int_t Ev_start, Int_t Ev_end)
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

//_____________________________________________________________________________
void FairRunOnline::RunOnProof(Int_t NStart,Int_t NStop)
{
  cout << "FairRunOnline::RunOnProof(" << NStart << "," << NStop << "): "
       << "running FairAnaSelector on proof server: \"" << fProofServerName.Data() << "\" "
       << "with PAR file name = \"" << fProofParName.Data() << "\"." << endl;

  FairAnaSelector* proofSelector = new FairAnaSelector();


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

//   cout << "+++++++ T P R O O F +++++++++++++++++++++++++++++++++" << endl;
//   cout << "creating TProof* proof = TProof::Open(\"" << fProofServerName.Data()
//        << "\");" << endl;
//   TProof::AddEnvVar("LOCALDATASERVER","file://");
//   //    TProof* proof = TProof::Open("lite:///?workers=1");
//   TProof* proof = TProof::Open(fProofServerName.Data());
//   cout << "+++++++ C R E A T E D +++++++++++++++++++++++++++++++" << endl;

  TString outFile = fRootManager->GetOutFile()->GetName();
  fRootManager->CloseOutFile();

  fProof->AddInput(fTask);

  fProof->AddInput(new TNamed("FAIRRUNANA_fContainerStatic",(fStatic?"kTRUE":"kFALSE")));
  fProof->AddInput(new TNamed("FAIRRUNANA_fProofOutputStatus",fProofOutputStatus.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputDirectory",outDir.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fOutputFileName",outFile.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput1FName",par1File.Data()));
  fProof->AddInput(new TNamed("FAIRRUNANA_fParInput2FName",par2File.Data()));

  cout << "0309: ClearPackages" << endl;
  fProof->ClearPackages();
  cout << "0309: UploadPackages" << endl;
  fProof->UploadPackage(fProofParName.Data());
  cout << "0309: EnablePackages" << endl;
  fProof->EnablePackage(fProofParName.Data());
  cout << "0309: ShowPackages" << endl;
  fProof->ShowPackages();
  cout << "0309: Done" << endl;

  Int_t nofChainEntries = inChain->GetEntries();
  cout << "FairRunOnline::RunOnProof(): The chain seems to have " << nofChainEntries << " entries." << endl;

  TObjArray* listOfFiles = inChain->GetListOfFiles();
  cout << "FairRunOnline::RunOnProof(): There are " << listOfFiles->GetEntries() << " files in the chain." << endl;

  inChain->SetProof();

  Int_t nofEventsToAnalyze = NStop-NStart;

  if ( nofEventsToAnalyze <= 0 ) {
    cout << "You requested to analyze events from " << NStart << " to " << NStop << " that is " << nofEventsToAnalyze << " events!!!" << endl;
    nofEventsToAnalyze = nofChainEntries-NStart;
    cout << "It will be changed to analyze all events from " << NStart << " to the end of chain (" << nofChainEntries << "), that is to analyze " << nofEventsToAnalyze << " events." << endl;
  }

  cout << "FairRunOnline::RunOnProof(): Starting inChain->Process(\"FairAnaSelector\",\"\","
       << nofEventsToAnalyze << "," << NStart << ")" << endl;
  inChain->Process("FairAnaSelector","",nofEventsToAnalyze,NStart);
  cout << "FairRunOnline::RunOnProof(): inChain->Process DONE" << endl;

  return;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::TerminateRun()
{
  fRootManager->StoreAllWriteoutBufferData();
  fTask->FinishTask();
  gDirectory->SetName(fRootManager->GetOutFile()->GetName());
  //  fRunInfo.WriteInfo(); // CRASHES due to file ownership i guess...
  //   cout << ">>> SlaveTerminate fRootManager->GetInChain()->Print()" << endl;
  //   fRootManager->GetInChain()->Print();
  //   cout << ">>>------------------------------------------------<<<" << endl;
  fRootManager->LastFill();
  fRootManager->Write();
  fRootManager->CloseOutFile();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunOnline::SetInputFile(TString name)
{
  if (!fMixedInput) {
    fRootManager->SetInputFile(name);
  }
}
//_____________________________________________________________________________
void FairRunOnline::SetSignalFile(TString name, UInt_t identifier )
{
  fMixedInput=kTRUE;
  if (identifier==0) {
    fLogger->Fatal(MESSAGE_ORIGIN," ----- Identifier 0 is reserved for background files! please use other value ------ ");
  }
  fRootManager->AddSignalFile(name, identifier);
  fLogger->Info(MESSAGE_ORIGIN," ----- Mixed input mode will be used ------ ");
}
//_____________________________________________________________________________
void FairRunOnline::SetBackgroundFile(TString name)
{
  fMixedInput=kTRUE;
  fRootManager->SetBackgroundFile(name);
  fLogger->Info(MESSAGE_ORIGIN," ----- Mixed input mode will be used ------ ");

}//_____________________________________________________________________________
void FairRunOnline::AddBackgroundFile(TString name)
{
  if (fMixedInput) {
    fRootManager->AddBackgroundFile(name);
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN," Background can be added only if mixed mode is used");
  }
}
//_____________________________________________________________________________
void FairRunOnline::AddSignalFile(TString name, UInt_t identifier )
{
  if (fMixedInput) {
    if (identifier==0) {
      fLogger->Fatal(MESSAGE_ORIGIN," ----- Identifier 0 is reserved for background files! please use other value ------ ");
    }
    fRootManager->AddSignalFile(name, identifier);
  } else {
    fLogger->Fatal(MESSAGE_ORIGIN," Signal can be added only if mixed mode is used");
  }
}
//_____________________________________________________________________________
void FairRunOnline::AddFriend (TString Name)
{
  if (fIsInitialized) {
    fLogger->Fatal(MESSAGE_ORIGIN, "AddFriend has to be set before Run::Init !");
  } else {
    fRootManager->AddFriend(Name);
  }
}
//_____________________________________________________________________________

void FairRunOnline::Reinit(UInt_t runId)
{
  // reinit procedure
  fRtdb->initContainers( runId );
}
//_____________________________________________________________________________

void FairRunOnline::AddFile(TString name)
{
  fRootManager->AddFile(name);
}
//_____________________________________________________________________________

void  FairRunOnline::RunWithTimeStamps()
{
  if (ROOT_VERSION_CODE >= ROOT_VERSION(5,29,1)) {
    if (fIsInitialized) {
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

void FairRunOnline::CompressData()
{
  fRootManager->SetCompressData(kTRUE);
}
//_____________________________________________________________________________
void FairRunOnline::SetEventTimeInterval(Double_t min, Double_t max)
{
  fRootManager->SetEventTimeInterval(min,max);
}
//_____________________________________________________________________________
void  FairRunOnline::SetEventMeanTime(Double_t mean)
{
  fRootManager->SetEventMeanTime(mean);
}
//_____________________________________________________________________________
void  FairRunOnline::SetContainerStatic(Bool_t tempBool)
{
  fStatic=tempBool;
  if ( fStatic ) {
    fLogger->Info(MESSAGE_ORIGIN, "Parameter Cont. initialisation is static");
  } else {
    fLogger->Info(MESSAGE_ORIGIN, "Parameter Cont. initialisation is NOT static");
  }
}
//_____________________________________________________________________________
void  FairRunOnline::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
  fRootManager->BGWindowWidthNo(background, Signalid);
}
//_____________________________________________________________________________
void  FairRunOnline::BGWindowWidthTime(Double_t background, UInt_t Signalid)
{
  fRootManager->BGWindowWidthTime(background, Signalid);
}
//_____________________________________________________________________________


void FairRunOnline::AddObject(TObject* object)
{
  if(! fFolder) {
    return;
  }
  fFolder->Add(object);
}


ClassImp(FairRunOnline)


