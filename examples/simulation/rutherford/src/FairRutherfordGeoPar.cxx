/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
 #include "FairRutherfordGeoPar.h"
 #include <TGenericClassInfo.h>  // for TGenericClassInfo
 #include <TObjArray.h>          // for TObjArray
 #include "FairParamList.h"      // for FairParamList

ClassImp(FairRutherfordGeoPar);

FairRutherfordGeoPar ::FairRutherfordGeoPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fGeoSensNodes(new TObjArray())
    , fGeoPassNodes(new TObjArray())
{}

FairRutherfordGeoPar::~FairRutherfordGeoPar() {}

void FairRutherfordGeoPar::clear()
{
    delete fGeoSensNodes;
    delete fGeoPassNodes;
}

void FairRutherfordGeoPar::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }
    l->addObject("FairGeoNodes Sensitive List", fGeoSensNodes);
    l->addObject("FairGeoNodes Passive List", fGeoPassNodes);
}

Bool_t FairRutherfordGeoPar::getParams(FairParamList* l)
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
