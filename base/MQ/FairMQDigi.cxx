/*
 * FairMQDigi.cxx
 *
 *  Created on: 20.07.2012
 *      Author: stockman
 */

#include "FairMQDigi.h"

//ClassImp(FairMQDigi);

FairMQDigi::FairMQDigi():
  FairTimeStamp(), fX(0), fY(0), fZ(0)
{
}


FairMQDigi::FairMQDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp):
  FairTimeStamp(timeStamp), fX(x), fY(y), fZ(z)
{
}

FairMQDigi::~FairMQDigi()
{
}



