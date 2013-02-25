#ifndef FAIRDBLOGENTRY_H
#define FAIRDBLOGENTRY_H


#include <string>
using std::string;
#include <iosfwd>

#include "TObject.h"

#include "FairDb.h"
#include "Detector.h"
#include "SimFlag.h"
#include "FairDbTableRow.h"
#include "ValTimeStamp.h"

class FairDbLogEntry;
class FairDbOutRowStream;
class FairDbResultSet;
class FairDbTableProxy;
class FairDbValidityRec;

std::ostream& operator<<(std::ostream& s, const FairDbLogEntry& logEntry);

class FairDbLogEntry : public FairDbTableRow
{

  public:

    using TObject::Write;

// Constructors and destructors.
    FairDbLogEntry(const string& tableName = "",
                   const string& reason = "",
                   Int_t detMask = Detector::FullMask(),
                   Int_t simMask = SimFlag::FullMask(),
                   FairDb::Task task = 0,
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
    const string& GetLogTableName() const { return fLogTableName; }
    Int_t GetDetectorMask() const { return fLogDetMask; }
    Int_t GetLogSeqNoMin() const { return fLogSeqNoMin; }
    Int_t GetLogSeqNoMax() const { return fLogSeqNoMax; }
    Int_t GetLogNumSeqNo() const { return fLogNumSeqNo; }
    Int_t GetSimMask() const { return fLogSimMask; }
    FairDb::Task GetTask() const { return fLogTask; }
    const string& GetUserName() const { return fUserName; }
    const string& GetProcessName() const { return fProcessName; }
    const string& GetHostName() const { return fHostName; }
    const string& GetServerName() const { return fServerName; }
    const string& GetReason() const { return fReason; }
    ValTimeStamp GetUpdateTime() const { return fUpdateTime; }

    Bool_t HasReason() const { return fReason.size() > 0; }

// State changing member functions
    void SetReason(const string& reason);
    void SetDetectorMask(Int_t detMask) { fLogDetMask = detMask; }
    void SetSimMask(Int_t simMask) { fLogSimMask = simMask; }
    void SetTask(FairDb::Task task) { fLogTask = task; }
    void SetUpdateTime(const ValTimeStamp& updateTime) {
      fUpdateTime = updateTime;
    }
    void Recreate (const string& tableName = "",
                   const string& reason = "",
                   Int_t detMask = Detector::FullMask(),
                   Int_t simMask = SimFlag::FullMask(),
                   FairDb::Task task = 0,
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
// Constructors and destructors.
    FairDbLogEntry(const FairDbLogEntry& from); // No!

    void SetServerName();

// Data members

/// Database no. written to. =0 if not output
    UInt_t fDbNo;

/// Seq. No. used to write this object. =0 if not output
    Int_t fSeqNo;

/// Table being updated.
    string fLogTableName;

/// Detector type mask of update.
    Int_t fLogDetMask;

/// SimFlag  mask of update.
    Int_t fLogSimMask;

/// Task of update
    FairDb::Task fLogTask;

/// Minimum Seq. No. being updated.
    Int_t fLogSeqNoMin;

/// Maximum Seq. No. being updated.
    Int_t fLogSeqNoMax;

/// Number of Seq. Nos. being updated.
    Int_t fLogNumSeqNo;

/// Time of update.
    ValTimeStamp fUpdateTime;

/// User performing update.
    string fUserName;

/// Process performing update.
    string fProcessName;

/// Host performing update.
    string fHostName;

/// Db server being updated.
    string fServerName;

/// Reason for update.
    string fReason;


// Note: fLogDetMask,fLogSimMask,fLogTask,fUpdateTime are used to construct the FairDbValidityRec
//       of the update; they are not store in main table.

    ClassDef(FairDbLogEntry,0)    // Configuration data.

};


#endif  // FAIRDBLOGENTRY_H
