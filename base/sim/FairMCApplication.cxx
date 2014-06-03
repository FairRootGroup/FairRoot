/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairMCApplication source file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------
#include "FairMCApplication.h"

#include "FairDetector.h"               // for FairDetector
#include "FairField.h"                  // for FairField
#include "FairGenericStack.h"           // for FairGenericStack
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoMedia.h"               // for FairGeoMedia
#include "FairGeoMedium.h"              // for FairGeoMedium
#include "FairIon.h"                    // for FairIon
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairMesh.h"                   // for FairMesh
#include "FairModule.h"                 // for FairModule, etc
#include "FairParticle.h"               // for FairParticle
#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairRadGridManager.h"         // for FairRadGridManager
#include "FairRadLenManager.h"          // for FairRadLenManager
#include "FairRadMapManager.h"          // for FairRadMapManager
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRun
#include "FairRunInfo.h"                // for FairRunInfo
#include "FairRunSim.h"                 // for FairRunSim
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTask.h"                   // for FairTask
#include "FairTrajFilter.h"             // for FairTrajFilter
#include "FairVolume.h"                 // for FairVolume

#include "Riosfwd.h"                    // for ostream
#include "TDatabasePDG.h"               // for TDatabasePDG
#include "TDirectory.h"                 // for TDirectory, gDirectory
#include "TGeoManager.h"                // for gGeoManager, TGeoManager
#include "TGeoMedium.h"                 // for TGeoMedium
#include "TGeoNode.h"                   // for TGeoNode
#include "TGeoTrack.h"                  // for TGeoTrack
#include "TGeoVolume.h"                 // for TGeoVolume
#include "TH2.h"                        // for TH2D
#include "TInterpreter.h"               // for TInterpreter, gInterpreter
#include "TIterator.h"                  // for TIterator
#include "TList.h"                      // for TList, TListIter
#include "TObjArray.h"                  // for TObjArray
#include "TObject.h"                    // for TObject
#include "TParticlePDG.h"               // for TParticlePDG
#include "TROOT.h"                      // for TROOT, gROOT
#include "TRefArray.h"                  // for TRefArray
#include "TSystem.h"                    // for TSystem, gSystem
#include "TTree.h"                      // for TTree
#include "TVirtualMC.h"                 // for TVirtualMC, gMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack
#include "THashList.h"
class TParticle;

