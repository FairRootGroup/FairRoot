// -------------------------------------------------------------------------
// -----                    FairDetector source file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------


#include "FairMCApplication.h"
#include "FairGenericStack.h"
#include "FairField.h"
#include "FairModule.h"
#include "FairDetector.h"
#include "FairRunSim.h"
#include "FairIon.h"
#include "FairMCEventHeader.h"
#include "FairEventHeader.h"
#include "FairPrimaryGenerator.h"
#include "FairTrajFilter.h"
#include "FairRootManager.h"
#include "FairTask.h"
#include "FairVolume.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"
#include "FairRadLenManager.h"
#include "FairRadGridManager.h"
#include "FairRadMapManager.h"
#include "FairMesh.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"
#include "FairRunInfo.h"

#include "TObjArray.h"
#include "TGeoTrack.h"
#include "TGeoVolume.h"
#include "TParticle.h"
#include "TGeoManager.h"
#include "TRefArray.h"
#include "TROOT.h"
#include "TInterpreter.h"
#include "TVirtualMC.h"
#include "TDatabasePDG.h"
#include "TGeoTrack.h"
#include "TGeoVolume.h"
#include "TParticle.h"
#include "TGeoManager.h"
#include "TParticlePDG.h"
#include "TMCParticleType.h"
#include "THashList.h"
#include "TSystem.h"

#include <iostream>

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
   fVolIter(NULL),
   fModVolMap(),
   fModVolIter(NULL),
   fTrkPos(TLorentzVector(0,0,0,0)),
   fRadLength(kFALSE),
   fRadLenMan(NULL),
   fRadMap(kFALSE),
   fRadMapMan(NULL),
   fRadGridMan(NULL),
   fEventHeader(NULL),
   fMCEventHeader(NULL),
   fRunInfo()
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
      detector=(FairDetector*)obj;
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
   fVolIter(NULL),
   fModVolMap(),
   fModVolIter(NULL),
   fTrkPos(TLorentzVector(0,0,0,0)),
   fRadLength(kFALSE),
   fRadLenMan(NULL),
   fRadMap(kFALSE),
   fRadMapMan(NULL),
   fRadGridMan(NULL),
   fEventHeader(NULL),
   fMCEventHeader(NULL),
   fRunInfo()
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
  fStack = (FairGenericStack*) gMC->GetStack();

#if ROOT_VERSION_CODE >= 333824
  gMC->SetMagField(fxField);
#endif

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
      FairMesh* aMesh = (FairMesh*) meshlist->At(i);
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
      FairMesh* aMesh = (FairMesh*) meshlist->At(i);
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
    TObjArray* fListOfTracks=gGeoManager->GetListOfTracks();
    fListOfTracks->Delete();
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

#if ROOT_VERSION_CODE < 333824
//_____________________________________________________________________________
void FairMCApplication::Field(const Double_t* x, Double_t* b) const
{
// put here a const magnetic field as 0th approx
// ---
// cout<< "FairMCApplication::Field" <<endl;
  b[0]=0;
  b[1]=0;
  b[2]=0;
  if(fxField) {
    fxField->GetFieldValue(x,b);
//     cout << " FairMCApplication::Field the old way of getting field " << endl;
  }
}
#endif
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
  while((medium=(FairGeoMedium*)iter.Next())) {
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
    gGeoManager->SetPdgName(22, "gamma");
    gGeoManager->SetPdgName(211, "pi+");
    gGeoManager->SetPdgName(321, "K+");
    gGeoManager->SetPdgName(2212, "proton");
    gGeoManager->SetPdgName(-211, "pi-");
    gGeoManager->SetPdgName(-321, "K-");
    gGeoManager->SetPdgName(111, "pi0");
    gGeoManager->SetPdgName(310, "K0");
    gGeoManager->SetPdgName(130, "K0");
    gGeoManager->SetPdgName(2112, "neutron");
    gGeoManager->SetPdgName(11, "e-");
    gGeoManager->SetPdgName(13, "mu-");
    gGeoManager->SetPdgName(-11, "e+");
    gGeoManager->SetPdgName(-13, "mu+");
    gGeoManager->SetPdgName(3312, "Xsi");
    gGeoManager->SetPdgName(3334, "Omega");
    gGeoManager->SetPdgName(50000050, "Ckov");
    gGeoManager->SetPdgName(-421, "D0bar");
    gGeoManager->SetPdgName(421, "D0");
    gGeoManager->SetPdgName(-411, "D-");
    gGeoManager->SetPdgName(411, "D+");
    gGeoManager->SetPdgName(-213, "rho-");
    gGeoManager->SetPdgName(213, "rho+");
    gGeoManager->SetPdgName(113, "rho0");
    gGeoManager->SetPdgName(1000010020, "Deuteron");
    gGeoManager->SetPdgName(1000010030, "Triton");
    gGeoManager->SetPdgName(1000020030, "HE3");
    gGeoManager->SetPdgName(1000020040, "Alpha");
  }
}
//_____________________________________________________________________________

void FairMCApplication::InitGeometry()
{
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
    fv= (FairVolume*)fSenVolumes->At(i);
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
          fN=(TGeoNode*)fNs->At(k);
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
  return (FairDetector*)fModules->FindObject(DetName);
}
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
//_____________________________________________________________________________
void  FairMCApplication::AddIons()
{
  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* NewIons=fRun->GetUserDefIons();
  TIterator* Iter=NewIons->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
  FairIon* ion=0;
  while((obj=Iter->Next())) {
    ion=dynamic_cast <FairIon*> (obj);
    if(ion) {
      gMC->DefineIon(ion->GetName(), ion->GetZ(), ion->GetA(), ion->GetQ(),
                     ion->GetExcEnergy(),ion->GetMass());
      //Add Ion to gGeoManager visualization
      if(gGeoManager) {
        gGeoManager->SetPdgName(TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode(),ion->GetName() );
      }
      fLogger->Info(MESSAGE_ORIGIN, "Add Ion:  %s  with PDG  %i ", ion->GetName(), TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode());
    }
  }
  delete   Iter;
  /** Initialize the event generator */
  if(fEvGen) {
    fEvGen->Init();
  }
}
#else
void  FairMCApplication::AddIons()
{
  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* NewIons=fRun->GetUserDefIons();
  TIterator* Iter=NewIons->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
  FairIon* ion=0;
  while((obj=Iter->Next())) {
    ion=dynamic_cast <FairIon*> (obj);
    if(ion) {
      gMC->DefineIon(ion->GetName(), ion->GetZ(), ion->GetA(), ion->GetQ(),
                     ion->GetExcEnergy(),ion->GetMass());
      //Add Ion to gGeoManager visualization
      if(gGeoManager) {
        gGeoManager->SetPdgName(TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode(),ion->GetName() );
      }
      fLogger->Info(MESSAGE_ORIGIN, "Add Ion:  %s  with PDG  %i ", ion->GetName(), TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode());
    }
  }
  delete   Iter;

  /** Initialize the event generator */
  if(fEvGen) {
    fEvGen->Init();
  }
}
#endif

//_____________________________________________________________________________
void  FairMCApplication::AddParticles()
{

  FairRunSim* fRun=FairRunSim::Instance();
  TObjArray* NewIons=fRun->GetUserDefIons();
  TIterator* Iter=NewIons->MakeIterator();
  Iter->Reset();
  TObject* obj=0;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
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
#else
  AddIons();
#endif
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
    FairRuntimeDb* fRTdb=  FairRun::Instance()->GetRuntimeDb();
    fRTdb->initContainers(FairRunSim::Instance()->GetRunId());

  }
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

ClassImp(FairMCApplication)


