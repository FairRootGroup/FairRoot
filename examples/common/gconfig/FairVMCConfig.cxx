/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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
    : FairXmlVMCConfig()
{}

FairVMCConfig::~FairVMCConfig() {}

void FairVMCConfig::SetupStack()
{
    FairStack *stack = new FairStack(1000);

    XMLNodePointer_t xmlNode = 0;
    if ((xmlNode = GetPointer("SIM:FairStack:StoreSecondaries", fXmlConfig))) {
        LOG(debug) << "Setting SIM:FairStack:StoreSecondaries to \"" << (ConvertTo<bool>(xmlNode) ? "true" : "false")
                   << "\"";
        stack->StoreSecondaries(ConvertTo<bool>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:FairStack:MinPoints", fXmlConfig))) {
        LOG(debug) << "Setting SIM:FairStack:MinPoints to \"" << ConvertTo<float>(xmlNode) << "\"";
        stack->SetMinPoints(ConvertTo<float>(xmlNode));
    }

    TVirtualMC::GetMC()->SetStack(stack);
}

ClassImp(FairVMCConfig);
