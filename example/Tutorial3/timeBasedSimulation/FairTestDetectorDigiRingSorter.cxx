/*
 * FairTestDetectorDigiRingSorter.cxx
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#include "FairTestDetectorDigiRingSorter.h"

#include "FairTestDetectorDigi.h"       // for FairTestDetectorDigi

class FairTimeStamp;

ClassImp(FairTestDetectorDigiRingSorter);


FairTestDetectorDigiRingSorter::~FairTestDetectorDigiRingSorter()
{
  // TODO Auto-generated destructor stub
}

FairTimeStamp* FairTestDetectorDigiRingSorter::CreateElement(FairTimeStamp* data)
{
  return new FairTestDetectorDigi(*(FairTestDetectorDigi*)data);
}
