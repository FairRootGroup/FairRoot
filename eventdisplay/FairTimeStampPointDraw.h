/*
 * FairTimeStampPointDraw.h
 *
 *  Created on: Feb 28, 2011
 *      Author: stockman
 */

#ifndef FAIRTIMESTAMPPOINTDRAW_H_
#define FAIRTIMESTAMPPOINTDRAW_H_

#include "FairBoxSetDraw.h"

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
