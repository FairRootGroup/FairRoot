/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCPointsDraw.h
 *
 *  Created on: Sep. 30, 2009
 *      Author: stockman
 */

#ifndef FAIRHITPOINTSETDRAW_H_
#define FAIRHITPOINTSETDRAW_H_

#include "FairPointSetDraw.h"   // for FairPointSetDraw

#include <Rtypes.h>   // for FairHitPointSetDraw::Class, etc

class TObject;
class TVector3;

class FairHitPointSetDraw : public FairPointSetDraw
{
  public:
    FairHitPointSetDraw();
    FairHitPointSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose = 1)
        : FairPointSetDraw(name, color, mstyle, iVerbose)
    {}
    virtual ~FairHitPointSetDraw();
    virtual void SetUseTimeOffset(Bool_t val) { fUseTimeOffset = val; };

  protected:
    virtual InitStatus Init();
    void GetData(){};
    Int_t GetNPoints();
    TVector3 GetVector(Int_t index);
    double GetTime(Int_t index);

  private:
    TClonesArray* fPointList = nullptr;   //!

    ClassDef(FairHitPointSetDraw, 2);
};

#endif /* FAIRHITPOINTSETDRAW_H_ */
