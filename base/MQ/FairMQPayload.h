/**
 * FairMQPayload.h
 *
 *  @since 2013-04-22
 *  @author A. Rybalchenko
 */

#ifndef FAIRMQPAYLOAD_H_
#define FAIRMQPAYLOAD_H_

#include <string>
#include "FairMQDigi.h"
#include "TString.h"

/*
namespace TestDetectorBranch
{

// branch names
const TString TestDetectorDigis2 = "FairTestDetectorDigi";
const TString TestDetectorHits2 = "FairTestDetectorHit";

}
*/

namespace FairMQPayload
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

#endif /* FAIRMQPAYLOAD_H_ */
