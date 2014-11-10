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

MyDigi::MyDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp)
    : FairTimeStamp(timeStamp)
    , fX(x)
    , fY(y)
    , fZ(z)
{
}

MyDigi::~MyDigi()
{
}
