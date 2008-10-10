// -------------------------------------------------------------------------
// -----                        FairMCStack source file                  -----
// -----                  Created 09/10/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairMCStack.h"
#include "TEveTrack.h"
#include <iostream>
#include "TEveTrackPropagator.h"
#include "TGeoTrack.h"
#include "CbmRootManager.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TEveManager.h"
#include "FairEventManager.h"
#include "CbmMCTrack.h"

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairMCStack::FairMCStack() 
{

}
// -------------------------------------------------------------------------


// -----   Standard constructor   ------------------------------------------
FairMCStack::FairMCStack(const char* name, Int_t iVerbose) 
  : CbmTask(name, iVerbose),
    fEveTrList( new TObjArray(16))
{

}
// -------------------------------------------------------------------------
InitStatus FairMCStack::Init()
{
   if(fVerbose>1) cout<<  "FairMCStack::Init()" << endl;
   CbmRootManager* fManager = CbmRootManager::Instance();
   fTrackList = (TClonesArray *)fManager->GetObject("MCTrack");
   if(fTrackList==0){
      cout << "FairMCPointDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl; 
      SetActive(kFALSE);
   }
   if(fVerbose>2) cout<<  "FairMCStack::Init() get track list" << fTrackList<< endl;
   if(fVerbose>2) cout<<  "FairMCStack::Init()  create propagator" << endl;
   fEventManager =FairEventManager::Instance();
   if(fVerbose>2) cout<<  "FairMCStack::Init() get instance of FairEventManager " << endl;
   fEvent = "Current Event";
   MinEnergyLimit=fEventManager->GetEvtMinEnergy();
   MaxEnergyLimit=fEventManager->GetEvtMaxEnergy();
   PEnergy=0;
   if(IsActive()) return kSUCCESS;
   else return kERROR;
}  
// -------------------------------------------------------------------------
void FairMCStack::Exec(Option_t* option)
{
    
  if (IsActive()){
 
	if(fVerbose>1)  cout << " FairMCStack::Exec "<< endl;
    CbmMCTrack *tr;             
    const Double_t *point;
    
    Reset();
   
    for (Int_t i=0; i<fTrackList->GetEntriesFast(); i++)	{
		if(fVerbose>2) cout << "FairMCStack::Exec "<< i << endl;
        tr=(CbmMCTrack *)fTrackList->At(i);
		
		TVector3 Ptot = tr->GetMomentum();
		Int_t  MotherId =tr->GetMotherID();  
		TVector3 Vertex =tr->GetStartVertex();
		Double_t time= tr->GetStartTime()*1e-09; 
		
        //TParticle *P=(TParticle *)tr->GetParticle();
		Double_t mass=0.0;
		Double_t ene=0.0;
		TParticlePDG* fParticlePDG = TDatabasePDG::Instance()->GetParticle(tr->GetPdgCode());
		
		if (fParticlePDG)
			mass    = fParticlePDG->Mass();
		if ( mass >= 0 ) {
			ene  = TMath::Sqrt(mass*mass + Ptot.Mag2());
		}
		//TParticle(Int_t pdg, Int_t status, Int_t mother1, Int_t mother2, Int_t daughter1, Int_t daughter2, Double_t px, Double_t py, Double_t pz, Double_t etot, Double_t vx, Double_t vy, Double_t vz, Double_t time)
		    
		TParticle *P =new TParticle(tr->GetPdgCode(), i, MotherId, -1, -1, -1, Ptot.Px(), Ptot.Py(),Ptot.Pz(),ene, Vertex.x(), Vertex.z(), Vertex.z(), time);
		
		PEnergy=P->Energy();
        MinEnergyLimit=TMath::Min(PEnergy,MinEnergyLimit) ;
        MaxEnergyLimit=TMath::Max(PEnergy,MaxEnergyLimit) ;
		 if(fVerbose>2)cout << "MinEnergyLimit " << MinEnergyLimit << " MaxEnergyLimit " << MaxEnergyLimit << endl;
        if (fEventManager->IsPriOnly() && P->GetMother(0)>-1) continue;
        if(fEventManager->GetCurrentPDG()!=0 && fEventManager->GetCurrentPDG()!= tr->GetPdgCode())continue;
		 if(fVerbose>2)cout << "PEnergy " << PEnergy << " Min "  << fEventManager->GetMinEnergy() << " Max " << fEventManager->GetMaxEnergy() <<endl;
        if( (PEnergy<fEventManager->GetMinEnergy()) || (PEnergy >fEventManager->GetMaxEnergy())) continue;
		
		//here we have to propagate 
		
        //Int_t Np=tr->GetNpoints(); 
		
        fTrList= GetTrGroup(P);
        TEveTrack *track= new TEveTrack(P, tr->GetPdgCode(), fTrPr);
        track->SetLineColor(fEventManager->Color(tr->GetPdgCode()));
     
		/*   for (Int_t n=0; n<Np; n++){
           point=tr->GetPoint(n);
           track->SetPoint(n,point[0],point[1],point[2]);
           TEveVector pos= TEveVector(point[0], point[1],point[2]);
	       TEvePathMark *path = new TEvePathMark();
		   path->fV=pos ;
		   path->fTime= point[3];
           if(n==0){
               TEveVector Mom= TEveVector(P->Px(), P->Py(),P->Pz());
               path->fP=Mom; 
           }
           if(fVerbose>3) cout << "Path marker added " << path << endl;     
#if ROOT_VERSION_CODE <= ROOT_VERSION(5,18,0)	   
           track->AddPathMark(path);
#else
           track->AddPathMark(*path);
#endif	   
		  if(fVerbose>3) cout << "Path marker added " << path << endl;     
        }
	  
        fTrList->AddElement(track);
		if(fVerbose>3)cout << "track added " << track->GetName() << endl; 
    */
	}
    for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++){
       TEveTrackList *TrListIn=( TEveTrackList *) fEveTrList->At(i);
       TrListIn->FindMomentumLimits(TrListIn, kFALSE); 
    } 
    fEventManager->SetEvtMaxEnergy(MaxEnergyLimit);
    fEventManager->SetEvtMinEnergy(MinEnergyLimit);
    gEve->Redraw3D(kFALSE);
 }
}    
// -----   Destructor   ----------------------------------------------------
FairMCStack::~FairMCStack()
{
}
// -------------------------------------------------------------------------
void FairMCStack::SetParContainers()
{

}

// -------------------------------------------------------------------------
void FairMCStack::Finish() 
{

}
// -------------------------------------------------------------------------
void FairMCStack::Reset()
{
   for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++){
      TEveTrackList  *ele=( TEveTrackList *) fEveTrList->At(i);
      gEve->RemoveElement(ele,fEventManager); 
   }
   fEveTrList->Clear();
}

TEveTrackList *FairMCStack::GetTrGroup(TParticle *P)
{

  fTrList=0;
  for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++){
     TEveTrackList *TrListIn=( TEveTrackList *) fEveTrList->At(i);
     if ( strcmp(TrListIn->GetName(),P->GetName())==0 ) {
	 fTrList= TrListIn;
         break;
     }
  }
  if(fTrList ==0){
    fTrPr=new TEveTrackPropagator();
    fTrList= new  TEveTrackList(P->GetName(),fTrPr );
    fTrList->SetMainColor(fEventManager->Color(P->GetPdgCode()));
    fEveTrList->Add(fTrList);
    gEve->AddElement( fTrList ,fEventManager );
    fTrList->SetRnrLine(kTRUE);
  }                          
  return fTrList;
}

ClassImp(FairMCStack)


