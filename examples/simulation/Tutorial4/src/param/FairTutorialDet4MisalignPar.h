/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4MISSALLIGNPAR_H
#define FAIRTUTORIALDET4MISSALLIGNPAR_H

#include "FairParGenericSet.h"   // for FairParGenericSet

#include <Rtypes.h>    // for ClassDef
#include <TArrayD.h>   // for TArrayD

class FairParamList;

class FairTutorialDet4MisalignPar : public FairParGenericSet
{
  public:
    FairTutorialDet4MisalignPar(
        const char* name = "FairTutorialDet4MissallignPar",
        const char* title = "Missalignment parameter for FairTutorialDet4HitProducerIdealMissallign Parameters",
        const char* context = "TestDefaultContext");
    ~FairTutorialDet4MisalignPar();
    void clear();
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetShiftX() { return fShiftX; }
    TArrayD GetShiftY() { return fShiftY; }
    TArrayD GetShiftZ() { return fShiftZ; }
    TArrayD GetRotX() { return fRotX; }
    TArrayD GetRotY() { return fRotY; }
    TArrayD GetRotZ() { return fRotZ; }
    Int_t GetNrOfDetectors() { return fNrOfDetectors; }

  private:
    TArrayD fShiftX;        // Array to hold the misalignment in x-direction
    TArrayD fShiftY;        // Array to hold the misalignment in y-direction
    TArrayD fShiftZ;        // Array to hold the misalignment in z-direction
    TArrayD fRotX;          // Array to hold the rotation in x-direction
    TArrayD fRotY;          // Array to hold the rotation in y-direction
    TArrayD fRotZ;          // Array to hold the rotation in z-direction
    Int_t fNrOfDetectors;   // Total number of detectors

    FairTutorialDet4MisalignPar(const FairTutorialDet4MisalignPar&);
    FairTutorialDet4MisalignPar& operator=(const FairTutorialDet4MisalignPar&);

    ClassDef(FairTutorialDet4MisalignPar, 1);
};

#endif
