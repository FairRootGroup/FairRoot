/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                   FairRunAna source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#include "FairRunAna.h"

#include "FairBaseParSet.h"             // for FairBaseParSet
#include "FairGeoParSet.h"              // for FairGeoParSet
#include "FairEventHeader.h"            // for FairEventHeader
#include "FairField.h"                  // for FairField
#include "FairFieldFactory.h"           // for FairFieldFactory
#include "FairFileHeader.h"             // for FairFileHeader
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairParIo.h"                  // for FairParIo
#include "FairParSet.h"                 // for FairParSet
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunIdGenerator.h"         // for FairRunIdGenerator
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTask.h"                   // for FairTask
#include "FairTrajFilter.h"             // for FairTrajFilter

#include "FairFileSource.h"             // ONLY TEMPORARILY, FOR COMPABILITY
#include "FairMixedSource.h"            // ONLY TEMPORARILY, FOR COMPABILITY

#include "RVersion.h"                   // for ROOT_VERSION, etc
#include "Riosfwd.h"                    // for ostream
#include "TChain.h"                     // for TChain
#include "TCollection.h"                // for TIter
#include "TDirectory.h"                 // for TDirectory, gDirectory
#include "TFile.h"                      // for TFile, gFile
#include "TGeoManager.h"                // for gGeoManager, TGeoManager
#include "TKey.h"                       // for TKey
#include "TList.h"                      // for TList
#include "TNamed.h"                     // for TNamed
#include "TObjArray.h"                  // for TObjArray
#include "TObject.h"                    // for TObject
#include "TROOT.h"                      // for TROOT, gROOT
#include "TSeqCollection.h"             // for TSeqCollection
#include "TSystem.h"                    // for TSystem, gSystem
#include "TTree.h"                      // for TTree

#include <stdlib.h>                     // for NULL, exit
#include "signal.h"
#include <string.h>                     // for strcmp
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <list>                         // for list

using std::cout;
using std::endl;
using std::list;

Bool_t gFRAIsInterrupted;

