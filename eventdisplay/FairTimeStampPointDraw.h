/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTimeStampPointDraw.h
 *
 *  Created on: Feb 28, 2011
 *      Author: stockman
 */

#ifndef FAIRTIMESTAMPPOINTDRAW_H_
#define FAIRTIMESTAMPPOINTDRAW_H_

#include "FairBoxSetDraw.h"             // for FairBoxSetDraw

#include "Rtypes.h"                     // for Int_t, etc
#include "TVector3.h"                   // for TVector3

class TObject;

class FairTimeStampPointDraw : public FairBoxSetDraw
{
  public:
    FairTimeStampPointDraw();
    FairTimeStampPointDraw(const char* name, Int_t iVerbose = 1);
    virtual ~FairTimeStampPointDraw();

  private:
    virtual TVector3 GetVector(TObject* obj);
    virtual Int_t GetValue(TObject* obj,Int_t i);

    ClassDef(FairTimeStampPointDraw, 1);
};

#endif /* FAIRTIMESTAMPPOINTDRAW_H_ */
