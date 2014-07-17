/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBRESULT_H
#define FAIRDBRESULT_H

#include "TObject.h"                    // for TObject

#include "FairDb.h"                     // for DbTypes, DataTypes, Version
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbTableBuffer.h"            // for FairDbTableBuffer
#include "FairDbValRecord.h"          // for FairDbValRecord
#include "ValTimeStamp.h"               // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for UInt_t, Bool_t, Int_t, etc
#include "TString.h"                    // for TString

#include <iosfwd>                       // for ostream
#include <list>                         // for list
#include <map>                          // for map, map<>::value_compare
#include <string>                       // for string, basic_string, etc
#include <vector>                       // for vector

class FairDbBufferFile;
class FairDbCache;
class FairDbProxy;
class FairDbStatement;
class FairDbString;
class FairDbTableMetaData;
class FairDbTableInterface;
class FairDbObjTableMap;
class FairDbValRecordFactory;
class TSQLStatement;
class ValCondition;
class FairDbStreamer;


class FairDbResultKey : public TObject
{

  public:

    using TObject::Compare;

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
    std::string GetObjTableMapName() const;
    Bool_t IsEqualTo(const FairDbResultKey* that) const {
      return this->Compare(that) == 1.;
    }
    void AddVRecKey(UInt_t seqno, ValTimeStamp ts);

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



class FairDbResultPool : public FairDbTableBuffer
{
  public:

    FairDbResultPool(FairDbStatement* stmtDb,
                     const FairDbString& sql,
                     const FairDbTableMetaData* metaData,
                     const FairDbTableInterface* tableProxy,
                     UInt_t dbNo,
                     const std::string& fillOpts = "");
    virtual ~FairDbResultPool();


    Bool_t CurColExists() const;
    std::string CurColString() const;
    std::string CurColValue() const { LoadCurValue(); return fValString;}
    UInt_t CurRowNum() const { return fCurRow;}
    UInt_t GetCurrentRowNo() const {return fCurRow;}
    UInt_t GetDbNo() const { return fDbNo; }
    FairDb::DbTypes GetDBType() const { return fDbType; }
    std::string GetFillOpts() const { return fFillOpts;}
    const FairDbTableInterface* GetTableInterface() const { return fTableInterface; }

    Bool_t IsBeforeFirst() const { return false; };
    Bool_t IsExhausted() const { return fExhausted; }
    Bool_t IsCompleted() const {return fExhausted;}
    void RowAsCsv(std::string& row) const;


    FairDbResultPool& operator>>(Bool_t& dest);
    FairDbResultPool& operator>>(Char_t& dest);
    FairDbResultPool& operator>>(Short_t& dest);
    FairDbResultPool& operator>>(UShort_t& dest);
    FairDbResultPool& operator>>(Int_t& dest);
    FairDbResultPool& operator>>(UInt_t& dest);
    FairDbResultPool& operator>>(Long_t& dest);
    FairDbResultPool& operator>>(ULong_t& dest);
    FairDbResultPool& operator>>(Float_t& dest);
    FairDbResultPool& operator>>(Double_t& dest);
    FairDbResultPool& operator>>(std::string& dest);
    FairDbResultPool& operator>>(ValTimeStamp& dest);
    FairDbResultPool& operator>>(FairDbStreamer& dest);

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
    const FairDbTableInterface* fTableInterface;
    mutable  std::string fValString;
    std::string fFillOpts;

    FairDbResultPool(const FairDbResultPool&);
    FairDbResultPool operator=(const FairDbResultPool&);

    ClassDef(FairDbResultPool,0)     //ResultPool from Query to database table

};


typedef std::map<UInt_t,const FairDbObjTableMap*> IndexToRow_t;

class FairDbResult
{
  public:

    FairDbResult(FairDbResultPool* resultSet = 0,
                 const FairDbValRecord* vrec = 0,
                 const std::string& sqlQualifiers = "");
    //    FairDbResult& operator=(const FairDbResult&);
    FairDbResult(const FairDbResult&);
    virtual ~FairDbResult();


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
    virtual    const FairDbObjTableMap* GetObjTableMap(UInt_t rowNum) const =0;
    virtual    const FairDbObjTableMap* GetObjTableMapByIndex(UInt_t index) const;
    virtual const FairDbValRecord& GetValidityRec(
      const FairDbObjTableMap* row = 0) const {
      return GetValidityRecGlobal();
    }
    virtual const FairDbValRecord& GetValidityRecGlobal() const {
      return fEffVRec;
    }
    Bool_t IsExtendedContext() const {
      return this->GetSqlQualifiers() != "";
    }
    virtual  Bool_t Owns(const FairDbObjTableMap* table) const { return kFALSE; }
    Bool_t ResultsFromDb() const { return fResultsFromDb; }
    virtual const std::string& TableName() const { return fTableName; }

