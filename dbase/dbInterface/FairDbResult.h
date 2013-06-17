#ifndef FAIRDBRESULT_H
#define FAIRDBRESULT_H

#include "TObject.h"                    // for TObject

#include "FairDb.h"                     // for DbTypes, DataTypes, Version
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbRowStream.h"            // for FairDbRowStream
#include "FairDbValidityRec.h"          // for FairDbValidityRec
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for UInt_t, Bool_t, Int_t, etc
#include "TString.h"                    // for TString

#include <iosfwd>                       // for ostream
#include <list>                         // for list
#include <map>                          // for map, map<>::value_compare
#include <string>                       // for string, basic_string, etc
#include <vector>                       // for vector

class FairDbBinaryFile;
class FairDbCache;
class FairDbProxy;
class FairDbStatement;
class FairDbString;
class FairDbTableMetaData;
class FairDbTableProxy;
class FairDbTableRow;
class FairDbValidityRecBuilder;
class TSQLStatement;
class ValContext;
class FairDbStreamer;

//------------------------- Result Key --------------------------------//
class FairDbResultKey : public TObject
{

  public:

    using TObject::Compare;

    // Constructors and destructors.
    FairDbResultKey(const FairDbResultKey* that = 0);
    FairDbResultKey(std::string tableName,
                    std::string rowName,
                    UInt_t seqno,
                    ValTimeStamp ts);
    virtual ~FairDbResultKey();

    std::string AsString() const;
    Float_t Compare(const FairDbResultKey* that) const;
    static const FairDbResultKey*
    GetEmptyKey() { return &fgEmptyKey; }
    Int_t GetNumVrecs() const { return fNumVRecKeys; }
    std::string GetTableRowName() const;
    Bool_t IsEqualTo(const FairDbResultKey* that) const {
      return this->Compare(that) == 1.;
    }

    // State changing member functions

    void AddVRecKey(UInt_t seqno, ValTimeStamp ts);

    // push this put to the public: portion so that rootcint dict compiles
    struct VRecKey {
      VRecKey() : SeqNo(0), CreationDate() {}
      VRecKey(UInt_t seqno, ValTimeStamp ts) : SeqNo(seqno), CreationDate(ts) {}
      UInt_t SeqNo;
      ValTimeStamp CreationDate;
    };

  private:

    static FairDbResultKey fgEmptyKey;
    std::string fTableName;
    std::string fRowName;
    std::list<FairDbResultKey::VRecKey> fVRecKeys;
    Int_t fNumVRecKeys;

    ClassDef(FairDbResultKey,1)

};

std::ostream& operator<<(std::ostream& os, const FairDbResultKey& key);

//---------------------- Result Set-------------------------------------//
class FairDbResultSet : public FairDbRowStream
{
  public:

// Constructors and destructors.
    FairDbResultSet(FairDbStatement* stmtDb,
                    const FairDbString& sql,
                    const FairDbTableMetaData* metaData,
                    const FairDbTableProxy* tableProxy,
                    UInt_t dbNo,
                    const std::string& fillOpts = "");
    virtual ~FairDbResultSet();

// State testing member functions
    Bool_t CurColExists() const;
    std::string CurColString() const;
    std::string CurColValue() const { LoadCurValue(); return fValString;}
    UInt_t CurRowNum() const { return fCurRow;}
    UInt_t GetDbNo() const { return fDbNo; }
    FairDb::DbTypes GetDBType() const { return fDbType; }
    std::string GetFillOpts() const { return fFillOpts;}
    const FairDbTableProxy* GetTableProxy() const { return fTableProxy; }
/// IsBeforeFirst not needed for ROOT API, but leave a dummy
/// for now so as not to disturb FairDbResultSet API.
    Bool_t IsBeforeFirst() const { return false; };
    Bool_t IsExhausted() const { return fExhausted; }
    void RowAsCsv(std::string& row) const;

// State changing member functions

