#include "FairTimeStamp.h"

// -----   Default constructor   -------------------------------------------
FairTimeStamp::FairTimeStamp()
  : FairMultiLinkedData(),
    fTimeStamp(-1),
    fTimeStampError(-1),
    fEntryNr()
{
}
// -----   Standard constructor   ------------------------------------------
FairTimeStamp::FairTimeStamp(Double_t time)
  : FairMultiLinkedData(),
    fTimeStamp(time),
    fTimeStampError(-1),
    fEntryNr()
{
}

FairTimeStamp::FairTimeStamp(Double_t time, Double_t timeerror)
  : FairMultiLinkedData(),
    fTimeStamp(time),
    fTimeStampError(timeerror),
    fEntryNr()
{
}
// -----   Destructor   ----------------------------------------------------
FairTimeStamp::~FairTimeStamp()
{
}

// -------------------------------------------------------------------------

void FairTimeStamp::Print(std::ostream& out) const
{
  out << "EntryNr of Data: " << fEntryNr << " TimeStamp: " << GetTimeStamp() << " +/- " << GetTimeStampError() << std::endl;
  FairMultiLinkedData::Print(out);
}
ClassImp(FairTimeStamp)
