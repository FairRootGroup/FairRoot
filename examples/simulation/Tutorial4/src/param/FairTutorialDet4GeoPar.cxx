/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4GeoPar.h"

#include "FairParamList.h"   // for FairParamList

#include <TObjArray.h>   // for TObjArray

FairTutorialDet4GeoPar ::FairTutorialDet4GeoPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fGeoSensNodes(new TObjArray())
    , fGeoPassNodes(new TObjArray())
    , fGlobalCoordinates(kFALSE)
{}

void FairTutorialDet4GeoPar::clear()
{
    delete fGeoSensNodes;
    delete fGeoPassNodes;
}

void FairTutorialDet4GeoPar::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }
    l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
    l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
    l->add("GlobalCoordinates", fGlobalCoordinates);
}

Bool_t FairTutorialDet4GeoPar::getParams(FairParamList* l)
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
    if (!l->fill("GlobalCoordinates", &fGlobalCoordinates)) {
        return kFALSE;
    }
    return kTRUE;
}
