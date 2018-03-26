/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet1.h"

#include "FairDetectorList.h"           // for DetectorId::kTutDet
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairStack.h"                  // for FairStack
#include "FairTutorialDet1Geo.h"        // for FairTutorialDet1Geo
#include "FairTutorialDet1GeoPar.h"     // for FairTutorialDet1GeoPar
#include "FairTutorialDet1Point.h"      // for FairTutorialDet1Point
#include "FairVolume.h"                 // for FairVolume
#include "FairLogger.h"                 // for logging

#include <iosfwd>                       // for ostream
#include "TClonesArray.h"               // for TClonesArray
#include "TList.h"                      // for TListIter, TList (ptr only)
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString
#include "TVirtualMC.h"                 // for TVirtualMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include <stddef.h>                     // for NULL

FairTutorialDet1Geo* FairTutorialDet1::fgGeo = NULL;

FairTutorialDet1::FairTutorialDet1()
  : FairDetector("TutorialDet", kTRUE, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDet1PointCollection(new TClonesArray("FairTutorialDet1Point"))
{
}

FairTutorialDet1::FairTutorialDet1(const char* name, Bool_t active)
  : FairDetector(name, active, kTutDet),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDet1PointCollection(new TClonesArray("FairTutorialDet1Point"))
{
}

FairTutorialDet1::FairTutorialDet1(const FairTutorialDet1& rhs)
  : FairDetector(rhs),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairTutorialDet1PointCollection(new TClonesArray("FairTutorialDet1Point"))
{
}

FairTutorialDet1::~FairTutorialDet1()
{
  if (fFairTutorialDet1PointCollection) {
    fFairTutorialDet1PointCollection->Delete();
    delete fFairTutorialDet1PointCollection;
  }
}

void FairTutorialDet1::Initialize()
{
  SetSensitiveVolumes();

  FairDetector::Initialize();
/*
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDet1GeoPar* par=(FairTutorialDet1GeoPar*)(rtdb->getContainer("FairTutorialDet1GeoPar"));
*/
}

Bool_t  FairTutorialDet1::ProcessHits(FairVolume* vol)
{
  /** This method is called from the MC stepping */

  LOG(debug) << "In FairTutorialDet1::ProcessHits";
  //Set parameters at entrance of volume. Reset ELoss.
  if ( TVirtualMC::GetMC()->IsTrackEntering() ) {
    fELoss  = 0.;
    fTime   = TVirtualMC::GetMC()->TrackTime() * 1.0e09;
    fLength = TVirtualMC::GetMC()->TrackLength();
    TVirtualMC::GetMC()->TrackPosition(fPos);
    TVirtualMC::GetMC()->TrackMomentum(fMom);
  }

  // Sum energy loss for all steps in the active volume
  fELoss += TVirtualMC::GetMC()->Edep();

  // Create FairTutorialDet1Point at exit of active volume
  if ( TVirtualMC::GetMC()->IsTrackExiting()    ||
       TVirtualMC::GetMC()->IsTrackStop()       ||
       TVirtualMC::GetMC()->IsTrackDisappeared()   ) {
    fTrackID  = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of tutorial det points in TParticle
    FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
    stack->AddPoint(kTutDet);
  }

  return kTRUE;
}

void FairTutorialDet1::EndOfEvent()
{

  fFairTutorialDet1PointCollection->Clear();

}



void FairTutorialDet1::Register()
{

  /** This will create a branch in the output tree called
      FairTutorialDet1Point, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  if ( ! gMC->IsMT() ) {
    FairRootManager::Instance()->Register("TutorialDetPoint", "TutorialDet",
                                          fFairTutorialDet1PointCollection, kTRUE);
  } else {
    FairRootManager::Instance()->RegisterAny("TutorialDetPoint",
                                             fFairTutorialDet1PointCollection, kTRUE);
  }
}


TClonesArray* FairTutorialDet1::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fFairTutorialDet1PointCollection; }
  else { return NULL; }
}

void FairTutorialDet1::Reset()
{
  fFairTutorialDet1PointCollection->Clear();
}

void FairTutorialDet1::ConstructGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  fgGeo  = new FairTutorialDet1Geo();
  fgGeo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(fgGeo);

  Bool_t rc = geoFace->readSet(fgGeo);
  if (rc) { fgGeo->create(geoLoad->getGeoBuilder()); }
}

FairTutorialDet1Point* FairTutorialDet1::AddHit(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t time, Double_t length,
    Double_t eLoss)
{
  TClonesArray& clref = *fFairTutorialDet1PointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) FairTutorialDet1Point(trackID, detID, pos, mom,
         time, length, eLoss);
}

FairModule* FairTutorialDet1::CloneModule() const
{
  return new FairTutorialDet1(*this);
}

void FairTutorialDet1::SetSensitiveVolumes()
{
  TList* volList = fgGeo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairTutorialDet1GeoPar* par=static_cast<FairTutorialDet1GeoPar*>(rtdb->getContainer("FairTutorialDet1GeoPar"));
  TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
  TObjArray* fPassNodes = par->GetGeoPassiveNodes();

  TListIter iter(volList);
  FairGeoNode* node   = NULL;
  FairGeoVolume* aVol=NULL;

  while( (node = static_cast<FairGeoNode*>(iter.Next())) ) {
    aVol = dynamic_cast<FairGeoVolume*> ( node );
    if ( node->isSensitive()  ) {
      fSensNodes->AddLast( aVol );
    } else {
      fPassNodes->AddLast( aVol );
    }
  }
  par->setChanged();
  par->setInputVersion(fRun->GetRunId(),1);

  ProcessNodes ( volList );
}


ClassImp(FairTutorialDet1)
