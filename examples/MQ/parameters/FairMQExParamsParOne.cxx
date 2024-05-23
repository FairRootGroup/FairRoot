/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairMQExParamsParOne.h"

#include "FairParamList.h"   // for FairParamList

#include <TString.h>             // for TString
#include <fairlogger/Logger.h>   // for LOG, Logger

FairMQExParamsParOne::FairMQExParamsParOne(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fParameterValue(0)
{
    detName = "TutorialDet";
}

void FairMQExParamsParOne::print()
{
    FairParGenericSet::print();
    LOG(info) << "fParameterValue: " << fParameterValue;
}

void FairMQExParamsParOne::putParams(FairParamList* list)
{
    LOG(info) << "FairMQExParamsParOne::putParams()";

    if (!list) {
        return;
    }

    list->add("Example7ParameterValue", fParameterValue);
}

Bool_t FairMQExParamsParOne::getParams(FairParamList* list)
{
    LOG(info) << "FairMQExParamsParOne::getParams()";

    if (!list) {
        return kFALSE;
    }

    if (!list->fill("Example7ParameterValue", &fParameterValue)) {
        return kFALSE;
    }

    return kTRUE;
}
