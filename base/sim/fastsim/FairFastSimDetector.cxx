/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairFastSimDetector.h"

#include "FairGeoBuilder.h"
#include "FairGeoInterface.h"   // for FairGeoInterface
#include "FairGeoLoader.h"      // for FairGeoLoader
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"   // for FairGeoMedium

// #include <TGeoMedium.h>
#include <TGeoManager.h>   // gGeoManager

FairFastSimDetector::FairFastSimDetector()
    : FairDetector("FastSimulation", kTRUE)
    , fFastSimMedium(nullptr)
{}

FairFastSimDetector::FairFastSimDetector(const char* name, Int_t DetId)
    : FairDetector(name, kTRUE, DetId)
    , fFastSimMedium(nullptr)
{}

FairFastSimDetector::FairFastSimDetector(const FairFastSimDetector& right)
    : FairDetector(right)
    , fFastSimMedium(right.fFastSimMedium)
{}

FairFastSimDetector::~FairFastSimDetector() {}

void FairFastSimDetector::ConstructGeometry()
{
    FairGeoLoader* geoLoad = FairGeoLoader::Instance();
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();
    FairGeoMedia* geoMedia = geoFace->getMedia();
    FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

    TGeoMedium* medium = gGeoManager->GetMedium("FastSimMedium");
    if (!medium) {
        FairGeoMedium* fairMedium = geoMedia->getMedium("FastSimMedium");
        if (!fairMedium) {
            fairMedium = new FairGeoMedium("FastSimMedium");
            fairMedium->setMediumIndex(geoMedia->getListOfMedia()->GetEntries());
            fairMedium->setNComponents(1);
            fairMedium->setComponent(0, 1, 1, 1.);
            fairMedium->setDensity(1e-16);
            fairMedium->setMediumPar(1, 1, 20., 0.001);
            geoMedia->addMedium(fairMedium);
        }
        geoBuild->createMedium(fairMedium);
        fFastSimMedium = gGeoManager->GetMedium("FastSimMedium");
    } else {
        fFastSimMedium = medium;
    }
}

void FairFastSimDetector::ProcessHits()
{
    FastSimProcessParticle();
}

ClassImp(FairFastSimDetector);
