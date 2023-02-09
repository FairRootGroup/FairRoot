/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairConstPar.h"

#include "FairConstField.h"   // for FairConstField
#include "FairParamList.h"    // for FairParamList

#include <TString.h>   // for TString

class FairField;

FairConstPar::FairConstPar(const char* name, const char* title, const char* context)
    : FairMapPar(name, title, context)
    , fBx(0)
    , fBy(0)
    , fBz(0)
{
    fType = 0;
}

FairConstPar::FairConstPar()
    : FairMapPar()
    , fBx(0)
    , fBy(0)
    , fBz(0)
{
    fType = 0;
}

FairConstPar::~FairConstPar() {}

void FairConstPar::putParams(FairParamList* list)
{
    if (!list) {
        return;
    }

    list->add("Field Type", fType);

    list->add("Field min x", fXmin);
    list->add("Field max x", fXmax);
    list->add("Field min y", fYmin);
    list->add("Field max y", fYmax);
    list->add("Field min z", fZmin);
    list->add("Field max z", fZmax);
    list->add("Field Bx", fBx);
    list->add("Field By", fBy);
    list->add("Field Bz", fBz);
}

Bool_t FairConstPar::getParams(FairParamList* list)
{
    if (!list) {
        return kFALSE;
    }
    if (!list->fill("Field Type", &fType)) {
        return kFALSE;
    }
    if (!list->fill("Field min x", &fXmin)) {
        return kFALSE;
    }
    if (!list->fill("Field max x", &fXmax)) {
        return kFALSE;
    }
    if (!list->fill("Field min y", &fYmin)) {
        return kFALSE;
    }
    if (!list->fill("Field max y", &fYmax)) {
        return kFALSE;
    }
    if (!list->fill("Field min z", &fZmin)) {
        return kFALSE;
    }
    if (!list->fill("Field max z", &fZmax)) {
        return kFALSE;
    }
    if (!list->fill("Field Bx", &fBx)) {
        return kFALSE;
    }
    if (!list->fill("Field By", &fBy)) {
        return kFALSE;
    }
    if (!list->fill("Field Bz", &fBz)) {
        return kFALSE;
    }
    return kTRUE;
}

void FairConstPar::SetParameters(FairField* field)
{
    FairConstField* fieldConst = static_cast<FairConstField*>(field);
    fBx = fieldConst->GetBx();
    fBy = fieldConst->GetBy();
    fBz = fieldConst->GetBz();
    fXmin = fieldConst->GetXmin();
    fXmax = fieldConst->GetXmax();
    fYmin = fieldConst->GetYmin();
    fYmax = fieldConst->GetYmax();
    fZmin = fieldConst->GetZmin();
    fZmax = fieldConst->GetZmax();
    fMapName = "";
    fPosX = fPosY = fPosZ = fScale = 0.;
    fType = fieldConst->GetType();
}
