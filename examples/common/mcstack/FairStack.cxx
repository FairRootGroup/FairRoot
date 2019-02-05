/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairStack source file                    -----
// -----             Created 10/08/04  by D. Bertini / V. Friese       -----
// -------------------------------------------------------------------------
#include "FairStack.h"

#include "FairDetector.h"               // for FairDetector
#include "FairLink.h"                   // for FairLink
#include "FairMCPoint.h"                // for FairMCPoint
#include "FairMCTrack.h"                // for FairMCTrack
#include "FairRootManager.h"            // for FairRootManager
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN

#include <iosfwd>                       // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TGeoManager.h"                // for gGeoManager
#include "TIterator.h"                  // for TIterator
#include "TLorentzVector.h"             // for TLorentzVector
#include "TParticle.h"                  // for TParticle
#include "TRefArray.h"                  // for TRefArray
#include "TVirtualMC.h"                 // for gMC

#include <stddef.h>                     // for NULL
#include <iostream>                     // for operator<<, etc

using std::pair;


// -----   Default constructor   -------------------------------------------
FairStack::FairStack(Int_t size)
  : FairGenericStack(),
    fStack(),
    fParticles(new TClonesArray("TParticle", size)),
    fTracks(new TClonesArray("FairMCTrack", size)),
    fStoreMap(),
    fStoreIter(),
    fIndexMap(),
    fIndexIter(),
    fFSTrackMap(),
    fFSTrackIter(),
    fFSMovedIndex(-2),
    fPointsMap(),
    fCurrentTrack(-1),
    fNPrimaries(0),
    fNParticles(0),
    fNTracks(0),
    fIndex(0),
    fStoreSecondaries(kTRUE),
    fMinPoints(1),
    fEnergyCut(0.),
    fStoreMothers(kTRUE)
{
}

// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
FairStack::~FairStack()
{
  if (fParticles) {
    fParticles->Delete();
    delete fParticles;
  }
  if (fTracks) {
    fTracks->Delete();
    delete fTracks;
  }
}
// -------------------------------------------------------------------------

void FairStack::PushTrack(Int_t toBeDone, Int_t parentId, Int_t pdgCode,
                          Double_t px, Double_t py, Double_t pz,
                          Double_t e, Double_t vx, Double_t vy, Double_t vz,
                          Double_t time, Double_t polx, Double_t poly,
                          Double_t polz, TMCProcess proc, Int_t& ntr,
                          Double_t weight, Int_t is)
{

  PushTrack( toBeDone, parentId, pdgCode,
             px,  py,  pz,
             e,  vx,  vy,  vz,
             time,  polx,  poly,
             polz, proc, ntr,
             weight, is, -1);
}






// -----   Virtual public method PushTrack   -------------------------------
void FairStack::PushTrack(Int_t toBeDone, Int_t parentId, Int_t pdgCode,
                          Double_t px, Double_t py, Double_t pz,
                          Double_t e, Double_t vx, Double_t vy, Double_t vz,
                          Double_t time, Double_t polx, Double_t poly,
                          Double_t polz, TMCProcess proc, Int_t& ntr,
                          Double_t weight, Int_t /*is*/, Int_t /*secondparentID*/)
{
    // LOG(info) << "FairStack::PushTrack(" << toBeDone << ", " << parentId << ", " << pdgCode << ": "
    //           << vx << ", " << vy << ", " << vz << " / "
    //           << px << ", " << py << ", " << pz <<")";
  // --> Get TParticle array
  TClonesArray& partArray = *fParticles;

  // --> Create new TParticle and add it to the TParticle array
  Int_t trackId = fNParticles;
  Int_t nPoints = 0;
  Int_t daughter1Id = -1;
  Int_t daughter2Id = -1;
  TParticle* particle =
    new(partArray[fNParticles++]) TParticle(pdgCode, trackId, parentId,
        nPoints, daughter1Id,
        daughter2Id, px, py, pz, e,
        vx, vy, vz, time);
  particle->SetPolarisation(polx, poly, polz);
  particle->SetWeight(weight);
  particle->SetUniqueID(proc);

  // --> Increment counter
  if (parentId < 0) { fNPrimaries++; }

  // --> Set argument variable
  ntr = trackId;

  // --> Push particle on the stack if toBeDone is set
  if (toBeDone == 1) { fStack.push(particle); }

}
// -------------------------------------------------------------------------



