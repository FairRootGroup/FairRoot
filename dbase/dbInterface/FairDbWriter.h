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

    FairDbWriter();

    FairDbWriter(const ValRange& vr,
                 Int_t aggNo,
                 FairDb::Version task,
                 ValTimeStamp creationDate,
                 const std::string& dbName,
                 const std::string& logComment = "",
                 const std::string& tableName = "");

    FairDbWriter(const ValRange& vr,
                 Int_t aggNo,
                 FairDb::Version task = 0,
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

    FairDbTableProxy& TableProxy() const;

    Bool_t IsOpen(Bool_t reportErrors = kTRUE) const;
    Bool_t CanOutput(Bool_t reportErrors = kTRUE) const;

    void SetDbNo(UInt_t dbNo) { fDbNo = dbNo;}
    void SetDbName(const std::string& dbName);
    void SetLogComment(const std::string& reason);
    void SetContObj(T* cont_obj) { fContObj = cont_obj;}

    void SetRequireGlobalSeqno(Int_t requireGlobal) {fRequireGlobalSeqno = requireGlobal;}
    void SetOverlayCreationDate() {fUseOverlayCreationDate = kTRUE;}

//  I/O functions
    void Abort() { Reset(); }
    Bool_t Close(const char* fileSpec=0);
    Bool_t Open(const ValRange& vr,
                Int_t aggNo,
                FairDb::Version task,
                ValTimeStamp creationDate,
                const std::string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const ValRange& vr,
                Int_t aggNo,
                FairDb::Version task = 0,
                ValTimeStamp creationDate = ValTimeStamp(),
                UInt_t dbNo = 0,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValidityRec& vrec,
                const std::string& dbName,
                const std::string& logComment = "");
    Bool_t Open(const FairDbValidityRec& vrec,
                UInt_t dbNo = 0,
                const std::string& logComment = "");

    FairDbWriter<T>& operator<<(const T& row);

  private:

    Bool_t NeedsLogEntry() const;
    Bool_t WritingToMaster() const;

    FairDbWriter(const FairDbWriter&); // Forbidden
    FairDbWriter& operator=(const FairDbWriter&); // Forbidden

    void CompleteOpen(UInt_t dbNo = 0,
                      const std::string& logComment = "");
    void Reset();

    static FairDbTableProxy& GetTableProxy();
    static FairDbTableProxy& GetTableProxy(const std::string& tableName);

// Data members
    Int_t fAggregateNo;
    UInt_t fDbNo;
    FairDbSqlValPacket* fPacket;
    Int_t fRequireGlobalSeqno;
    FairDbTableProxy* fTableProxy;
    std::string fTableName;
    Bool_t fUseOverlayCreationDate;
    FairDbValidityRec* fValidRec;
    FairDbLogEntry fLogEntry;
    T* fContObj;  ///

    ClassDefT(FairDbWriter<T>,0)          // Writer for specific database table.

};
ClassDefT2(FairDbWriter,T)

#endif  // FAIRDBWRITER_H
