/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet1.h"

#include "FairDetectorList.h"         // for DetectorId::kTutDet
#include "FairLogger.h"               // for logging
#include "FairRootManager.h"          // for FairRootManager
#include "FairStack.h"                // for FairStack
#include "FairTutorialDet1Geo.h"      // for FairTutorialDet1Geo
#include "FairTutorialDet1GeoPar.h"   // for FairTutorialDet1GeoPar
#include "FairTutorialDet1Point.h"    // for FairTutorialDet1Point
#include "FairVolume.h"               // for FairVolume

#include <TClonesArray.h>      // for TClonesArray
#include <TVirtualMC.h>        // for TVirtualMC
#include <TVirtualMCStack.h>   // for TVirtualMCStack

FairTutorialDet1::FairTutorialDet1()
    : FairDetector("TutorialDet", kTRUE, kTutDet)
{}

FairTutorialDet1::FairTutorialDet1(const char* name, Bool_t active)
    : FairDetector(name, active, kTutDet)
{}

FairTutorialDet1::FairTutorialDet1(const FairTutorialDet1& rhs)
    : FairDetector(rhs)
{}

FairTutorialDet1::~FairTutorialDet1()
{
    if (fFairTutorialDet1PointCollection) {
        fFairTutorialDet1PointCollection->Delete();
    }
}

void FairTutorialDet1::Initialize()
{
    LOG(info) << "Initializing FairTutorialDet1";

    // Prevent duplicate initialisation
    assert(!fIsInitialised);

    FairDetector::Initialize();
    fIsInitialised = true;
}

Bool_t FairTutorialDet1::ProcessHits(FairVolume* vol)
{
    /** This method is called from the MC stepping */

    LOG(debug) << "In FairTutorialDet1::ProcessHits";
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

    // Create FairTutorialDet1Point at exit of active volume
    if (TVirtualMC::GetMC()->IsTrackExiting() || TVirtualMC::GetMC()->IsTrackStop()
        || TVirtualMC::GetMC()->IsTrackDisappeared()) {
        auto trackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
        auto volumeID = vol->getMCid();
        if (fELoss == 0.) {
            return kFALSE;
        }
        AddHit(trackID,
               volumeID,
               TVector3(fPos.X(), fPos.Y(), fPos.Z()),
               TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
               fTime,
               fLength,
               fELoss);

        // Increment number of tutorial det points in TParticle
        auto stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
        stack->AddPoint(kTutDet);
    }

    return kTRUE;
}

void FairTutorialDet1::EndOfEvent() { fFairTutorialDet1PointCollection->Clear(); }

void FairTutorialDet1::Register()
{
    /** This will create a branch in the output tree called
      FairTutorialDet1Point, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

    FairRootManager::Instance()->Register(
        "TutorialDetPoint", "TutorialDet", fFairTutorialDet1PointCollection.get(), kTRUE);
}

TClonesArray* FairTutorialDet1::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fFairTutorialDet1PointCollection.get();
    } else {
        return nullptr;
    }
}

void FairTutorialDet1::Reset() { fFairTutorialDet1PointCollection->Clear(); }

Bool_t FairTutorialDet1::IsSensitive(const std::string& name)
{
    return name.find("tutdet") != std::string::npos;
}

void FairTutorialDet1::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

    ConstructASCIIGeometry<FairTutorialDet1Geo, FairTutorialDet1GeoPar>("FairTutorialDet1GeoPar");
}

FairTutorialDet1Point* FairTutorialDet1::AddHit(Int_t trackID,
                                                Int_t detID,
                                                TVector3 pos,
                                                TVector3 mom,
                                                Double_t time,
                                                Double_t length,
                                                Double_t eLoss)
{
    TClonesArray& clref = *fFairTutorialDet1PointCollection;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size]) FairTutorialDet1Point(trackID, detID, pos, mom, time, length, eLoss);
}

FairModule* FairTutorialDet1::CloneModule() const { return new FairTutorialDet1(*this); }

ClassImp(FairTutorialDet1);