    virtual Bool_t CanDelete(const FairDbResult* res = 0);

    virtual Bool_t Satisfies(const ValCondition& vc,
                             const FairDb::Version& task);
    virtual  Bool_t Satisfies(const std::string&) {return kFALSE;}
    virtual  Bool_t Satisfies(const FairDbValRecord&,
                              const std::string& = "") {return kFALSE;}

    virtual void DeRegisterKey();
    virtual void RegisterKey();

    virtual void Streamer(FairDbBufferFile& file);
    virtual void SetCanReuse(Bool_t reuse)  { fCanReuse = reuse ; }
	// ELog
    const FairDbExceptionLog& GetErrorLog() const { return fExceptionLog; }
    void CaptureExceptionLog(UInt_t startFrom);
  protected:
    void SetResultsFromDb() { fResultsFromDb = kTRUE; }
    void BuildLookUpTable() const;
    Bool_t LookUpBuilt() const { return fIndexKeys.size() > 0; }
    virtual void SetTableName(const std::string& tableName)  {
      fTableName = tableName;
    }
    virtual void SetValidityRec(const FairDbValRecord& vRec)  {
      fEffVRec = vRec;
    }

  private:

    Int_t fID;
    Bool_t fCanReuse;
    FairDbValRecord fEffVRec;
    mutable IndexToRow_t fIndexKeys;
    const FairDbResultKey* fKey;
    Bool_t fResultsFromDb;
    mutable Int_t fNumClients;
    std::string fTableName;
    std::string fSqlQualifiers;
    static  Int_t fgLastID;
    FairDbExceptionLog fExceptionLog;

    FairDbResult& operator=(const FairDbResult&);

    ClassDef(FairDbResult,0)     //API for  query result

};

FairDbBufferFile& operator<<(FairDbBufferFile& bf, const FairDbResult& res);
FairDbBufferFile& operator>>(FairDbBufferFile& bf, FairDbResult& res);





class FairDbResultCombo : public FairDbResult
{
  public:
    using FairDbResult::Satisfies;

    FairDbResultCombo(const std::string& tableName = "Unknown",
                      const FairDbObjTableMap* tableRow = 0,
                      FairDbCache* cache = 0,
                      const FairDbValRecordFactory* vrecFactory = 0,
                      const FairDbProxy* proxy=0,
                      const std::string& sqlQualifiers = "" );
    virtual ~FairDbResultCombo();


    virtual   FairDbResultKey* CreateKey() const;
    virtual   UInt_t GetNumAggregates() const {
      return 1 + fResults.size();
    };
    virtual   UInt_t GetNumRows() const {
      return fSize;
    }
    virtual const FairDbObjTableMap* GetObjTableMap(UInt_t row) const;
    virtual const FairDbValRecord& GetValidityRec(
      const FairDbObjTableMap* row=0) const;

    virtual     Bool_t Satisfies(const std::string& sqlQualifiers);
    virtual void Streamer(FairDbBufferFile& bf);


  private:
    std::vector<const FairDbResult*>   fResults;
    std::vector<const FairDbObjTableMap*> fRowKeys;
    UInt_t fSize;

    ClassDef(FairDbResultCombo,0)     // Results table of composite data.

};




class FairDbResultNonCombo : public FairDbResult
{
  public:

    using FairDbResult::Satisfies;


    FairDbResultNonCombo(FairDbResultPool* resultSet = 0,
                         const FairDbObjTableMap* tableRow = 0,
                         const FairDbValRecord* vrec = 0,
                         Bool_t dropSeqNo = kTRUE,
                         const std::string& sqlQualifiers = "");
    virtual ~FairDbResultNonCombo();



    virtual  FairDbResultKey* CreateKey() const;
    virtual                UInt_t GetNumAggregates() const { return 1; }
    virtual                UInt_t GetNumRows() const {
      return fRows.size();
    }
    virtual    const FairDbObjTableMap* GetObjTableMap(UInt_t rowNum) const;
    virtual    const FairDbObjTableMap* GetObjTableMapByIndex(UInt_t index) const;

    virtual Bool_t Owns(const FairDbObjTableMap* row ) const;
    Bool_t Satisfies(const FairDbValRecord& vrec,
                     const std::string& sqlQualifiers = "");
    virtual void   Streamer(FairDbBufferFile& file);

  private:

    void DebugCtor() const;

    std::vector<FairDbObjTableMap*> fRows;
    Char_t* fBuffer;

    FairDbResultNonCombo(const FairDbResultNonCombo&);
    FairDbResultNonCombo operator=(const FairDbResultNonCombo&);

    ClassDef(FairDbResultNonCombo,0)     // Non-composite data

};



#endif  // FAIRDBRESULT_H
