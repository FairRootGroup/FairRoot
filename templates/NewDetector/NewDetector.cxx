/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewDetector.h"

#include "NewDetectorPoint.h"
#include "NewDetectorGeo.h"
#include "NewDetectorGeoPar.h"

#include "FairVolume.h"
#include "FairGeoVolume.h"
#include "FairGeoNode.h"
#include "FairRootManager.h"
#include "FairGeoLoader.h"
#include "FairGeoInterface.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairDetectorList.h"
#include "FairStack.h"

#include "TClonesArray.h"
#include "TVirtualMC.h"

#include <iostream>
using std::cout;
using std::endl;

NewDetector::NewDetector()
  : FairDetector("NewDetector", kTRUE, kNewDetector),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fNewDetectorPointCollection(new TClonesArray("NewDetectorPoint"))
{
}

NewDetector::NewDetector(const char* name, Bool_t active)
  : FairDetector(name, active, kNewDetector),
    fTrackID(-1),
    fVolumeID(-1),
    fPos(),
    fMom(),
    fTime(-1.),
    fLength(-1.),
    fELoss(-1),
    fNewDetectorPointCollection(new TClonesArray("NewDetectorPoint"))
{
}

NewDetector::~NewDetector()
{
  if (fNewDetectorPointCollection) {
    fNewDetectorPointCollection->Delete();
    delete fNewDetectorPointCollection;
  }
}

void NewDetector::Initialize()
{
  FairDetector::Initialize();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  NewDetectorGeoPar* par=(NewDetectorGeoPar*)(rtdb->getContainer("NewDetectorGeoPar"));
}

Bool_t  NewDetector::ProcessHits(FairVolume* vol)
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

  // Create NewDetectorPoint at exit of active volume
  if ( gMC->IsTrackExiting()    ||
       gMC->IsTrackStop()       ||
       gMC->IsTrackDisappeared()   ) {
    fTrackID  = gMC->GetStack()->GetCurrentTrackNumber();
    fVolumeID = vol->getMCid();
    if (fELoss == 0. ) { return kFALSE; }
    AddHit(fTrackID, fVolumeID, TVector3(fPos.X(),  fPos.Y(),  fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()), fTime, fLength,
           fELoss);

    // Increment number of NewDetector det points in TParticle
    FairStack* stack = (FairStack*) gMC->GetStack();
    stack->AddPoint(kNewDetector);
  }

  return kTRUE;
}

void NewDetector::EndOfEvent()
{

  fNewDetectorPointCollection->Clear();

}



void NewDetector::Register()
{

  /** This will create a branch in the output tree called
      NewDetectorPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

  FairRootManager::Instance()->Register("NewDetectorPoint", "NewDetector",
                                        fNewDetectorPointCollection, kTRUE);

}


TClonesArray* NewDetector::GetCollection(Int_t iColl) const
{
  if (iColl == 0) { return fNewDetectorPointCollection; }
  else { return NULL; }
}

void NewDetector::Reset()
{
  fNewDetectorPointCollection->Clear();
}

void NewDetector::ConstructGeometry()
{
  /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

  FairGeoLoader*    geoLoad = FairGeoLoader::Instance();
  FairGeoInterface* geoFace = geoLoad->getGeoInterface();
  NewDetectorGeo*  Geo  = new NewDetectorGeo();
  Geo->setGeomFile(GetGeometryFileName());
  geoFace->addGeoModule(Geo);

  Bool_t rc = geoFace->readSet(Geo);
  if (rc) { Geo->create(geoLoad->getGeoBuilder()); }
  TList* volList = Geo->getListOfVolumes();

  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();
  NewDetectorGeoPar* par=(NewDetectorGeoPar*)(rtdb->getContainer("NewDetectorGeoPar"));
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

NewDetectorPoint* NewDetector::AddHit(Int_t trackID, Int_t detID,
                                      TVector3 pos, TVector3 mom,
                                      Double_t time, Double_t length,
                                      Double_t eLoss)
{
  TClonesArray& clref = *fNewDetectorPointCollection;
  Int_t size = clref.GetEntriesFast();
  return new(clref[size]) NewDetectorPoint(trackID, detID, pos, mom,
         time, length, eLoss);
}

ClassImp(NewDetector)
