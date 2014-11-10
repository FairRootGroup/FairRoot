/* 
 * File:   MyHit.cxx
 * Author: winckler
 * 
 * Created on November 24, 2014, 1:40 PM
 */

#include "MyHit.h"
#include "MyHit.h"

MyHit::MyHit()
    : FairHit()
{
}

MyHit::MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{
}

MyHit::~MyHit()
{
}

ClassImp(MyHit)