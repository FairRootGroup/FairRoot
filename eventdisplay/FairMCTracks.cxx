/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                        FairMCTracks source file                  -----
// -----                  Created 10/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#include "FairMCTracks.h"

#include "FairEventManager.h"           // for FairEventManager
#include "FairRootManager.h"            // for FairRootManager
#include "FairLogger.h"

#include "Riosfwd.h"                    // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TEveManager.h"                // for TEveManager, gEve
#include "TEvePathMark.h"               // for TEvePathMark
#include "TEveTrack.h"                  // for TEveTrackList, TEveTrack
#include "TEveTrackPropagator.h"        // for TEveTrackPropagator
#include "TEveVector.h"                 // for TEveVector, TEveVectorT
#include "TGeoTrack.h"                  // for TGeoTrack
#include "TMathBase.h"                  // for Max, Min
#include "TObjArray.h"                  // for TObjArray
#include "TParticle.h"                  // for TParticle

#include <string.h>                     // for NULL, strcmp
#include <iostream>                     // for operator<<, basic_ostream, etc


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
  LOG(DEBUG) <<  "FairMCTracks::Init()" << FairLogger::endl; 
  FairRootManager* fManager = FairRootManager::Instance();
  fTrackList = static_cast<TClonesArray*>(fManager->GetObject("GeoTracks"));
  if(fTrackList==0) {
    LOG(ERROR) << "FairMCTracks::Init()  branch " << GetName() << " Not found! Task will be deactivated "<< FairLogger::endl;
    SetActive(kFALSE);
  }
  LOG(DEBUG1) <<  "FairMCTracks::Init() get track list" << fTrackList << FairLogger::endl; 
  LOG(DEBUG1) <<  "FairMCTracks::Init()  create propagator" << FairLogger::endl; 
  fEventManager =FairEventManager::Instance();
  LOG(DEBUG1) <<  "FairMCTracks::Init() get instance of FairEventManager " << FairLogger::endl; 
  fEvent = "Current Event";
  MinEnergyLimit=fEventManager->GetEvtMinEnergy();
  MaxEnergyLimit=fEventManager->GetEvtMaxEnergy();
  PEnergy=0;
  if(IsActive()) { return kSUCCESS; }
  else { return kERROR; }
}
// -------------------------------------------------------------------------
void FairMCTracks::Exec(Option_t* /*option*/)
{

  if (IsActive()) {

    LOG(DEBUG1) << " FairMCTracks::Exec "<< FairLogger::endl; 
    TGeoTrack* tr;
    const Double_t* point;

    Reset();

    for (Int_t i=0; i<fTrackList->GetEntriesFast(); i++)  {
      LOG(DEBUG3) << "FairMCTracks::Exec "<< i << FairLogger::endl; 
      tr=static_cast<TGeoTrack*>(fTrackList->At(i));
      TParticle* P=static_cast<TParticle*>(tr->GetParticle());
      PEnergy=P->Energy();
      MinEnergyLimit=TMath::Min(PEnergy,MinEnergyLimit) ;
      MaxEnergyLimit=TMath::Max(PEnergy,MaxEnergyLimit) ;
      LOG(DEBUG3)<< "MinEnergyLimit " << MinEnergyLimit << " MaxEnergyLimit " << MaxEnergyLimit << FairLogger::endl; 
      if (fEventManager->IsPriOnly() && P->GetMother(0)>-1) { continue; }
      if(fEventManager->GetCurrentPDG()!=0 && fEventManager->GetCurrentPDG()!= tr->GetPDG()) { continue; }
      LOG(DEBUG3) << "PEnergy " << PEnergy << " Min "  << fEventManager->GetMinEnergy() << " Max " << fEventManager->GetMaxEnergy() << FairLogger::endl; 
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
        LOG(DEBUG4) << "Path marker added " << path << FairLogger::endl; 

        track->AddPathMark(*path);

        LOG(DEBUG4) << "Path marker added " << path << FairLogger::endl; 

        delete path;
      }
      fTrList->AddElement(track);
      LOG(DEBUG3) << "track added " << track->GetName() << FairLogger::endl; 

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
    TEveTrackList*  ele=static_cast<TEveTrackList*>(fEveTrList->At(i));
    gEve->RemoveElement(ele,fEventManager);
  }
  fEveTrList->Clear();
}

TEveTrackList* FairMCTracks::GetTrGroup(TParticle* P)
{

  fTrList=0;
  for (Int_t i=0; i<fEveTrList->GetEntriesFast(); i++) {
    TEveTrackList* TrListIn=static_cast<TEveTrackList*>(fEveTrList->At(i));
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