#include <float.h>                      // for DBL_MAX
#include <stdlib.h>                     // for NULL, getenv, exit
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;
using std::pair;
//_____________________________________________________________________________
FairMCApplication::FairMCApplication(const char* name, const char* title,
                                     TObjArray* ModList, const char* MatName)
  :TVirtualMCApplication(name,title),
   fActDetIter(NULL),
   fActiveDetectors(NULL),
   fFairTaskList(NULL),
   fDetIter(NULL),
   fDetectors(NULL),
   fDetMap(NULL),
   fLogger(FairLogger::GetLogger()),
   fModIter(NULL),
   fModules(NULL),
   fNoSenVolumes(0),
   fPythiaDecayer(kFALSE),
   fPythiaDecayerConfig(""),
   fStack(NULL),
   fRootManager(NULL),
   fSenVolumes(NULL),
   fxField(NULL),
   fEvGen(NULL),
   fMcVersion(-1),
   fTrajFilter(NULL),
   fTrajAccepted(kFALSE),
   fUserDecay(kFALSE),
   fUserDecayConfig(""),
   fDebug(kFALSE),
   fDisVol(NULL),
   fDisDet(NULL),
   fVolMap(),
   fVolIter(),
   fModVolMap(),
   fModVolIter(),
   fTrkPos(TLorentzVector(0,0,0,0)),
   fRadLength(kFALSE),
   fRadLenMan(NULL),
   fRadMap(kFALSE),
   fRadMapMan(NULL),
   fRadGridMan(NULL),
   fEventHeader(NULL),
   fMCEventHeader(NULL),
   fRunInfo(),
   fGeometryIsInitialized(kFALSE)
{
// Standard Simulation constructor
// Check if the Fair root manager exist!
  fRootManager=FairRootManager::Instance();
// Create an ObjArray of Modules and its iterator
  fModules=ModList;
  fModIter = fModules->MakeIterator();
// Create and fill a list of active detectors
  fDetectors=new TRefArray;
  fActiveDetectors=new TRefArray();
  fModIter->Reset();
  FairDetector* detector;
  TObject* obj;
  while((obj=fModIter->Next())) {
    if(obj->InheritsFrom("FairDetector")) {
      detector=dynamic_cast<FairDetector*>(obj);
      fDetectors->Add(detector);
      if(detector->IsActive()) {
        fActiveDetectors->Add(detector);
      }
    }
  }
  fDetIter=fDetectors->MakeIterator();
  fActDetIter=fActiveDetectors->MakeIterator();
// Create a Task list
  fFairTaskList= new FairTask("Task List", 1);
  gROOT->GetListOfBrowsables()->Add(fFairTaskList);
  fMcVersion=-1;
  // Initialise fTrajFilter pointer
  fTrajFilter = NULL;
  fDetMap=new TRefArray(1000);
  fDisVol=0;
  fDisDet=0;

}
//_____________________________________________________________________________
FairMCApplication::FairMCApplication()
  :TVirtualMCApplication(),
   fActDetIter(0),
   fActiveDetectors(0),
   fFairTaskList(0),
   fDetIter(0),
   fDetectors(0),
   fDetMap(0),
   fLogger(FairLogger::GetLogger()),
   fModIter(0),
   fModules(0),
   fNoSenVolumes(0),
   fPythiaDecayer(kFALSE),
   fPythiaDecayerConfig(""),
   fStack(0),
   fRootManager(0),
   fSenVolumes(0),
   fxField(0),
   fEvGen(0),
   fMcVersion(-1),
   fTrajFilter(NULL),
   fTrajAccepted(kFALSE),
   fUserDecay(kFALSE),
   fUserDecayConfig(""),
   fDebug(kFALSE),
   fDisVol(0),
   fDisDet(0),
   fVolMap(),
   fVolIter(),
   fModVolMap(),
   fModVolIter(),
   fTrkPos(TLorentzVector(0,0,0,0)),
   fRadLength(kFALSE),
   fRadLenMan(NULL),
   fRadMap(kFALSE),
   fRadMapMan(NULL),
   fRadGridMan(NULL),
   fEventHeader(NULL),
   fMCEventHeader(NULL),
   fRunInfo(),
   fGeometryIsInitialized(kFALSE)
{
// Default constructor
}
//_____________________________________________________________________________
FairMCApplication::~FairMCApplication()
{
// Destructor
//   cout<<"Enter Destructor of FairMCApplication"<<endl;
  delete fStack;
  delete fActiveDetectors; // don't do fActiveDetectors->Delete() here
  // the modules are already deleted in FairRunSim
  delete fActDetIter;
  delete fDetectors;
  delete gMC;
  delete fModIter;
  delete fDetIter;
  gMC=0;
  //   cout<<"Leave Destructor of FairMCApplication"<<endl;
}
//_____________________________________________________________________________
void FairMCApplication::RegisterStack()
{
// Registers stack in Root manager.
//  cout << "FairMCApplication::RegisterStack() " << endl;
  if(fEvGen) {
    fStack->Register();
  }
}
//_____________________________________________________________________________
void FairMCApplication::InitMC(const char* setup, const char* cuts)
{
// Initialize MC.
// ---
  fStack = dynamic_cast<FairGenericStack*>(gMC->GetStack()) ;
  if(fStack==NULL) { fLogger->Fatal(MESSAGE_ORIGIN, "NO Stack defined "); }
  gMC->SetMagField(fxField);

  gMC->Init();
  gMC->BuildPhysics();
  TString MCName=gMC->GetName();
  if     (MCName == "TGeant3" || MCName == "TGeant3TGeo") {
    fMcVersion = 0 ;
  } else if(MCName == "TGeant4") {
    fMcVersion = 1;
  } else if(MCName == "TFluka") {
    fMcVersion = 2;
  } else {
    fMcVersion = 3;  //Geane
  }
  fTrajFilter = FairTrajFilter::Instance();

  fLogger->Info(MESSAGE_ORIGIN, "Monte carlo Engine Initialisation  with : %s  ", MCName.Data());
}
//_____________________________________________________________________________
void FairMCApplication::RunMC(Int_t nofEvents)
{
  // Reset the time for FairRunInfo. Otherwise the time of the
  // first event will include the time needed for initilization.
  fRunInfo.Reset();

  /** Set the list of active detectors to the stack*/
  fStack->SetDetArrayList(fActiveDetectors);

  // MC run.
  gMC->ProcessRun(nofEvents);
  // finish run
  FinishRun();
  // Save histograms with memory and runtime information in the output file
  if (FairRunSim::Instance()->GetWriteRunInfoFile()) {
    fRunInfo.WriteInfo();
  }
}
//____________________________________________________________________________
void FairMCApplication::FinishRun()
{
// Finish MC run.
// ---
  if(fActDetIter) {
    fActDetIter->Reset();
    FairDetector* detector=NULL;
    TObject* obj=0;
    while((obj=fActDetIter->Next())) {
      detector = dynamic_cast<FairDetector*>(obj);
      if (detector) {
        detector->FinishRun();
      }
    }
  }
  fFairTaskList->FinishTask();
  //fRootManager->Fill();

  FairPrimaryGenerator* gen = FairRunSim::Instance()->GetPrimaryGenerator();
  //FairMCEventHeader* header = gen->GetEvent();
  Int_t nprimary = gen->GetTotPrimary();
  TObjArray* meshlist  = NULL;

  if (fRadGridMan ) {
    //      cout << "-I FairMCApplication::FinishRun scaling ... " << endl;
    meshlist = fRadGridMan->GetMeshList();
    //      cout << " entries " << meshlist->GetEntriesFast() << endl;
    for(Int_t i=0; i<meshlist->GetEntriesFast(); i++ ) {
      FairMesh* aMesh = dynamic_cast<FairMesh*>(meshlist->At(i));
      aMesh->Scale(1./nprimary);
    }
  }
  if (fRadGridMan) {
    TH2D* tid = NULL;
    TH2D* flu = NULL;
    TH2D* seu = NULL;
    //      cout << "-I FairMCApplication::FinishRun saving ... " << endl;
    //      cout << " entries " << meshlist->GetEntriesFast() << endl;

    cout << endl << endl;
    cout << "======================================================="
         << endl;
    cout << "   Dosimetry  histos saving " << endl << endl;
    cout << "======================================================="
         << endl;
    cout << endl << endl;

    gDirectory->mkdir("Dosimetry");
    gDirectory->cd("Dosimetry");
    gDirectory->cd("");


    for(Int_t i=0; i<meshlist->GetEntriesFast(); i++ ) {
      FairMesh* aMesh = dynamic_cast<FairMesh*> (meshlist->At(i));
      tid = aMesh->GetMeshTid();
      flu = aMesh->GetMeshFlu();
      seu = aMesh->GetMeshSEU();
      //
      // tid->Dump();
      tid->Write();
      flu->Write();
      seu->Write();
    }
  }
  gDirectory->cd("..");
  if (!fRadGridMan) {
    fRootManager->Write();
  }

  //  fRootManager->Write();

}
//_____________________________________________________________________________
void FairMCApplication::BeginEvent()
{
// User actions at beginning of event
// ---
  if(fActDetIter) {
    fActDetIter->Reset();
    FairDetector* detector;
    TObject* obj=0;
    while((obj=fActDetIter->Next())) {
      detector = dynamic_cast<FairDetector*>(obj);
      if (detector) {
        detector->BeginEvent();
      }
    }
  }

}

