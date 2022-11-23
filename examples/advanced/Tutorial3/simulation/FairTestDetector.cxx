/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetector.h"

#include "FairDetectorList.h"         // for DetectorId::kTutDet
#include "FairLink.h"                 // for FairLink
#include "FairRootManager.h"          // for FairRootManager
#include "FairRun.h"                  // for FairRun
#include "FairRuntimeDb.h"            // for FairRuntimeDb
#include "FairStack.h"                // for FairStack
#include "FairTestDetectorGeo.h"      // for FairTestDetectorGeo
#include "FairTestDetectorGeoPar.h"   // for FairTestDetectorGeoPar
#include "FairTestDetectorPoint.h"    // for FairTestDetectorPoint
#include "FairVolume.h"               // for FairVolume

#include <TClonesArray.h>      // for TClonesArray
#include <TVirtualMC.h>        // for TVirtualMC
#include <TVirtualMCStack.h>   // for TVirtualMCStack

FairTestDetector::FairTestDetector()
    : FairDetector("FairTestDetector", kTRUE, kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fPosOut()
    , fMomOut()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fEventNr(0)
    , fFairTestDetectorPointCollection(new TClonesArray("FairTestDetectorPoint"))
{}

FairTestDetector::FairTestDetector(const char* name, Bool_t active)
    : FairDetector(name, active, kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fPosOut()
    , fMomOut()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fEventNr(0)
    , fFairTestDetectorPointCollection(new TClonesArray("FairTestDetectorPoint"))
{}

FairTestDetector::~FairTestDetector()
{
    if (fFairTestDetectorPointCollection) {
        fFairTestDetectorPointCollection->Delete();
        delete fFairTestDetectorPointCollection;
    }
}

void FairTestDetector::Initialize()
{
    FairDetector::Initialize();
    FairRuntimeDb* rtdb = FairRun::Instance()->GetRuntimeDb();
    rtdb->getContainer("FairTestDetectorGeoPar");
}

Bool_t FairTestDetector::ProcessHits(FairVolume* vol)
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

    // Create FairTestDetectorPoint at exit of active volume
    if (TVirtualMC::GetMC()->IsTrackExiting() || TVirtualMC::GetMC()->IsTrackStop()
        || TVirtualMC::GetMC()->IsTrackDisappeared()) {
        fTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
        fVolumeID = vol->getMCid();
        TVirtualMC::GetMC()->TrackPosition(fPosOut);
        TVirtualMC::GetMC()->TrackMomentum(fMomOut);
        if (fELoss == 0.) {
            return kFALSE;
        }
        AddHit(fTrackID,
               fVolumeID,
               TVector3(fPos.X(), fPos.Y(), fPos.Z()),
               TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
               TVector3(fPosOut.X(), fPosOut.Y(), fPosOut.Z()),
               TVector3(fMomOut.Px(), fMomOut.Py(), fMomOut.Pz()),
               fTime,
               fLength,
               fELoss);

        // Increment number of FairTestDetector det points in TParticle
        FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
        stack->AddPoint(kTutDet);
    }

    return kTRUE;
}

void FairTestDetector::EndOfEvent()
{

    fFairTestDetectorPointCollection->Clear();
    fEventNr++;
}

void FairTestDetector::Register()
{

    /** This will create a branch in the output tree called
        FairTestDetectorPoint, setting the last parameter to kFALSE means:
        this collection will not be written to the file, it will exist
        only during the simulation.
    */

    FairRootManager::Instance()->Register(
        "FairTestDetectorPoint", "FairTestDetector", fFairTestDetectorPointCollection, kTRUE);
}

TClonesArray* FairTestDetector::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fFairTestDetectorPointCollection;
    } else {
        return nullptr;
    }
}

void FairTestDetector::Reset() { fFairTestDetectorPointCollection->Clear(); }

void FairTestDetector::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
        just copy this and use it for your detector, otherwise you can
        implement here you own way of constructing the geometry. */

    ConstructASCIIGeometry<FairTestDetectorGeo, FairTestDetectorGeoPar>("FairTestDetectorGeoPar");
}

FairTestDetectorPoint* FairTestDetector::AddHit(Int_t trackID,
                                                Int_t detID,
                                                TVector3 pos,
                                                TVector3 mom,
                                                TVector3 posOut,
                                                TVector3 momOut,
                                                Double_t time,
                                                Double_t length,
                                                Double_t eLoss)
{
    TClonesArray& clref = *fFairTestDetectorPointCollection;
    Int_t size = clref.GetEntriesFast();
    FairTestDetectorPoint* myPoint =
        new (clref[size]) FairTestDetectorPoint(trackID, detID, pos, mom, posOut, momOut, time, length, eLoss);
    myPoint->SetLink(FairLink(-1, fEventNr, FairRootManager::Instance()->GetBranchId("MCTrack"), trackID));
    return myPoint;
}

ClassImp(FairTestDetector);
