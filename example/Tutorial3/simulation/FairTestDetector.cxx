/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetector.h"

#include "FairDetectorList.h"       // for DetectorId::kTutDet
#include "FairGeoInterface.h"       // for FairGeoInterface
#include "FairGeoLoader.h"          // for FairGeoLoader
#include "FairGeoNode.h"            // for FairGeoNode
#include "FairGeoVolume.h"          // for FairGeoVolume
#include "FairRootManager.h"        // for FairRootManager
#include "FairRun.h"                // for FairRun
#include "FairRuntimeDb.h"          // for FairRuntimeDb
#include "FairStack.h"              // for FairStack
#include "FairTestDetectorGeo.h"    // for FairTestDetectorGeo
#include "FairTestDetectorGeoPar.h" // for FairTestDetectorGeoPar
#include "FairTestDetectorPoint.h"  // for FairTestDetectorPoint
#include "FairVolume.h"             // for FairVolume

#include "TClonesArray.h"    // for TClonesArray
#include "TList.h"           // for TListIter, TList (ptr only)
#include "TObjArray.h"       // for TObjArray
#include "TString.h"         // for TString
#include "TVirtualMC.h"      // for TVirtualMC, gMC
#include "TVirtualMCStack.h" // for TVirtualMCStack

#include <stddef.h> // for NULL
#include <iostream> // for cout, endl

using std::cout;
using std::endl;

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
    , fFairTestDetectorPointCollection(new TClonesArray("FairTestDetectorPoint"))
{
}

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
    , fFairTestDetectorPointCollection(new TClonesArray("FairTestDetectorPoint"))
{
}

FairTestDetector::~FairTestDetector()
{
    if (fFairTestDetectorPointCollection)
    {
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
    if (gMC->IsTrackEntering())
    {
        fELoss = 0.;
        fTime = gMC->TrackTime() * 1.0e09;
        fLength = gMC->TrackLength();
        gMC->TrackPosition(fPos);
        gMC->TrackMomentum(fMom);
    }

    // Sum energy loss for all steps in the active volume
    fELoss += gMC->Edep();

    // Create FairTestDetectorPoint at exit of active volume
    if (gMC->IsTrackExiting() || gMC->IsTrackStop() || gMC->IsTrackDisappeared())
    {
        fTrackID = gMC->GetStack()->GetCurrentTrackNumber();
        fVolumeID = vol->getMCid();
        gMC->TrackPosition(fPosOut);
        gMC->TrackMomentum(fMomOut);
        if (fELoss == 0.)
        {
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
        FairStack* stack = (FairStack*)gMC->GetStack();
        stack->AddPoint(kTutDet);
    }

    return kTRUE;
}

void FairTestDetector::EndOfEvent()
{

    fFairTestDetectorPointCollection->Clear();
}

void FairTestDetector::Register()
{

    /** This will create a branch in the output tree called
        FairTestDetectorPoint, setting the last parameter to kFALSE means:
        this collection will not be written to the file, it will exist
        only during the simulation.
    */

    FairRootManager::Instance()->Register("FairTestDetectorPoint", "FairTestDetector", fFairTestDetectorPointCollection, kTRUE);
}

TClonesArray* FairTestDetector::GetCollection(Int_t iColl) const
{
    if (iColl == 0)
    {
        return fFairTestDetectorPointCollection;
    }
    else
    {
        return NULL;
    }
}

void FairTestDetector::Reset()
{
    fFairTestDetectorPointCollection->Clear();
}

void FairTestDetector::ConstructGeometry()
{
    /** If you are using the standard ASCII input for the geometry
        just copy this and use it for your detector, otherwise you can
        implement here you own way of constructing the geometry. */

    FairGeoLoader* geoLoad = FairGeoLoader::Instance();
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();
    FairTestDetectorGeo* Geo = new FairTestDetectorGeo();
    Geo->setGeomFile(GetGeometryFileName());
    geoFace->addGeoModule(Geo);

    Bool_t rc = geoFace->readSet(Geo);
    if (rc)
    {
        Geo->create(geoLoad->getGeoBuilder());
    }
    TList* volList = Geo->getListOfVolumes();

    // store geo parameter
    FairRun* fRun = FairRun::Instance();
    FairRuntimeDb* rtdb = FairRun::Instance()->GetRuntimeDb();
    FairTestDetectorGeoPar* par = (FairTestDetectorGeoPar*)(rtdb->getContainer("FairTestDetectorGeoPar"));
    TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
    TObjArray* fPassNodes = par->GetGeoPassiveNodes();

    TListIter iter(volList);
    FairGeoNode* node = NULL;
    FairGeoVolume* aVol = NULL;

    while ((node = (FairGeoNode*)iter.Next()))
    {
        aVol = dynamic_cast<FairGeoVolume*>(node);
        if (node->isSensitive())
        {
            fSensNodes->AddLast(aVol);
        }
        else
        {
            fPassNodes->AddLast(aVol);
        }
    }
    par->setChanged();
    par->setInputVersion(fRun->GetRunId(), 1);

    ProcessNodes(volList);
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
    return new (clref[size]) FairTestDetectorPoint(trackID, detID, pos, mom, posOut, momOut, time, length, eLoss);
}

ClassImp(FairTestDetector)
