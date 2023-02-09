/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropHitProducer.h"

#include "FairLogger.h"         // for FairLogger, MESSAGE_ORIGIN
#include "FairMCTrack.h"        // for FairMCTrack
#include "FairRootManager.h"    // for FairRootManager
#include "FairTutPropHit.h"     // for FairTutPropHit
#include "FairTutPropPoint.h"   // for FairTutPropPoint

#include <TClonesArray.h>   // for TClonesArray
#include <TDatabasePDG.h>   // for TDatabase
#include <TRandom.h>        // for TRandom, gRandom
#include <TVector3.h>       // for TVector3

FairTutPropHitProducer::FairTutPropHitProducer()
    : FairTask("FairTutPropHitProducer")
    , fPointsArrayName("FairTutPropPoint")
    , fHitsArrayName("FairTutPropHits")
    , fPointsArray(nullptr)
    , fTracksArray(nullptr)
    , fHitsArray(new TClonesArray("FairTutPropHit", 100))
{
    LOG(debug) << "Default Constructor of FairTutPropHitProducer";
}

FairTutPropHitProducer::~FairTutPropHitProducer()
{
    LOG(debug) << "Destructor of FairTutPropHitProducer";
    fHitsArray->Delete();
    delete fHitsArray;
}

void FairTutPropHitProducer::SetParContainers()
{
    LOG(debug) << "SetParContainers of FairTutPropHitProducer";
    // Load all necessary parameter containers from the runtime data base
    /*
    FairRunAna* ana = FairRunAna::Instance();
    FairRuntimeDb* rtdb=ana->GetRuntimeDb();

    <FairTutPropHitProducerDataMember> = (<ClassPointer>*)
      (rtdb->getContainer("<ContainerName>"));
    */
}

InitStatus FairTutPropHitProducer::Init()
{
    LOG(debug) << "Initilization of FairTutPropHitProducer";

    // Get a handle from the IO manager
    FairRootManager* ioman = FairRootManager::Instance();

    // Get a pointer to the previous already existing data level
    fPointsArray = static_cast<TClonesArray*>(ioman->GetObject(fPointsArrayName.c_str()));
    fTracksArray = static_cast<TClonesArray*>(ioman->GetObject("MCTrack"));
    if (!fPointsArray || !fTracksArray) {
        LOG(error) << "No InputDataLevelName array!";
        LOG(error) << "FairTutPropHitProducer will be inactive";
        return kERROR;
    }

    // Create the TClonesArray for the output data and register
    // it in the IO manager
    ioman->Register(fHitsArrayName.c_str(), "TutProp", fHitsArray, kTRUE);

    // Do whatever else is needed at the initilization stage
    // Create histograms to be filled
    // initialize variables

    return kSUCCESS;
}

InitStatus FairTutPropHitProducer::ReInit()
{
    LOG(debug) << "Reinitilization of FairTutPropHitProducer";
    return kSUCCESS;
}

void FairTutPropHitProducer::Exec(Option_t* /*option*/)
{
    LOG(debug) << "Exec of FairTutPropHitProducer";

    fHitsArray->Delete();

    // fill the map
    FairTutPropPoint* point = nullptr;
    // FairTutPropHit* hit = nullptr;
    for (int iPoint = 0; iPoint < fPointsArray->GetEntriesFast(); iPoint++) {
        point = static_cast<FairTutPropPoint*>(fPointsArray->At(iPoint));
        if (!point) {
            continue;
        }

        TVector3 position;
        TVector3 momentum;
        point->Position(position);
        point->Momentum(momentum);

        TVector3 dposition;
        TVector3 dmomentum;

        // simulate the detector response: smear position with gaussians
        dposition.SetXYZ(0.05, 0.05, 0.);
        position.SetXYZ(gRandom->Gaus(position.X(), 0.05), gRandom->Gaus(position.Y(), 0.05), position.Z());
        dmomentum.SetXYZ(0.05, 0.05, 0.05);
        momentum.SetXYZ(
            gRandom->Gaus(momentum.X(), 0.05), gRandom->Gaus(momentum.Y(), 0.05), gRandom->Gaus(momentum.Z(), 0.05));
        // position.SetXYZ(position.X(), position.Y(), position.Z());

        FairMCTrack* track = static_cast<FairMCTrack*>(fTracksArray->At(point->GetTrackID()));
        TDatabasePDG* dbPDG = TDatabasePDG::Instance();
        TParticlePDG* particle = dbPDG->GetParticle(track->GetPdgCode());
        double charge = 0;
        if (particle)
            charge = particle->Charge();

        // hit = new ((*fHitsArray)[iPoint]) FairTutPropHit(point->GetDetectorID(), iPoint, position, dposition);
        new ((*fHitsArray)[iPoint]) FairTutPropHit(point->GetDetectorID(),
                                                   iPoint,
                                                   position,
                                                   dposition,
                                                   point->GetTrackID(),
                                                   track->GetPdgCode(),
                                                   charge,
                                                   momentum,
                                                   dmomentum);
    }
}

void FairTutPropHitProducer::Finish()
{
    LOG(debug) << "Finish of FairTutPropHitProducer";
}