//_____________________________________________________________________________
void FairMCApplication::BeginPrimary()
{
// User actions at beginning of a primary track
// ---
  if(fActDetIter) {
    fActDetIter->Reset();
    FairDetector* detector=NULL;
    TObject* obj=0;
    while((obj=fActDetIter->Next())) {
      detector = dynamic_cast<FairDetector*>(obj);
      if( detector ) {
        detector->BeginPrimary();
      }
    }
  }
}
//_____________________________________________________________________________
void FairMCApplication::PreTrack()
{

// User actions at beginning of each track
// ---

  if(fActDetIter) {
    fActDetIter->Reset();
    FairDetector* detector=NULL;
    TObject* obj=0;
    while((obj=fActDetIter->Next())) {
      detector = dynamic_cast<FairDetector*>(obj);
      if (detector) {
        detector->PreTrack();
      }
    }
  }
  fTrajAccepted=kFALSE;
  if(NULL != fTrajFilter) {
    // Get the pointer to current track
    TParticle* particle = fStack->GetCurrentTrack();
//  cout << " FairMCApplication::PreTrack()" << particle << endl;
    // Apply cuts
    fTrajAccepted = fTrajFilter->IsAccepted(particle);
    if(fTrajAccepted) {
      // Add trajectory to geo manager
      //    Int_t trackId = fStack->GetCurrentTrackNumber();
      TGeoTrack* fTrack=fTrajFilter->AddTrack(particle);
      // TLorentzVector pos;
      gMC->TrackPosition(fTrkPos);
      fTrack->AddPoint(fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z(), fTrkPos.T());
    }
  }
}
//_____________________________________________________________________________
void FairMCApplication::Stepping()
{
// User actions at each step
// ---
  // Work around for Fluka VMC, which does not call
  // MCApplication::PreTrack()
  static Int_t TrackId = 0;
  if ( fMcVersion ==2 && gMC->GetStack()->GetCurrentTrackNumber() != TrackId ) {
    PreTrack();
    TrackId = gMC->GetStack()->GetCurrentTrackNumber();
  }

  Int_t copyNo;
  Int_t id = gMC->CurrentVolID(copyNo);
  Bool_t InMap =kFALSE;
  fDisVol=0;
  fDisDet=0;
  Int_t fCopyNo=0;
  fVolIter =fVolMap.find(id);
  if (fVolIter!=fVolMap.end()) {
    do {
      fDisVol=fVolIter->second;
      fCopyNo=fDisVol->getCopyNo();
      if(copyNo==fCopyNo) {
        fDisDet=dynamic_cast<FairDetector*> (fDisVol->GetModule());
        if (fDisDet) {
          fDisDet->ProcessHits(fDisVol);
        }
        InMap=kTRUE;
        break;
      }
      fVolIter++;
    } while(fVolIter!=fVolMap.upper_bound(id));
    if(fDisVol && !InMap) {
      FairVolume* fNewV=new FairVolume( gMC->CurrentVolName(), id);
      fNewV->setMCid(id);
      fNewV->setModId(fDisVol->getModId());
      fNewV->SetModule(fDisVol->GetModule());
      fNewV->setCopyNo(copyNo);
      fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
      fDisDet=dynamic_cast<FairDetector*> (fDisVol->GetModule());
      if ( fDisDet) {
        fDisDet->ProcessHits(fNewV);
      }
    }
  }
  if(fTrajAccepted) {
    if(gMC->TrackStep() > fTrajFilter->GetStepSizeCut()) {
      gMC->TrackPosition(fTrkPos);
      fTrajFilter->GetCurrentTrk()->AddPoint(fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z(), fTrkPos.T());
    }
  }
  if(fRadLenMan) {
    id = gMC->CurrentVolID(copyNo);
    fModVolIter =fModVolMap.find(id);
    fRadLenMan->AddPoint(fModVolIter->second);
  }
  if(fRadMapMan) {
    id = gMC->CurrentVolID(copyNo);
    fModVolIter =fModVolMap.find(id);
    fRadMapMan->AddPoint(fModVolIter->second);
  }
  if(fRadGridMan) {
    fRadGridMan->FillMeshList();
  }

}
//_____________________________________________________________________________
void FairMCApplication::PostTrack()
{
// User actions after finishing of each track
// ---
  fActDetIter->Reset();
  FairDetector* detector=NULL;
  TObject* obj=0;
  while((obj=fActDetIter->Next())) {
    detector = dynamic_cast<FairDetector*>(obj);
    if (detector ) {
      detector->PostTrack();
    }
  }
}