// -----   Virtual method PopNextTrack   -----------------------------------
TParticle* FairStack::PopNextTrack(Int_t& iTrack)
{
  // If end of stack: Return empty pointer
  if (fStack.empty()) {
    iTrack = -1;
    return NULL;
  }

  // If not, get next particle from stack
  TParticle* thisParticle = fStack.top();
  fStack.pop();

  if ( !thisParticle) {
    iTrack = 0;
    return NULL;
  }

  fCurrentTrack = thisParticle->GetStatusCode();
  iTrack = fCurrentTrack;

  return thisParticle;

}
// -------------------------------------------------------------------------



// -----   Virtual method PopPrimaryForTracking   --------------------------
TParticle* FairStack::PopPrimaryForTracking(Int_t iPrim)
{
  // Get the iPrimth particle from the fStack TClonesArray. This
  // should be a primary (if the index is correct).

  // Test for index
  if (iPrim < 0 || iPrim >= fNPrimaries) {
    LOG(fatal) << "Primary index out of range!" << iPrim;
  }

  // Return the iPrim-th TParticle from the fParticle array. This should be
  // a primary.
  TParticle* part = static_cast<TParticle*>(fParticles->At(iPrim));
  if ( ! (part->GetMother(0) < 0) ) {
    LOG(fatal) << "Not a primary track!" << iPrim;
  }

  return part;

}
// -------------------------------------------------------------------------



// -----   Virtual public method GetCurrentTrack   -------------------------
TParticle* FairStack::GetCurrentTrack() const
{
  TParticle* currentPart = GetParticle(fCurrentTrack);
  if ( ! currentPart) {
    LOG(warn) << "Current track not found in stack!" ;
  }
  return currentPart;
}
// -------------------------------------------------------------------------



// -----   Public method AddParticle   -------------------------------------
void FairStack::AddParticle(TParticle* oldPart)
{
  TClonesArray& array = *fParticles;
  TParticle* newPart = new(array[fIndex]) TParticle(*oldPart);
  newPart->SetWeight(oldPart->GetWeight());
  newPart->SetUniqueID(oldPart->GetUniqueID());
  fIndex++;
}
// -------------------------------------------------------------------------



// -----   Public method FillTrackArray   ----------------------------------
void FairStack::FillTrackArray()
{

  LOG(debug) << "Filling MCTrack array...";

  // --> Reset index map and number of output tracks
  fIndexMap.clear();
  fNTracks = 0;

  // --> Check tracks for selection criteria
  SelectTracks();

  // --> Loop over fParticles array and copy selected tracks
  for (Int_t iPart=0; iPart<fNParticles; iPart++) {
    Bool_t store = kFALSE;

    fStoreIter = fStoreMap.find(iPart);
    if (fStoreIter == fStoreMap.end() ) {
      LOG(fatal) << "Particle " << iPart << " not found in storage map! ";
    } else {
      store = (*fStoreIter).second;
    }

    if (store) {
      FairMCTrack* track =
        new( (*fTracks)[fNTracks]) FairMCTrack(GetParticle(iPart));
      fIndexMap[iPart] = fNTracks;
      // --> Set the number of points in the detectors for this track
      for (Int_t iDet=kREF; iDet<kSTOPHERE; iDet++) {
        pair<Int_t, Int_t> a(iPart, iDet);
        track->SetNPoints(iDet, fPointsMap[a]);
      }
      fNTracks++;
    } else { 
      fIndexMap[iPart] = -2; 
    }

  }

  // --> Map index for primary mothers
  fIndexMap[-1] = -1;

  // --> Screen output
  //Print(1);

}
// -------------------------------------------------------------------------



