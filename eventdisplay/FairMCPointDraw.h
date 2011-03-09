/*
 * FairMCPointsDraw.h
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#ifndef FAIRMCPOINTDRAW_H_
#define FAIRMCPOINTDRAW_H_

#include "FairPointSetDraw.h"

class TVector3;

class FairMCPointDraw: public FairPointSetDraw
{
  public:
    FairMCPointDraw();
    FairMCPointDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1):FairPointSetDraw(name, color, mstyle, iVerbose) {};
    virtual ~FairMCPointDraw();

  protected:
    TVector3 GetVector(TObject* obj);

    ClassDef(FairMCPointDraw,1);
};

#endif /* FAIRMCPOINTDRAW_H_ */