    FairDbResultSet& operator>>(Bool_t& dest);
    FairDbResultSet& operator>>(Char_t& dest);
    FairDbResultSet& operator>>(Short_t& dest);
    FairDbResultSet& operator>>(UShort_t& dest);
    FairDbResultSet& operator>>(Int_t& dest);
    FairDbResultSet& operator>>(UInt_t& dest);
    FairDbResultSet& operator>>(Long_t& dest);
    FairDbResultSet& operator>>(ULong_t& dest);
    FairDbResultSet& operator>>(Float_t& dest);
    FairDbResultSet& operator>>(Double_t& dest);
    FairDbResultSet& operator>>(std::string& dest);
    FairDbResultSet& operator>>(ValTimeStamp& dest);
    FairDbResultSet& operator>>(FairDbStreamer& dest);

    Bool_t FetchRow();

  private:

    std::string& AsString(FairDb::DataTypes type);
    Bool_t LoadCurValue() const;
    TString GetStringFromTSQL(Int_t col) const;
    Int_t fCurRow;
    UInt_t fDbNo;
    FairDb::DbTypes fDbType;
    FairDbStatement* fStatement;
    TSQLStatement* fTSQLStatement;
    Bool_t fExhausted;
    const FairDbTableProxy* fTableProxy;
    mutable  std::string fValString;
    std::string fFillOpts;

    FairDbResultSet(const FairDbResultSet&);
    FairDbResultSet operator=(const FairDbResultSet&);

    ClassDef(FairDbResultSet,0)     //ResultSet from Query to database table

};

//------------------------- Main Result class ---------------------------//

typedef std::map<UInt_t,const FairDbTableRow*> IndexToRow_t;

class FairDbResult
{

  public:

    // Constructors and destructors.
    FairDbResult(FairDbResultSet* resultSet = 0,
                 const FairDbValidityRec* vrec = 0,
                 const std::string& sqlQualifiers = "");
    //    FairDbResult& operator=(const FairDbResult&);
    FairDbResult(const FairDbResult&);
    virtual ~FairDbResult();

    // State testing member functions

    virtual                Bool_t CanReuse() const  { return fCanReuse; }
    virtual                Bool_t CanSave() const  { return kTRUE; }
    virtual                  void Connect() const { ++fNumClients; }
    virtual         FairDbResultKey* CreateKey() const = 0;
    virtual                  void Disconnect() const { --fNumClients; }
    Int_t GetID() const { return fID; }
    virtual   const FairDbResultKey* GetKey() const;
    virtual                UInt_t GetNumAggregates() const =0;
    virtual                UInt_t GetNumClients() const {
      return fNumClients;
    }
    virtual                UInt_t GetNumRows() const =0;
    const std::string& GetSqlQualifiers() const { return fSqlQualifiers; }
    virtual    const FairDbTableRow* GetTableRow(UInt_t rowNum) const =0;
    virtual    const FairDbTableRow* GetTableRowByIndex(UInt_t index) const;
    virtual const FairDbValidityRec& GetValidityRec(
      const FairDbTableRow* row = 0) const {
      return GetValidityRecGlobal();
    }
    virtual const FairDbValidityRec& GetValidityRecGlobal() const {
      return fEffVRec;
    }
    Bool_t IsExtendedContext() const {
      return this->GetSqlQualifiers() != "";
    }
    virtual  Bool_t Owns(const FairDbTableRow* table) const { return kFALSE; }
    Bool_t ResultsFromDb() const { return fResultsFromDb; }
    virtual const std::string& TableName() const { return fTableName; }

    virtual Bool_t CanDelete(const FairDbResult* res = 0);

    virtual Bool_t Satisfies(const ValContext& vc,
                             const FairDb::Version& task);
    virtual  Bool_t Satisfies(const std::string&) {return kFALSE;}
    virtual  Bool_t Satisfies(const FairDbValidityRec&,
                              const std::string& = "") {return kFALSE;}

    virtual void DeRegisterKey();
    virtual void RegisterKey();

    virtual void Streamer(FairDbBinaryFile& file);
    virtual void SetCanReuse(Bool_t reuse)  { fCanReuse = reuse ; }
    void CaptureExceptionLog(UInt_t startFrom);
  protected:
    void SetResultsFromDb() { fResultsFromDb = kTRUE; }
    void BuildLookUpTable() const;
    Bool_t LookUpBuilt() const { return fIndexKeys.size() > 0; }
    virtual void SetTableName(const std::string& tableName)  {
      fTableName = tableName;
    }
    virtual void SetValidityRec(const FairDbValidityRec& vRec)  {
      fEffVRec = vRec;
    }




