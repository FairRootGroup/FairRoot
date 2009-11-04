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
#include "TParticlePDG.h"
#include "TMCParticleType.h"
#include "THashList.h"
#include <iostream>
#include "FairRadLenManager.h"
#include "TSystem.h"
#include "FairRuntimeDb.h"
using std::cout;              
using std::endl;
using std::pair;
//_____________________________________________________________________________
FairMCApplication::FairMCApplication(const char *name, const char *title, 
   TObjArray *ModList, const char *MatName) 
  : TVirtualMCApplication(name,title),
    fActDetIter(0),
    fActiveDetectors(0),
    fFairTaskList(0),
    fDetIter(0),
    fDetectors(0),
	fDetMap(0),
	fGeane(kFALSE),
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
	fVolIter(0),
	fTrkPos(TLorentzVector(0,0,0,0)),
	fRadLength(kFALSE),
    fRadLenMan(NULL)
			    
{ 
// Standard Simulation constructor
// Check if the Fair root manager exist!
   fRootManager=FairRootManager::Instance();
   if(fRootManager==0) fRootManager= new FairRootManager();
// Create an ObjArray of Modules and its iterator
   fModules=ModList;
   fModIter = fModules->MakeIterator();
// Create and fill a list of active detectors
   fDetectors=new TRefArray;
   fActiveDetectors=new TRefArray();
   fModIter->Reset();
   FairDetector *detector;
   TObject *obj;
   while((obj=fModIter->Next())) {
      if(obj->InheritsFrom("FairDetector")){
         detector=(FairDetector *)obj;
         fDetectors->Add(detector);
         if(detector->IsActive())fActiveDetectors->Add(detector);
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
  : TVirtualMCApplication(),
    fActDetIter(0),
    fActiveDetectors(0),
    fFairTaskList(0),
    fDetIter(0),
    fDetectors(0),
	fDetMap(0),
	fGeane(kFALSE),
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
	fVolIter(0),
	fTrkPos(TLorentzVector(0,0,0,0)),
	fRadLength(kFALSE),
    fRadLenMan(NULL)


{    
// Default constructor
}
//_____________________________________________________________________________
FairMCApplication::FairMCApplication(Bool_t Geane)
  : TVirtualMCApplication(),
    fActDetIter(0),
    fActiveDetectors(0),
    fFairTaskList(0),
    fDetIter(0),
    fDetectors(0),
	fDetMap(0),
	fGeane(Geane),
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
	fVolIter(0),
	fTrkPos(TLorentzVector(0,0,0,0)),
	fRadLength(kFALSE),
    fRadLenMan(NULL)

{
        //constructur used by Geane track propagation
}

//_____________________________________________________________________________
FairMCApplication::~FairMCApplication() 
{
// Destructor  
   delete fStack;
   delete fActiveDetectors;
   delete fActDetIter;
   delete fDetectors;
   delete gMC;	
   gMC=0;
}
//_____________________________________________________________________________
void FairMCApplication::RegisterStack()
{
// Registers stack in Root manager.
 //  cout << "FairMCApplication::RegisterStack() " << endl;
   if(fEvGen) fStack->Register();
}
//_____________________________________________________________________________
void FairMCApplication::InitMC(const char* setup, const char *cuts)
{
// Initialize MC.
// ---
/*  gROOT->LoadMacro(setup);
  gInterpreter->ProcessLine("Config()");
  
  gROOT->LoadMacro(cuts);
  gInterpreter->ProcessLine("SetCuts()");
	
*/	
  fStack = (FairGenericStack*) gMC->GetStack();
 
  gMC->Init();
  gMC->BuildPhysics();
  TString MCName=gMC->GetName();
  if     (MCName == "TGeant3" || MCName == "TGeant3TGeo")  fMcVersion = 0 ; 
  else if(MCName == "TGeant4")  fMcVersion = 1;
  else if(MCName == "TFluka")   fMcVersion = 2;
  else fMcVersion = 3;  //Geane
  fTrajFilter = FairTrajFilter::Instance();
 
  
#if ROOT_VERSION_CODE >= 333824
 gMC->SetMagField(fxField);
#endif
  cout << " -I- FairMCApplication:: Monte carlo Engine Initialisation  with "<< MCName.Data() << endl;
}
//_____________________________________________________________________________
void FairMCApplication::RunMC(Int_t nofEvents)
{    
  //write geometry to first output file
 // fRootManager->WriteGeometry();
  // MC run.
  gMC->ProcessRun(nofEvents);
  // finish run
  FinishRun();
}                                                      
//____________________________________________________________________________
void FairMCApplication::FinishRun()
{    
// Finish MC run.
// ---
  if(fActDetIter){
	  fActDetIter->Reset();
	  FairDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<FairDetector*>(obj);
		  if (detector) detector->FinishRun();
	  }  
  }
  fFairTaskList->FinishTask();
  fRootManager->Write();
}     
//_____________________________________________________________________________
void FairMCApplication::BeginEvent()
{    
// User actions at beginning of event
// ---
   if(fActDetIter){
	   fActDetIter->Reset();
	   FairDetector *detector;
	   TObject *obj=0;
	   while((obj=fActDetIter->Next())) {
		   detector = dynamic_cast<FairDetector*>(obj);
		   if (detector) detector->BeginEvent();
	   }
   }
}

//_____________________________________________________________________________
void FairMCApplication::BeginPrimary()
{    
// User actions at beginning of a primary track
// ---
 if(fActDetIter){
	 fActDetIter->Reset();
	 FairDetector *detector=NULL;
	 TObject *obj=0;
	 while((obj=fActDetIter->Next())) {
		 detector = dynamic_cast<FairDetector*>(obj);
		 if( detector ) detector->BeginPrimary();
	 }  
 }
}
//_____________________________________________________________________________
void FairMCApplication::PreTrack()
{    

// User actions at beginning of each track
// ---

  if(fActDetIter){
	  fActDetIter->Reset();
	  FairDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<FairDetector*>(obj);
		  if (detector) detector->PreTrack();
	  }
  }    
  fTrajAccepted=kFALSE;
  if(NULL != fTrajFilter) {
    // Get the pointer to current track
    TParticle *particle = fStack->GetCurrentTrack();
//	cout << " FairMCApplication::PreTrack()" << particle << endl;
    // Apply cuts
    fTrajAccepted = fTrajFilter->IsAccepted(particle);
    if(fTrajAccepted) {
      // Add trajectory to geo manager
   //    Int_t trackId = fStack->GetCurrentTrackNumber();
       TGeoTrack *fTrack=fTrajFilter->AddTrack(particle);
      // TLorentzVector pos;
       gMC->TrackPosition(fTrkPos);
       fTrack->AddPoint(fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z(), fTrkPos.T());
    }
  }
}
//_____________________________________________________________________________
 void  FairMCApplication::GeanePreTrack(Float_t *x,  Float_t *p ,Int_t PDG) 
{
   fTrajFilter = FairTrajFilter::Instance();
   if(fTrajFilter){
      TParticle *par= new TParticle(PDG, 0, 0, 0, 0, 0, TLorentzVector(p[0], p[1],p[2], 0),TLorentzVector(x[0], x[1],x[2], 0));
      TGeoTrack *fTrack=fTrajFilter->AddTrack(par);
	  fTrack->AddPoint(x[0], x[1],x[2], 0);
      fTrajAccepted=kTRUE;
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

  if(fMcVersion !=3){
    Int_t copyNo;
    Int_t id = gMC->CurrentVolID(copyNo);
    Bool_t InMap =kFALSE;
    fDisVol=0; 
    fDisDet=0;
    Int_t fCopyNo=0;                                      
    fVolIter =fVolMap.find(id);
    if (fVolIter!=fVolMap.end()){
	  do{
		  fDisVol=fVolIter->second;
		  fCopyNo=fDisVol->getCopyNo();		
		  if(copyNo==fCopyNo){
			  fDisDet=dynamic_cast<FairDetector*> (fDisVol->GetModule());
			  if (fDisDet) fDisDet->ProcessHits(fDisVol);
			  InMap=kTRUE;
			  break;
		  }
		  fVolIter++;
	  }while(fVolIter!=fVolMap.upper_bound(id));
	  
	  if(fDisVol && !InMap){ 
		  FairVolume *fNewV=new FairVolume( gMC->CurrentVolName(), id);
		  fNewV->setMCid(id);
		  fNewV->setModId(fDisVol->getModId());
		  fNewV->SetModule(fDisVol->GetModule());
		  fNewV->setCopyNo(copyNo);
		  fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
		  fDisDet=dynamic_cast<FairDetector*> (fDisVol->GetModule());
		  if ( fDisDet) fDisDet->ProcessHits(fNewV);
	  }
    }
  } else {  //Geane tracking
	  gMC->TrackPosition(fTrkPos); 
	//  TLorentzVector mom;
	//  gMC->TrackMomentum(mom);
	//  cout <<  "FairMCApplication::Stepping()" <<  gMC->TrackPid() << " Pos : " << fTrkPos.X()<< " "<< fTrkPos.Y()<< "  "<<  fTrkPos.Z() << endl;
	//  cout <<  "FairMCApplication::Stepping()" <<  gMC->TrackPid() << " Mom : " << mom.X() << " "<< mom.Y()<< "  "<<  mom.Z() << endl;
  }
  
  if(fTrajAccepted) {
        if(gMC->TrackStep() > fTrajFilter->GetStepSizeCut()) {
           gMC->TrackPosition(fTrkPos);
           fTrajFilter->GetCurrentTrk()->AddPoint(fTrkPos.X(), fTrkPos.Y(), fTrkPos.Z(), fTrkPos.T());
	//	   cout << "Current Track" <<  fTrajFilter->GetCurrentTrk() << endl;
        }
  }
  if(fRadLenMan){
      fRadLenMan->AddPoint();
  }
}
//_____________________________________________________________________________
void FairMCApplication::PostTrack()
{    
// User actions after finishing of each track
// ---
  fActDetIter->Reset();
  FairDetector *detector=NULL;
  TObject *obj=0;
  while((obj=fActDetIter->Next())) {
    detector = dynamic_cast<FairDetector*>(obj);
    if (detector ) detector->PostTrack();
  }  
}

//_____________________________________________________________________________
void FairMCApplication::FinishPrimary()
{    
// User actions after finishing of a primary track
// ---
  if(fActDetIter){
	  fActDetIter->Reset();
	  FairDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<FairDetector*>(obj);
		  if (detector) detector->FinishPrimary();
	  }  
  }
}

//_____________________________________________________________________________

void FairMCApplication::StopRun(){
  FinishEvent();
  FinishRun();
  fRootManager->Write(); 
  fRootManager->CloseOutFile(); 
  cout << "StopRun() exiting not safetly oopps !!!@@@!!!" << endl;
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
  fRootManager->Fill();
  fActDetIter->Reset();
  FairDetector *detector=NULL;
  TObject *obj=0;
  while((obj=fActDetIter->Next())) {
     detector = dynamic_cast<FairDetector*>(obj);
     if (detector) detector->EndOfEvent();
  }  
  fStack->Reset();
  if(NULL != fTrajFilter){
     fTrajFilter->Reset();
     TObjArray *fListOfTracks=gGeoManager->GetListOfTracks();
     fListOfTracks->Delete();
  }
  if(NULL !=fRadLenMan) fRadLenMan->Reset();


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
  if(fxField){
     fxField->GetFieldValue(x,b);
//     cout << " FairMCApplication::Field the old way of getting field " << endl;
  }
}
#endif
//_____________________________________________________________________________
void FairMCApplication::SetField(FairField *field)
{ 
    fxField=field;
}
//_____________________________________________________________________________
void FairMCApplication::ConstructOpGeometry()
{
  if(!IsGeane()){
    FairGeoLoader *loader=FairGeoLoader::Instance();
    FairGeoInterface *GeoInterface =loader->getGeoInterface();
    FairGeoMedia* media= GeoInterface->getMedia();
    TList* MediaList= media->getListOfMedia();
    TListIter iter(MediaList);
    FairGeoMedium* medium;
    Int_t NK=0;
    Double_t p[4]; 
    while((medium=(FairGeoMedium*)iter.Next())) {
       NK=medium->getNpckov();
       if(NK>0){
          Int_t Mid=0;
          TGeoMedium * Med = 0;
          if ( gGeoManager && (Med = gGeoManager->GetMedium(medium->GetName())) ){
             Mid=Med->GetId();
          }else{
             Mid=medium->getMediumIndex();
             if(Mid<=0) continue;
          }
          Double_t ppckov[NK], absco[NK], effic[NK],rindex[NK];
          for (Int_t i=0; i<NK; i++){
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
    FairModule *Mod=NULL;
    while((Mod = dynamic_cast<FairModule *>(fModIter->Next()))) {
       Mod->ConstructOpGeometry();
    }
  }

}

//_____________________________________________________________________________
void FairMCApplication::ConstructGeometry()
{
   
   if(!IsGeane()){
      fModIter->Reset();
      FairModule *Mod=NULL;
      while((Mod = dynamic_cast<FairModule *>(fModIter->Next()))) {
         Mod->ConstructGeometry();
      }
      fSenVolumes=FairModule::svList;
      if(fSenVolumes)fNoSenVolumes=fSenVolumes->GetEntries();
   }
   if (gGeoManager) {
      cout << "FairMCApplication::ConstructGeometry() : Now closing the geometry"<<endl;
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
// Initialize geometry
// --> Register stack and detector collections
   if(!IsGeane()){
      FairVolume *fv=0;
      Int_t id=0;
      fModIter->Reset();
      FairDetector *detector=NULL;
      if(fEvGen!=0 && fStack!=0)fStack->Register();
      else cout << "--Warning-- Stack is not registerd " << endl;
      
	  // Initialize the event generator 
	  if(fEvGen)fEvGen->Init();
	   
	  // Initialize the detectors.    
	  fActDetIter->Reset();
      while((detector = dynamic_cast<FairDetector*>(fActDetIter->Next()))) {
        detector->Initialize();                // initialize the detectors
        detector->SetSpecialPhysicsCuts();     // set the detector specific detector cuts
        detector->Register();                  //  add branches to tree
      }
	  /**Tasks has to be initialized here, they have access to the detector branches and still can create objects in the tree*/

      // There is always a Main Task  !
      // so .. always a InitTasks() is called <D.B>
      if (fFairTaskList) InitTasks();

      // store the EventHeader Info
      FairEventHeader *evt = new FairEventHeader();
      fRootManager->Register("EventHeader.","EvtHeader",evt, kTRUE);
      cout << " -I- FairMCApplication ->  simulation RunID:  " <<  FairRunSim::Instance()->GetRunId() << endl;
      evt->SetRunId( FairRunSim::Instance()->GetRunId() );

      // Create and register MCEventHeader
      UInt_t runId = FairRunSim::Instance()->GetRunId();
      FairMCEventHeader* mcEvent = new FairMCEventHeader(runId);
      fRootManager->Register("MCEventHeader.", "Event", mcEvent, kTRUE);
      if(fEvGen)fEvGen->SetEvent(mcEvent);
      fTrajFilter = FairTrajFilter::Instance();
      if(NULL != fTrajFilter ) fTrajFilter->Init();
      if(NULL !=fRadLenMan)fRadLenMan->Init();

      // save Geo Params in Output file
      fRootManager->WriteFolder();
      TTree *outTree =new TTree("cbmsim", "/cbmroot", 99);
      fRootManager->TranicateBranchNames(outTree, "cbmroot");
      fRootManager->SetOutTree(outTree);
      for ( Int_t i = 0 ; i < fNoSenVolumes ; i++ ){
         fv= (FairVolume *)fSenVolumes->At(i);
         id=fv->getMCid();
         if(fv->getGeoNode()==0){   //handel sensetive volumes created directly by user 
            TGeoNode *fN=0;
            TGeoVolume *v=gGeoManager->GetVolume(fv->GetName());
            TObjArray *fNs=0;
            if(v)fNs=v->GetNodes();	
            if(fNs){
               for(Int_t k=0; k<fNs->GetEntriesFast();k++){
                  fN=(TGeoNode *)fNs->At(k);
                  FairVolume *fNewV=new FairVolume( fv->GetName(), id);
                  fNewV->setModId(fv->getModId());
                  fNewV->SetModule(fv->GetModule());
                  fNewV->setCopyNo(fN->GetNumber());
                  fNewV->setMCid(id);
                  fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
               }
            }else{
               FairVolume *fNewV=new FairVolume( fv->GetName(), id);
               fNewV->setModId(fv->getModId());
               fNewV->SetModule(fv->GetModule());
               fNewV->setCopyNo(1);
               fNewV->setMCid(id);
               fVolMap.insert(pair<Int_t, FairVolume* >(id, fNewV));
            }
        }else{
            fVolMap.insert(pair<Int_t, FairVolume* >(id, fv));
        }
     }
  }

}

//_____________________________________________________________________________
void FairMCApplication::GeneratePrimaries()
{    
 // Fill the user stack (derived from TVirtualMCStack) with primary particles.
 // ---
  if(fEvGen){
     cout << "FairMCApplication::GeneratePrimaries()" << endl;
    if (!fEvGen->GenerateEvent( fStack) ){
       StopRun();
    }
  }
}
//_____________________________________________________________________________
FairDetector *FairMCApplication::GetDetector(const char *DetName)
{
   return (FairDetector *)fModules->FindObject(DetName);
}
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
//_____________________________________________________________________________
void  FairMCApplication::AddIons()
{
   if(!IsGeane()) {
	FairRunSim *fRun=FairRunSim::Instance();
	TObjArray *NewIons=fRun->GetUserDefIons();
	TIterator *Iter=NewIons->MakeIterator();
	Iter->Reset();
	TObject *obj=0;
	FairIon *ion=0;

	while((obj=Iter->Next())) {
		ion=dynamic_cast <FairIon *> (obj);
	   if(ion){
		gMC->DefineIon(ion->GetName(), ion->GetZ(), ion->GetA(), ion->GetQ(),
		ion->GetExcEnergy(),ion->GetMass());
		//Add Ion to gGeoManager visualization
  	        if(gGeoManager)gGeoManager->SetPdgName(TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode(),ion->GetName() );
                cout << "Add Ion: " << ion->GetName()  << " with PDG " <<  TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode() << endl;
	  }
	}
        delete   Iter;    
   }
}
#else
void  FairMCApplication::AddIons()
{
  if(!IsGeane()) {
        FairRunSim *fRun=FairRunSim::Instance();
        TObjArray *NewIons=fRun->GetUserDefIons();
        TIterator *Iter=NewIons->MakeIterator();
        Iter->Reset();
        TObject *obj=0;
        FairIon *ion=0;

        while((obj=Iter->Next())) {
                ion=dynamic_cast <FairIon *> (obj);
           if(ion){
                gMC->DefineIon(ion->GetName(), ion->GetZ(), ion->GetA(), ion->GetQ(),
                ion->GetExcEnergy(),ion->GetMass());
                //Add Ion to gGeoManager visualization
                if(gGeoManager)gGeoManager->SetPdgName(TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode(),ion->GetName() );
                cout << "Add Ion: " << ion->GetName()  << " with PDG " <<  TDatabasePDG::Instance()->GetParticle(ion->GetName())->PdgCode() << endl;
          }
        }
        delete   Iter;   
   }
}
#endif

//_____________________________________________________________________________
void  FairMCApplication::AddParticles()
{
   if(!IsGeane()) {
	FairRunSim *fRun=FairRunSim::Instance();
	TObjArray *NewIons=fRun->GetUserDefIons();
	TIterator *Iter=NewIons->MakeIterator();
	Iter->Reset();
	TObject *obj=0;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
        TObjArray *NewPart=fRun->GetUserDefParticles();
	TIterator *parIter=NewPart->MakeIterator();
	parIter->Reset();
	obj=0;
	FairParticle *particle=0;
	while((obj=parIter->Next())) {
		particle=dynamic_cast <FairParticle *> (obj);
	   if(particle){                 // (Int_t pdg, const char* name, TMCParticleType type,
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
   	        if(gGeoManager)gGeoManager->SetPdgName(particle->GetPDG(),particle->GetName() );
		
	  }
	}
        delete   parIter;      
        AddDecayModes();
#else
	AddIons();
#endif
    
  }
}
//_____________________________________________________________________________
void FairMCApplication::AddDecayModes()
{
   TString work = getenv("VMCWORKDIR"); 
   TString work_config=work+"/gconfig/";
   TString config_dir= getenv("CONFIG_DIR");
   Bool_t AbsPath=kFALSE;
   
   if (!config_dir.EndsWith("/")) config_dir+="/"; 
   // set Pythia as external decayer

   if(fPythiaDecayer){ 
	   TString decayConfig; 
	   if(fPythiaDecayerConfig.IsNull()){
	       decayConfig="DecayConfig.C";
		   fPythiaDecayerConfig= decayConfig;
	   }else{
		   if (fPythiaDecayerConfig.Contains("/")) AbsPath=kTRUE;
		   decayConfig=fPythiaDecayerConfig;
	   }
	 
      if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), decayConfig)) != TString("")){
          cout << "---User path for Configuration (DecayConfig.C) is used : " <<  config_dir.Data() << endl;
      }else{
		  if(AbsPath) decayConfig=   fPythiaDecayerConfig;
          else decayConfig=work_config+ fPythiaDecayerConfig ;
      }
      // Add decay modes using an external configuration script
      cout << "External Decay Modes with script \n "<<  decayConfig.Data() << endl;
      // Load configuration script and execute it
      Int_t pyt= gROOT->LoadMacro(decayConfig.Data());
      if(pyt==0)gInterpreter->ProcessLine("DecayConfig()"); 
   }
   // set user defined phase space decay for particles (ions)
   AbsPath=kFALSE;
   if(fUserDecay) {
	   TString Userdecay;
	   if(fUserDecayConfig.IsNull()){
	       Userdecay="UserDecay.C";
		   fUserDecayConfig =Userdecay;	   
	   }else{
		   if(fUserDecayConfig.Contains("/"))AbsPath=kTRUE;
		   Userdecay=  fUserDecayConfig;
	   }
			   
			   
	if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), Userdecay)) != TString("")){
          cout << "---User path for Configuration (UserDecay.C) is used : " <<  config_dir.Data() << endl;
      }else{
		 if(AbsPath) Userdecay=fUserDecayConfig;
         else Userdecay=work_config+fUserDecayConfig; 
	  }
      cout << "User Decay Modes with script \n "<<  Userdecay.Data() << endl;
      Int_t dec= gROOT->LoadMacro(Userdecay.Data());
      if(dec==0)gInterpreter->ProcessLine("UserDecayConfig()"); 
   }
}
//_____________________________________________________________________________
FairPrimaryGenerator *FairMCApplication::GetGenerator()
{
	return fEvGen;            
}
//_____________________________________________________________________________
void FairMCApplication::SetGenerator(FairPrimaryGenerator *pGen)
{
     fEvGen=pGen;
}
//_____________________________________________________________________________
void FairMCApplication::AddTask(TTask *fTask)
{
   if (! fFairTaskList ) {
      fFairTaskList= new FairTask("Task List", 1);
      gROOT->GetListOfBrowsables()->Add(fFairTaskList);
   }
   fFairTaskList->Add(fTask);
}
//_____________________________________________________________________________
FairGenericStack *FairMCApplication::GetStack()
{
    return fStack;
}
//_____________________________________________________________________________
TTask *FairMCApplication::GetListOfTasks()
{
    return fFairTaskList;
}
//_____________________________________________________________________________
void FairMCApplication::InitTasks()
{	
	fFairTaskList->SetParTask();
	

        // Only RTDB init when more than Main Task list
	if(fFairTaskList->GetListOfTasks()->GetEntries() > 1 ) {
	FairRunSim::Instance()->GetRunId();
	FairRuntimeDb*  fRtdb =FairRunSim::Instance()->GetRuntimeDb();
	fRtdb->initContainers( FairRunSim::Instance()->GetRunId() );
	}


	fFairTaskList->InitTask();
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
    if(fRadLength){
        fRadLenMan= new FairRadLenManager();
    }
}
//_____________________________________________________________________________


ClassImp(FairMCApplication)


