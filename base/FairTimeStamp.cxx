#include "FairTimeStamp.h"

// -----   Default constructor   -------------------------------------------
FairTimeStamp::FairTimeStamp()
  : FairMultiLinkedData(),
    fTimeStamp(0), fTimeStampError(-1)
{
}
// -----   Standard constructor   ------------------------------------------
FairTimeStamp::FairTimeStamp(Double_t time)
  :FairMultiLinkedData(),
   fTimeStamp(time), fTimeStampError(-1)
{
}

FairTimeStamp::FairTimeStamp(Double_t time, Double_t timeerror)
  :FairMultiLinkedData(),
   fTimeStamp(time), fTimeStampError(timeerror)
{
}
// -----   Destructor   ----------------------------------------------------
FairTimeStamp::~FairTimeStamp()
{
}

// -------------------------------------------------------------------------
ClassImp(FairTimeStamp)
