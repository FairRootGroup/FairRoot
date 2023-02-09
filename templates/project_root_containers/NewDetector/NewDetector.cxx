/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewDetector.h"

#include "FairGeoInterface.h"
#include "FairGeoLoader.h"
#include "FairGeoNode.h"
#include "FairGeoVolume.h"
#include "FairRootManager.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"
#include "FairVolume.h"
#include "MyProjDetectorList.h"
#include "MyProjStack.h"
#include "NewDetectorGeo.h"
#include "NewDetectorGeoPar.h"
#include "NewDetectorPoint.h"

#include <TClonesArray.h>
#include <TGeoBBox.h>
#include <TGeoCompositeShape.h>
#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoTube.h>
#include <TVirtualMC.h>
#include <iostream>
using std::cout;
using std::endl;

NewDetector::NewDetector()
    : FairDetector("NewDetector", kTRUE, kNewDetector)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fNewDetectorPointCollection(new TClonesArray("NewDetectorPoint"))
{}

NewDetector::NewDetector(const char* name, Bool_t active)
    : FairDetector(name, active, kNewDetector)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fNewDetectorPointCollection(new TClonesArray("NewDetectorPoint"))
{}

NewDetector::NewDetector(const NewDetector& right)
    : FairDetector(right)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fNewDetectorPointCollection(new TClonesArray("NewDetectorPoint"))
{}

NewDetector::~NewDetector()
{
    if (fNewDetectorPointCollection) {
        fNewDetectorPointCollection->Delete();
        delete fNewDetectorPointCollection;
    }
}

void NewDetector::Initialize()
{
    /**
     * WORKAROUND needed for Geant4 in MT mode
     * Call AddSensitiveVolume for sensitive volumes in order to fill
     * thread-local FairModule::svList.
     */
    DefineSensitiveVolumes();

    FairDetector::Initialize();
    FairRuntimeDb* rtdb = FairRun::Instance()->GetRuntimeDb();
    auto par = (NewDetectorGeoPar*)(rtdb->getContainer("NewDetectorGeoPar"));
    (void)par;   // stop warning about unused variable
}

Bool_t NewDetector::ProcessHits(FairVolume* vol)
{
    /** This method is called from the MC stepping */

    // Set parameters at entrance of volume. Reset ELoss.
    if (TVirtualMC::GetMC()->IsTrackEntering()) {
        fELoss = 0.;
        fTime = TVirtualMC::GetMC()->TrackTime() * 1.0e09;
        fLength = TVirtualMC::GetMC()->TrackLength();
        TVirtualMC::GetMC()->TrackPosition(fPos);
        TVirtualMC::GetMC()->TrackMomentum(fMom);
    }

    // Sum energy loss for all steps in the active volume
    fELoss += TVirtualMC::GetMC()->Edep();

    // Create NewDetectorPoint at exit of active volume
    if (TVirtualMC::GetMC()->IsTrackExiting() || TVirtualMC::GetMC()->IsTrackStop()
        || TVirtualMC::GetMC()->IsTrackDisappeared()) {
        fTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
        fVolumeID = vol->getMCid();
        if (fELoss == 0.) {
            return kFALSE;
        }
        AddHit(fTrackID,
               fVolumeID,
               TVector3(fPos.X(), fPos.Y(), fPos.Z()),
               TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
               fTime,
               fLength,
               fELoss);

        // Increment number of NewDetector det points in TParticle
        MyProjStack* stack = (MyProjStack*)TVirtualMC::GetMC()->GetStack();
        stack->AddPoint(kNewDetector);
    }

    return kTRUE;
}

void NewDetector::EndOfEvent()
{

    LOG(info) << "NewDetector: " << fNewDetectorPointCollection->GetEntriesFast() << " points registered in this event";

    fNewDetectorPointCollection->Clear();
}

