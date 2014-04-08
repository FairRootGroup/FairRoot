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



FairTimeStamp::FairTimeStamp(const FairTimeStamp &TimeStamp) :
  FairMultiLinkedData(), fTimeStamp(TimeStamp.fTimeStamp), fTimeStampError(TimeStamp.fTimeStampError), fEntryNr(TimeStamp.fEntryNr)
//  fTimeStamp(TimeStamp.fTimeStamp), fTimeStampError(TimeStamp.fTimeStampError), fEntryNr(TimeStamp.fEntryNr)

{
    
}


// -----   Destructor   ----------------------------------------------------
FairTimeStamp::~FairTimeStamp()
{
}

// -------------------------------------------------------------------------

std::ostream& FairTimeStamp::Print(std::ostream& out) const
{
  out << "EntryNr of Data: " << fEntryNr << " TimeStamp: " << GetTimeStamp() << " +/- " << GetTimeStampError() << std::endl;
  FairMultiLinkedData::Print(out);

  return out;
}
ClassImp(FairTimeStamp)
