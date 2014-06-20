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
#include "MyProjDetectorList.h"
#include "MyProjStack.h"

#include "TClonesArray.h"
#include "TVirtualMC.h"
#include "TGeoManager.h"
#include "TGeoBBox.h"
#include "TGeoCompositeShape.h"
#include "TGeoTube.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"

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
    MyProjStack* stack = (MyProjStack*) gMC->GetStack();
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
    
    TGeoVolume *top=gGeoManager->GetTopVolume();
    TGeoMedium *Si =gGeoManager->GetMedium("Si");
    
    
    if(Si==0){
        TGeoMaterial *matSi     = new TGeoMaterial("Si", 28.0855, 14, 2.33);
        Si     = new TGeoMedium("Si", 2, matSi);
    }
    
    TGeoBBox *detbox1 = new TGeoBBox("detbox1", 250, 250, 10);
    TGeoBBox *detbox2 = new TGeoBBox("detbox2", 245, 245, 10);
    
    TGeoCompositeShape *detcomp1 = new TGeoCompositeShape("detcomp1", "detbox1-detbox2");
    
    TGeoVolume *detmu1 = new TGeoVolume("MuX", detcomp1, Si);
    TGeoVolume *muonfilter = gGeoManager->MakeBox("muonfilter", Si, 250, 250, 20);
    AddSensitiveVolume(muonfilter);
    muonfilter->SetLineColor(kGreen);
    top->AddNode(muonfilter, 1, new TGeoTranslation(0, 0, 2500));
    
    top->AddNode(detmu1, 10, new TGeoTranslation(0, 0, 2570));
    detmu1->SetLineColor(kViolet+10);
    TGeoRotation r5;
    r5.SetAngles(15,0,0);
    TGeoTranslation t5(0, 0, 2590);
    TGeoCombiTrans c5(t5, r5);
    TGeoHMatrix *h5 = new TGeoHMatrix(c5);
    TGeoVolume *detmu2 = new TGeoVolume("MuS", detcomp1, Si);
    detmu2->SetLineColor(kViolet+4);
    top->AddNode(detmu2, 10, h5);
    
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