//_____________________________________________________________________________
void FRA_handler_ctrlc(int s)
{
  LOG(INFO) << "*********** CTRL C PRESSED *************" << FairLogger::endl;
  gFRAIsInterrupted = kTRUE;
}
//_____________________________________________________________________________

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
   fRunInfo(),
   fIsInitialized(kFALSE),
   fInputGeoFile(0),
   fLoadGeo( kFALSE),
   fStatic(kFALSE),
   fField(0),
   fTimeStamps(kFALSE),
   fInFileIsOpen(kFALSE),
   fEventTimeMin(0),
   fEventTimeMax(0),
   fEventTime(0),
   fEventMeanTime(0),
   fTimeProb(0),
   fFinishProcessingLMDFile(kFALSE)
  ,fFileSource(0)
  ,fMixedSource(0)
{

  fgRinstance=this;
  fAna=kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
FairRunAna::~FairRunAna()
{
  //  delete fFriendFileList;
  if (fField) {
    delete fField;
  }
  if (gGeoManager) {
    delete gGeoManager;
  }
}

//_____________________________________________________________________________

void  FairRunAna::SetGeomFile(const char* GeoFileName)
{
  if (fIsInitialized) {
    LOG(FATAL) << "Geometry file has to be set before Run::Init !" 
	       << FairLogger::endl;
    exit(-1);
  } else {

    TFile* CurrentFile=gFile;
    fInputGeoFile= new TFile(GeoFileName);
    if (fInputGeoFile->IsZombie()) {
      LOG(ERROR) << "Error opening Geometry Input file"
		 << FairLogger::endl;
      fInputGeoFile=0;
    }
    LOG(INFO) << "Opening Geometry input file: " << GeoFileName
	      << FairLogger::endl;
    fLoadGeo=kTRUE;
    gFile=CurrentFile;
  }
}

//_____________________________________________________________________________

void FairRunAna::Init()
{

  if (fIsInitialized) {
    LOG(FATAL) << "Error Init is already called before!" << FairLogger::endl;
    exit(-1);
  } else {
    fIsInitialized=kTRUE;
  }
  fRtdb= GetRuntimeDb();

  // Check if we have an input file to be used
  fInFileIsOpen = fRootManager->InitSource();

 //Load Geometry from user file
  if (fLoadGeo) {
    if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
      TIter next(fInputGeoFile->GetListOfKeys());
      TKey* key;
      while ((key =dynamic_cast< TKey*>(next()))) {
        if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
          continue;
        }
        gGeoManager = dynamic_cast<TGeoManager*>(key->ReadObj());
        break;
      }
    }
  } else {
    /*** Get the container that normly has the geometry and all the basic stuff from simulation*/
    fRtdb->getContainer("FairGeoParSet");
  }

  if (fInFileIsOpen) {
    //check that the geometry was loaded if not try all connected files!
    if (fLoadGeo && gGeoManager==0) {
      LOG(INFO) << "Geometry was not found in the input file we will look in the friends if any!" << FairLogger::endl;
      TFile* currentfile= gFile;
      TFile* nextfile=0;
      TSeqCollection* fileList=gROOT->GetListOfFiles();
      for (Int_t k=0; k<fileList->GetEntries(); k++) {
        nextfile=dynamic_cast<TFile*>(fileList->At(k));
        if (nextfile) {
          nextfile->Get("FAIRGeom");
        }
        if (gGeoManager) {
          break;
        }
      }
      gFile=currentfile;
    }
  } else { //  if(fInputFile )
    // NO input file but there is a geometry file
    if (fLoadGeo) {
      if (fInputGeoFile!=0) { //First check if the user has a separate Geo file!
        TIter next(fInputGeoFile->GetListOfKeys());
        TKey* key;
        while ((key = dynamic_cast<TKey*>(next()))) {
          if (strcmp(key->GetClassName(),"TGeoManager") != 0) {
            continue;
          }
          gGeoManager = dynamic_cast<TGeoManager*>(key->ReadObj());
          break;
        }
      }
    }
  }
 
  gROOT->GetListOfBrowsables()->Add(fTask);

  // Init the RTDB containers

  FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));


  /**Set the IO Manager to run with time stamps*/
  if (fTimeStamps) {
    fRootManager->RunWithTimeStamps();
  }



  // Assure that basic info is there for the run
  //  if(par && fInputFile) {
  if (par && fInFileIsOpen) {

    LOG(INFO) << "Parameter and input file are available, Assure that basic info is there for the run!" << FairLogger::endl;
    fRootManager->ReadEvent(0);

//    fEvtHeader = GetEventHeader();
    GetEventHeader();
    
    fRootManager->FillEventHeader(fEvtHeader);
    
    fRunId = fEvtHeader->GetRunId();

    //Copy the Event Header Info to Output
    fEvtHeader->Register();

    // Init the containers in Tasks

    fRtdb->initContainers(fRunId);
    fTask->SetParTask();
    
    //fRtdb->initContainers( fRunId );
    
  } else {  //end----- if(fMixedInput)
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
  // Create a list of time based branches (if any).
  
  fRootManager->UpdateListOfTimebasedBranches();
  
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
void FairRunAna::Run(Int_t Ev_start, Int_t Ev_end)
{
  gFRAIsInterrupted = kFALSE;

  if (fTimeStamps) {
    RunTSBuffers();
  } else {
    UInt_t tmpId =0;
    //  if (fInputFile==0) {
    if (!fInFileIsOpen) {
      DummyRun(Ev_start,Ev_end);
      return;
    }

   Int_t MaxAllowed=fRootManager->CheckMaxEventNo(Ev_end);
    if ( MaxAllowed != -1 ) {
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
          cout << "-------------------Warning---------------------------" << endl;
          cout << " -W FairRunAna : File has less events than requested!!" << endl;
          cout << " File contains : " << MaxAllowed  << " Events" << endl;
          cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
          cout << " The number of events is set to " << MaxAllowed << " Events"<< endl;
          cout << "-----------------------------------------------------" << endl;
          Ev_end = MaxAllowed;
        }
      }
      LOG(INFO) << "FairRunAna::Run() After checking, the run will run from event " << Ev_start << " to " << Ev_end << "." << FairLogger::endl;
    }
    else {
      LOG(INFO) << "FairRunAna::Run() continue running without stop" << FairLogger::endl;
    }
    
    if (fGenerateRunInfo) {
      fRunInfo.Reset();
    }

    Int_t readEventReturn = 0;

    for (int i=Ev_start; i< Ev_end || MaxAllowed==-1 ; i++) {
      
      gSystem->IgnoreInterrupt();
      //  gFRAIsInterrupted = kFALSE;
      signal(SIGINT, FRA_handler_ctrlc);
      
      if ( gFRAIsInterrupted ) {
        LOG(WARNING) << "FairRunAna::Run() Event loop was interrupted by the user!" << FairLogger::endl;
        break;
      }
      
      readEventReturn = fRootManager->ReadEvent(i);

      if ( readEventReturn != 0 ) {
        LOG(WARNING) << "FairRunAna::Run() fRootManager->ReadEvent(" << i << ") returned " << readEventReturn << ". Breaking the event loop" << FairLogger::endl;
        break;
      }
      
      fRootManager->FillEventHeader(fEvtHeader);

      tmpId = fEvtHeader->GetRunId();
      if ( tmpId != fRunId ) {
        fRunId = tmpId;
        if ( !fStatic ) {
          Reinit( fRunId );
          fTask->ReInitTask();
        }
      }
      //std::cout << "WriteoutBufferData with time: " << fRootManager->GetEventTime();
      fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
      fTask->ExecuteTask("");
      Fill();
      fRootManager->DeleteOldWriteoutBufferData();
      fTask->FinishEvent();

      if (fGenerateRunInfo) {
        fRunInfo.StoreInfo();
      }
      if (NULL !=  FairTrajFilter::Instance()) {
        FairTrajFilter::Instance()->Reset();
      }

    }

    fRootManager->StoreAllWriteoutBufferData();
    fTask->FinishTask();
    if (fGenerateRunInfo) {
      fRunInfo.WriteInfo();
    }
    fRootManager->LastFill();
    fRootManager->Write();
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunEventReco(Int_t Ev_start, Int_t Ev_end)
{
  UInt_t tmpId =0;

  Int_t MaxAllowed=fRootManager->CheckMaxEventNo(Ev_end);
  if ( MaxAllowed != -1 ) {
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
	cout << "-------------------Warning---------------------------" << endl;
	cout << " -W FairRunAna : File has less events than requested!!" << endl;
	cout << " File contains : " << MaxAllowed  << " Events" << endl;
	cout << " Requested number of events = " <<  Ev_end <<  " Events"<< endl;
	cout << " The number of events is set to " << MaxAllowed << " Events"<< endl;
	cout << "-----------------------------------------------------" << endl;
	Ev_end = MaxAllowed;
      }
    }
    LOG(INFO) << "FairRunAna::Run() After checking, the run will run from event " << Ev_start << " to " << Ev_end << "." << FairLogger::endl;
  }
  else {
    LOG(INFO) << "FairRunAna::Run() continue running without stop" << FairLogger::endl;
  }
  
  if (fGenerateRunInfo) {
    fRunInfo.Reset();
  }

  for (int i=Ev_start; i< Ev_end; i++) {
    fRootManager->ReadEvent(i);
    /**
     * if we have simulation files then they have MC Event Header and the Run Id is in it, any way it
     * would be better to make FairMCEventHeader a subclass of FairEvtHeader.
     */
    if ( tmpId != fRunId ) {
      fRunId = tmpId;
      if ( !fStatic ) {
        Reinit( fRunId );
        fTask->ReInitTask();
      }
    }
    //FairMCEventHeader* header = dynamic_cast<FairMCEventHeader*>(fRootManager->GetObject("MCEventHeader.");
    //    std::cout << "WriteoutBufferData with time: " << fRootManager->GetEventTime();
    fRootManager->StoreWriteoutBufferData(fRootManager->GetEventTime());
    fTask->ExecuteTask("");

    fRootManager->FillEventHeader(fEvtHeader);
    // Fill();
    fTask->FinishEvent();

    if (fGenerateRunInfo) {
      fRunInfo.StoreInfo();
    }
    if (NULL !=  FairTrajFilter::Instance()) {
      FairTrajFilter::Instance()->Reset();
    }

  }

  fTask->FinishTask();
  if (fGenerateRunInfo) {
    fRunInfo.WriteInfo();
  }
  fRootManager->LastFill();
  fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::Run(Double_t delta_t)
{
  while (fRootManager->ReadNextEvent(delta_t)==kTRUE) {
    fTask->ExecuteTask("");
    fRootManager->FillEventHeader(fEvtHeader);
    Fill();
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
void FairRunAna::RunMQ(Long64_t entry)
{
  /**
   This methode is only needed and used with ZeroMQ
   it read a certain event and call the task exec, but no output is written
   */
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
  fRootManager->FillEventHeader(fEvtHeader);
  fTask->FinishTask();
}
//_____________________________________________________________________________


//_____________________________________________________________________________
void FairRunAna::Run(Long64_t entry)
{
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
  fRootManager->FillEventHeader(fEvtHeader);
  fTask->FinishTask();
  Fill();
  fRootManager->DeleteOldWriteoutBufferData();
  fRootManager->LastFill();
  fRootManager->Write();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::RunTSBuffers()
{
  Int_t globalEvent = 0;

  bool firstRun = true;
  while (firstRun || fRootManager->AllDataProcessed() == kFALSE) {
    firstRun = false;
    if (globalEvent < fRootManager->CheckMaxEventNo(0) ) { //this step is necessary to load in all data which is not read in via TSBuffers
      fRootManager->ReadNonTimeBasedEventFromBranches(globalEvent++);
    }
    fTask->ExecuteTask("");
    fRootManager->FillEventHeader(fEvtHeader);
    Fill();
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

void FairRunAna::RunOnLmdFiles(UInt_t NStart, UInt_t NStop)
{
  if(NStart==0 && NStop==0) {
    NStart=0;
    NStop=1000000000;
    LOG(INFO) << " Maximum number of event is set to 1E9" << FairLogger::endl;
  }
  for (UInt_t i=NStart; i< NStop; i++) {
    if ( fFinishProcessingLMDFile ) {
      i = NStop; ///Same result like break

    }

    fTask->ExecuteTask("");
    fRootManager->FillEventHeader(fEvtHeader);
    Fill();
  }

  fTask->FinishTask();
  fRootManager->Write();

}
//_____________________________________________________________________________
void FairRunAna::RunOnTBData() {
      std::cout << "FairRunAna::RunOnTBData " << std::endl;
        while (fRootManager->FinishRun() != kTRUE) {
		fTask->ExecuteTask("");
            Fill();
            fTask->FinishEvent();
        }

        fTask->FinishTask();
        fRootManager->LastFill();
        fRootManager->Write();
}
//_____________________________________________________________________________
void FairRunAna::DummyRun(Int_t Ev_start, Int_t Ev_end)
{

  /** This methode is just for testing, if you are not sure about what you do, don't use it */
  for (int i=Ev_start; i< Ev_end; i++) {
    fTask->ExecuteTask("");
    fRootManager->FillEventHeader(fEvtHeader);
    Fill();
  }
  fTask->FinishTask();
  fRootManager->Write();

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairRunAna::TerminateRun()
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

void FairRunAna::Reinit(UInt_t runId)
{
  // reinit procedure
  fRtdb->initContainers( runId );
}
//_____________________________________________________________________________

void  FairRunAna::RunWithTimeStamps()
{
  if (ROOT_VERSION_CODE >= ROOT_VERSION(5,29,1)) {
    if (fIsInitialized) {
      LOG(WARNING) << "RunWithTimeStamps has to be set before Run::Init !" << FairLogger::endl;
      exit(-1);
    } else {
      fTimeStamps=kTRUE;
      fRootManager->RunWithTimeStamps();
    }
  } else {
    LOG(FATAL) << "RunWithTimeStamps need at least ROOT version 5.29.1" << FairLogger::endl;
  }
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void  FairRunAna::SetContainerStatic(Bool_t tempBool)
{
  fStatic=tempBool;
  if ( fStatic ) {
    LOG(INFO) << "Parameter Cont. initialisation is static" << FairLogger::endl;
  } else {
    LOG(INFO) << "Parameter Cont. initialisation is NOT static" << FairLogger::endl;
  }
}

// BELOW FUNCTIONS SHOULD BE DELETED AND MOVED TO FairFileSource ONLY
//_____________________________________________________________________________
void FairRunAna::SetInputFile(TString name)
{
  LOG(WARNING) << "FairRunAna::SetInputFile is obsolete. Set it by FairFileSource" << FairLogger::endl;
  if ( fMixedSource ) 
    { 
      LOG(ERROR) << "Mixed input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fFileSource ) 
    {
      fFileSource = new FairFileSource(name);
      SetSource(fFileSource);
      return;
    }
  fFileSource->SetInputFile(name);
}
//_____________________________________________________________________________
void FairRunAna::AddFriend (TString name)
{
  LOG(WARNING) << "FairRunAna::AddFriend is obsolete. Set it by FairFileSource" << FairLogger::endl;
  if ( fMixedSource ) 
    { 
      LOG(ERROR) << "Mixed input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fFileSource ) 
    {
      LOG(ERROR) << "Input file not yet set!" << FairLogger::endl;
      return;
    }
  fFileSource->AddFriend(name);
}
//_____________________________________________________________________________
void FairRunAna::AddFile(TString name)
{
  LOG(WARNING) << "FairRunAna::AddFile is obsolete. Set it by FairFileSource" << FairLogger::endl;
  if ( fMixedSource ) 
    { 
      LOG(ERROR) << "Mixed input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fFileSource ) 
    {
      LOG(ERROR) << "Input file not yet set!" << FairLogger::endl;
      return;
    }
  fFileSource->AddFile(name);
}
//_____________________________________________________________________________
// ABOVE FUNCTIONS SHOULD BE DELETED AND MOVED TO FairFileSource ONLY

// BELOW FUNCTIONS SHOULD BE DELETED AND MOVED TO FairMixedSource ONLY
//_____________________________________________________________________________
void FairRunAna::SetSignalFile(TString name, UInt_t identifier )
{
  LOG(WARNING) << "FairRunAna::SetSignalFile is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if (identifier==0) {
    LOG(FATAL) << " ----- Identifier 0 is reserved for background files! please use other value ------ " << FairLogger::endl;
  }
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      fMixedSource = new FairMixedSource(name,identifier);
      SetSource(fMixedSource);
      return;
    }
  fMixedSource->AddSignalFile(name, identifier);
}
//_____________________________________________________________________________
void FairRunAna::AddSignalFile(TString name, UInt_t identifier )
{
  LOG(WARNING) << "FairRunAna::AddSignalFile is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if (identifier==0) {
    LOG(FATAL) << " ----- Identifier 0 is reserved for background files! please use other value ------ " << FairLogger::endl;
  }
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      fMixedSource = new FairMixedSource(name,identifier);
      SetSource(fMixedSource);
      return;
    }
  fMixedSource->AddSignalFile(name, identifier);
}
//_____________________________________________________________________________
void FairRunAna::SetBackgroundFile(TString name)
{
  LOG(WARNING) << "FairRunAna::SetBackgroundFile is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      fMixedSource = new FairMixedSource(name,0);
      SetSource(fMixedSource);
      return;
    }
  fMixedSource->SetBackgroundFile(name);
}
//_____________________________________________________________________________
void FairRunAna::AddBackgroundFile(TString name)
{
  LOG(WARNING) << "FairRunAna::AddBackgroundFile is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      LOG(ERROR) << "Background file not yet set!" << FairLogger::endl;
      return;
    }
  fMixedSource->AddBackgroundFile(name);
}
//_____________________________________________________________________________
void  FairRunAna::BGWindowWidthNo(UInt_t background, UInt_t Signalid)
{
  LOG(WARNING) << "FairRunAna::BGWindowWidthNo is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      LOG(ERROR) << "Background file not yet set!" << FairLogger::endl;
      return;
    }
  fMixedSource->BGWindowWidthNo(background, Signalid);
}
//_____________________________________________________________________________
void  FairRunAna::BGWindowWidthTime(Double_t background, UInt_t Signalid)
{
  LOG(WARNING) << "FairRunAna::BGWindowWidthTime is obsolete. Set it by FairMixedSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      LOG(ERROR) << "Standard input already set!" << FairLogger::endl; 
      return;
    }
  if ( !fMixedSource ) 
    {
      LOG(ERROR) << "Background file not yet set!" << FairLogger::endl;
      return;
    }
  fMixedSource->BGWindowWidthTime(background, Signalid);
}
//_____________________________________________________________________________
// ABOVE FUNCTIONS SHOULD BE DELETED AND MOVED TO FairMixedSource ONLY

// BELOW FUNCTIONS SHOULD BE DELETED AND MOVED TO FairFileSource AND FairMixedSource ONLY
//_____________________________________________________________________________
void FairRunAna::SetEventTimeInterval(Double_t min, Double_t max)
{
  LOG(WARNING) << "FairRunAna::SetEventTimeInterval is obsolete. Set it by FairSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      fFileSource->SetEventTimeInterval(min,max);
      return;
    }
  if ( fMixedSource ) 
    {
      fMixedSource->SetEventTimeInterval(min,max);
      return;
    }
  LOG(ERROR) << "SetEventTimeInterval only by input source!" << FairLogger::endl; 
}
//_____________________________________________________________________________
void  FairRunAna::SetEventMeanTime(Double_t mean)
{
  LOG(WARNING) << "FairRunAna::SetEventMeanTime is obsolete. Set it by FairSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      fFileSource->SetEventMeanTime(mean);
      return;
    }
  if ( fMixedSource ) 
    {
      fMixedSource->SetEventMeanTime(mean);
      return;
    }
  LOG(ERROR) << "SetEventMeanTime only by input source!" << FairLogger::endl; 
}
//_____________________________________________________________________________
void FairRunAna::SetBeamTime(Double_t beamTime, Double_t gapTime)
{
  LOG(WARNING) << "FairRunAna::SetBeamTime is obsolete. Set it by FairSource" << FairLogger::endl;
  if ( fFileSource ) 
    { 
      fFileSource->SetBeamTime(beamTime, gapTime);
      return;
    }
  if ( fMixedSource ) 
    {
      fMixedSource->SetBeamTime(beamTime, gapTime);
      return;
    }
  LOG(ERROR) << "SetBeamTime only by input source!" << FairLogger::endl; 
}
//_____________________________________________________________________________

// void  FairRunAna::SetMixAllInputs(Bool_t Status)
// {
//    fLogger->Info(MESSAGE_ORIGIN, "Mixing for all input is choosed, in this mode one event per input file is read per step");
//    fRootManager->SetMixAllInputs(Status);
// }
//_____________________________________________________________________________
// ABOVE FUNCTIONS SHOULD BE DELETED AND MOVED TO FairFileSource AND FairMixedSource ONLY


ClassImp(FairRunAna)