//_____________________________________________________________________________
void FairMCApplication::FinishPrimary()
{
// User actions after finishing of a primary track
// ---
  if(fActDetIter) {
    fActDetIter->Reset();
    FairDetector* detector=NULL;
    TObject* obj=0;
    while((obj=fActDetIter->Next())) {
      detector = dynamic_cast<FairDetector*>(obj);
      if (detector) {
        detector->FinishPrimary();
      }
    }
  }
}

//_____________________________________________________________________________

void FairMCApplication::StopRun()
{
  FinishEvent();
  FinishRun();
  fRootManager->Write();
  fRootManager->CloseOutFile();
  fLogger->Warning(MESSAGE_ORIGIN, "StopRun() exiting not safetly oopps !!!@@@!!!" );
  exit(0) ;
}
//_____________________________________________________________________________
void FairMCApplication::FinishEvent()
{
// User actions after finishing of an event
// ---
  // --> Fill the stack output array
  fStack->FillTrackArray();
  // --> Update track indizes in MCTracks and MCPoints
  fStack->UpdateTrackIndex(fActiveDetectors);
  // --> Screen output of stack
  fFairTaskList->ExecuteTask("");
  fFairTaskList->FinishEvent();
  TObject* obj=NULL;
  FairDetector* detector=NULL;
  fActDetIter->Reset();

  while((obj=fActDetIter->Next())) {
    detector = dynamic_cast<FairDetector*>(obj);
    if (detector) {
      detector->FinishEvent();
    }
  }

  fRootManager->Fill();
  fActDetIter->Reset();
  detector=NULL;
  obj=NULL;
  while((obj=fActDetIter->Next())) {
    detector = dynamic_cast<FairDetector*>(obj);
    if (detector) {
      detector->EndOfEvent();
    }
  }
  fStack->Reset();
  if(NULL != fTrajFilter) {
    fTrajFilter->Reset();
//    TObjArray* fListOfTracks=gGeoManager->GetListOfTracks();
//    fListOfTracks->Delete();
    gGeoManager->GetListOfTracks()->Delete();
  }
  if(NULL !=fRadLenMan) {
    fRadLenMan->Reset();
  }
  if(NULL !=fRadMapMan) {
    fRadMapMan->Reset();
  }

  // Store information about runtime for one event and memory consuption
  // for later usage.
  fRunInfo.StoreInfo();
}
//_____________________________________________________________________________
Double_t FairMCApplication::TrackingRmax() const
{
// No limit
// ---
  return DBL_MAX;
}
//_____________________________________________________________________________
Double_t FairMCApplication::TrackingZmax() const
{
// No limit
// ---
  return DBL_MAX;
}
//_____________________________________________________________________________
void FairMCApplication::SetField(FairField* field)
{
  fxField=field;
}
//_____________________________________________________________________________
void FairMCApplication::ConstructOpGeometry()
{
  FairGeoLoader* loader=FairGeoLoader::Instance();
  FairGeoInterface* GeoInterface =loader->getGeoInterface();
  FairGeoMedia* media= GeoInterface->getMedia();
  TList* MediaList= media->getListOfMedia();
  TListIter iter(MediaList);
  FairGeoMedium* medium;
  Int_t NK=0;
  Double_t p[4];
  while((medium=dynamic_cast<FairGeoMedium*>(iter.Next()))) {
    NK=medium->getNpckov();
    if(NK>0) {
      Int_t Mid=0;
      TGeoMedium* Med = 0;
      if ( gGeoManager && (Med = gGeoManager->GetMedium(medium->GetName())) ) {
        Mid=Med->GetId();
      } else {
        Mid=medium->getMediumIndex();
        if(Mid<=0) {
          continue;
        }
      }
      Double_t ppckov[NK], absco[NK], effic[NK],rindex[NK];
      for (Int_t i=0; i<NK; i++) {
        medium->getCerenkovPar(i, p);
        ppckov[i]=p[0]*1E-9;
        absco[i]=p[1];
        effic[i]=p[2];
        rindex[i]=p[3];
      }
      gMC->SetCerenkov(Mid, NK, ppckov,absco, effic, rindex);
    }
  }
  fModIter->Reset();
  FairModule* Mod=NULL;
  while((Mod = dynamic_cast<FairModule*>(fModIter->Next()))) {
    Mod->ConstructOpGeometry();
  }
}

