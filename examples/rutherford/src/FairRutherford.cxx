/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRutherford.h"

#include "FairDetectorList.h"           // for DetectorId::kFairRutherford
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairRootManager.h"            // for FairRootManager
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairRutherfordGeo.h"          // for FairRutherfordGeo
#include "FairRutherfordGeoPar.h"       // for FairRutherfordGeoPar
#include "FairRutherfordPoint.h"        // for FairRutherfordPoint
#include "FairStack.h"                  // for FairStack
#include "FairVolume.h"                 // for FairVolume

#include "TClonesArray.h"               // for TClonesArray
#include "TList.h"                      // for TListIter, TList (ptr only)
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString
#include "TVirtualMC.h"                 // for TVirtualMC, gMC
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include <stddef.h>                     // for NULL
#include <iostream>                     // for cout, endl

using std::cout;
using std::endl;

FairRutherford::FairRutherford()
  : FairDetector("FairRutherford", kTRUE, kFairRutherford),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairRutherfordPointCollection(new TClonesArray("FairRutherfordPoint"))
{
}

FairRutherford::FairRutherford(const char* name, Bool_t active)
  : FairDetector(name, active, kFairRutherford),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fFairRutherfordPointCollection(new TClonesArray("FairRutherfordPoint"))
{
}

FairRutherford::~FairRutherford()
{
  if (fFairRutherfordPointCollection) {
    fFairRutherfordPointCollection->Delete();
    delete fFairRutherfordPointCollection;
  }
}

void FairRutherford::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairRutherfordGeoPar* par=(FairRutherfordGeoPar*)(rtdb->getContainer("FairRutherfordGeoPar"));
}

Bool_t  FairRutherford::ProcessHits(FairVolume* vol)
{
  /** This method is called from the MC stepping */

  //Set parameters at entrance of volume. Reset ELoss.
  if ( gMC->IsTrackEntering() ) {
    fELoss  = 0.;
    fTime   = gMC->TrackTime() * 1.0e09;
    fLength = gMC->TrackLength();
    gMC->TrackPosition(fPos);
    gMC->TrackMomentum(fMom);
  }

  // Sum energy loss for all steps in the active volume
  fELoss += gMC->Edep();

  // Create FairRutherfordPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of FairRutherford points in TParticle
    FairStack* stack = (FairStack*) gMC->GetStack();
    stack->AddPoint(kFairRutherford);
  }

  return kTRUE;
}

void FairRutherford::EndOfEvent()
{

  fFairRutherfordPointCollection->Clear();

}



void FairRutherford::Register()
{

  /** This will create a branch in the output tree called
      FairRutherfordPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("FairRutherfordPoint", "FairRutherford",
                                        fFairRutherfordPointCollection, kTRUE);

}


TClonesArray* FairRutherford::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fFairRutherfordPointCollection; }
  else { return NULL; }
}

void FairRutherford::Reset()
{
  fFairRutherfordPointCollection->Clear();
}

void FairRutherford::ConstructGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  FairRutherfordGeo*  Geo  = new FairRutherfordGeo();
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  FairRutherfordGeoPar* par=(FairRutherfordGeoPar*)(rtdb->getContainer("FairRutherfordGeoPar"));
  TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
  TObjArray* fPassNodes = par->GetGeoPassiveNodes();

  TListIter iter(volList);
  FairGeoNode* node   = NULL;
  FairGeoVolume* aVol=NULL;

  while( (node = (FairGeoNode*)iter.Next()) ) {
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

FairRutherfordPoint* FairRutherford::AddHit(Int_t trackID, Int_t detID,
    TVector3 pos, TVector3 mom,
    Double_t time, Double_t length,
    Double_t eLoss)
{
  TClonesArray& clref = *fFairRutherfordPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) FairRutherfordPoint(trackID, detID, pos, mom,
         time, length, eLoss, pos.Mag(), pos.Phi(), pos.Theta());
}

ClassImp(FairRutherford)
