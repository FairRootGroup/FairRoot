/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/


#ifndef FAIRDBEXTSQLCONTENT
#define FAIRDBEXTSQLCONTENT


#include "FairDbString.h"               // for FairDbString
#include "DataType.h"                    // for DataType_t
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for FairDbDetector, etc

#include "Rtypes.h"                     // for FairDbExtSqlContent::Class, etc

#include <string>                       // for string

class FairDbExtSqlContent : public FairDbString
{

  public:


    enum  IntervalType { kBefore,      kAfter,    kMisses,
                         kThroughout,  kWithin,   kOverlaps,
                         kStarts,      kEnds,
                         kUndefined
                       };


    FairDbExtSqlContent(const std::string& ctxt = "");
    FairDbExtSqlContent(IntervalType interval,
                        ValTimeStamp start,
                        ValTimeStamp end,
                        FairDbDetector::Detector_t det,
                        DataType::DataType_t sim);

    virtual ~FairDbExtSqlContent();


    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    FairDbDetector::Detector_t     GetDetector()  const { return fDetType; }
    DataType::DataType_t       GetDataType()   const { return fSimType; }



  private:

    IntervalType             fIntervalType;
    ValTimeStamp             fTimeStart;
    ValTimeStamp             fTimeEnd;
    FairDbDetector::Detector_t     fDetType;
    DataType::DataType_t       fSimType;


    ClassDef(FairDbExtSqlContent,0)     // SQL for Extended Content Query

};


#endif // FAIRDBEXTSQLCONTENT

