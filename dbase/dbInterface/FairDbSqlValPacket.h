#ifndef FAIRDBSQLVALPACKET
#define FAIRDBSQLVALPACKET

#include "FairDb.h"                     // for Version

#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Riosfwd.h"                    // for ifstream, ofstream
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Bool_t, UInt_t, kFALSE, etc
#endif

#include <fstream>                      // for ifstream, ofstream
#include <list>                         // for list
#include <string>                       // for string
#include <vector>                       // for vector

class FairDbTableProxy;
class FairDbTableRow;
class FairDbValidityRec;
class ValRange;

class FairDbSqlValPacket
{

  public:

// Types and enum

    typedef enum ECompResult {
      kIdentical,
      kUpdate,
      kOutOfDate,
      kConflict
    } CompResult_t;

// Constructors and destructors.
    FairDbSqlValPacket();
    FairDbSqlValPacket(std::ifstream& is);
    FairDbSqlValPacket(const FairDbValidityRec& vrec);
    virtual ~FairDbSqlValPacket();

// State testing member functions
    Bool_t CanBeStored() const {
      return (fSeqNo > 0 && fNumErrors == 0 && this->GetNumSqlStmts()> 0)
             ? kTRUE : kFALSE;
    };
    CompResult_t Compare(const FairDbSqlValPacket& that,
                         Bool_t log = kFALSE,
                         const Char_t* thisName = "this",
                         const Char_t* thatName = "that" ) const;
    Bool_t CreateTable(UInt_t dbNo) const;
    UInt_t GetNumErrors() const { return fNumErrors; }
    UInt_t GetNumSqlStmts() const { return fNumStmts; }
    UInt_t GetSeqNo() const { return fSeqNo; }
    ValTimeStamp GetCreationDate() const { return fCreationDate; }
    std::string GetStmt(UInt_t stmtNo) const;
    std::vector<std::string> GetStmtValues(UInt_t stmtNo) const;
    const std::string& GetTableName() const { return fTableName; }
    Bool_t IsEqual(const FairDbSqlValPacket& that,
                   Bool_t log = kFALSE,
                   const Char_t* thisName = "this",
                   const Char_t* thatName = "that" ) const;

//  I/O
    Bool_t Fill(std::ifstream& is);
    Bool_t Store(UInt_t dbNo, Bool_t replace = kFALSE) const;
    Bool_t Write(std::ofstream& ios,
                 Bool_t addMetadata = kFALSE) const;

//  Reconstruct.
    void Recreate(const std::string& tableName,
                  const ValRange& vr,
                  Int_t aggNo,
                  FairDb::Version task = 0,
                  ValTimeStamp creationDate = ValTimeStamp());
    Bool_t AddDataRow(const FairDbTableProxy& tblProxy,
                      const FairDbValidityRec* vrec,
                      const FairDbTableRow& row);

//  State changing member functions
    void Clear() { this->Reset(); fNumErrors = 0; }
    void SetCreationDate(ValTimeStamp ts);
    void SetSeqNo(UInt_t seqno);
    void Reset();  //Doesn't clear fNumErrors.

    virtual void Print(Option_t* option="") const;

  protected:

  private:
    void AddRow(const std::string& row);
    Bool_t AddRow(const FairDbTableProxy& tblProxy,
                  const FairDbValidityRec* vrec,
                  const FairDbTableRow& row);
    void Report(const char* msg,
                UInt_t line_num,
                const std::string& line);
    void SetMetaData() const;
    void SetSeqNoOnRow(std::string& row,const std::string& seqno);

    static Bool_t fgLastMetaHadRowCounter;  // Ugly hack during transition to ROW_COUNTER tables.
    FairDbSqlValPacket(const FairDbSqlValPacket& );  // Not allowed.


// Data members

/// Number of error encountered while filling.
    UInt_t fNumErrors;

/// Sequence number or 0 if not filled.
    UInt_t fSeqNo;

/// MySQL SQL to create main table. May be empty until needed.
    mutable std::string fSqlMySqlMetaMain;

/// As fSqlMySqlMetaMain but for aux. table.
    mutable std::string fSqlMySqlMetaVal;

/// Set of SQL statements to generate packet.
    std::list<std::string>  fSqlStmts;

/// Number of statements
    UInt_t fNumStmts;

/// Table name or null if not filled.
    std::string fTableName;

/// Creation date, or object creation date if unfilled.
    ValTimeStamp fCreationDate;

    ClassDef(FairDbSqlValPacket,0)           // SQL to generate Validity Packet.

};
#endif  // FAIRDBSQLVALPACKET
