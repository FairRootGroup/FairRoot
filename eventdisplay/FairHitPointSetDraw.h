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

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Color_t, Int_t, Style_t

class TObject;
class TVector3;
class TBuffer;
class TClass;
class TMemberInspector;

class FairHitPointSetDraw : public FairPointSetDraw
{
  public:
    FairHitPointSetDraw();
    FairHitPointSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose = 1)
        : FairPointSetDraw(name, color, mstyle, iVerbose)
    {}
    virtual ~FairHitPointSetDraw();

  protected:
    TVector3 GetVector(TObject* obj);
    double GetTime(TObject* obj);

    ClassDef(FairHitPointSetDraw, 1);
};

#endif /* FAIRHITPOINTSETDRAW_H_ */
