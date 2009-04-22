/*
 * PndSttMCPointsDraw.cpp
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#include "PndSttMCPointDraw.h"
#include "PndSttPoint.h"

PndSttMCPointDraw::PndSttMCPointDraw()
{
	// TODO Auto-generated constructor stub

}

PndSttMCPointDraw::~PndSttMCPointDraw()
{
	// TODO Auto-generated destructor stub
}

TVector3 PndSttMCPointDraw::GetVector(TObject* obj)
{
	PndSttPoint* p = (PndSttPoint*)obj;
	return TVector3(p->GetXtot(), p->GetYtot(), p->GetZtot());
}


ClassImp(PndSttMCPointDraw)
