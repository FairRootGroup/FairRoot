/*
 * FairMCPointsDraw.h
 *
 *  Created on: Sep. 30, 2009
 *      Author: stockman
 */

#ifndef FAIRHITPOINTSETDRAW_H_
#define FAIRHITPOINTSETDRAW_H_

#include "FairPointSetDraw.h"

class TVector3;

class FairHitPointSetDraw: public FairPointSetDraw
{
  public:
    FairHitPointSetDraw();
    FairHitPointSetDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1):FairPointSetDraw(name, color, mstyle, iVerbose) {};
    virtual ~FairHitPointSetDraw();

  protected:
    TVector3 GetVector(TObject* obj);

    ClassDef(FairHitPointSetDraw,1);
};

#endif /* FAIRHITPOINTSETDRAW_H_ */