  private:

    Int_t fID;
    Bool_t fCanReuse;
    FairDbValidityRec fEffVRec;
    mutable IndexToRow_t fIndexKeys;
    const FairDbResultKey* fKey;
    Bool_t fResultsFromDb;
    mutable Int_t fNumClients;
    std::string fTableName;
    std::string fSqlQualifiers;
    static  Int_t fgLastID;
    FairDbExceptionLog fExceptionLog;

    FairDbResult& operator=(const FairDbResult&);

    ClassDef(FairDbResult,0)     //Abstract base representing query result

};
FairDbBinaryFile& operator<<(FairDbBinaryFile& bf, const FairDbResult& res);
FairDbBinaryFile& operator>>(FairDbBinaryFile& bf, FairDbResult& res);




//------------------------------- Result Aggregat ---------------------//
class FairDbResultAgg : public FairDbResult
{
  public:
// Only some Satisfies methods are overriden so include base class ones.
    using FairDbResult::Satisfies;

// Constructors and destructors.
    FairDbResultAgg(const std::string& tableName = "Unknown",
                    const FairDbTableRow* tableRow = 0,
                    FairDbCache* cache = 0,
                    const FairDbValidityRecBuilder* vrecBuilder = 0,
                    const FairDbProxy* proxy=0,
                    const std::string& sqlQualifiers = "" );
    virtual ~FairDbResultAgg();

// State testing member functions

    virtual   FairDbResultKey* CreateKey() const;
    virtual   UInt_t GetNumAggregates() const {
      return 1 + fResults.size();
    };
    virtual   UInt_t GetNumRows() const {
      return fSize;
    }
    virtual const FairDbTableRow* GetTableRow(UInt_t row) const;
    virtual const FairDbValidityRec& GetValidityRec(
      const FairDbTableRow* row=0) const;

//  State changing member functions.
    virtual     Bool_t Satisfies(const std::string& sqlQualifiers);
    virtual void Streamer(FairDbBinaryFile& bf);


  private:
    std::vector<const FairDbResult*>   fResults;
    std::vector<const FairDbTableRow*> fRowKeys;
    UInt_t fSize;

    ClassDef(FairDbResultAgg,0)     // Results table of aggregated data.

};





//---------------------- Result Non Aggregat ----------------------------//

class FairDbResultNonAgg : public FairDbResult
{
  public:

// Only some Satisfies methods are overriden so include base class ones.
    using FairDbResult::Satisfies;


// Constructors and destructors.
    FairDbResultNonAgg(FairDbResultSet* resultSet = 0,
                       const FairDbTableRow* tableRow = 0,
                       const FairDbValidityRec* vrec = 0,
                       Bool_t dropSeqNo = kTRUE,
                       const std::string& sqlQualifiers = "");
    virtual ~FairDbResultNonAgg();



    virtual  FairDbResultKey* CreateKey() const;
    virtual                UInt_t GetNumAggregates() const { return 1; }
    virtual                UInt_t GetNumRows() const {
      return fRows.size();
    }
    virtual    const FairDbTableRow* GetTableRow(UInt_t rowNum) const;
    virtual    const FairDbTableRow* GetTableRowByIndex(UInt_t index) const;

    virtual Bool_t Owns(const FairDbTableRow* row ) const;
    Bool_t Satisfies(const FairDbValidityRec& vrec,
                     const std::string& sqlQualifiers = "");
    virtual void   Streamer(FairDbBinaryFile& file);

  private:

    void DebugCtor() const;

    std::vector<FairDbTableRow*> fRows;
    Char_t* fBuffer;

    FairDbResultNonAgg(const FairDbResultNonAgg&);
    FairDbResultNonAgg operator=(const FairDbResultNonAgg&);

    ClassDef(FairDbResultNonAgg,0)     // Non-aggregated data

};



#endif  // FAIRDBRESULT_H
