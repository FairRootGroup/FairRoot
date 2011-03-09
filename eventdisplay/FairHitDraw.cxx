/*
 * FairHitDraw.cpp
 *
 *  Created on: Apr 16, 2009
 *      Author: stockman
 */

#include "FairHitDraw.h"
#include "FairHit.h"

FairHitDraw::FairHitDraw()
{
}

FairHitDraw::FairHitDraw(const char* name, Int_t iVerbose):FairBoxSetDraw(name, iVerbose)
{
}

TVector3 FairHitDraw::GetVector(TObject* obj)
{
  FairHit* hit =(FairHit*)obj;
  return TVector3(hit->GetX(), hit->GetY(), hit->GetZ());
}

ClassImp(FairHitDraw)
