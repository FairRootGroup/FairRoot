/*
 * PndSttMCPointsDraw.h
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#ifndef PNDSTTMCPOINTDRAW_H_
#define PNDSTTMCPOINTDRAW_H_

#include "FairPointSetDraw.h"
#include "TVector3.h"

class PndSttMCPointDraw: public FairPointSetDraw
{
public:
	PndSttMCPointDraw();
	PndSttMCPointDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1):FairPointSetDraw(name, color, mstyle, iVerbose){};
	virtual ~PndSttMCPointDraw();

protected:
	TVector3 GetVector(TObject* obj);

	ClassDef(PndSttMCPointDraw,1);
};

#endif /* PndSttMCPOINTDRAW_H_ */