// -----   Public method UpdateTrackIndex   --------------------------------
void FairStack::UpdateTrackIndex(TRefArray* detList)
{

  LOG(debug) << "Updating track indizes...";
  Int_t nColl = 0;

  // First update mother ID in MCTracks
  for (Int_t i=0; i<fNTracks; i++) {
    FairMCTrack* track = static_cast<FairMCTrack*>(fTracks->At(i));
    Int_t iMotherOld = track->GetMotherId();
    fIndexIter = fIndexMap.find(iMotherOld);
    if (fIndexIter == fIndexMap.end()) {
      LOG(fatal) << "Particle index " << iMotherOld << " not found in index map!";
    } else {
      track->SetMotherId( (*fIndexIter).second );
    }
  }


  if(fDetList==0) {
    // Now iterate through all active detectors
    fDetIter = detList->MakeIterator();
    fDetIter->Reset();
  } else {
    fDetIter->Reset();
  }

  FairDetector* det = NULL;
  while( (det = static_cast<FairDetector*>(fDetIter->Next()) ) ) {


    // --> Get hit collections from detector
    Int_t iColl = 0;
    TClonesArray* hitArray;
    while ( (hitArray = det->GetCollection(iColl++)) ) {
      nColl++;
      Int_t nPoints = hitArray->GetEntriesFast();

      // --> Update track index for all MCPoints in the collection
      for (Int_t iPoint=0; iPoint<nPoints; iPoint++) {
        FairMCPoint* point = static_cast<FairMCPoint*>(hitArray->At(iPoint));
        Int_t iTrack = point->GetTrackID();

        //        LOG(debug) << "point at " << point->GetX() << "," << point->GetY() << "," << point->GetZ() << " has trackID = " << point->GetTrackID();
        fFSTrackIter = fFSTrackMap.find(iTrack);      // check if point created by FastSimulation
        if ( fFSTrackIter != fFSTrackMap.end() ) {    // indeed the point has been created by the FastSimulation mechanism
            iTrack = fFSTrackIter->second;
            point->SetTrackID(iTrack);                // set proper TrackID
        }

        fIndexIter = fIndexMap.find(iTrack);
        if (fIndexIter == fIndexMap.end()) {
          LOG(fatal) << "Particle index " << iTrack << " not found in index map!";
        } else {
	  point->SetTrackID((*fIndexIter).second);
	  point->SetLink(FairLink("MCTrack", (*fIndexIter).second));
	}
      }

    }   // Collections of this detector
  }     // List of active detectors
  LOG(debug) << "...stack and  " << nColl << " collections updated."
;
}
// -------------------------------------------------------------------------



// -----   Public method Reset   -------------------------------------------
void FairStack::Reset()
{
  fIndex = 0;
  fCurrentTrack = -1;
  fNPrimaries = fNParticles = fNTracks = 0;
  while (! fStack.empty() ) { fStack.pop(); }
  fParticles->Clear();
  fTracks->Clear();
  fFSTrackMap.clear();
  fPointsMap.clear();
}
// -------------------------------------------------------------------------



// -----   Public method Register   ----------------------------------------
void FairStack::Register()
{
  if ( gMC && ( ! gMC->IsMT() ) ) {
    FairRootManager::Instance()->Register("MCTrack", "Stack", fTracks,kTRUE);
  } else {
    FairRootManager::Instance()->RegisterAny("MCTrack",fTracks,kTRUE);
  }
}
// -------------------------------------------------------------------------



// -----   Public method Print  --------------------------------------------
void FairStack::Print(Option_t*) const
{
  LOG(info) << "FairStack: Number of primaries        = " << fNPrimaries;
  LOG(info) << "              Total number of particles  = " << fNParticles;
  LOG(info) << "              Number of tracks in output = " << fNTracks;
  if (gLogger->IsLogNeeded(fair::Severity::DEBUG1)) {
    for (Int_t iTrack=0; iTrack<fNTracks; iTrack++) {
      (static_cast<FairMCTrack*>( fTracks->At(iTrack))->Print(iTrack));
    }
  }
}
// -------------------------------------------------------------------------



