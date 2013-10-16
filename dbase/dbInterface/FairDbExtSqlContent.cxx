
#include "FairDbExtSqlContent.h"


ClassImp(FairDbExtSqlContent)

FairDbExtSqlContent::FairDbExtSqlContent(const std::string& ctxt)
  : FairDbString(ctxt),
    fIntervalType(kUndefined),
    fTimeStart(),
    fTimeEnd(),
    fDetType(Detector::kUnknown),
    fSimType(DataType::kUnknown)
{

}

FairDbExtSqlContent::FairDbExtSqlContent(IntervalType interval,
    ValTimeStamp start,
    ValTimeStamp end,
    Detector::Detector_t det,
    DataType::DataType_t sim)
  : FairDbString(),
    fIntervalType(interval),
    fTimeStart(start),
    fTimeEnd(end),
    fDetType(det),
    fSimType(sim)
{

  switch (interval) {

  case kBefore:
    (*this) <<     "TIMEEND <= \'"   << start.AsString("s") << '\'';
    break;

  case kAfter:
    (*this) <<     "TIMESTART >= \'" << end.AsString("s")   << '\'';
    break;

  case kMisses:
    (*this) <<     "TIMESTART >= \'" << end.AsString("s")   << '\''
            << " or TIMEEND <= \'"   << start.AsString("s") << '\'';
    break;

  case kThroughout:
    (*this) <<     "TIMESTART <= \'" << start.AsString("s") << '\''
            << " and TIMEEND >= \'"  << end.AsString("s")   << '\'';
    break;

  case kWithin:
    (*this) <<     "TIMESTART >= \'" << start.AsString("s") << '\''
            << " and TIMEEND <= \'"  << end.AsString("s")   << '\'';
    break;

  case kOverlaps:
    (*this) <<     "TIMESTART < \'"  << end.AsString("s")   << '\''
            << " and TIMEEND > \'"   << start.AsString("s") << '\'';
    break;

  case kStarts:
    (*this) <<     "TIMESTART >= \'" << start.AsString("s") << '\''
            << " and TIMESTART < \'" << end.AsString("s")   << '\'';
    break;

  case kEnds:
    (*this) <<     "TIMEEND > \'"    << start.AsString("s") << '\''
            << " and TIMEEND <=  \'" << end.AsString("s")   << '\'';
    break;

  default:
    (*this) << " 1 = 0 ";
  }

  (*this) << " and DetectorMask & " << static_cast<unsigned int>(fDetType)
          << " and SimMask & "      << static_cast<unsigned int>(fSimType);
}



FairDbExtSqlContent::~FairDbExtSqlContent()
{

}
