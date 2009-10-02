/*
 * FairMCPointsDraw.cpp
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#include "FairHitPointSetDraw.h"
#include "FairHit.h"

#include <iostream>

FairHitPointSetDraw::FairHitPointSetDraw()
{
	// TODO Auto-generated constructor stub

}

FairHitPointSetDraw::~FairHitPointSetDraw()
{
	// TODO Auto-generated destructor stub
}

TVector3 FairHitPointSetDraw::GetVector(TObject* obj)
{
	FairHit* p = (FairHit*)obj;
	if (fVerbose > 1)
		std::cout << "-I- FairHitPointSetDraw::GetVector: " << p->GetX() << " " << p->GetY() << " " << p->GetZ() << std::endl;
	return TVector3(p->GetX(), p->GetY(), p->GetZ());
}


ClassImp(FairHitPointSetDraw)
