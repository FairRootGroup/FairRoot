/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairMapPar.h"

FairMapPar::FairMapPar(const char* name, const char* title, const char* context)
    : FairParGenericSet(name, title, context)
    , fType(-1)
    , fXmin(0)
    , fXmax(0)
    , fYmin(0)
    , fYmax(0)
    , fZmin(0)
    , fZmax(0)
    , fMapName(TString(""))
    , fPosX(0)
    , fPosY(0)
    , fPosZ(0)
    , fScale(0)
{}

FairMapPar::FairMapPar()
    : fType(-1)
    , fXmin(0)
    , fXmax(0)
    , fYmin(0)
    , fYmax(0)
    , fZmin(0)
    , fZmax(0)
    , fMapName(TString(""))
    , fPosX(0)
    , fPosY(0)
    , fPosZ(0)
    , fScale(0)
{}

FairMapPar::~FairMapPar() {}
