#ifndef FAIRDBWRITER_H
#define FAIRDBWRITER_H

#include <list>
#include <string>

#include "FairDb.h"
#include "FairDbLogEntry.h"
#include "FairDbTableProxyRegistry.h"
#include "ValRange.h"
#include "ValTimeStamp.h"

class FairDbSqlValPacket;
class FairDbTableProxy;
class FairDbValidityRec;

template <class T> class FairDbWriter
{

  public:

// Constructors and destructors.
    FairDbWriter();
    FairDbWriter(const ValRange& vr,
                 Int_t aggNo,
                 FairDb::Task task,
                 ValTimeStamp creationDate,
                 const std::string& dbName,
                 const std::string& logComment = "",
                 const std::string& tableName = "");
    FairDbWriter(const ValRange& vr,
                 Int_t aggNo,
                 FairDb::Task task = 0,
                 ValTimeStamp creationDate = ValTimeStamp(0,0),
                 UInt_t dbNo = 0,
                 const std::string& logComment = "",
                 const std::string& tableName = "");
    FairDbWriter(const FairDbValidityRec& vrec,
                 const std::string& dbName,
                 const std::string& logComment = "");
    FairDbWriter(const FairDbValidityRec& vrec,
                 UInt_t dbNo = 0,
                 const std::string& logComment = "");

    virtual ~FairDbWriter();

// State testing member functions

    FairDbTableProxy& TableProxy() const;

///    Open and ready to receive data.
    Bool_t IsOpen(Bool_t reportErrors = kTRUE) const;
///    Open and ready to receive/output data.
    Bool_t CanOutput(Bool_t reportErrors = kTRUE) const;

// State changing member functions

    void SetDbNo(UInt_t dbNo) { fDbNo = dbNo;}
    void SetDbName(const string& dbName);
    void SetLogComment(const std::string& reason);
    // For setting of requireGlobal see FairDbCascader::AllocateSeqNo
    void SetRequireGlobalSeqno(Int_t requireGlobal) {fRequireGlobalSeqno = requireGlobal;}
    void SetOverlayCreationDate() {fUseOverlayCreationDate = kTRUE;}

//  I/O functions
    void Abort() { Reset(); }
    Bool_t Close(const char* fileSpec=0);
    Bool_t Open(const ValRange& vr,
                Int_t aggNo,
                FairDb::Task task,
                ValTimeStamp creationDate,
                const string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const ValRange& vr,
                Int_t aggNo,
                FairDb::Task task = 0,
                ValTimeStamp creationDate = ValTimeStamp(),
                UInt_t dbNo = 0,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValidityRec& vrec,
                const string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValidityRec& vrec,
                UInt_t dbNo = 0,
                const std::string& logComment = "");

    FairDbWriter<T>& operator<<(const T& row);

  private:

// State testing member functions

    Bool_t NeedsLogEntry() const;
    Bool_t WritingToMaster() const;

// State changing member functions

    FairDbWriter(const FairDbWriter&); // Forbidden
    FairDbWriter& operator=(const FairDbWriter&); // Forbidden

    void CompleteOpen(UInt_t dbNo = 0,
                      const std::string& logComment = "");
    void Reset();

    static FairDbTableProxy& GetTableProxy();
    static FairDbTableProxy& GetTableProxy(const std::string& tableName);

// Data members

/// Aggregate noumber for set.
    Int_t fAggregateNo;

///Database number in cascade
    UInt_t fDbNo;

/// The assembled record to be output. Never null.
    FairDbSqlValPacket* fPacket;

/// Controls SEQNO type (see FairDbCascader::AllocateSeqNo)
    Int_t fRequireGlobalSeqno;

/// Proxy to associated table.
    FairDbTableProxy* fTableProxy;

/// Associated table name.
    std::string fTableName;

/// Use overlay creation date if true.
    Bool_t fUseOverlayCreationDate;

/// Validity record. May be =0 if closed.
    FairDbValidityRec* fValidRec;

/// Associated log entry (if any) for update
    FairDbLogEntry fLogEntry;

    ClassDefT(FairDbWriter<T>,0)          // Writer for specific database table.

};
ClassDefT2(FairDbWriter,T)

#endif  // FAIRDBWRITER_H
