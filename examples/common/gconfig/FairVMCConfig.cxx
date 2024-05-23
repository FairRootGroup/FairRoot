/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairVMCConfig source file                       -----
// -----            Created 2019.02.19  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#include "FairVMCConfig.h"

#include "FairLogger.h"
#include "FairRunSim.h"
#include "FairStack.h"

#include <TVirtualMC.h>

FairVMCConfig::FairVMCConfig()
    : FairYamlVMCConfig()
{}

FairVMCConfig::~FairVMCConfig() {}

void FairVMCConfig::SetupStack()
{
    FairStack *stack = new FairStack(1000);
    if (fYamlConfig["FairStack_StoreSecondaries"])
        stack->StoreSecondaries(fYamlConfig["FairStack_StoreSecondaries"].as<bool>());
    if (fYamlConfig["FairStack_MinPoints"])
        stack->SetMinPoints(fYamlConfig["FairStack_MinPoints"].as<int>());
    TVirtualMC::GetMC()->SetStack(stack);
}
