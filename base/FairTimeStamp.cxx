#include "FairTimeStamp.h"

// -----   Default constructor   -------------------------------------------
FairTimeStamp::FairTimeStamp()
: FairMultiLinkedData(),
  fTimeStamp(0)
{
}
// -----   Standard constructor   ------------------------------------------
FairTimeStamp::FairTimeStamp(Double_t time)
  :FairMultiLinkedData(),
   fTimeStamp(time)
{
}

// -----   Destructor   ----------------------------------------------------
FairTimeStamp::~FairTimeStamp() 
{
}

// -------------------------------------------------------------------------
ClassImp(FairTimeStamp)