//_____________________________________________________________________________
void FairMCApplication::ConstructGeometry()
{

  fModIter->Reset();
  FairModule* Mod=NULL;
  Int_t NoOfVolumes=0;
  Int_t NoOfVolumesBefore=0;
  Int_t ModId=0;
  while((Mod = dynamic_cast<FairModule*>(fModIter->Next()))) {
    NoOfVolumesBefore=gGeoManager->GetListOfVolumes()->GetEntriesFast();
    Mod->ConstructGeometry();
    ModId=Mod->GetModId();
    NoOfVolumes=gGeoManager->GetListOfVolumes()->GetEntriesFast();
    for (Int_t n=NoOfVolumesBefore; n <= NoOfVolumes; n++) {
      fModVolMap.insert(pair<Int_t, Int_t >(n,ModId));
    }
  }
  fSenVolumes=FairModule::svList;
  if(fSenVolumes) {
    fNoSenVolumes=fSenVolumes->GetEntries();
  }
  if (gGeoManager) {
    //  cout << "FairMCApplication::ConstructGeometry() : Now closing the geometry"<<endl;
    gGeoManager->CloseGeometry();   // close geometry
    gMC->SetRootGeometry();         // notify VMC about Root geometry
      
    TDatabasePDG* pdgDatabase = TDatabasePDG::Instance();
    const THashList *list=pdgDatabase->ParticleList();
    if(list==0)pdgDatabase->ReadPDGTable();
    list =pdgDatabase->ParticleList();
    if(list!=0){
      TIterator *particleIter = list->MakeIterator();
      TParticlePDG *Particle=0;
      while((Particle=dynamic_cast<TParticlePDG*> (particleIter->Next()))) {
         gGeoManager->SetPdgName(Particle->PdgCode(), Particle->GetName());
      }
    }
  }
}
//_____________________________________________________________________________

