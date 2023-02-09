/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRutherford.h"

#include "FairDetectorList.h"       // for DetectorId::kFairRutherford
#include "FairRootManager.h"        // for FairRootManager
#include "FairRutherfordGeo.h"      // for FairRutherfordGeo
#include "FairRutherfordGeoPar.h"   // for FairRutherfordGeoPar
#include "FairRutherfordPoint.h"    // for FairRutherfordPoint
#include "FairStack.h"              // for FairStack
#include "FairVolume.h"             // for FairVolume

#include <TClonesArray.h>      // for TClonesArray
#include <TVirtualMC.h>        // for TVirtualMC
#include <TVirtualMCStack.h>   // for TVirtualMCStack

FairRutherford::FairRutherford()
    : FairDetector("FairRutherford", kTRUE, kFairRutherford)
    , fFairRutherfordPointCollection(new TClonesArray("FairRutherfordPoint"))
{}

FairRutherford::FairRutherford(const char* name, Bool_t active)
    : FairDetector(name, active, kFairRutherford)
    , fFairRutherfordPointCollection(new TClonesArray("FairRutherfordPoint"))
{}

FairRutherford::FairRutherford(const FairRutherford& rhs)
    : FairDetector(rhs)
    , fFairRutherfordPointCollection(new TClonesArray("FairRutherfordPoint"))
{}

FairRutherford::~FairRutherford()
{
    if (fFairRutherfordPointCollection) {
        fFairRutherfordPointCollection->Delete();
        delete fFairRutherfordPointCollection;
    }
}

Bool_t FairRutherford::ProcessHits(FairVolume* vol)
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

    // Create FairRutherfordPoint at exit of active volume
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

        // Increment number of FairRutherford points in TParticle
        auto stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
        stack->AddPoint(kFairRutherford);
    }

    return kTRUE;
}

void FairRutherford::EndOfEvent() { fFairRutherfordPointCollection->Clear(); }

void FairRutherford::Register()
{
    /** This will create a branch in the output tree called
      FairRutherfordPoint, setting the last parameter to kFALSE means:
      this collection will not be written to the file, it will exist
      only during the simulation.
  */

    FairRootManager::Instance()->Register(
        "FairRutherfordPoint", "FairRutherford", fFairRutherfordPointCollection, kTRUE);
}

TClonesArray* FairRutherford::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fFairRutherfordPointCollection;
    } else {
        return nullptr;
    }
}

void FairRutherford::Reset() { fFairRutherfordPointCollection->Clear(); }

void FairRutherford::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
      just copy this and use it for your detector, otherwise you can
      implement here you own way of constructing the geometry. */

    ConstructASCIIGeometry<FairRutherfordGeo, FairRutherfordGeoPar>("FairRutherfordGeoPar");
}

FairRutherfordPoint* FairRutherford::AddHit(Int_t trackID,
                                            Int_t detID,
                                            TVector3 pos,
                                            TVector3 mom,
                                            Double_t time,
                                            Double_t length,
                                            Double_t eLoss)
{
    TClonesArray& clref = *fFairRutherfordPointCollection;
    Int_t size = clref.GetEntriesFast();
    return new (clref[size])
        FairRutherfordPoint(trackID, detID, pos, mom, time, length, eLoss, pos.Mag(), pos.Phi(), pos.Theta());
}

FairModule* FairRutherford::CloneModule() const
{
    return new FairRutherford(*this);
}
