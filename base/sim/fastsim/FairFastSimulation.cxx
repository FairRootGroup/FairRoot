/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimulation source file                  -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------

#include "FairFastSimulation.h"
#include "FairFastSimModel.h"

#include <G4RegionStore.hh>
#include <G4Material.hh>
#include <GFlashHomoShowerParameterisation.hh>
#include <G4FastSimulationManager.hh>
#include <GFlashShowerModel.hh>
#include <GFlashHitMaker.hh>
#include <GFlashParticleBounds.hh>
#include <G4NistManager.hh>

#include "FairLogger.h"

//_____________________________________________________________________________
FairFastSimulation::FairFastSimulation() 
  : TG4VUserFastSimulation()
{
    SetModel("fairFastSimModel");
    LOG(info) << "FairFastSimulation::FairFastSimulation() model set";
    
    SetModelParticles("fairFastSimModel", "all");
    SetModelRegions("fairFastSimModel", "FastSim");
    /// Standard constructor
    
    LOG(info) << "FairFastSimulation::FairFastSimulation() finished";
}

//_____________________________________________________________________________
FairFastSimulation::~FairFastSimulation()
{
/// Destructor
}

//
// protected methods
//

//_____________________________________________________________________________
void  FairFastSimulation::Construct()
{
/// This function must be overriden in user class and users should create
/// the simulation models and register them to VMC framework

    LOG(info) << "Construct FairFastSimulation model.";

    // Create the fast simulation model
    FairFastSimModel* fairFastSimModel 
        = new FairFastSimModel("fairFastSimModel");

    // Register the model in the VMC framework
    Register(fairFastSimModel);
    
    LOG(info) << "end construct FairFastSimulation model.";
  //
  // end Initializing shower model
}

