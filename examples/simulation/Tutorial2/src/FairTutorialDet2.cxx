/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2.h"

#include "FairDetectorList.h"
#include "FairRootManager.h"
#include "FairStack.h"
#include "FairTutorialDet2Geo.h"
#include "FairTutorialDet2GeoPar.h"
#include "FairTutorialDet2Point.h"
#include "FairVolume.h"

#include <TClonesArray.h>
#include <TVirtualMC.h>
#include <TVirtualMCStack.h>

#ifdef NDEBUG
#undef NDEBUG
#endif

FairTutorialDet2::FairTutorialDet2()
    : FairDetector("TutorialDet", kTRUE, kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fFairTutorialDet2PointCollection(new TClonesArray("FairTutorialDet2Point"))
    , fCustomData(new Det2PointContainer())
{}

FairTutorialDet2::FairTutorialDet2(const char* name, Bool_t active)
    : FairDetector(name, active, kTutDet)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fFairTutorialDet2PointCollection(new TClonesArray("FairTutorialDet2Point"))
    , fCustomData(new Det2PointContainer())
{}

FairTutorialDet2::FairTutorialDet2(const FairTutorialDet2& rhs)
    : FairDetector(rhs)
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fFairTutorialDet2PointCollection(new TClonesArray("FairTutorialDet2Point"))
    , fCustomData(new Det2PointContainer())
{}

FairTutorialDet2::~FairTutorialDet2()
{
    if (fFairTutorialDet2PointCollection) {
        fFairTutorialDet2PointCollection->Delete();
        delete fFairTutorialDet2PointCollection;
    }
}

Bool_t FairTutorialDet2::ProcessHits(FairVolume* vol)
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

    // Create FairTutorialDet2Point at exit of active volume
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

        // Increment number of tutorial det points in TParticle
        FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
        stack->AddPoint(kTutDet);
    }

    return kTRUE;
}

void FairTutorialDet2::EndOfEvent() { Reset(); }

void FairTutorialDet2::Register()
{
    /** This will create a branch in the output tree called
      FairTutorialDet2Point, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */
    auto mgr = FairRootManager::Instance();

    mgr->Register("TutorialDetPoint", "TutorialDet", fFairTutorialDet2PointCollection, kTRUE);

    // example how to register any type T
    mgr->RegisterAny("TutorialCustomData", fCustomData, kTRUE);
}

TClonesArray* FairTutorialDet2::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fFairTutorialDet2PointCollection;
    } else {
        return nullptr;
    }
}

void FairTutorialDet2::Reset()
{
    fFairTutorialDet2PointCollection->Clear();
    fCustomData->clear();
}

void FairTutorialDet2::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

    ConstructASCIIGeometry<FairTutorialDet2Geo, FairTutorialDet2GeoPar>("FairTutorialDet2GeoPar");
}

FairTutorialDet2Point* FairTutorialDet2::AddHit(Int_t trackID,
                                                Int_t detID,
                                                TVector3 pos,
                                                TVector3 mom,
                                                Double_t time,
                                                Double_t length,
                                                Double_t eLoss)
{
    TClonesArray& clref = *fFairTutorialDet2PointCollection;
    Int_t size = clref.GetEntriesFast();

    // fill this with some (meaningless) data
    fCustomData->emplace_back(pos.X(), size);

    return new (clref[size]) FairTutorialDet2Point(trackID, detID, pos, mom, time, length, eLoss);
}

FairModule* FairTutorialDet2::CloneModule() const { return new FairTutorialDet2(*this); }

ClassImp(FairTutorialDet2);
