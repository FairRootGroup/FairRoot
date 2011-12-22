#include "FairTimeStamp.h"

// -----   Default constructor   -------------------------------------------
FairTimeStamp::FairTimeStamp()
  : FairMultiLinkedData(),
    fTimeStamp(-1), fTimeStampError(-1)
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

void FairTimeStamp::Print(std::ostream& out) const
{
  out << "Entry: (" << fEntryNr.GetFile()<< "/" << fEntryNr.GetEntry() << "/" << fEntryNr.GetType() << "/" << fEntryNr.GetType() << "/" << fEntryNr.GetIndex() << ") "
      << "TimeStamp: " << GetTimeStamp() << " +/- " << GetTimeStampError() << std::endl;
  FairMultiLinkedData::Print(out);
}
ClassImp(FairTimeStamp)