// -----   Public method AddPoint (for current track)   --------------------
void FairStack::AddPoint(DetectorId detId)
{
  Int_t iDet = detId;
  Int_t iTr = fCurrentTrack;
  fFSTrackIter = fFSTrackMap.find(iTr);      // check if this track is not already created by FastSimulation
  if ( fFSTrackIter != fFSTrackMap.end() ) {  // indeed the track has been created by the FastSimulation mechanism
      iTr = fFSTrackIter->second;            // use the ID of the original track
  }

  pair<Int_t, Int_t> a(iTr, iDet);
  if ( fPointsMap.find(a) == fPointsMap.end() ) { fPointsMap[a] = 1; }
  else { fPointsMap[a]++; }
}
// -------------------------------------------------------------------------



// -----   Public method AddPoint (for arbitrary track)  -------------------
void FairStack::AddPoint(DetectorId detId, Int_t iTrack)
{
  if ( iTrack < 0 ) { return; }
  Int_t iDet = detId;
  Int_t iTr = iTrack;
  fFSTrackIter = fFSTrackMap.find(iTr);      // check if this track is not already created by FastSimulation
  if ( fFSTrackIter != fFSTrackMap.end() ) {  // indeed the track has been created by the FastSimulation mechanism
      iTr = fFSTrackIter->second;            // use the ID of the original track
  }
  pair<Int_t, Int_t> a(iTr, iDet);
  if ( fPointsMap.find(a) == fPointsMap.end() ) { fPointsMap[a] = 1; }
  else { fPointsMap[a]++; }
}
// -------------------------------------------------------------------------




// -----   Virtual method GetCurrentParentTrackNumber   --------------------
Int_t FairStack::GetCurrentParentTrackNumber() const
{
  TParticle* currentPart = GetCurrentTrack();
  if ( currentPart ) { return currentPart->GetFirstMother(); }
  else { return -1; }
}
// -------------------------------------------------------------------------



// -----   Public method GetParticle   -------------------------------------
TParticle* FairStack::GetParticle(Int_t trackID) const
{
  if (trackID < 0 || trackID >= fNParticles) {
    LOG(fatal) << "Particle index " << trackID << " out of range.";
  }
  return static_cast<TParticle*>(fParticles->At(trackID));
}
// -------------------------------------------------------------------------



