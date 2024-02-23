/********************************************************************************
 * Copyright (C) 2023-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIREXAMPLERUNSIM_H
#define FAIREXAMPLERUNSIM_H

#include "FairRunSim.h"

/**
 * \brief RunSim with specific behaviour for an experiment
 *
 * \note This is an advanced use case and is likely only
 *       interesting for bigger / more complex experiments
 *       that need this kind of refactoring.
 *
 * One can derive from the FairRun classes.
 * But please only call public APIs from inside any member
 * functions.
 */
class FairExampleRunSim : public FairRunSim
{
  public:
    explicit FairExampleRunSim(const char* mcEngine);
    ~FairExampleRunSim() override = default;
    ClassDefOverride(FairExampleRunSim, 0);
};

#endif
