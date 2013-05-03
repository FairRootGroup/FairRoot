

#ifndef FAIRDBSQLCONTEXT
#define FAIRDBSQLCONTEXT


#include "FairDbString.h"               // for FairDbString
#include "SimFlag.h"                    // for SimFlag_t
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector, etc

#include "Rtypes.h"                     // for FairDbSqlContext::Class, etc

#include <string>                       // for string

class FairDbSqlContext : public FairDbString
{

  public:


// Types and enum

    enum  IntervalType { kBefore,      kAfter,    kMisses,
                         kThroughout,  kWithin,   kOverlaps,
                         kStarts,      kEnds,
                         kUndefined
                       };

// Constructors and destructors.
    FairDbSqlContext(const std::string& ctxt = "");
    FairDbSqlContext(IntervalType interval,
                     ValTimeStamp start,
                     ValTimeStamp end,
                     Detector::Detector_t det,
                     SimFlag::SimFlag_t sim);

    virtual ~FairDbSqlContext();

// State testing member functions

    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    Detector::Detector_t     GetDetector()  const { return fDetType; }
    SimFlag::SimFlag_t       GetSimFlag()   const { return fSimType; }


// State changing member functions

  private:

// Data members

    IntervalType             fIntervalType;
    ValTimeStamp             fTimeStart;
    ValTimeStamp             fTimeEnd;
    Detector::Detector_t     fDetType;
    SimFlag::SimFlag_t       fSimType;


    ClassDef(FairDbSqlContext,0)     // SQL for Extended Context Query

};


#endif // FAIRDBSQLCONTEXT

