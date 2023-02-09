/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelTrack.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelTrack.h"

#include "FairTimeStamp.h"

PixelTrack::PixelTrack()
    : FairTimeStamp()
    , fX0(0.)
    , fAX(0.)
    , fY0(0.)
    , fAY(0.)
    , fX0Err(0.)
    , fAXErr(0.)
    , fY0Err(0.)
    , fAYErr(0.)
    , fHitIndices()
{}

PixelTrack::PixelTrack(Double_t x0,
                       Double_t ax,
                       Double_t y0,
                       Double_t ay,
                       Double_t x0e,
                       Double_t axe,
                       Double_t y0e,
                       Double_t aye)
    : FairTimeStamp()
    , fX0(x0)
    , fAX(ax)
    , fY0(y0)
    , fAY(ay)
    , fX0Err(x0e)
    , fAXErr(axe)
    , fY0Err(y0e)
    , fAYErr(aye)
    , fHitIndices()
{}

PixelTrack::~PixelTrack() {}
