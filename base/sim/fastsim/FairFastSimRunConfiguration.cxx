/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimRunConfiguration source file         -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#include "FairFastSimRunConfiguration.h"

#include <TG4RunConfiguration.h>  // for TG4RunConfiguration
#include <fairlogger/Logger.h>    // for LOG

#include "FairFastSimulation.h"   // for FairFastSimulation

FairFastSimRunConfiguration::FairFastSimRunConfiguration(const TString& geometry,
                                                         const TString& physicsList,
                                                         const TString& specialProcess,
                                                         const bool specialStacking,
                                                         const bool isMT)
    : TG4RunConfiguration(geometry, physicsList, specialProcess, specialStacking, isMT)
{
    /// Standard constructor
    /// \param geometry        Selection of geometry option
    /// \param physicsList     Selection of physics
    /// \param specialProcess  Selection of the special processes
}

FairFastSimRunConfiguration::~FairFastSimRunConfiguration()
{
    /// Destructor
}

//
// protected methods
//

TG4VUserFastSimulation* FairFastSimRunConfiguration::CreateUserFastSimulation()
{
    LOG(info) << "Going to create FairFastSimulation";
    return new FairFastSimulation();
}
