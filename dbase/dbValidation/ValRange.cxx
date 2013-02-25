
#include "ValRange.h"
#include "ValContext.h"


ClassImp(ValRange)

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const ValRange& vldr)
{
  return os << vldr.AsString();
}

//_____________________________________________________________________________
ValRange::ValRange()
  : fDetectorMask(0), fSimMask(0),
    fTimeStart(), fTimeEnd(), fDataSource("unknown")
{
  // Default constructor
}
//_____________________________________________________________________________
ValRange::ValRange(const Int_t detMask, const Int_t simMask,
                   const ValTimeStamp& tstart,
                   const ValTimeStamp& tend,
                   const TString& source)
  : fDetectorMask(detMask), fSimMask(simMask),
    fTimeStart(tstart), fTimeEnd(tend), fDataSource(source)
{
  // normal constructor
}

//_____________________________________________________________________________
ValRange::~ValRange()
{
  // delete all the owned sub-objects

}

//_____________________________________________________________________________
const char* ValRange::AsString(Option_t* option) const
{
  // Return the ValRange as a string
  //
  // Result is a pointer to a statically allocated string.
  // User should copy this into their own buffer before calling
  // this method again.
  //
  // option "a": give detector/simflag masks as alpha chars
  // option "c": compact (single line)
  // option "s": drop nsec part of times
  // option "1": include only "start time"
  // option "-": don't include "source" info

  static char newstring[255] = " ";

  TString opt = option;
  opt.ToLower();

  Bool_t opt_a = opt.Contains("a");
  Bool_t opt_c = opt.Contains("c");

  TString detbits;
  if (opt_a) {
    detbits = Detector::MaskToString(fDetectorMask);
  } else {
    sprintf(newstring,"det %#4.4x",fDetectorMask);
    detbits = newstring;
  }

  TString simbits;
  if (opt_a) {
    simbits = SimFlag::MaskToString(fSimMask);
  } else {
    sprintf(newstring,"sim %#4.4x",fSimMask);
    simbits = newstring;
  }

  // ValTimeStamp::AsString returns pointer to statically allocated string
  // one needs to copy this before calling it again in same function call
  static char timeopt[4] = "c  ";
  timeopt[0] = (opt.Contains("s")?'s':'c');
  TString start_str = fTimeStart.AsString(timeopt);
  TString end_str;
  if ( ! opt.Contains("1")) {
    end_str = fTimeEnd.AsString(timeopt);
    if ( !opt_c ) { end_str.Prepend("\n\t "); }
    else { end_str.Prepend(" "); }
  }
  if ( ! opt_c ) { start_str.Prepend("\n\t "); }

  TString source;
  if ( ! opt.Contains("-")) {
    source +=  (opt_c) ? " '" : "\n\t from source: ";
    source += fDataSource;
    source +=  (opt_c) ? "'" : "";
  }

  sprintf(newstring,
          "|%s|%s|%s%s%s",
          (const char*)detbits,
          (const char*)simbits,
          (const char*)start_str,
          (const char*)end_str,
          (const char*)source);

  return newstring;
}

//_____________________________________________________________________________
Bool_t ValRange::IsCompatible(const ValContext& vldc) const
{
  // compare ValContext with this ValRange to see if the
  // the tagged set is compatible

  Int_t detector = (Int_t)vldc.GetDetector();
  Int_t simflag  = (Int_t)vldc.GetSimFlag();

  // account for case where both ValContext and ValRange
  // are using "kUnknown" which has no bits set
  if ( ! (detector & fDetectorMask) &&
       (detector      != Detector::kUnknown ||
        fDetectorMask != Detector::kUnknown    ) ) { return kFALSE; }
  if ( ! (simflag  & fSimMask) &&
       (simflag  != SimFlag::kUnknown ||
        fSimMask != SimFlag::kUnknown   ) ) { return kFALSE; }

  // the start time is taken as inclusive, but the end time is exclusive

  if ( vldc.GetTimeStamp() <  fTimeStart ) { return kFALSE; }
  if ( vldc.GetTimeStamp() >= fTimeEnd   ) { return kFALSE; }

  return kTRUE;
}

//_____________________________________________________________________________
Bool_t ValRange::IsCompatible(const ValContext* vldc) const
{
  // compare ValContext with this ValRange to see if the
  // the tagged set is compatible

  return IsCompatible(*vldc);
}

//_____________________________________________________________________________
void ValRange::Print(Option_t* option) const
{
  // Print this object

  printf("%s\n",AsString(option));
}

//_____________________________________________________________________________
void ValRange::TrimTo(const ValRange& vldr)
{
  // Trim this range to the intersection (ie. more restricted)
  // limits of it's initial value and that of the argument

  fDetectorMask &= vldr.fDetectorMask;
  fSimMask      &= vldr.fSimMask;
  if (fTimeStart < vldr.fTimeStart) { fTimeStart = vldr.fTimeStart; }
  if (fTimeEnd   > vldr.fTimeEnd  ) { fTimeEnd   = vldr.fTimeEnd; }
  if (!fDataSource.Contains(vldr.fDataSource)) {
    fDataSource   += ", ";
    fDataSource   += vldr.fDataSource;
  }
}

//_____________________________________________________________________________