void NewDetector::Register()
{

    /** This will create a branch in the output tree called
      NewDetectorPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

    if (!gMC->IsMT()) {
        FairRootManager::Instance()->Register("NewDetectorPoint", "NewDetector", fNewDetectorPointCollection, kTRUE);
    } else {
        FairRootManager::Instance()->RegisterAny("NewDetectorPoint", fNewDetectorPointCollection, kTRUE);
    }
}

TClonesArray* NewDetector::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fNewDetectorPointCollection;
    } else {
        return NULL;
    }
}

void NewDetector::Reset() { fNewDetectorPointCollection->Clear(); }

void NewDetector::ConstructGeometry()
{
    TGeoVolume* top = gGeoManager->GetTopVolume();
    TGeoMedium* Si = gGeoManager->GetMedium("Si");
    TGeoMedium* Carbon = gGeoManager->GetMedium("C");

    if (Si == 0) {
        TGeoMaterial* matSi = new TGeoMaterial("Si", 28.0855, 14, 2.33);
        Si = new TGeoMedium("Si", 2, matSi);
    }
    if (Carbon == 0) {
        TGeoMaterial* matCarbon = new TGeoMaterial("C", 12.011, 6.0, 2.265);
        Carbon = new TGeoMedium("C", 3, matCarbon);
    }

    TGeoVolume* det1 = gGeoManager->MakeTubs("Det1", Si, 5, 80, 0.1, 0, 360);
    TGeoRotation r1;
    r1.SetAngles(0, 0, 0);
    TGeoTranslation t1(0, 0, 0);
    TGeoCombiTrans c1(t1, r1);
    TGeoHMatrix* h1 = new TGeoHMatrix(c1);
    top->AddNode(det1, 1, h1);
    det1->SetLineColor(kGreen);
    AddSensitiveVolume(det1);

    TGeoVolume* passive1 = gGeoManager->MakeTubs("Pass1", Si, 5, 120, 10, 0, 360);
    TGeoRotation rp1;
    rp1.SetAngles(0, 0, 0);
    TGeoTranslation tp1(0, 0, 20);
    TGeoCombiTrans cp1(tp1, rp1);
    TGeoHMatrix* hp1 = new TGeoHMatrix(cp1);
    top->AddNode(passive1, 1, hp1);
    passive1->SetLineColor(kRed);

    TGeoVolume* det2 = gGeoManager->MakeTubs("Det2", Si, 5, 150, 0.1, 0, 360);
    TGeoRotation r2;
    r2.SetAngles(0, 0, 0);
    TGeoTranslation t2(0, 0, 70);
    TGeoCombiTrans c2(t2, r2);
    TGeoHMatrix* h2 = new TGeoHMatrix(c2);
    top->AddNode(det2, 1, h2);
    det2->SetLineColor(kGreen);
    AddSensitiveVolume(det2);

    TGeoVolume* det3 = gGeoManager->MakeTubs("Det3", Si, 5, 150, 0.1, 0, 360);
    TGeoRotation r3;
    r3.SetAngles(0, 0, 0);
    TGeoTranslation t3(0, 0, 150);
    TGeoCombiTrans c3(t3, r3);
    TGeoHMatrix* h3 = new TGeoHMatrix(c3);
    top->AddNode(det3, 1, h3);
    det3->SetLineColor(kGreen);
    AddSensitiveVolume(det3);
}

NewDetectorPoint* NewDetector::AddHit(Int_t trackID,
                                      Int_t detID,
                                      TVector3 pos,
                                      TVector3 mom,
                                      Double_t time,
                                      Double_t length,
                                      Double_t eLoss)
{
    TClonesArray& clref = *fNewDetectorPointCollection;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) NewDetectorPoint(trackID, detID, pos, mom, time, length, eLoss);
}

FairModule* NewDetector::CloneModule() const { return new NewDetector(*this); }

void NewDetector::DefineSensitiveVolumes()
{
    TObjArray* volumes = gGeoManager->GetListOfVolumes();
    TIter next(volumes);
    TGeoVolume* volume;
    while ((volume = static_cast<TGeoVolume*>(next()))) {
        if (IsSensitive(volume->GetName())) {
            LOG(debug2) << "Sensitive Volume " << volume->GetName();
            AddSensitiveVolume(volume);
        }
    }
}

Bool_t NewDetector::IsSensitive(const std::string& name)
{
    if (name.find("Det") != std::string::npos) {
        return kTRUE;
    }
    return kFALSE;
}
