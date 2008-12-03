#include "CbmMCApplication.h"
#include "CbmGenericStack.h"
#include "CbmField.h"
#include "CbmModule.h"
#include "CbmDetector.h"
#include "CbmRunSim.h"
#include "CbmIon.h"
#include "CbmMCEventHeader.h"
#include "CbmEventHeader.h"
#include "CbmPrimaryGenerator.h"
#include "CbmTrajFilter.h"
#include "CbmRootManager.h"
#include "CbmTask.h"
#include "CbmVolume.h"
#include "CbmGeoLoader.h"
#include "CbmGeoInterface.h"
#include "CbmGeoMedia.h"
#include "CbmGeoMedium.h"
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
#include "CbmRadLenManager.h"
#include "TSystem.h"

using std::cout;              
using std::endl;
using std::pair;
//_____________________________________________________________________________
CbmMCApplication::CbmMCApplication(const char *name, const char *title, 
   TObjArray *ModList, const char *MatName) 
  : TVirtualMCApplication(name,title),
    fActDetIter(0),
    fActiveDetectors(0),
    fCbmTaskList(0),
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
// Check if the Cbm root manager exist!
   fRootManager=CbmRootManager::Instance();
   if(fRootManager==0) fRootManager= new CbmRootManager();
// Create an ObjArray of Modules and its iterator
   fModules=ModList;
   fModIter = fModules->MakeIterator();
// Create and fill a list of active detectors
   fDetectors=new TRefArray;
   fActiveDetectors=new TRefArray();
   fModIter->Reset();
   CbmDetector *detector;
   TObject *obj;
   while((obj=fModIter->Next())) {
      if(obj->InheritsFrom("CbmDetector")){
         detector=(CbmDetector *)obj;
         fDetectors->Add(detector);
         if(detector->IsActive())fActiveDetectors->Add(detector);
      }
   }  
   fDetIter=fDetectors->MakeIterator();
   fActDetIter=fActiveDetectors->MakeIterator();
// Create a Task list
   fCbmTaskList= new CbmTask("Task List", 1);
   gROOT->GetListOfBrowsables()->Add(fCbmTaskList);  
   fMcVersion=-1;
   // Initialise fTrajFilter pointer
   fTrajFilter = NULL;
   fDetMap=new TRefArray(1000);
   fDisVol=0; 
   fDisDet=0;
   
}
//_____________________________________________________________________________
CbmMCApplication::CbmMCApplication()
  : TVirtualMCApplication(),
    fActDetIter(0),
    fActiveDetectors(0),
    fCbmTaskList(0),
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
CbmMCApplication::CbmMCApplication(Bool_t Geane)
  : TVirtualMCApplication(),
    fActDetIter(0),
    fActiveDetectors(0),
    fCbmTaskList(0),
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
CbmMCApplication::~CbmMCApplication() 
{
// Destructor  
  delete fStack;
  delete fActiveDetectors;
  delete fActDetIter;
  delete fDetectors;
  delete fCbmTaskList;
}
//_____________________________________________________________________________
void CbmMCApplication::RegisterStack()
{
// Registers stack in Root manager.
 //  cout << "CbmMCApplication::RegisterStack() " << endl;
   if(fEvGen) fStack->Register();
}
//_____________________________________________________________________________
void CbmMCApplication::InitMC(const char* setup, const char *cuts)
{
// Initialize MC.
// ---
/*  gROOT->LoadMacro(setup);
  gInterpreter->ProcessLine("Config()");
  
  gROOT->LoadMacro(cuts);
  gInterpreter->ProcessLine("SetCuts()");
	
*/	
  fStack = (CbmGenericStack*) gMC->GetStack();
  gMC->Init();
  gMC->BuildPhysics();
  TString MCName=gMC->GetName();
  if     (MCName == "TGeant3" || MCName == "TGeant3TGeo")  fMcVersion = 0 ; 
  else if(MCName == "TGeant4")  fMcVersion = 1;
  else if(MCName == "TFluka")   fMcVersion = 2;
  else fMcVersion = 3;  //Geane
  fTrajFilter = CbmTrajFilter::Instance();
 
  cout << " -I- CbmMCApplication:: Monte carlo Engine Initialisation  with "<< MCName.Data() << endl;
}
//_____________________________________________________________________________
void CbmMCApplication::RunMC(Int_t nofEvents)
{    
  //write geometry to first output file
  fRootManager->WriteGeometry();
  // MC run.
  gMC->ProcessRun(nofEvents);
  // finish run
  FinishRun();
}                                                      
//____________________________________________________________________________
void CbmMCApplication::FinishRun()
{    
// Finish MC run.
// ---
  if(fActDetIter){
	  fActDetIter->Reset();
	  CbmDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<CbmDetector*>(obj);
		  if (detector) detector->FinishRun();
	  }  
  }
   fRootManager->Write();
}     
//_____________________________________________________________________________
void CbmMCApplication::BeginEvent()
{    
// User actions at beginning of event
// ---
   if(fActDetIter){
	   fActDetIter->Reset();
	   CbmDetector *detector;
	   TObject *obj=0;
	   while((obj=fActDetIter->Next())) {
		   detector = dynamic_cast<CbmDetector*>(obj);
		   if (detector) detector->BeginEvent();
	   }
   }
}

