/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Denis Bertini
//*-- Created : 21/06/2005

#include "FairGeoPassivePar.h"

#include "FairParamList.h"   // for FairParamList

#include <TObjArray.h>   // for TObjArray

ClassImp(FairGeoPassivePar);

FairGeoPassivePar::FairGeoPassivePar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fGeoSensNodes(new TObjArray())
    , fGeoPassNodes(new TObjArray())
{}

FairGeoPassivePar::~FairGeoPassivePar(void) {}

void FairGeoPassivePar::clear(void)
{
    delete fGeoSensNodes;
    delete fGeoPassNodes;
}

void FairGeoPassivePar::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }
    l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
    l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairGeoPassivePar::getParams(FairParamList* l)
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
