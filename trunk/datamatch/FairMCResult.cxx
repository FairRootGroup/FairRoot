/*
 * FairMCResult.cpp
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#include "FairMCResult.h"

ClassImp(FairMCResult);

FairMCResult::FairMCResult()
  : FairMCObject(),
    fStartType(-1),
    fStopType(-1)
{
}

FairMCResult::~FairMCResult()
{
}

FairMCResult::FairMCResult(Int_t start, Int_t stop)
  : FairMCObject(),
    fStartType(start),
    fStopType(stop)
{
}