void FairMCApplication::InitGeometry()
{
  
  //ToBeDone
  // Recently the InitGeometry is called twice from the G4VMC, This is a work around tell the problem get fixed in G4VMC
  if (fGeometryIsInitialized) return;
    
  /// Initialize geometry
  /** Register stack and detector collections*/
  FairVolume* fv=0;
  Int_t id=0;
  fModIter->Reset();
  FairDetector* detector=NULL;
  if(fEvGen!=0 && fStack!=0) {
    fStack->Register();
  } else {
    fLogger->Warning(MESSAGE_ORIGIN, "Stack is not registerd ");
  }
  /** Initialize the event generator */
  // if(fEvGen)fEvGen->Init();
  /** Initialize the detectors.    */
  fActDetIter->Reset();
  while((detector = dynamic_cast<FairDetector*>(fActDetIter->Next()))) {
    detector->Initialize();                // initialize the detectors
    detector->SetSpecialPhysicsCuts();     // set the detector specific detector cuts
    detector->Register();                  //  add branches to tree
  }
  /**Tasks has to be initialized here, they have access to the detector branches and still can create objects in the tree*/
  /// There is always a Main Task  !
  /// so .. always a InitTasks() is called <D.B>
  if (fFairTaskList) {
    InitTasks();
  }

  // store the EventHeader Info
  // Get and register EventHeader
  UInt_t runId = FairRunSim::Instance()->GetRunId();

  fLogger->Info(MESSAGE_ORIGIN, "Simulation RunID: %i  ", runId);

  // Get and register the MCEventHeader
  fMCEventHeader = FairRunSim::Instance()->GetMCEventHeader();
  fMCEventHeader->SetRunID(runId);
  fMCEventHeader->Register();

  if(NULL !=fRadGridMan) {
    fRadGridMan->Init();
  }

  if(fEvGen) {
    fEvGen->SetEvent(fMCEventHeader);
  }
  fTrajFilter = FairTrajFilter::Instance();
  if(NULL != fTrajFilter ) {
    fTrajFilter->Init();
  }
  if(NULL !=fRadLenMan) {
    fRadLenMan->Init();
  }
  if(NULL !=fRadMapMan) {
    fRadMapMan->Init();
  }
  if(NULL !=fRadGridMan) {
    fRadGridMan->Init();
  }


  /// save Geo Params in Output file
  fRootManager->WriteFolder();
  TTree* outTree =new TTree("cbmsim", "/cbmroot", 99);
  fRootManager->TruncateBranchNames(outTree, "cbmroot");
  fRootManager->SetOutTree(outTree);

  for ( Int_t i = 0 ; i < fNoSenVolumes ; i++ ) {
    fv= dynamic_cast<FairVolume*>(fSenVolumes->At(i));
    id=fv->getMCid();
    if(fv->getGeoNode()==0) {  //handel sensetive volumes created directly by user
      TGeoNode* fN=0;
      TGeoVolume* v=gGeoManager->GetVolume(fv->GetName());
      TObjArray* fNs=0;
      if(v) {
        fNs=v->GetNodes();
      }
      if(fNs) {
        for(Int_t k=0; k<fNs->GetEntriesFast(); k++) {
          fN=dynamic_cast<TGeoNode*>(fNs->At(k));
          FairVolume* fNewV=new FairVolume( fv->GetName(), id);
          fNewV->setModId(fv->getModId());
          fNewV->SetModule(fv->GetModule());
          fNewV->setCopyNo(fN->GetNumber());
          fNewV->setMCid(id);
          fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
        }
      } else {
        FairVolume* fNewV=new FairVolume( fv->GetName(), id);
        fNewV->setModId(fv->getModId());
        fNewV->SetModule(fv->GetModule());
        fNewV->setCopyNo(1);
        fNewV->setMCid(id);
        fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
      }
    } else {
      fVolMap.insert(pair<Int_t, FairVolume* >(id, fv));
    }
  }
  fGeometryIsInitialized=kTRUE;

}

