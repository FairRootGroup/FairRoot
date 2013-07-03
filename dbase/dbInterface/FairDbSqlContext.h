

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


    enum  IntervalType { kBefore,      kAfter,    kMisses,
                         kThroughout,  kWithin,   kOverlaps,
                         kStarts,      kEnds,
                         kUndefined
                       };


    FairDbSqlContext(const std::string& ctxt = "");
    FairDbSqlContext(IntervalType interval,
                     ValTimeStamp start,
                     ValTimeStamp end,
                     Detector::Detector_t det,
                     SimFlag::SimFlag_t sim);

    virtual ~FairDbSqlContext();


    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    Detector::Detector_t     GetDetector()  const { return fDetType; }
    SimFlag::SimFlag_t       GetSimFlag()   const { return fSimType; }



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

