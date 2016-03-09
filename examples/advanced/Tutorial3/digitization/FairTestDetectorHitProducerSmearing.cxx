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
  LOG(DEBUG) << "Default Constructor of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;
}

// ---- Destructor ----------------------------------------------------
FairTestDetectorHitProducerSmearing::~FairTestDetectorHitProducerSmearing()
{
  LOG(DEBUG) << "Destructor of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;
    fHitsArray->Delete();
    delete fHitsArray;
}

// ----  Initialisation  ----------------------------------------------
void FairTestDetectorHitProducerSmearing::SetParContainers()
{
  LOG(DEBUG) << "SetParContainers of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;
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
  LOG(DEBUG) << "Initilization of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;

    // Get a handle from the IO manager
    FairRootManager* ioman = FairRootManager::Instance();

    // Get a pointer to the previous already existing data level
    fPointsArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorPoint"));
    if (!fPointsArray)
    {
      LOG(ERROR) << "No InputDataLevelName array!" << FairLogger::endl;
      LOG(ERROR) << "FairTestDetectorHitProducerSmearing will be inactive"
		 << FairLogger::endl;
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
  LOG(DEBUG) << "Reinitilization of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;
    return kSUCCESS;
}

// ---- Exec ----------------------------------------------------------
void FairTestDetectorHitProducerSmearing::Exec(Option_t* /*option*/)
{
  LOG(DEBUG) << "Exec of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;

    fHitsArray->Delete();

    // fill the map
    FairTestDetectorPoint* point = NULL;
    FairTestDetectorHit* hit = NULL;
    for (int iPoint = 0; iPoint < fPointsArray->GetEntriesFast(); iPoint++)
    {
        point = static_cast<FairTestDetectorPoint*>(fPointsArray->At(iPoint));
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
  LOG(DEBUG) << "Finish of FairTestDetectorHitProducerSmearing"
	     << FairLogger::endl;
}

ClassImp(FairTestDetectorHitProducerSmearing)
