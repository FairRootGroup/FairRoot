/*
 * FairMCPointsDraw.cpp
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#include "FairMCPointDraw.h"
#include "FairMCPoint.h"

FairMCPointDraw::FairMCPointDraw()
{
  // TODO Auto-generated constructor stub

}

FairMCPointDraw::~FairMCPointDraw()
{
  // TODO Auto-generated destructor stub
}

TVector3 FairMCPointDraw::GetVector(TObject* obj)
{
  FairMCPoint* p = (FairMCPoint*)obj;
  return TVector3(p->GetX(), p->GetY(), p->GetZ());
}


ClassImp(FairMCPointDraw)
