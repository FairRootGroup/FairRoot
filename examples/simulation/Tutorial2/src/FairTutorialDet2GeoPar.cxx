/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2GeoPar.h"

#include "FairParamList.h"

#include <TObjArray.h>

FairTutorialDet2GeoPar ::FairTutorialDet2GeoPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fGeoSensNodes(new TObjArray())
    , fGeoPassNodes(new TObjArray())
{}

FairTutorialDet2GeoPar::~FairTutorialDet2GeoPar() {}

void FairTutorialDet2GeoPar::clear()
{
    delete fGeoSensNodes;
    delete fGeoPassNodes;
}

void FairTutorialDet2GeoPar::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }
    l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
    l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairTutorialDet2GeoPar::getParams(FairParamList* l)
{
    if (!l) {
        return kFALSE;
    }
    if (!l->fillObject("FairGeoNodes Sensitive List", fGeoSensNodes)) {
        return kFALSE;
    }
    if (!l->fillObject("FairGeoNodes Passive List", fGeoPassNodes)) {
        return kFALSE;
    }
    return kTRUE;
}
