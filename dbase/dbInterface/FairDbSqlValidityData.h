/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBSQLVALIDITYDATA
#define FAIRDBSQLVALIDITYDATA

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

class FairDbTableInterface;
class FairDbObjTableMap;
class FairDbValRecord;
class ValInterval;

class FairDbSqlValidityData
{

  public:

    typedef enum ECompResult {
      kIdentical,
      kUpdate,
      kOutOfDate,
      kConflict
    } CompResult_t;

    FairDbSqlValidityData();
    FairDbSqlValidityData(std::ifstream& is);
    FairDbSqlValidityData(const FairDbValRecord& vrec);
    virtual ~FairDbSqlValidityData();

    Bool_t CanBeStored() const {
      return (fSeqNo > 0 && fNumErrors == 0 && this->GetNumSqlStmts()> 0)
             ? kTRUE : kFALSE;
    };
    CompResult_t Compare(const FairDbSqlValidityData& that,
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
    Bool_t IsEqual(const FairDbSqlValidityData& that,
                   Bool_t log = kFALSE,
                   const Char_t* thisName = "this",
                   const Char_t* thatName = "that" ) const;

//  I/O
    Bool_t Fill(std::ifstream& is);
    Bool_t Store(UInt_t dbNo, Bool_t replace = kFALSE) const;
    Bool_t Write(std::ofstream& ios,
                 Bool_t addMetadata = kFALSE) const;

    void Recreate(const std::string& tableName,
                  const ValInterval& vr,
                  Int_t aggNo,
                  FairDb::Version task = 0,
                  ValTimeStamp creationDate = ValTimeStamp());
    Bool_t AddDataRow(const FairDbTableInterface& tblProxy,
                      const FairDbValRecord* vrec,
                      const FairDbObjTableMap& row);

    void Clear() { this->Reset(); fNumErrors = 0; }
    void SetCreationDate(ValTimeStamp ts);
    void SetSeqNo(UInt_t seqno);
    void Reset();  //Doesn't clear fNumErrors.

    virtual void Print(Option_t* option="") const;

  protected:

  private:
    void AddRow(const std::string& row);
    Bool_t AddRow(const FairDbTableInterface& tblProxy,
                  const FairDbValRecord* vrec,
                  const FairDbObjTableMap& row);
    void Report(const char* msg,
                UInt_t line_num,
                const std::string& line);
    void SetMetaData() const;
    void SetSeqNoOnRow(std::string& row,const std::string& seqno);

    static Bool_t fgLastMetaHadRowCounter;
    FairDbSqlValidityData(const FairDbSqlValidityData& );


    UInt_t fNumErrors;
    UInt_t fSeqNo;
    mutable std::string fSqlMySqlMetaMain;
    mutable std::string fSqlMySqlMetaVal;
    std::list<std::string>  fSqlStmts;
    UInt_t fNumStmts;
    std::string fTableName;
    ValTimeStamp fCreationDate;

    ClassDef(FairDbSqlValidityData,0)           // SQL to generate Validity Data Stream

};
#endif  // FAIRDBSQLVALIDITYDATA
