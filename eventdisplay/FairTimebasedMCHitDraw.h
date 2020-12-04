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
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#ifndef FAIRTIMEBASEDMCPHITDRAW_H_
#define FAIRTIMEBASEDMCPHITDRAW_H_

#include "FairMCPoint.h"
#include "FairPointSetDraw.h"   // for FairPointSetDraw
#include "FairTimebasedDataHandlerT.h"

#include <Rtypes.h>   // for FairTimebasedMCHitDraw::Class, etc

class TObject;
class TVector3;

class FairTimebasedMCHitDraw : public FairPointSetDraw
{
  public:
    FairTimebasedMCHitDraw();
    FairTimebasedMCHitDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose = 1)
        : FairPointSetDraw(name, color, mstyle, iVerbose){};
    virtual ~FairTimebasedMCHitDraw();

  protected:
    virtual InitStatus Init();
    void GetData();
    Int_t GetNPoints();
    TVector3 GetVector(Int_t index);
    Double_t GetTime(Int_t index);
    TClonesArray* GetPointList() { return fPointList; }

  private:
    TClonesArray* fPointList = nullptr;                //!
    std::vector<double> const* fEventTime = nullptr;   //!
    TBranch* fBranch = nullptr;                        //!
    FairTimebasedDataHandlerT<FairHit> fDataHandler;   //!
    Double_t fCurrentEventTime = -1.0;                 //!

    ClassDef(FairTimebasedMCHitDraw, 2);
};

#endif /* FAIRMCPOINTDRAW_H_ */
