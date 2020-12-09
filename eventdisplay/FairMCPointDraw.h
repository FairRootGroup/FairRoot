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

#ifndef FAIRMCPOINTDRAW_H_
#define FAIRMCPOINTDRAW_H_

#include "FairPointSetDraw.h"   // for FairPointSetDraw

#include <Rtypes.h>   // for FairMCPointDraw::Class, etc

class TObject;
class TVector3;

class FairMCPointDraw : public FairPointSetDraw
{
  public:
    FairMCPointDraw();
    FairMCPointDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose = 1)
        : FairPointSetDraw(name, color, mstyle, iVerbose){};
    FairMCPointDraw(const char* name, FairDataSourceI* dataSource, Color_t color, Style_t mstyle, Int_t iVerbose = 1)
        : FairPointSetDraw(name, dataSource, color, mstyle, iVerbose){};
    virtual ~FairMCPointDraw();

  protected:
    TVector3 GetVector(TObject* obj);

  private:
    ClassDef(FairMCPointDraw, 3);
};

#endif /* FAIRMCPOINTDRAW_H_ */
