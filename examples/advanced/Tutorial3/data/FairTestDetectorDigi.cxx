/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigi.cxx
 *
 *  Created on: 20.07.2012
 *      Author: stockman
 */

#include "FairTestDetectorDigi.h"

FairTestDetectorDigi::FairTestDetectorDigi()
    : FairTimeStamp()
    , fX(0)
    , fY(0)
    , fZ(0)
{}

FairTestDetectorDigi::FairTestDetectorDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp)
    : FairTimeStamp(timeStamp)
    , fX(x)
    , fY(y)
    , fZ(z)
{}

FairTestDetectorDigi::~FairTestDetectorDigi() {}
