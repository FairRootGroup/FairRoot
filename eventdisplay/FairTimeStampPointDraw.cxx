/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTimeStampPointDraw.cxx
 *
 *  Created on: Feb 28, 2011
 *      Author: stockman
 */

#include "FairTimeStampPointDraw.h"

#include "FairMCPoint.h"                // for FairMCPoint
#include "FairTimeStamp.h"              // for FairTimeStamp

class TObject;

ClassImp(FairTimeStampPointDraw);

FairTimeStampPointDraw::FairTimeStampPointDraw()
{
  // TODO Auto-generated constructor stub

}


FairTimeStampPointDraw::FairTimeStampPointDraw(const char* name, Int_t iVerbose):FairBoxSetDraw(name, iVerbose)
{
}

FairTimeStampPointDraw::~FairTimeStampPointDraw()
{
  // TODO Auto-generated destructor stub
}

TVector3 FairTimeStampPointDraw::GetVector(TObject* obj)
{
  FairMCPoint* hit =static_cast<FairMCPoint*>(obj);
  return TVector3(hit->GetX(), hit->GetY(), hit->GetZ());
}

Int_t FairTimeStampPointDraw::GetValue(TObject* obj,Int_t /*i*/)
{
  FairTimeStamp* tsdata = static_cast<FairTimeStamp*>(obj);
  if (tsdata > 0) {
    return static_cast<Int_t>(tsdata->GetTimeStamp());
  } else {
    return 0;
  }
}