//_____________________________________________________________________________
void FairMCApplication::GeneratePrimaries()
{
// Fill the user stack (derived from TVirtualMCStack) with primary particles.
// ---
  if(fEvGen) {
//    cout << "FairMCApplication::GeneratePrimaries()" << endl;
    if (!fEvGen->GenerateEvent( fStack) ) {
      StopRun();
    }
  }
}
//_____________________________________________________________________________
FairDetector* FairMCApplication::GetDetector(const char* DetName)
{
  return dynamic_cast<FairDetector*>(fModules->FindObject(DetName));
}
//_____________________________________________________________________________
void  FairMCApplication::AddIons()
{
  TDatabasePDG* pdgDatabase = TDatabasePDG::Instance();
  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* NewIons=fRun->GetUserDefIons();
  TIterator* Iter=NewIons->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
  FairIon* ion=0;
  while((obj=Iter->Next())) {
    ion=dynamic_cast <FairIon*> (obj);
    if(ion) {
      // Check if an ion with the calculated pdg code already exists in the
      // TDatabasePDG.
      // If the ion already exist don't create a new one because this fails for
      // Geant4. Instead modify the FairIon to use the already existing ion
      // from the TDatabasePDG.
      // The problem occured for example for Alphas which exist already.
      Int_t ionPdg = GetIonPdg( ion->GetZ(), ion->GetA() );
      if ( !pdgDatabase->GetParticle( ionPdg ) ) {
        gMC->DefineIon(ion->GetName(), ion->GetZ(), ion->GetA(), ion->GetQ(),
                       ion->GetExcEnergy(),ion->GetMass());

      } else {
        ion->SetName(pdgDatabase->GetParticle(ionPdg)->GetName());
      }
      //Add Ion to gGeoManager visualization
      if(gGeoManager) {
        gGeoManager->SetPdgName(pdgDatabase->GetParticle(ion->GetName())->PdgCode(),ion->GetName() );
      }
      fLogger->Info(MESSAGE_ORIGIN, "Add Ion:  %s  with PDG  %i ", ion->GetName(), pdgDatabase->GetParticle(ion->GetName())->PdgCode());
    }
  }
  delete   Iter;
  /** Initialize the event generator */
  if(fEvGen) {
    fEvGen->Init();
  }
}
//_____________________________________________________________________________
void  FairMCApplication::AddParticles()
{

  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* NewIons=fRun->GetUserDefIons();
  TIterator* Iter=NewIons->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
  TObjArray* NewPart=fRun->GetUserDefParticles();
  TIterator* parIter=NewPart->MakeIterator();
  parIter->Reset();
  obj=0;
  FairParticle* particle=0;
  while((obj=parIter->Next())) {
    particle=dynamic_cast <FairParticle*> (obj);
    if(particle) {                // (Int_t pdg, const char* name, TMCParticleType type,
      //Double_t mass, Double_t charge, Double_t lifetime);
      cout << "Add Particle: " << particle->GetName()  << " with PDG " <<   particle->GetPDG() << "\n"<<
           particle->GetName() << "            // const TString& name \n" <<
           particle->GetMCType()<<"             // TMCParticleType mcType \n" <<
           particle->GetMass()<<"             // Double_t mass   \n" <<
           particle->GetCharge()<<"           // Double_t charge \n" <<
           particle->GetDecayTime()<<"        // Double_t lifetime  \n" <<
           particle->GetPType()<<  "           // const TString& pType, \n" <<
           particle->GetWidth()<<   "         // Double_t width   \n" <<
           particle->GetSpin()<<    "         // Int_t iSpin  \n" <<
           particle->GetiParity()<< "         // Int_t iParity \n" <<
           particle->GetConjugation()<<"       // Int_t iConjugation  \n" <<
           particle->GetIsospin()<<   "       // Int_t iIsospin   \n" <<
           particle->GetIsospinZ()<<  "       // Int_t iIsospinZ    \n" <<
           particle->GetgParity()<<   "       // Int_t gParity    \n" <<
           particle->GetLepton()<<  "         // Int_t lepton  \n" <<
           particle->GetBaryon()<<  "         // Int_t baryon   \n" <<
           particle->IsStable() <<  "         // Bool_t stable   \n" << endl;
      gMC->DefineParticle(particle->GetPDG(),              // Int_t pdg
                          particle->GetName(),             // const TString& name
                          particle->GetMCType(),             // TMCParticleType mcType
                          particle->GetMass(),             // Double_t mass
                          particle->GetCharge(),           // Double_t charge
                          particle->GetDecayTime(),        // Double_t lifetime
                          particle->GetPType(),             // const TString& pType,
                          particle->GetWidth(),            // Double_t width
                          particle->GetSpin(),             // Int_t iSpin
                          particle->GetiParity(),          // Int_t iParity
                          particle->GetConjugation(),       // Int_t iConjugation
                          particle->GetIsospin(),          // Int_t iIsospin
                          particle->GetIsospinZ(),         // Int_t iIsospinZ
                          particle->GetgParity(),          // Int_t gParity
                          particle->GetLepton(),           // Int_t lepton
                          particle->GetBaryon(),           // Int_t baryon
                          particle->IsStable()             // Bool_t stable
                         );
      //Add Ion to gGeoManager visualization
      if(gGeoManager) {
        gGeoManager->SetPdgName(particle->GetPDG(),particle->GetName() );
      }
    }
  }
  delete   parIter;
  AddDecayModes();
  delete Iter;
}

