/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorHitProducerSmearing.h"

#include "FairLogger.h"            // for FairLogger, MESSAGE_ORIGIN
#include "FairRootManager.h"       // for FairRootManager
#include "FairTestDetectorHit.h"   // for FairTestDetectorHit
#include "FairTestDetectorPoint.h" // for FairTestDetectorPoint

#include "TClonesArray.h" // for TClonesArray
#include "TRandom.h"      // for TRandom, gRandom
#include "TVector3.h"     // for TVector3

#include <stddef.h> // for NULL

// ---- Default constructor -------------------------------------------
FairTestDetectorHitProducerSmearing::FairTestDetectorHitProducerSmearing()
    : FairTask("FairTestDetectorHitProducerSmearing")
    , fPointsArray(NULL)
    , fHitsArray(new TClonesArray("FairTestDetectorHit", 100))
{
    fLogger->Debug(MESSAGE_ORIGIN, "Defaul Constructor of FairTestDetectorHitProducerSmearing");
}

// ---- Destructor ----------------------------------------------------
FairTestDetectorHitProducerSmearing::~FairTestDetectorHitProducerSmearing()
{
    fLogger->Debug(MESSAGE_ORIGIN, "Destructor of FairTestDetectorHitProducerSmearing");
    fHitsArray->Delete();
    delete fHitsArray;
}

// ----  Initialisation  ----------------------------------------------
void FairTestDetectorHitProducerSmearing::SetParContainers()
{
    fLogger->Debug(MESSAGE_ORIGIN, "SetParContainers of FairTestDetectorHitProducerSmearing");
    // Load all necessary parameter containers from the runtime data base
    /*
    FairRunAna* ana = FairRunAna::Instance();
    FairRuntimeDb* rtdb=ana->GetRuntimeDb();

    <FairTestDetectorHitProducerSmearingDataMember> = (<ClassPointer>*)
      (rtdb->getContainer("<ContainerName>"));
    */
}

// ---- Init ----------------------------------------------------------
InitStatus FairTestDetectorHitProducerSmearing::Init()
{
    fLogger->Debug(MESSAGE_ORIGIN, "Initilization of FairTestDetectorHitProducerSmearing");

    // Get a handle from the IO manager
    FairRootManager* ioman = FairRootManager::Instance();

    // Get a pointer to the previous already existing data level
    fPointsArray = (TClonesArray*)ioman->GetObject("FairTestDetectorPoint");
    if (!fPointsArray)
    {
        fLogger->Error(MESSAGE_ORIGIN, "No InputDataLevelName array!\n FairTestDetectorHitProducerSmearing will be inactive");
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

// ---- ReInit  -------------------------------------------------------
InitStatus FairTestDetectorHitProducerSmearing::ReInit()
{
    fLogger->Debug(MESSAGE_ORIGIN, "Initilization of FairTestDetectorHitProducerSmearing");
    return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void FairTestDetectorHitProducerSmearing::Exec(Option_t* option)
{
    fLogger->Debug(MESSAGE_ORIGIN, "Exec of FairTestDetectorHitProducerSmearing");

    fHitsArray->Delete();

    // fill the map
    FairTestDetectorPoint* point = NULL;
    FairTestDetectorHit* hit = NULL;
    for (int iPoint = 0; iPoint < fPointsArray->GetEntriesFast(); iPoint++)
    {
        point = (FairTestDetectorPoint*)fPointsArray->At(iPoint);
        if (!point)
        {
            continue;
        }

        TVector3 position;
        point->Position(position);

        TVector3 dposition;

        // simulate the detector response: smear position with gaussians
        dposition.SetXYZ(0.05, 0.05, 0.);
        position.SetXYZ(gRandom->Gaus(position.X(), 0.05), gRandom->Gaus(position.Y(), 0.05), position.Z());

        hit = new ((*fHitsArray)[iPoint]) FairTestDetectorHit(point->GetDetectorID(), iPoint, position, dposition);
    }
}

// ---- Finish --------------------------------------------------------
void FairTestDetectorHitProducerSmearing::Finish()
{
    fLogger->Debug(MESSAGE_ORIGIN, "Finish of FairTestDetectorHitProducerSmearing");
}

ClassImp(FairTestDetectorHitProducerSmearing)
