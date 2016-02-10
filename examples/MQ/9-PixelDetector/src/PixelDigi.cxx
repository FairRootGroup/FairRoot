/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelDigi.cxx
 *
 *  Created on: 10.02.2016
 *      Author: M. Al-Turany
 */

#include "PixelDigi.h"
ClassImp(PixelDigi);

PixelDigi::PixelDigi()
    : FairTimeStamp()
    , index(0)
    , detID(0)
    , SensorID(0)
    , feID(0)
    , charge(0.)
{
}

PixelDigi::PixelDigi(Int_t in, Int_t detid, Int_t Sensorid, Int_t feid, Double_t ch, Double_t tstamp)
    : FairTimeStamp(tstamp)
    , index(in)
    , detID(detid)
    , SensorID(Sensorid)
    , feID(feid)
    , charge(ch)
{
}

PixelDigi::~PixelDigi()
{
}
