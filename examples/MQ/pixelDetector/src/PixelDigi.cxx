/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelDigi.cxx
 *
 *  Created on: 10.02.2016
 *      Author: M. Al-Turany
 */

#include "PixelDigi.h"

PixelDigi::PixelDigi()
    : FairTimeStamp()
    , fPointIndex(0)
    , fDetectorID(0)
    , fFeID(0)
    , fCharge(0.)
    , fCol(0)
    , fRow(0)
{}

PixelDigi::PixelDigi(Int_t in, Int_t detid, Int_t feid, Int_t col, Int_t row, Double_t ch, Double_t tstamp)
    : FairTimeStamp(tstamp)
    , fPointIndex(in)
    , fDetectorID(detid)
    , fFeID(feid)
    , fCharge(ch)
    , fCol(col)
    , fRow(row)
{}

PixelDigi::~PixelDigi() {}
