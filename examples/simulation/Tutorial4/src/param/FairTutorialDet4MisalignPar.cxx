/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4MisalignPar.h"

#include "FairParamList.h"

FairTutorialDet4MisalignPar ::FairTutorialDet4MisalignPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fShiftX()
    , fShiftY()
    , fShiftZ()
    , fRotX()
    , fRotY()
    , fRotZ()
    , fNrOfDetectors(0)
{}

FairTutorialDet4MisalignPar::~FairTutorialDet4MisalignPar() {}

void FairTutorialDet4MisalignPar::clear() {}

void FairTutorialDet4MisalignPar::putParams(FairParamList* l)
{
    if (!l) {
        return;
    }

    l->add("NrOfDetectors", fNrOfDetectors);
    l->add("ShiftX", fShiftX);
    l->add("ShiftY", fShiftY);
    l->add("ShiftZ", fShiftZ);
    l->add("RotationX", fRotX);
    l->add("RotationY", fRotY);
    l->add("RotationZ", fRotZ);
}

Bool_t FairTutorialDet4MisalignPar::getParams(FairParamList* l)
{
    if (!l) {
        return kFALSE;
    }

    if (!l->fill("NrOfDetectors", &fNrOfDetectors)) {
        return kFALSE;
    }

    fShiftX.Set(fNrOfDetectors);
    if (!l->fill("ShiftX", &fShiftX)) {
        return kFALSE;
    }

    fShiftY.Set(fNrOfDetectors);
    if (!l->fill("ShiftY", &fShiftY)) {
        return kFALSE;
    }

    fShiftZ.Set(fNrOfDetectors);
    if (!l->fill("ShiftZ", &fShiftZ)) {
        return kFALSE;
    }

    fRotX.Set(fNrOfDetectors);
    if (!l->fill("RotationX", &fRotX)) {
        return kFALSE;
    }

    fRotY.Set(fNrOfDetectors);
    if (!l->fill("RotationY", &fRotY)) {
        return kFALSE;
    }

    fRotZ.Set(fNrOfDetectors);
    return l->fill("RotationZ", &fRotZ);
}
