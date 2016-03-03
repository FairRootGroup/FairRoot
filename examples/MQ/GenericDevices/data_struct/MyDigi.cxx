/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyDigi.cxx
 * Author: winckler
 * 
 * Created on November 24, 2014, 1:31 PM
 */

#include "MyDigi.h"
ClassImp(MyDigi);

MyDigi::MyDigi()
    : FairTimeStamp()
    , fX(0)
    , fY(0)
    , fZ(0)
{
}

MyDigi::MyDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp, Double_t timeStampError)
    : FairTimeStamp(timeStamp,timeStampError)
    , fX(x)
    , fY(y)
    , fZ(z)
{
}

MyDigi::~MyDigi()
{
}
