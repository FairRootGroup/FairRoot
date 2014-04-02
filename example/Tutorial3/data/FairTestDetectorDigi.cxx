/*
 * FairTestDetectorDigi.cxx
 *
 *  Created on: 20.07.2012
 *      Author: stockman
 */

#include "FairTestDetectorDigi.h"
ClassImp(FairTestDetectorDigi);

FairTestDetectorDigi::FairTestDetectorDigi():
  FairTimeStamp(), fX(0), fY(0), fZ(0)
{
}


FairTestDetectorDigi::FairTestDetectorDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp):
  FairTimeStamp(timeStamp), fX(x), fY(y), fZ(z)
{
 
}


FairTestDetectorDigi::FairTestDetectorDigi(const FairTestDetectorDigi &Digi) :
  FairTimeStamp(Digi), fX(Digi.fX), fY(Digi.fY), fZ(Digi.fZ)
{
    
}

FairTestDetectorDigi::~FairTestDetectorDigi()
{
}



