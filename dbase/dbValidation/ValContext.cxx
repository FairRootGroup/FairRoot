#include "ValContext.h"


ClassImp(ValContext)


ValContext::ValContext()
  :  fDetector(Detector::kUnknown),
     fSimFlag(SimFlag::kUnknown),
     fTimeStamp()
{
  // Default constructor (unknown experiment, simflag, timestamp=now)
}

ValContext::~ValContext() { ; }




//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const ValContext& vldc)
{
  if (os.good()) {
    if (os.tie()) { os.tie()->flush(); } // instead of opfx
    os << vldc.AsString();
  }
  // instead of os.osfx()
  if (os.flags() & std::ios::unitbuf) { os.flush(); }
  return os;
}

//_____________________________________________________________________________
ValContext::ValContext(const Detector::Detector_t& detector,
                       const SimFlag::SimFlag_t mcFlag,
                       const ValTimeStamp& tstamp)
  : TObject(),
    fDetector(detector),
    fSimFlag(mcFlag),
    fTimeStamp(tstamp)
{
  // normal constructor
}

//_____________________________________________________________________________
const char* ValContext::AsString(Option_t* option) const
{
  // Return a formatted string of the contents of this object
  // User should copy result because it points to a
  // statically allocated string.

  static char newstring[80] = " ";

  switch (option[0]) {
  case 'c':
  case 'C':
    sprintf(newstring,"{%c%c %s}",
            Detector::AsString(GetDetector())[0],
            SimFlag::AsString(GetSimFlag())[0],
            fTimeStamp.AsString("c"));
    break;
  default:
    sprintf(newstring,"{%6.6s|%6.6s|%s}",
            Detector::AsString(GetDetector()),
            SimFlag::AsString(GetSimFlag()),
            fTimeStamp.AsString("c"));
  }

  return newstring;
}

//_____________________________________________________________________________
void ValContext::Print(Option_t* option) const
{
  printf("%s\n",AsString(option));
}

//_____________________________________________________________________________
Bool_t ValContext::IsNull() const
{
  // Return true if this was initialized by default ctor
  // we can only test detector type and simflag
  return fDetector==Detector::kUnknown && fSimFlag == SimFlag::kUnknown;

}

//_____________________________________________________________________________