//_____________________________________________________________________________
void CbmMCApplication::BeginPrimary()
{    
// User actions at beginning of a primary track
// ---
 if(fActDetIter){
	 fActDetIter->Reset();
	 CbmDetector *detector=NULL;
	 TObject *obj=0;
	 while((obj=fActDetIter->Next())) {
		 detector = dynamic_cast<CbmDetector*>(obj);
		 if( detector ) detector->BeginPrimary();
	 }  
 }
}
//_____________________________________________________________________________
void CbmMCApplication::PreTrack()
{    

// User actions at beginning of each track
// ---

  if(fActDetIter){
	  fActDetIter->Reset();
	  CbmDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<CbmDetector*>(obj);
		  if (detector) detector->PreTrack();
	  }
  }    
  fTrajAccepted=kFALSE;
  if(NULL != fTrajFilter) {
    // Get the pointer to current track
    TParticle *particle = fStack->GetCurrentTrack();
//	cout << " CbmMCApplication::PreTrack()" << particle << endl;
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
 void  CbmMCApplication::GeanePreTrack(Float_t *x,  Float_t *p ,Int_t PDG) 
{
   fTrajFilter = CbmTrajFilter::Instance();
   if(fTrajFilter){
      TParticle *par= new TParticle(PDG, 0, 0, 0, 0, 0, TLorentzVector(p[0], p[1],p[2], 0),TLorentzVector(x[0], x[1],x[2], 0));
      TGeoTrack *fTrack=fTrajFilter->AddTrack(par);
	  fTrack->AddPoint(x[0], x[1],x[2], 0);
      fTrajAccepted=kTRUE;
   }
}
//_____________________________________________________________________________
void CbmMCApplication::Stepping()
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
			  fDisDet=dynamic_cast<CbmDetector*> (fDisVol->GetModule());
			  if (fDisDet) fDisDet->ProcessHits(fDisVol);
			  InMap=kTRUE;
			  break;
		  }
		  fVolIter++;
	  }while(fVolIter!=fVolMap.upper_bound(id));
	  
	  if(fDisVol && !InMap){ 
		  CbmVolume *fNewV=new CbmVolume( gMC->CurrentVolName(), id);
		  fNewV->setMCid(id);
		  fNewV->setModId(fDisVol->getModId());
		  fNewV->SetModule(fDisVol->GetModule());
		  fNewV->setCopyNo(copyNo);
		  fVolMap.insert(pair<Int_t, CbmVolume* >(id, fNewV));
		  fDisDet=dynamic_cast<CbmDetector*> (fDisVol->GetModule());
		  if ( fDisDet) fDisDet->ProcessHits(fNewV);
	  }
    }
  } else {  //Geane tracking
	  gMC->TrackPosition(fTrkPos); 
	//  TLorentzVector mom;
	//  gMC->TrackMomentum(mom);
	//  cout <<  "CbmMCApplication::Stepping()" <<  gMC->TrackPid() << " Pos : " << fTrkPos.X()<< " "<< fTrkPos.Y()<< "  "<<  fTrkPos.Z() << endl;
	//  cout <<  "CbmMCApplication::Stepping()" <<  gMC->TrackPid() << " Mom : " << mom.X() << " "<< mom.Y()<< "  "<<  mom.Z() << endl;
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
void CbmMCApplication::PostTrack()
{    
// User actions after finishing of each track
// ---
  fActDetIter->Reset();
  CbmDetector *detector=NULL;
  TObject *obj=0;
  while((obj=fActDetIter->Next())) {
    detector = dynamic_cast<CbmDetector*>(obj);
    if (detector ) detector->PostTrack();
  }  
}

//_____________________________________________________________________________
void CbmMCApplication::FinishPrimary()
{    
// User actions after finishing of a primary track
// ---
  if(fActDetIter){
	  fActDetIter->Reset();
	  CbmDetector *detector=NULL;
	  TObject *obj=0;
	  while((obj=fActDetIter->Next())) {
		  detector = dynamic_cast<CbmDetector*>(obj);
		  if (detector) detector->FinishPrimary();
	  }  
  }
}

//_____________________________________________________________________________

void CbmMCApplication::StopRun(){
  FinishEvent();
  FinishRun();
  fRootManager->Write(); 
  fRootManager->CloseOutFile(); 
  cout << "StopRun() exiting not safetly oopps !!!@@@!!!" << endl;
  exit(0) ; 
}
//_____________________________________________________________________________
void CbmMCApplication::FinishEvent()
{    
// User actions after finishing of an event
// ---
  // --> Fill the stack output array
  fStack->FillTrackArray();
  // --> Update track indizes in MCTracks and MCPoints
  fStack->UpdateTrackIndex(fActiveDetectors);
  // --> Screen output of stack
  fCbmTaskList->ExecuteTask("");
  fRootManager->Fill();
  fActDetIter->Reset();
  CbmDetector *detector=NULL;
  TObject *obj=0;
  while((obj=fActDetIter->Next())) {
     detector = dynamic_cast<CbmDetector*>(obj);
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
Double_t CbmMCApplication::TrackingRmax() const
{ 
// No limit
// ---
  return DBL_MAX; 
}
//_____________________________________________________________________________
Double_t CbmMCApplication::TrackingZmax() const
{ 
// No limit
// ---
  return DBL_MAX; 
}
//_____________________________________________________________________________
void CbmMCApplication::Field(const Double_t* x, Double_t* b) const
{
// put here a const magnetic field as 0th approx 
// ---
 // cout<< "CbmMCApplication::Field" <<endl;
  if(fxField){
     fxField->GetFieldValue(x,b);
  }else{
     b[0]=0;
     b[1]=0;
     b[2]=0;
  }
}
//_____________________________________________________________________________
void CbmMCApplication::SetField(CbmField *field)
{ 
    fxField=field;
}
//_____________________________________________________________________________
void CbmMCApplication::ConstructOpGeometry()
{
  if(!IsGeane()){
    CbmGeoLoader *loader=CbmGeoLoader::Instance();
    CbmGeoInterface *GeoInterface =loader->getGeoInterface();
    CbmGeoMedia* media= GeoInterface->getMedia();
    TList* MediaList= media->getListOfMedia();
    TListIter iter(MediaList);
    CbmGeoMedium* medium;
    Int_t NK=0;
    Double_t p[4]; 
    while((medium=(CbmGeoMedium*)iter.Next())) {
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
    CbmModule *Mod=NULL;
    while((Mod = dynamic_cast<CbmModule *>(fModIter->Next()))) {
       Mod->ConstructOpGeometry();
    }
  }

}

//_____________________________________________________________________________
void CbmMCApplication::ConstructGeometry()
{
   
   if(!IsGeane()){
      fModIter->Reset();
      CbmModule *Mod=NULL;
      while((Mod = dynamic_cast<CbmModule *>(fModIter->Next()))) {
         Mod->ConstructGeometry();
      }
      fSenVolumes=CbmModule::svList;
      if(fSenVolumes)fNoSenVolumes=fSenVolumes->GetEntries();
   }
   if (gGeoManager) {
      cout << "CbmMCApplication::ConstructGeometry() : Now closing the geometry"<<endl;
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

void CbmMCApplication::InitGeometry()
{    
// Initialize geometry
// --> Register stack and detector collections
   if(!IsGeane()){
      CbmVolume *fv=0;
      Int_t id=0;
      fModIter->Reset();
      CbmDetector *detector=NULL;
      if(fEvGen!=0 && fStack!=0)fStack->Register();
      else cout << "--Warning-- Stack is not registerd " << endl;
      fActDetIter->Reset();

      while((detector = dynamic_cast<CbmDetector*>(fActDetIter->Next()))) {
        detector->Initialize();
        detector->SetSpecialPhysicsCuts();
        detector->Register();
      }
      InitTasks();
     // store the EventHeader Info
      CbmEventHeader *evt = new CbmEventHeader();
      fRootManager->Register("EventHeader.","EvtHeader",evt, kTRUE);
      cout << " -I- CbmMCApplication ->  simulation RunID:  " <<  CbmRunSim::Instance()->GetRunId() << endl;
      evt->SetRunId( CbmRunSim::Instance()->GetRunId() );

      // Create and register MCEventHeader
      UInt_t runId = CbmRunSim::Instance()->GetRunId();
      CbmMCEventHeader* mcEvent = new CbmMCEventHeader(runId);
      fRootManager->Register("MCEventHeader.", "Event", mcEvent, kTRUE);
      if(fEvGen)fEvGen->SetEvent(mcEvent);
      fTrajFilter = CbmTrajFilter::Instance();
      if(NULL != fTrajFilter ) fTrajFilter->Init();
      if(NULL !=fRadLenMan)fRadLenMan->Init();

      // save Geo Params in Output file
      fRootManager->WriteFolder();
      TTree *outTree =new TTree("cbmsim", "/cbmroot", 99);
      fRootManager->TranicateBranchNames(outTree, "cbmroot");
      fRootManager->SetOutTree(outTree);
      for ( Int_t i = 0 ; i < fNoSenVolumes ; i++ ){
         fv= (CbmVolume *)fSenVolumes->At(i);
         id=fv->getMCid();
         if(fv->getGeoNode()==0){   //handel sensetive volumes created directly by user 
            TGeoNode *fN=0;
            TGeoVolume *v=gGeoManager->GetVolume(fv->GetName());
            TObjArray *fNs=0;
            if(v)fNs=v->GetNodes();	
            if(fNs){
               for(Int_t k=0; k<fNs->GetEntriesFast();k++){
                  fN=(TGeoNode *)fNs->At(k);
                  CbmVolume *fNewV=new CbmVolume( fv->GetName(), id);
                  fNewV->setModId(fv->getModId());
                  fNewV->SetModule(fv->GetModule());
                  fNewV->setCopyNo(fN->GetNumber());
                  fNewV->setMCid(id);
                  fVolMap.insert(pair<Int_t, CbmVolume* >(id, fNewV));
               }
            }else{
               CbmVolume *fNewV=new CbmVolume( fv->GetName(), id);
               fNewV->setModId(fv->getModId());
               fNewV->SetModule(fv->GetModule());
               fNewV->setCopyNo(1);
               fNewV->setMCid(id);
               fVolMap.insert(pair<Int_t, CbmVolume* >(id, fNewV));
            }
        }else{
            fVolMap.insert(pair<Int_t, CbmVolume* >(id, fv));
        }
     }
  }

}

//_____________________________________________________________________________
void CbmMCApplication::GeneratePrimaries()
{    
 // Fill the user stack (derived from TVirtualMCStack) with primary particles.
 // ---
  if(fEvGen){
     cout << "CbmMCApplication::GeneratePrimaries()" << endl;
    if (!fEvGen->GenerateEvent( fStack) ){
       StopRun();
    }
  }
}
//_____________________________________________________________________________
CbmDetector *CbmMCApplication::GetDetector(const char *DetName)
{
   return (CbmDetector *)fModules->FindObject(DetName);
}
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
//_____________________________________________________________________________
void  CbmMCApplication::AddIons()
{
   if(!IsGeane()) {
	CbmRunSim *fRun=CbmRunSim::Instance();
	TObjArray *NewIons=fRun->GetUserDefIons();
	TIterator *Iter=NewIons->MakeIterator();
	Iter->Reset();
	TObject *obj=0;
	CbmIon *ion=0;

	while((obj=Iter->Next())) {
		ion=dynamic_cast <CbmIon *> (obj);
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
void  CbmMCApplication::AddIons()
{
  if(!IsGeane()) {
        CbmRunSim *fRun=CbmRunSim::Instance();
        TObjArray *NewIons=fRun->GetUserDefIons();
        TIterator *Iter=NewIons->MakeIterator();
        Iter->Reset();
        TObject *obj=0;
        CbmIon *ion=0;

        while((obj=Iter->Next())) {
                ion=dynamic_cast <CbmIon *> (obj);
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
void  CbmMCApplication::AddParticles()
{
   if(!IsGeane()) {
	CbmRunSim *fRun=CbmRunSim::Instance();
	TObjArray *NewIons=fRun->GetUserDefIons();
	TIterator *Iter=NewIons->MakeIterator();
	Iter->Reset();
	TObject *obj=0;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,17,4)
        TObjArray *NewPart=fRun->GetUserDefParticles();
	TIterator *parIter=NewPart->MakeIterator();
	parIter->Reset();
	obj=0;
	CbmParticle *particle=0;
	while((obj=parIter->Next())) {
		particle=dynamic_cast <CbmParticle *> (obj);
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
void CbmMCApplication::AddDecayModes()
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
CbmPrimaryGenerator *CbmMCApplication::GetGenerator()
{
	return fEvGen;            
}
//_____________________________________________________________________________
void CbmMCApplication::SetGenerator(CbmPrimaryGenerator *pGen)
{
     fEvGen=pGen;
}
//_____________________________________________________________________________
void CbmMCApplication::AddTask(TTask *fTask)
{
   if (! fCbmTaskList ) {
      fCbmTaskList= new CbmTask("Task List", 1);
      gROOT->GetListOfBrowsables()->Add(fCbmTaskList);
   }
   fCbmTaskList->Add(fTask);
}
//_____________________________________________________________________________
CbmGenericStack *CbmMCApplication::GetStack()
{
    return fStack;
}
//_____________________________________________________________________________
TTask *CbmMCApplication::GetListOfTasks()
{
    return fCbmTaskList;
}
//_____________________________________________________________________________
void CbmMCApplication::InitTasks()
{	
    fCbmTaskList->InitTask();
}
//_____________________________________________________________________________
TChain* CbmMCApplication::GetChain()
{
    return fRootManager->GetInChain();
}
//_____________________________________________________________________________

void  CbmMCApplication::SetRadiationLengthReg(Bool_t RadLen)
{
    fRadLength=RadLen;
    if(fRadLength){
        fRadLenMan= new CbmRadLenManager();
    }
}
//_____________________________________________________________________________


ClassImp(CbmMCApplication)


