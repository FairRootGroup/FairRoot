/********************************************************************************
 * Copyright (C) 2019-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropDet.h"

#include "FairDetectorList.h"   // for DetectorId::kTutDet
#include "FairGeoInterface.h"   // for FairGeoInterface
#include "FairGeoLoader.h"      // for FairGeoLoader
#include "FairGeoNode.h"        // for FairGeoNode
#include "FairGeoVolume.h"      // for FairGeoVolume
#include "FairLogger.h"         // for logging
#include "FairRootManager.h"    // for FairRootManager
#include "FairRun.h"            // for FairRun
#include "FairRuntimeDb.h"      // for FairRuntimeDb
#include "FairStack.h"          // for FairStack
#include "FairTutPropGeo.h"
#include "FairTutPropGeoPar.h"
#include "FairTutPropPoint.h"
#include "FairVolume.h"     // for FairVolume
#include "TClonesArray.h"   // for TClonesArray
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoPhysicalNode.h"
#include "TList.h"             // for TListIter, TList (ptr only)
#include "TObjArray.h"         // for TObjArray
#include "TString.h"           // for TString
#include "TVirtualMC.h"        // for TVirtualMC
#include "TVirtualMCStack.h"   // for TVirtualMCStack

#include <iosfwd>   // for ostream
#include <iostream>
#include <stddef.h>   // for NULL
using std::cout;
using std::endl;

FairTutPropDet::FairTutPropDet()
    : FairTutPropDet("FairTutPropDet", kTRUE)
{}

FairTutPropDet::FairTutPropDet(const char* name, Bool_t active)
    : FairDetector(name, active, kTutProp)
    , fPointsArrayName("FairTutPropPoint")
    , fTrackID(-1)
    , fVolumeID(-1)
    , fPos()
    , fMom()
    , fTime(-1.)
    , fLength(-1.)
    , fELoss(-1)
    , fFairTutPropPointCollection(new TClonesArray("FairTutPropPoint"))
{}

FairTutPropDet::~FairTutPropDet()
{
    if (fFairTutPropPointCollection) {
        fFairTutPropPointCollection->Delete();
        delete fFairTutPropPointCollection;
    }
}

void FairTutPropDet::ProcessHits()
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

    // Create FairTutPropPoint at exit of active volume
    if (TVirtualMC::GetMC()->IsTrackExiting() || TVirtualMC::GetMC()->IsTrackStop()
        || TVirtualMC::GetMC()->IsTrackDisappeared()) {
        fTrackID = TVirtualMC::GetMC()->GetStack()->GetCurrentTrackNumber();
        Int_t copyNo;
        fVolumeID = fMC->CurrentVolID(copyNo);

        if (fELoss == 0.) {
            return;
        }

        // Taking stationNr from string is almost effortless.
        {
            TString detPath = TVirtualMC::GetMC()->CurrentVolPath();
            detPath.Remove(0, detPath.Last('/') + 1);
            detPath.Remove(0, detPath.First("Pixel") + 5);
            Int_t stationNr = detPath.Atoi();
            fVolumeID = stationNr;
        }

        AddHit(fTrackID,
               fVolumeID,
               TVector3(fPos.X(), fPos.Y(), fPos.Z()),
               TVector3(fMom.Px(), fMom.Py(), fMom.Pz()),
               fTime,
               fLength,
               fELoss);

        // Increment number of FairTutPropDet points in TParticle
        FairStack* stack = static_cast<FairStack*>(TVirtualMC::GetMC()->GetStack());
        stack->AddPoint(kTutProp);
    }

    return;
}

void FairTutPropDet::EndOfEvent() { fFairTutPropPointCollection->Clear(); }

void FairTutPropDet::Register()
{

    /** This will create a branch in the output tree called
        FairTutPropPoint, setting the last parameter to kFALSE means:
        this collection will not be written to the file, it will exist
        only during the simulation.
    */

    FairRootManager::Instance()->Register(
        fPointsArrayName.c_str(), "FairTutPropDet", fFairTutPropPointCollection, kTRUE);
}

TClonesArray* FairTutPropDet::GetCollection(Int_t iColl) const
{
    if (iColl == 0) {
        return fFairTutPropPointCollection;
    }
    return NULL;
}

void FairTutPropDet::Reset() { fFairTutPropPointCollection->Clear(); }

void FairTutPropDet::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
        just copy this and use it for your detector, otherwise you can
        implement here you own way of constructing the geometry. */

    ConstructASCIIGeometry<FairTutPropGeo, FairTutPropGeoPar>("FairTutPropGeoPar");
}

FairTutPropPoint* FairTutPropDet::AddHit(Int_t trackID,
                                         Int_t detID,
                                         TVector3 pos,
                                         TVector3 mom,
                                         Double_t time,
                                         Double_t length,
                                         Double_t eLoss)
{
    Int_t size = fFairTutPropPointCollection->GetEntriesFast();
    return new ((*fFairTutPropPointCollection)[size]) FairTutPropPoint(trackID, detID, pos, mom, time, length, eLoss);
}

ClassImp(FairTutPropDet);