//_____________________________________________________________________________
void FairMCApplication::AddDecayModes()
{
  TString work = getenv("VMCWORKDIR");
  TString work_config=work+"/gconfig/";
  TString config_dir= getenv("CONFIG_DIR");
  Bool_t AbsPath=kFALSE;

  if (!config_dir.EndsWith("/")) {
    config_dir+="/";
  }
  // set Pythia as external decayer

  if(fPythiaDecayer) {
    TString decayConfig;
    if(fPythiaDecayerConfig.IsNull()) {
      decayConfig="DecayConfig.C";
      fPythiaDecayerConfig= decayConfig;
    } else {
      if (fPythiaDecayerConfig.Contains("/")) {
        AbsPath=kTRUE;
      }
      decayConfig=fPythiaDecayerConfig;
    }

    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), decayConfig)) != TString("")) {
      cout << "---User path for Configuration (DecayConfig.C) is used : " <<  config_dir.Data() << endl;
    } else {
      if(AbsPath) {
        decayConfig=   fPythiaDecayerConfig;
      } else {
        decayConfig=work_config+ fPythiaDecayerConfig ;
      }
    }
    // Add decay modes using an external configuration script
    cout << "External Decay Modes with script \n "<<  decayConfig.Data() << endl;
    // Load configuration script and execute it
    Int_t pyt= gROOT->LoadMacro(decayConfig.Data());
    if(pyt==0) {
      gInterpreter->ProcessLine("DecayConfig()");
    }
  }
  // set user defined phase space decay for particles (ions)
  AbsPath=kFALSE;
  if(fUserDecay) {
    TString Userdecay;
    if(fUserDecayConfig.IsNull()) {
      Userdecay="UserDecay.C";
      fUserDecayConfig =Userdecay;
    } else {
      if(fUserDecayConfig.Contains("/")) {
        AbsPath=kTRUE;
      }
      Userdecay=  fUserDecayConfig;
    }


    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), Userdecay)) != TString("")) {
      cout << "---User path for Configuration (UserDecay.C) is used : " <<  config_dir.Data() << endl;
    } else {
      if(AbsPath) {
        Userdecay=fUserDecayConfig;
      } else {
        Userdecay=work_config+fUserDecayConfig;
      }
    }
    cout << "User Decay Modes with script \n "<<  Userdecay.Data() << endl;
    Int_t dec= gROOT->LoadMacro(Userdecay.Data());
    if(dec==0) {
      gInterpreter->ProcessLine("UserDecayConfig()");
    }
  }
}
//_____________________________________________________________________________
FairPrimaryGenerator* FairMCApplication::GetGenerator()
{
  return fEvGen;
}
//_____________________________________________________________________________
void FairMCApplication::SetGenerator(FairPrimaryGenerator* pGen)
{
  fEvGen=pGen;
}
//_____________________________________________________________________________
void FairMCApplication::AddTask(TTask* fTask)
{
  if (! fFairTaskList ) {
    fFairTaskList= new FairTask("Task List", 1);
    gROOT->GetListOfBrowsables()->Add(fFairTaskList);
  }
  fFairTaskList->Add(fTask);
  SetParTask();
}
//_____________________________________________________________________________
FairGenericStack* FairMCApplication::GetStack()
{
  return fStack;
}
//_____________________________________________________________________________
TTask* FairMCApplication::GetListOfTasks()
{
  return fFairTaskList;
}

//_____________________________________________________________________________
void FairMCApplication::SetParTask()
{
  // Only RTDB init when more than Main Task list
  if(FairRun::Instance()->GetNTasks() >= 1 ) {
    fFairTaskList->SetParTask();
  }
  fModIter->Reset();
  FairModule* Mod=NULL;
  while((Mod = dynamic_cast<FairModule*>(fModIter->Next()))) {
    Mod->SetParContainers();
  }
  FairRuntimeDb* fRTdb=  FairRun::Instance()->GetRuntimeDb();
  fRTdb->initContainers(FairRunSim::Instance()->GetRunId());

}
//_____________________________________________________________________________
void FairMCApplication::InitTasks()
{

  // Only RTDB init when more than Main Task list
  if(FairRun::Instance()->GetNTasks() >= 1 ) {
    fLogger->Info(MESSAGE_ORIGIN, "Initialize Tasks--------------------------");
    fFairTaskList->InitTask();

  }


}
//_____________________________________________________________________________
TChain* FairMCApplication::GetChain()
{
  return fRootManager->GetInChain();
}
//_____________________________________________________________________________

void  FairMCApplication::SetRadiationLengthReg(Bool_t RadLen)
{
  fRadLength=RadLen;
  if(fRadLength) {
    fRadLenMan= new FairRadLenManager();
  }
}
//_____________________________________________________________________________


void  FairMCApplication::SetRadiationMapReg(Bool_t RadMap)
{
  fRadMap=RadMap;
  if(fRadMap) {
    fRadMapMan= new FairRadMapManager();
  }
}
//_____________________________________________________________________________


void  FairMCApplication::AddMeshList(TObjArray* meshList)
{
  if (!fRadGridMan) {
    fRadGridMan = new FairRadGridManager();
  }
  fRadGridMan->AddMeshList (meshList);
}
//_____________________________________________________________________________

Int_t FairMCApplication::GetIonPdg(Int_t z, Int_t a) const
{
  // Acording to
  // http://pdg.lbl.gov/2012/reviews/rpp2012-rev-monte-carlo-numbering.pdf

  return 1000000000 + 10*1000*z + 10*a;
}

ClassImp(FairMCApplication)


