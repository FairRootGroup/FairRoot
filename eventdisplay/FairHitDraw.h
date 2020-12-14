/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairHitDraw.h
 *
 *  Created on: Apr 16, 2009
 *      Author: stockman
 *
 *      Simple method to draw points derived from FairHit
 */

#ifndef FAIRHITDRAW_H_
#define FAIRHITDRAW_H_

#include "FairBoxSetDraw.h"   // for FairBoxSetDraw

#include <Rtypes.h>     // for FairHitDraw::Class, etc
#include <TVector3.h>   // for TVector3

class TObject;

class FairHitDraw : public FairBoxSetDraw
{
  public:
    FairHitDraw();

    /** Standard constructor
     *@param name        Name of task
     *@param dataSource  Input container for data to be displayed
     *@param iVerbose    Verbosity level
     **/
    FairHitDraw(const char* name, FairDataSourceI* dataSource, Int_t iVerbose = 1);

    /** Legacy constructor
     *@param name        Name of task
     *@param dataSource  Input container for data to be displayed
     *@param iVerbose    Verbosity level
     **/
    FairHitDraw(const char* name, Int_t iVerbose = 1);

  protected:
    TVector3 GetVector(TObject* obj);
    double GetTime(TObject* obj);

    ClassDef(FairHitDraw, 1);
};

#endif /* FAIRHITDRAW_H_ */