// -----   Private method SelectTracks   -----------------------------------
void FairStack::SelectTracks()
{

  // --> Clear storage map
  fStoreMap.clear();

  // loop over tracks created by FastSim to order the tracks
  for (  fFSTrackIter = fFSTrackMap.begin(); fFSTrackIter != fFSTrackMap.end(); ++fFSTrackIter ) {
      for (Int_t i=0; i<fNParticles; i++) {
          TParticle* thisPart = GetParticle(i);
          if ( thisPart->GetMother(0) == fFSTrackIter->first )
              thisPart->SetMother(0,fFSTrackIter->second);
      }
  }

  // --> Check particles in the fParticle array
  for (Int_t i=0; i<fNParticles; i++) {

    TParticle* thisPart = GetParticle(i);
    Bool_t store = kTRUE;

    // --> Get track parameters
    Int_t iMother   = thisPart->GetMother(0);
    TLorentzVector p;
    thisPart->Momentum(p);
    Double_t energy = p.E();
    Double_t mass   = p.M();
//    Double_t mass   = thisPart->GetMass();
    Double_t eKin = energy - mass;

    // --> Calculate number of points
    Int_t nPoints = 0;
    for (Int_t iDet=kREF; iDet<kSTOPHERE; iDet++) {
      pair<Int_t, Int_t> a(i, iDet);
      if ( fPointsMap.find(a) != fPointsMap.end() ) {
        nPoints += fPointsMap[a];
      }
    }

    // check if the track was created by the FastSim mechanism. Do not store such tracks
    Bool_t fastSimTrack = kFALSE;
    fFSTrackIter = fFSTrackMap.find(i);
    if ( fFSTrackIter != fFSTrackMap.end() )
        fastSimTrack = kTRUE;

    // --> Check for cuts (store primaries in any case)
    if (iMother < 0) { store = kTRUE; }
    else {
      if (!fStoreSecondaries) { store = kFALSE; }
      if (nPoints < fMinPoints) { store = kFALSE; }
      if (eKin < fEnergyCut) { store = kFALSE; }
      if (fastSimTrack)      { store = kFALSE; }
    }

    // --> Set storage flag
    fStoreMap[i] = store;


  }

  // --> If flag is set, flag recursively mothers of selected tracks
  if (fStoreMothers) {
    for (Int_t i=0; i<fNParticles; i++) {
      if (fStoreMap[i]) {
        Int_t iMother = GetParticle(i)->GetMother(0);
        while(iMother >= 0) {
          fStoreMap[iMother] = kTRUE;
          iMother = GetParticle(iMother)->GetMother(0);
        }
      }
    }
  }

}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void FairStack::FastSimMoveParticleTo(Double_t xx, Double_t yy, Double_t zz, Double_t tt,
                                      Double_t px, Double_t py, Double_t pz, Double_t en)
{
    TLorentzVector curPos;
    TVirtualMC::GetMC()->TrackPosition(curPos);
    LOG(debug) << "track is in " << curPos.X() << "," << curPos.Y() << "," << curPos.Z() << ", moving to " << xx << "," << yy << "," << zz;
    if ( strcmp(gMC->CurrentVolName(),gGeoManager->FindNode(xx,yy,zz)->GetVolume()->GetName()) == 0 ) {
        LOG(fatal) << "FairStack::FastSimMoveParticleTo(" << xx << "," << yy << "," << zz << ": "
                   << gMC->CurrentVolName() << " = " << gGeoManager->FindNode(xx,yy,zz)->GetVolume()->GetName() << ") crashes the simulation.";
    }

    Int_t tobedone  = 1;
    Int_t parent    = 0; // do not store it as mother
    Int_t pdg       = TVirtualMC::GetMC()->TrackPid();
    Double_t polx   = 0.;
    Double_t poly   = 0.;
    Double_t polz   = 0.;
    TMCProcess proc = kPPrimary;// not important, the track will not be saved
    Int_t ntr       = 0;    // Track number; to be filled by the stack
    Int_t status    = 0; // not important, the track will not be saved
    Double_t weight = 0.;

    PushTrack(tobedone, parent, pdg,
              px, py, pz, en,
              xx, yy, zz, tt,
              polx, poly, polz,
              proc, ntr, weight, status);
    fFSMovedIndex = fNParticles-1;
    Int_t trackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
    fFSTrackIter = fFSTrackMap.find(trackID);      // check if this track is not already created by FastSimulation
    if ( fFSTrackIter != fFSTrackMap.end() )       // indeed the track has been created by the FastSimulation mechanism
        trackID = fFSTrackIter->second;            // use the ID of the original track
    fFSTrackMap[ntr] = trackID;

    LOG(debug) << "FairStack::FastSimMoveParticleTo() created track number " << ntr << " to replace track number " << trackID;

    if ( strcmp(TVirtualMC::GetMC()->GetName(),"TGeant3TGeo") == 0 ) {
        TVirtualMC::GetMC()->StopTrack();
    }
}
// -------------------------------------------------------------------------

// -------------------------------------------------------------------------
void FairStack::FastSimStopParticle()
{
    if ( TVirtualMC::GetMC()->IsTrackStop() )
        LOG(fatal) << "FairStack::FastSimStopParticle() tries to stop particle that was probably moved!";
    fFSMovedIndex = -1;
    TVirtualMC::GetMC()->StopTrack();
}
// -------------------------------------------------------------------------


ClassImp(FairStack)
