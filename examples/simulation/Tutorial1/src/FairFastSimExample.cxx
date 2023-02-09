/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairFastSimExample.h"

#include "FairDetector.h"            // for FairDetector
#include "FairDetectorList.h"        // for DetectorId::kTutDet
#include "FairRootManager.h"         // for FairRootManager
#include "FairStack.h"               // for FairStack
#include "FairTutorialDet1Point.h"   // for FairTutorialDet1Point

#include <TClonesArray.h>   // for TClonesArray
#include <TGeoBBox.h>
#include <TGeoManager.h>
#include <TGeoMatrix.h>        // for TGeoCombiTrans, TGeoRotation
#include <TGeoVolume.h>        // for TGeoVolume
#include <TMCProcess.h>        // for kPHadronic
#include <TVirtualMC.h>        // for TVirtualMC
#include <TVirtualMCStack.h>   // for TVirtualMCStack

FairFastSimExample::FairFastSimExample()
    : FairFastSimDetector("TutorialDet", kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fPointsArray(new TClonesArray("FairTutorialDet1Point"))
{}

FairFastSimExample::FairFastSimExample(const char* name)
    : FairFastSimDetector(name, kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fPointsArray(new TClonesArray("FairTutorialDet1Point"))
{}

FairFastSimExample::FairFastSimExample(const FairFastSimExample& rhs)
    : FairFastSimDetector(rhs)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fPointsArray(new TClonesArray("FairTutorialDet1Point"))
{}

FairFastSimExample::~FairFastSimExample()
{
    if (fPointsArray) {
        fPointsArray->Delete();
        delete fPointsArray;
    }
}

void FairFastSimExample::FastSimProcessParticle()
{
    TVirtualMC::GetMC()->TrackPosition(fPos);
    TVirtualMC::GetMC()->TrackMomentum(fMom);

    FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
    fTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();

    if (TVirtualMC::GetMC()->TrackPid() == 211) {   // let only pion create secondaries
        stack->FastSimPushSecondary(
            fTrackID, 11, -12.5, -12.5, 20. + 5. + 0.1, fPos.T(), 0.1, 0.1, 1.0, 1.0, 0., 0., 0., kPHadronic, 1, 0);
        stack->FastSimPushSecondary(
            fTrackID, 11, -12.5, -12.5, 20. + 5. + 0.1, fPos.T(), -0.1, -0.1, 1.0, 1.0, 0., 0., 0., kPHadronic, 1, 0);
    }
    stack->FastSimMoveParticleTo(
        12.5, 12.5, 20. + 5. + 0.1, TVirtualMC::GetMC()->TrackTime(), fMom.X(), fMom.Y(), fMom.Z(), 0.99 * fMom.E());

    if (TVirtualMC::GetMC()->TrackPid() == 211) {   // let only pion create secondaries
        stack->FastSimPushSecondary(
            fTrackID, 11, -12.5, -12.5, 20. + 5. + 0.1, fPos.T(), -0.1, 0.1, 1.0, 1.0, 0., 0., 0., kPHadronic, 1, 0);
        stack->FastSimPushSecondary(
            fTrackID, 11, -12.5, -12.5, 20. + 5. + 0.1, fPos.T(), 0.1, -0.1, 1.0, 1.0, 0., 0., 0., kPHadronic, 1, 0);
    }

    //    stack->FastSimMoveParticleTo(
    //        25., 25., 20. + 0.1, TVirtualMC::GetMC()->TrackTime(), fMom.X(), fMom.Y(), fMom.Z(), fMom.E());

    //    stack->FastSimMoveParticleTo(
    //        24., 24., 50. + 0.1, TVirtualMC::GetMC()->TrackTime(), fMom.X(), fMom.Y(), fMom.Z(), fMom.E());

    fVolumeID = 0;
    fTime = TVirtualMC::GetMC()->TrackTime() * 1.0e09;
    fLength = TVirtualMC::GetMC()->TrackLength();
    fELoss = 0.;

    AddHit(fTrackID,
           fVolumeID,
           TVector3(fPos.X(), fPos.Y(), fPos.Z()),
           TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
           fTime,
           fLength,
           fELoss);

    // Increment number of tutorial det points in TParticle
    stack->AddPoint(kTutDet);
}

void FairFastSimExample::EndOfEvent() { fPointsArray->Clear(); }

void FairFastSimExample::Register()
{
    /** This will create a branch in the output tree called
        FairTutorialDet1Point, setting the last parameter to kFALSE means:
        this collection will not be written to the file, it will exist
        only during the simulation.
    */
    FairRootManager::Instance()->Register("FastSimPoint", "FastSimDetDet", fPointsArray, kTRUE);
}

TClonesArray* FairFastSimExample::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fPointsArray;
    } else {
        return nullptr;
    }
}

void FairFastSimExample::Reset() { fPointsArray->Clear(); }

void FairFastSimExample::ConstructGeometry()
{
    FairFastSimDetector::ConstructGeometry();

    TGeoVolume* cave = gGeoManager->GetTopVolume();

    Double_t dx = 25.;
    Double_t dy = 25.;
    Double_t dz = 5.;
    TGeoBBox* bbox = new TGeoBBox("bbox", dx, dy, dz);
    TGeoVolume* vol = new TGeoVolume("fast_sim_vol", bbox, fFastSimMedium);

    Double_t x = 0.;
    Double_t y = 0.;
    Double_t z = 20.;
    TGeoRotation* rot = new TGeoRotation();
    TGeoCombiTrans* matr = new TGeoCombiTrans(x, y, z, rot);

    cave->AddNode(vol, 1, matr);

    AddSensitiveVolume(vol);
}

FairTutorialDet1Point* FairFastSimExample::AddHit(Int_t trackID,
                                                  Int_t detID,
                                                  TVector3 pos,
                                                  TVector3 mom,
                                                  Double_t time,
                                                  Double_t length,
                                                  Double_t eLoss)
{
    TClonesArray& clref = *fPointsArray;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) FairTutorialDet1Point(trackID, detID, pos, mom, time, length, eLoss);
}

Bool_t FairFastSimExample::IsSensitive(const std::string& name) { return name == "fast_sim_vol"; }

FairModule* FairFastSimExample::CloneModule() const
{
    return new FairFastSimExample(*this);
}
