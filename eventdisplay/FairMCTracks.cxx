// -------------------------------------------------------------------------
// -----                        FairMCTracks source file                  -----
// -----                  Created 10/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------

#include "FairMCTracks.h"

#include "FairEventManager.h"
#include "FairRootManager.h"

#include "TEveTrack.h"
#include "TEveTrackPropagator.h"
#include "TGeoTrack.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TEveManager.h"
#include "TParticle.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairMCTracks::FairMCTracks()
  : FairTask("FairMCTracks", 0),
    fTrackList(NULL),
    fTrPr(NULL),
    fEventManager(NULL),
    fEveTrList(NULL),
    fEvent(""),
    fTrList(NULL),
    MinEnergyLimit(-1.),
    MaxEnergyLimit(-1.),
    PEnergy(-1.)
{
}
// -------------------------------------------------------------------------


// -----   Standard constructor   ------------------------------------------
FairMCTracks::FairMCTracks(const char* name, Int_t iVerbose)
  : FairTask(name, iVerbose),
    fTrackList(NULL),
    fTrPr(NULL),
    fEventManager(NULL),
    fEveTrList(new TObjArray(16)),
    fEvent(""),
    fTrList(NULL),
    MinEnergyLimit(-1.),
    MaxEnergyLimit(-1.),
    PEnergy(-1.)
{
}
// -------------------------------------------------------------------------
InitStatus FairMCTracks::Init()
{
  if(fVerbose>1) { cout<<  "FairMCTracks::Init()" << endl; }
  FairRootManager* fManager = FairRootManager::Instance();
  fTrackList = (TClonesArray*)fManager->GetObject("GeoTracks");
  if(fTrackList==0) {
    cout << "FairMCPointDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< endl;
    SetActive(kFALSE);
  }
  if(fVerbose>2) { cout<<  "FairMCTracks::Init() get track list" << fTrackList<< endl; }
  if(fVerbose>2) { cout<<  "FairMCTracks::Init()  create propagator" << endl; }
  fEventManager =FairEventManager::Instance();
  if(fVerbose>2) { cout<<  "FairMCTracks::Init() get instance of FairEventManager " << endl; }
  fEvent = "Current Event";
  MinEnergyLimit=fEventManager->GetEvtMinEnergy();
  MaxEnergyLimit=fEventManager->GetEvtMaxEnergy();
  PEnergy=0;
  if(IsActive()) { return kSUCCESS; }
  else { return kERROR; }
}
// -------------------------------------------------------------------------
void FairMCTracks::Exec(Option_t* option)
{

  if (IsActive()) {

    if(fVerbose>1) { cout << " FairMCTracks::Exec "<< endl; }
    TGeoTrack* tr;
    const Double_t* point;

    Reset();

    for (Int_t i=0; i<fTrackList->GetEntriesFast(); i++)  {
      if(fVerbose>2) { cout << "FairMCTracks::Exec "<< i << endl; }
      tr=(TGeoTrack*)fTrackList->At(i);
      TParticle* P=(TParticle*)tr->GetParticle();
      PEnergy=P->Energy();
      MinEnergyLimit=TMath::Min(PEnergy,MinEnergyLimit) ;
      MaxEnergyLimit=TMath::Max(PEnergy,MaxEnergyLimit) ;
      if(fVerbose>2) { cout << "MinEnergyLimit " << MinEnergyLimit << " MaxEnergyLimit " << MaxEnergyLimit << endl; }
      if (fEventManager->IsPriOnly() && P->GetMother(0)>-1) { continue; }
      if(fEventManager->GetCurrentPDG()!=0 && fEventManager->GetCurrentPDG()!= tr->GetPDG()) { continue; }
      if(fVerbose>2) { cout << "PEnergy " << PEnergy << " Min "  << fEventManager->GetMinEnergy() << " Max " << fEventManager->GetMaxEnergy() <<endl; }
      if( (PEnergy<fEventManager->GetMinEnergy()) || (PEnergy >fEventManager->GetMaxEnergy())) { continue; }

      Int_t Np=tr->GetNpoints();
      fTrList= GetTrGroup(P);
      TEveTrack* track= new TEveTrack(P, tr->GetPDG(), fTrPr);
      track->SetLineColor(fEventManager->Color(tr->GetPDG()));
      for (Int_t n=0; n<Np; n++) {
        point=tr->GetPoint(n);
        track->SetPoint(n,point[0],point[1],point[2]);
        TEveVector pos= TEveVector(point[0], point[1],point[2]);
        TEvePathMark* path = new TEvePathMark();
        path->fV=pos ;
        path->fTime= point[3];
        if(n==0) {
          TEveVector Mom= TEveVector(P->Px(), P->Py(),P->Pz());
          path->fP=Mom;
        }
        if(fVerbose>3) { cout << "Path marker added " << path << endl; }

        track->AddPathMark(*path);

        if(fVerbose>3) { cout << "Path marker added " << path << endl; }
      }
      fTrList->AddElement(track);
      if(fVerbose>3) { cout << "track added " << track->GetName() << endl; }
    }
    for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++) {
      // TEveTrackList *TrListIn=( TEveTrackList *) fEveTrList->At(i);
      //TrListIn->FindMomentumLimits(TrListIn, kFALSE);
    }
    fEventManager->SetEvtMaxEnergy(MaxEnergyLimit);
    fEventManager->SetEvtMinEnergy(MinEnergyLimit);
    gEve->Redraw3D(kFALSE);
  }
}
// -----   Destructor   ----------------------------------------------------
FairMCTracks::~FairMCTracks()
{
}
// -------------------------------------------------------------------------
void FairMCTracks::SetParContainers()
{

}

// -------------------------------------------------------------------------
void FairMCTracks::Finish()
{

}
// -------------------------------------------------------------------------
void FairMCTracks::Reset()
{
  for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++) {
    TEveTrackList*  ele=( TEveTrackList*) fEveTrList->At(i);
    gEve->RemoveElement(ele,fEventManager);
  }
  fEveTrList->Clear();
}

TEveTrackList* FairMCTracks::GetTrGroup(TParticle* P)
{

  fTrList=0;
  for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++) {
    TEveTrackList* TrListIn=( TEveTrackList*) fEveTrList->At(i);
    if ( strcmp(TrListIn->GetName(),P->GetName())==0 ) {
      fTrList= TrListIn;
      break;
    }
  }
  if(fTrList ==0) {
    fTrPr=new TEveTrackPropagator();
    fTrList= new  TEveTrackList(P->GetName(),fTrPr );
    fTrList->SetMainColor(fEventManager->Color(P->GetPdgCode()));
    fEveTrList->Add(fTrList);
    gEve->AddElement( fTrList ,fEventManager );
    fTrList->SetRnrLine(kTRUE);
  }
  return fTrList;
}

ClassImp(FairMCTracks)


