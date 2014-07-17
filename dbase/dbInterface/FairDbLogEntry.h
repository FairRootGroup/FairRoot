/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGENTRY_H
#define FAIRDBLOGENTRY_H

#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector

#include "FairDb.h"                     // for Version

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "DataType.h"                    // for FullMask
#include "TObject.h"                    // for TObject

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairDbOutTableBuffer;
class FairDbResultPool;
class FairDbValRecord;

class FairDbLogEntry : public FairDbObjTableMap
{

  public:

    using TObject::Write;

    FairDbLogEntry(const std::string& tableName = "",
                   const std::string& reason = "",
                   Int_t detMask = Detector::FullMask(),
                   Int_t simMask = DataType::FullMask(),
                   FairDb::Version task = 0,
                   Int_t logSeqNoMin = 0,
                   Int_t logSeqNoMax = 0,
                   Int_t logNumSeqNo = 0);
    virtual ~FairDbLogEntry();

    virtual FairDbObjTableMap* CreateObjTableMap() const {
      return new FairDbLogEntry;
    }
    Int_t GetAggregateNo() const { return -1; }


    const std::string& GetLogTableName() const { return fLogTableName; }
    Int_t GetDetectorMask() const { return fLogDetMask; }
    Int_t GetLogSeqNoMin() const { return fLogSeqNoMin; }
    Int_t GetLogSeqNoMax() const { return fLogSeqNoMax; }
    Int_t GetLogNumSeqNo() const { return fLogNumSeqNo; }
    Int_t GetSimMask() const { return fLogSimMask; }
    FairDb::Version GetVersion() const { return fLogVersion; }
    const std::string& GetUserName() const { return fUserName; }
    const std::string& GetProcessName() const { return fProcessName; }
    const std::string& GetHostName() const { return fHostName; }
    const std::string& GetServerName() const { return fServerName; }
    const std::string& GetReason() const { return fReason; }
    ValTimeStamp GetUpdateTime() const { return fUpdateTime; }

    Bool_t HasReason() const { return fReason.size() > 0; }

    void SetReason(const std::string& reason);
    void SetDetectorMask(Int_t detMask) { fLogDetMask = detMask; }
    void SetSimMask(Int_t simMask) { fLogSimMask = simMask; }
    void SetVersion(FairDb::Version task) { fLogVersion = task; }
    void SetUpdateTime(const ValTimeStamp& updateTime) {
      fUpdateTime = updateTime;
    }
    void Recreate (const std::string& tableName = "",
                   const std::string& reason = "",
                   Int_t detMask = Detector::FullMask(),
                   Int_t simMask = DataType::FullMask(),
                   FairDb::Version task = 0,
                   Int_t logSeqNoMin = 0,
                   Int_t logSeqNoMax = 0,
                   Int_t logNumSeqNo = 0);

// I/O  member functions
    virtual void Fill(FairDbResultPool& rs,
                      const FairDbValRecord* vrec);
    virtual void Store(FairDbOutTableBuffer& ors,
                       const FairDbValRecord* vrec) const;
    Bool_t Write(UInt_t dbNo,Int_t logSeqNo=0);

  private:
    FairDbLogEntry(const FairDbLogEntry& from);

    void SetServerName();

    UInt_t fDbNo;

    Int_t fSeqNo;
    std::string fLogTableName;
    Int_t fLogDetMask;
    Int_t fLogSimMask;
    FairDb::Version fLogVersion;
    Int_t fLogSeqNoMin;
    Int_t fLogSeqNoMax;
    Int_t fLogNumSeqNo;
    ValTimeStamp fUpdateTime;
    std::string fUserName;
    std::string fProcessName;
    std::string fHostName;
    std::string fServerName;
    std::string fReason;

    ClassDef(FairDbLogEntry,0)    // Global Log Entry

};

std::ostream& operator<<(std::ostream& s, const FairDbLogEntry& logEntry);

#endif  // FAIRDBLOGENTRY_H
