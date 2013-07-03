#ifndef FAIRDBLOGENTRY_H
#define FAIRDBLOGENTRY_H

#include "FairDbTableRow.h"             // for FairDbTableRow
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector

#include "FairDb.h"                     // for Version

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "SimFlag.h"                    // for FullMask
#include "TObject.h"                    // for TObject

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairDbOutRowStream;
class FairDbResultSet;
class FairDbValidityRec;

class FairDbLogEntry : public FairDbTableRow
{

  public:

    using TObject::Write;

// Constructors and destructors.
    FairDbLogEntry(const std::string& tableName = "",
                   const std::string& reason = "",
                   Int_t detMask = Detector::FullMask(),
                   Int_t simMask = SimFlag::FullMask(),
                   FairDb::Version task = 0,
                   Int_t logSeqNoMin = 0,
                   Int_t logSeqNoMax = 0,
                   Int_t logNumSeqNo = 0);
    virtual ~FairDbLogEntry();

// State testing member functions.

// Inherited responsibilities.
    virtual FairDbTableRow* CreateTableRow() const {
      return new FairDbLogEntry;
    }
    Int_t GetAggregateNo() const { return -1; }

// New member functions.
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

// State changing member functions
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
                   Int_t simMask = SimFlag::FullMask(),
                   FairDb::Version task = 0,
                   Int_t logSeqNoMin = 0,
                   Int_t logSeqNoMax = 0,
                   Int_t logNumSeqNo = 0);

// I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec);
    virtual void Store(FairDbOutRowStream& ors,
                       const FairDbValidityRec* vrec) const;
    Bool_t Write(UInt_t dbNo,Int_t logSeqNo=0);

  private:
    FairDbLogEntry(const FairDbLogEntry& from);

    void SetServerName();

// Data members
// Database no. written to. =0 if not output
    UInt_t fDbNo;
// Seq. No. used to write this object. =0 if not output
    Int_t fSeqNo;
// Table being updated.
    std::string fLogTableName;
// Detector type mask of update.
    Int_t fLogDetMask;
// SimFlag  mask of update.
    Int_t fLogSimMask;
// Version of update
    FairDb::Version fLogVersion;
// Minimum Seq. No. being updated.
    Int_t fLogSeqNoMin;
// Maximum Seq. No. being updated.
    Int_t fLogSeqNoMax;
// Number of Seq. Nos. being updated.
    Int_t fLogNumSeqNo;
// Time of update.
    ValTimeStamp fUpdateTime;
// User performing update.
    std::string fUserName;
// Process performing update.
    std::string fProcessName;
// Host performing update.
    std::string fHostName;
// Db server being updated.
    std::string fServerName;
// Reason for update.
    std::string fReason;

    ClassDef(FairDbLogEntry,0)    // Log Entry

};

std::ostream& operator<<(std::ostream& s, const FairDbLogEntry& logEntry);

#endif  // FAIRDBLOGENTRY_H
