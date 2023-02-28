/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairFastSimulation header file                  -----
// -----            Created 2019/01/30  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#ifndef FAIR_FAST_SIMULATION_H
#define FAIR_FAST_SIMULATION_H

#include <TG4VUserFastSimulation.h>

class FairFastSimulation : public TG4VUserFastSimulation
{
  public:
    FairFastSimulation();
    ~FairFastSimulation() override;

    // methods
    void Construct() override;
};

#endif   // FAIR_FAST_SIMULATION_H
