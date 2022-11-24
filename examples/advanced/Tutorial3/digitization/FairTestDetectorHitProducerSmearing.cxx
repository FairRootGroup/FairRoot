/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorHitProducerSmearing.h"

#include "FairLogger.h"              // for FairLogger, MESSAGE_ORIGIN
#include "FairRootManager.h"         // for FairRootManager
#include "FairTestDetectorHit.h"     // for FairTestDetectorHit
#include "FairTestDetectorPoint.h"   // for FairTestDetectorPoint

#include <TClonesArray.h>   // for TClonesArray
#include <TRandom.h>        // for TRandom, gRandom
#include <TVector3.h>       // for TVector3

FairTestDetectorHitProducerSmearing::FairTestDetectorHitProducerSmearing()
    : FairTask("FairTestDetectorHitProducerSmearing")
    , fPointsArray(nullptr)
    , fHitsArray(new TClonesArray("FairTestDetectorHit", 100))
{
    LOG(debug) << "Default Constructor of FairTestDetectorHitProducerSmearing";
}

FairTestDetectorHitProducerSmearing::~FairTestDetectorHitProducerSmearing()
{
    LOG(debug) << "Destructor of FairTestDetectorHitProducerSmearing";
    fHitsArray->Delete();
    delete fHitsArray;
}

InitStatus FairTestDetectorHitProducerSmearing::Init()
{
    LOG(debug) << "Initilization of FairTestDetectorHitProducerSmearing";

    // Get a handle from the IO manager
    FairRootManager* ioman = FairRootManager::Instance();

    // Get a pointer to the previous already existing data level
    fPointsArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorPoint"));
    if (!fPointsArray) {
        LOG(error) << "No InputDataLevelName array!";
        LOG(error) << "FairTestDetectorHitProducerSmearing will be inactive";
        return kERROR;
    }

    // Create the TClonesArray for the output data and register
    // it in the IO manager
    ioman->Register("FairTestDetectorHit", "FairTestDetectorHit", fHitsArray, kTRUE);

    // Do whatever else is needed at the initilization stage
    // Create histograms to be filled
    // initialize variables

    return kSUCCESS;
}

InitStatus FairTestDetectorHitProducerSmearing::ReInit()
{
    LOG(debug) << "Reinitilization of FairTestDetectorHitProducerSmearing";
    return kSUCCESS;
}

void FairTestDetectorHitProducerSmearing::Exec(Option_t* /*option*/)
{
    LOG(debug) << "Exec of FairTestDetectorHitProducerSmearing";

    fHitsArray->Delete();

    // fill the map
    FairTestDetectorPoint* point = nullptr;
    // FairTestDetectorHit* hit = nullptr;
    for (int iPoint = 0; iPoint < fPointsArray->GetEntriesFast(); iPoint++) {
        point = static_cast<FairTestDetectorPoint*>(fPointsArray->At(iPoint));
        if (!point) {
            continue;
        }

        TVector3 position;
        point->Position(position);

        TVector3 dposition;

        // simulate the detector response: smear position with gaussians
        dposition.SetXYZ(0.05, 0.05, 0.);
        position.SetXYZ(gRandom->Gaus(position.X(), 0.05), gRandom->Gaus(position.Y(), 0.05), position.Z());

        // hit = new ((*fHitsArray)[iPoint]) FairTestDetectorHit(point->GetDetectorID(), iPoint, position, dposition);
        new ((*fHitsArray)[iPoint]) FairTestDetectorHit(point->GetDetectorID(), iPoint, position, dposition);
    }
}

void FairTestDetectorHitProducerSmearing::Finish() { LOG(debug) << "Finish of FairTestDetectorHitProducerSmearing"; }

ClassImp(FairTestDetectorHitProducerSmearing);
