/**
 * TestDetectorPayload.h
 *
 *  @since 2013-04-22
 *  @author A. Rybalchenko
 */

#ifndef TESTDETECTORPAYLOAD_H_
#define TESTDETECTORPAYLOAD_H_

#include <string>
#include "FairTestDetectorDigi.h"
#include "TString.h"


namespace TestDetectorBranch
{

// branch names
const TString TestDetectorDigis = "FairTestDetectorDigi";
const TString TestDetectorHits = "FairTestDetectorHit";

}


namespace TestDetectorPayload
{

// common base classes

class TimeStamp
{
  public:
    Double_t fTimeStamp;
    Double_t fTimeStampError;
};

class TestDetectorDigi : public TimeStamp
{
  public:
    Int_t fX;
    Int_t fY;
    Int_t fZ;
};

class TestDetectorHit : public TimeStamp
{
  public:
    Int_t detID;
    Int_t mcindex;
    Double_t posX;
    Double_t posY;
    Double_t posZ;
    Double_t dposX;
    Double_t dposY;
    Double_t dposZ;
};

}

#endif /* TESTDETECTORPAYLOAD_H_ */
