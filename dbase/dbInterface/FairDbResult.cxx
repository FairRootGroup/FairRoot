/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbResult.h"
#include "FairDbLogService.h"
#include "FairDbBufferFile.h"           // for string, FairDbBufferFile
#include "FairDbCache.h"                // for FairDbCache
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbFieldType.h"            // for FairDbFieldType
#include "FairDbProxy.h"                // for FairDbProxy
#include "FairDbStatement.h"            // for FairDbStatement
#include "FairDbString.h"               // for FairDbString, MakePrintable
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "FairDbStopWatchManager.h"         // for FairDbStopWatchManager, etc
#include "FairDbValRecordFactory.h"   // for FairDbValRecordFactory
#include "ValInterval.h"                   // for ValInterval
#include "ValTimeStamp.h"               // for ValTimeStamp, operator==, etc

#include "FairDbStreamer.h"               // 
#include "TBufferFile.h"
#include "FairUtilStream.h"

#include "TSQLStatement.h"              // for TSQLStatement

#include <stddef.h>                     // for NULL
#include <algorithm>                    // for sort
#include <iostream>                     // for cout
#include <sstream>                      // for operator<<, basic_ostream, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::ostringstream;
using std::istringstream;
using std::string;

// ------------------------- Result Pool  Implementation ---------------------------------

ClassImp(FairDbResultPool)


FairDbResultPool::FairDbResultPool(FairDbStatement* stmtDb,
                                   const FairDbString& sql,
                                   const FairDbTableMetaData* metaData,
                                   const FairDbTableInterface* tableProxy,
                                   UInt_t dbNo,
                                   const string& fillOpts) :
  FairDbTableBuffer(metaData),
  fCurRow(0),
  fDbNo(dbNo),
  fDbType(FairDb::kMySQL),
  fStatement(stmtDb),
  fTSQLStatement(0),
  fExhausted(true),
  fTableInterface(tableProxy),
  fValString(),
  fFillOpts(fillOpts)
{

  if ( stmtDb ) {
    fDbType = stmtDb->GetDBType();
    fTSQLStatement = stmtDb->ExecuteQuery(sql.c_str());
    if ( fTSQLStatement && fTSQLStatement->NextResultRow() ) { fExhausted = false; }
  }

}

FairDbResultPool::~FairDbResultPool()
{
  delete fTSQLStatement;
  fTSQLStatement = 0;
  delete fStatement;
  fStatement = 0;

}

#define INSTREAMER(t) istringstream in(AsString(t)); in

#define INSTREAMER2(t,m)                            \
  int col = CurColNum()-1;                  \
  if ( CurRowNum() == 0 ) {                 \
    istringstream in(AsString(t));          \
    in >> dest;                             \
  }                                         \
  else {                                    \
    dest = fTSQLStatement->m(col);          \
    IncrementCurCol();                      \
  }                                         \
 
#define INSTREAMER3(t)                                                      \
int col = this->CurColNum()-1;                                      \
const FairDbFieldType& fType = this->ColFieldType(col+1);              \
if ( fType.GetSize() == 8 ) {                                       \
  dest=fTSQLStatement->GetUInt(col);            \
}                                                                   \
else {                                                              \
  t dest_signed;                                                    \
  *this >> dest_signed;                                             \
  dest = dest_signed;                                               \
  if ( fType.GetSize() == 1 ) dest &= 0xff;                         \
  if ( fType.GetSize() == 2 ) dest &= 0xffff;                       \
  if ( fType.GetSize() == 4 ) dest &= 0xffffffff;                   \
}\
 
FairDbResultPool& FairDbResultPool::operator>>(Bool_t& dest)
{
  INSTREAMER(FairDb::kBool) >> dest;
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Char_t& dest)
{
  INSTREAMER(FairDb::kChar) >> dest;
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Short_t& dest)
{
  INSTREAMER2(FairDb::kInt,GetInt);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(UShort_t& dest)
{
  INSTREAMER3(Short_t);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Int_t& dest)
{
  INSTREAMER2(FairDb::kInt,GetInt);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(UInt_t& dest)
{
  INSTREAMER3(Int_t);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Long_t& dest)
{
  INSTREAMER2(FairDb::kLong, GetLong);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(ULong_t& dest)
{
  INSTREAMER3(Long_t);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Float_t& dest)
{
  INSTREAMER2(FairDb::kFloat,GetDouble);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(Double_t& dest)
{
  INSTREAMER2(FairDb::kDouble,GetDouble);
  return *this;
}


FairDbResultPool& FairDbResultPool::operator>>(string& dest)
{
  dest = AsString(FairDb::kString);
  return *this;
}
FairDbResultPool& FairDbResultPool::operator>>(ValTimeStamp& dest)
{
  dest=FairDb::MakeTimeStamp(AsString(FairDb::kDate));
  return *this;
}

FairDbResultPool& FairDbResultPool::operator>>(FairDbStreamer& dest)
{
  // Streamer operator for DB basic types
  string db_str =  AsString(FairDb::kString);
  dest.SetString(db_str);
  return *this;
}

string& FairDbResultPool::AsString(FairDb::DataTypes type)
{

  FairDbFieldType  reqdt(type);

//  Place table value string in value string buffer.
  Bool_t fail = ! LoadCurValue();
// Internally columns number from zero.
  UInt_t col = CurColNum();
  IncrementCurCol();

  if ( fail ) {
    string udef = reqdt.UndefinedValue();
    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "... value \"" << udef
        << "\" will be substitued." <<  endl;
    fValString = udef;
    return fValString;
  }

//  Check for compatibility with required data type.

  const FairDbFieldType& actdt = MetaData()->ColFieldType(col);

  if ( reqdt.IsCompatible(actdt) ) {
    Bool_t smaller = reqdt.IsSmaller(actdt);
//  Allow one character String to be stored in Char
    if ( reqdt.GetConcept() == FairDb::kChar && fValString.size() == 1
       ) { smaller = kFALSE; }
    if ( smaller  ) {

      MAXDBLOG("FairDb",FairDbLog::kWarning,20)
          << "In table " << TableNameTc()
          << " row " << fCurRow
          << " column "<< col
          << " (" << MetaData()->ColName(col) << ")"
          << " value \"" << fValString
          << "\" of type " << actdt.AsString()
          << " may be truncated before storing in " << reqdt.AsString()
          <<  endl;
    }
  } else {
    string udef = reqdt.UndefinedValue();
    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "In table " << TableNameTc()
        << " row " << fCurRow
        << " column "<< col
        << " (" << MetaData()->ColName(col) << ")"
        << " value \"" << fValString
        << "\" of type " << actdt.AsString()
        << " is incompatible with user type " << reqdt.AsString()
        << ", value \"" << udef
        << "\" will be substituted." <<  endl;
    fValString = udef;
  }

  return fValString;
}

Bool_t FairDbResultPool::CurColExists() const
{

  Int_t col = CurColNum();

  if ( IsExhausted() ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "In table " << TableNameTc()
        << " attempting to access row " << fCurRow
        << " column " << col
        << " but only " << fCurRow << " rows in table."  << endl;
    return kFALSE;
  }

  int numCols = NumCols();
  if ( col > numCols ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20)
        << "In table " << TableNameTc()
        << " row " << fCurRow
        << " attempting to access column "<< col
        << " but only " << NumCols() << " in table ."  << endl;
    return kFALSE;
  }

  return kTRUE;

}
string FairDbResultPool::CurColString() const
{

  if ( ! CurColExists() ) { return ""; }

  TString valStr = this->GetStringFromTSQL(CurColNum());
  return valStr.Data();

}

Bool_t FairDbResultPool::FetchRow()
{
  ClearCurCol();
  if ( IsExhausted() ) { return kFALSE; }
  ++fCurRow;
  if ( ! fTSQLStatement->NextResultRow() ) { fExhausted = true; }
  return ! fExhausted;

}
TString FairDbResultPool::GetStringFromTSQL(Int_t col) const
{
  TString valStr = fTSQLStatement->GetString(col-1);
  if (    this->GetDBType() == FairDb::kOracle
          && this->ColFieldType(col).GetConcept() == FairDb::kString ) {
    DBLOG("FairDb",FairDbLog::kInfo)  <<
                                      "ORACLE string conversion from: " << valStr << endl;
    valStr.ReplaceAll("\\n", "\n");
    valStr.ReplaceAll("\\t", "\t");
    valStr.ReplaceAll("\\\'","\'");
    valStr.ReplaceAll("\\\"","\"");
    valStr.ReplaceAll("\\\\","\\");
    DBLOG("FairDb",FairDbLog::kInfo) << "                           to: " << valStr <<endl;
  }
  return valStr;
}
Bool_t FairDbResultPool::LoadCurValue() const
{

  fValString.clear();

  if ( ! CurColExists() ) { return kFALSE; }

  Int_t col = CurColNum();
  TString valStr = this->GetStringFromTSQL(col);

  if ( CurColFieldType().GetConcept() == FairDb::kFloat ) {
    ostringstream out;
    if ( CurColFieldType().GetType() == FairDb::kDouble ) { ; }
    out << fTSQLStatement->GetDouble(col-1);
    valStr = out.str().c_str();
  }
  int len = valStr.Length();

  const char* pVal = valStr.Data();
  // trailing removal
  if (    len >= 2
          && ( *pVal == *(pVal+len-1) )
          && ( *pVal == '\'' || *pVal == '"' ) ) {
    ++pVal;
    len -= 2;
  }
  fValString.assign(pVal,len);

  return kTRUE;

}
void FairDbResultPool::RowAsCsv(string& row) const
{
  const FairDbTableMetaData* md = this->MetaData();

  Int_t maxCol = this->NumCols();
  for (Int_t col = 1; col <= maxCol; ++col) {
    // Deal with NULL values.
    if ( fTSQLStatement->IsNull(col-1) ) {
      row += "NULL";
      if ( col < maxCol ) { row += ','; }
      continue;
    }
    Bool_t mustDelimit  = md->ColMustDelimit(col);
    UInt_t concept      = md->ColFieldConcept(col);
    if ( mustDelimit ) { row += '\''; }
    TString str = this->GetStringFromTSQL(col);
    const char* value = str.Data();

    if ( concept == FairDb::kString ) { FairUtilString::MakePrintable(value,row); }

    else if ( concept == FairDb::kFloat ) {
      ostringstream out;
      if ( md->ColFieldType(col).GetType() == FairDb::kDouble ) { ; }
      out << fTSQLStatement->GetDouble(col-1);
      row += out.str();
    }
    // OK
    else { row += value; }

    if ( mustDelimit ) { row += '\''; }
    if ( col < maxCol ) { row += ','; }
  }
}


ClassImp(FairDbResultKey)

FairDbResultKey FairDbResultKey::fgEmptyKey;

std::ostream& operator<<(std::ostream& os, const FairDbResultKey& key)
{
  os << key.AsString() << endl;
  return os;
}


FairDbResultKey::FairDbResultKey(const FairDbResultKey* that) :
  fTableName(),
  fRowName(),
  fVRecKeys(),
  fNumVRecKeys(0)
{
  if ( that ) { *this = *that; }
}


FairDbResultKey::FairDbResultKey(std::string tableName,
                                 std::string rowName,
                                 UInt_t seqno,
                                 ValTimeStamp ts) :
  fTableName(tableName),
  fRowName(rowName),
  fVRecKeys(),
  fNumVRecKeys(0)
{

  this->AddVRecKey(seqno,ts);
}


FairDbResultKey::~FairDbResultKey()
{
}


void FairDbResultKey::AddVRecKey(UInt_t seqno, ValTimeStamp ts)
{

  fVRecKeys.push_back(VRecKey(seqno,ts));
  ++fNumVRecKeys;

}



std::string FairDbResultKey::AsString() const
{
  ostringstream os;
  os << "Table:" << fTableName << " row:" << fRowName;
  if ( fVRecKeys.empty() ) { os << " No vrecs"; }
  else {
    os << ".  " << fNumVRecKeys << " vrec";
    if ( fNumVRecKeys > 1 ) { os << "s (seqno min..max;creationdate min..max):"; }
    else { os << " (seq_id;transaction_time):"; }
    os << " ";
    std::list<VRecKey>::const_iterator itr    = fVRecKeys.begin();
    std::list<VRecKey>::const_iterator itrEnd = fVRecKeys.end();
    UInt_t seqnoMin    = itr->SeqNo;
    UInt_t seqnoMax    = seqnoMin;
    ValTimeStamp tsMin = itr->CreationDate;
    ValTimeStamp tsMax = tsMin;
    ++itr;
    while ( itr != itrEnd ) {
      UInt_t       seqno = itr->SeqNo;
      ValTimeStamp ts    = itr->CreationDate;
      if ( seqno < seqnoMin ) { seqnoMin = seqno; }
      if ( seqno > seqnoMax ) { seqnoMax = seqno; }
      if (    ts < tsMin    ) { tsMin    = ts; }
      if (    ts > tsMax    ) { tsMax    = ts; }
      ++itr;
    }
    os << seqnoMin;
    if ( seqnoMin < seqnoMax ) { os << ".." << seqnoMax; }
    os << ";" << tsMin.AsString("s");
    if ( tsMin < tsMax ) { os << ".." <<  tsMax.AsString("s"); }
  }
  return string(os.str());

}

Float_t FairDbResultKey::Compare(const FairDbResultKey* that) const
{

  // Check in table and row names.
  if ( fTableName != that->fTableName ) { return -2.; }
  if ( fRowName   != that->fRowName   ) { return -1.; }


  DBLOG("FairDb",FairDbLog::kInfo)<< "Comparing " << *this << " to "
                                  << *that << endl;

  const FairDbResultKey* keyBig   = this;
  const FairDbResultKey* keySmall = that;
  if ( that->GetNumVrecs() > this->GetNumVrecs() ) {
    keyBig   = that;
    keySmall = this;
  }
  int numVrecs = keyBig->GetNumVrecs();
  if ( numVrecs == 0 ) { return 0.; }

  std::map<UInt_t,ValTimeStamp> seqnoToCreationDate;
  std::list<FairDbResultKey::VRecKey>::const_iterator itrEnd = keyBig->fVRecKeys.end();
  for (  std::list<FairDbResultKey::VRecKey>::const_iterator itr = keyBig->fVRecKeys.begin();
         itr != itrEnd;
         ++itr ) { seqnoToCreationDate[itr->SeqNo] = itr->CreationDate; }
  float match = 0;
  itrEnd = keySmall->fVRecKeys.end();
  for (  std::list<FairDbResultKey::VRecKey>::const_iterator itr = keySmall->fVRecKeys.begin();
         itr != itrEnd;
         ++itr ) {
    DBLOG("FairDb",FairDbLog::kInfo) << "Comparing seq_id " << itr->SeqNo << " with transaction date " << itr->CreationDate
                                     << " to " <<  seqnoToCreationDate[itr->SeqNo] << endl;
    if ( seqnoToCreationDate[itr->SeqNo] == itr->CreationDate ) { ++match; }
  }

  DBLOG("FairDb",FairDbLog::kInfo) << "Matching results: " << match << " out of " << numVrecs << endl;

  return match/numVrecs;

}


std::string FairDbResultKey::GetObjTableMapName() const
{
  ostringstream os;
  os << fTableName << "::" << fRowName;
  return os.str();

}

//--------------------------------- Result Composite Implementation --------------------------//

ClassImp(FairDbResultCombo)

typedef vector<const FairDbResult*>::const_iterator ConstResultItr_t;

FairDbResultCombo::FairDbResultCombo(const string& tableName,
                                     const FairDbObjTableMap* tableRow,
                                     FairDbCache* cache,
                                     const FairDbValRecordFactory* vrecFactory,
                                     const FairDbProxy* proxy,
                                     const string& sqlQualifiers) :
  FairDbResult(0,0,sqlQualifiers),
  fResults(),
  fRowKeys(),
  fSize(0)
{
  typedef map<UInt_t,UInt_t> seqToRow_t;

  SetTableName(tableName);
  if ( ! tableRow || ! cache || ! vrecFactory || ! proxy ) { return; }

// Caution: StringTok - removes null strings

  string::size_type loc  = sqlQualifiers.find(';');
  string::size_type loc2 = sqlQualifiers.find(';',loc+1);
  string sqlData  = string(sqlQualifiers,loc+1,loc2-loc-1);
  string fillOpts = string(sqlQualifiers,loc2+1);


  vector<UInt_t> reqSeqNos;  // Sequence numbers required from DB.
  seqToRow_t seqToRow;       // Map SeqNo - > RowNo.
  UInt_t dbNo = 0;
  Int_t maxRowNo = vrecFactory->GetNumValidityRec() - 1;


  for ( Int_t rowNo = 1; rowNo <= maxRowNo; ++rowNo ) {
    const FairDbValRecord& vrecRow = vrecFactory->GetValidityRec(rowNo);

    const FairDbResult* res = cache->Search(vrecRow,sqlQualifiers);
    DBLOG("FairDb",FairDbLog::kInfo) << "Checking validity record " << rowNo
                                     << " " << vrecRow
                                     << "SQL qual: " << sqlQualifiers
                                     << " cache search: " << (void*) res << endl;
    if ( res ) {
      fResults.push_back(res);
      res->Connect();
      fSize += res->GetNumRows();
    }

    else if ( vrecRow.IsGap() ) {
      FairDbResult* newRes = new FairDbResultNonCombo(0, tableRow, &vrecRow);
      cache->Accept(newRes,false);
      fResults.push_back(newRes);
      newRes->Connect();
    }

    else {
      UInt_t seqNo = vrecRow.GetSeqNo();
      reqSeqNos.push_back(seqNo);
      seqToRow[seqNo] = rowNo;
      fResults.push_back(0);
      dbNo = vrecRow.GetDbNo();
    }
  }


  if ( reqSeqNos.size() ) {
    sort(reqSeqNos.begin(),reqSeqNos.end());
    FairDbResultPool* rs = proxy->QuerySeqNos(reqSeqNos,dbNo,sqlData,fillOpts);
    this->SetResultsFromDb();
    FairDbStopWatchManager::gStopWatchManager.StartSubWatch(1);
    while ( ! rs->IsExhausted() ) {
      Int_t seqNo;
      *rs >> seqNo;
      rs->DecrementCurCol();
      Int_t rowNo = -2;
      if ( seqToRow.find(seqNo) == seqToRow.end() ) {

        DBLOG("FairDb",FairDbLog::kWarning)   << "Unexpected Seq_Id: " << seqNo << endl;

      } else {
        rowNo = seqToRow[seqNo];
        DBLOG("FairDb",FairDbLog::kInfo)
            << "Procesing SeqNo: " << seqNo
            << " for row " << rowNo << endl;
      }

      const FairDbValRecord& vrecRow = vrecFactory->GetValidityRec(rowNo);
      FairDbResultNonCombo* newRes = new FairDbResultNonCombo(rs,tableRow,&vrecRow);

      if ( this->IsExtendedContext() ) { newRes->SetCanReuse(false); }
      if ( rowNo == -2 ) {
        delete newRes;
      } else {
        DBLOG("FairDb",FairDbLog::kInfo)
            << "Seq_Id: " << seqNo
            << " produced " << newRes->GetNumRows() << " rows" << endl;

        cache->Accept(newRes,false);
        fResults[rowNo-1] = newRes;
        newRes->Connect();
        fSize += newRes->GetNumRows();
      }
    }

    delete rs;
  }


  fRowKeys.reserve(fSize);

  FairDbValRecord vRec = vrecFactory->GetValidityRec(1);
  for ( Int_t rowNo = 1; rowNo <= maxRowNo; ++rowNo ) {

    const FairDbValRecord& vrecRow = vrecFactory->GetValidityRec(rowNo);
    ValInterval r = vrecRow.GetValInterval();
    vRec.AndTimeWindow(r.GetTimeStart(),r.GetTimeEnd());

    const FairDbResult* res = fResults[rowNo-1];
    if ( res ) {
      UInt_t numEnt = res->GetNumRows();
      for (UInt_t entNo = 0; entNo < numEnt; ++entNo ) {
        fRowKeys.push_back(res->GetObjTableMap(entNo));
      }
    }
  }


  this->BuildLookUpTable();

  vRec.SetAggregateNo(-1);
  SetValidityRec(vRec);

  DBLOG("FairDb",FairDbLog::kInfo)
      << "Composite Data contains " << fSize  << " entries.  ValRecord:" << endl
      << vRec << endl;

  DBLOG("FairDb",FairDbLog::kInfo)  << "Created composite result set no. of rows: "
                                    << this->GetNumRows() << endl;

}
FairDbResultCombo::~FairDbResultCombo()
{

  for ( ConstResultItr_t itr = fResults.begin();
        itr != fResults.end();
        ++itr) if ( *itr ) { (*itr)->Disconnect(); }

}


FairDbResultKey* FairDbResultCombo::CreateKey() const
{

  FairDbResultKey* key = 0;
  for ( ConstResultItr_t itr = fResults.begin();
        itr != fResults.end();
        ++itr ) {
    const FairDbResult* result = *itr;
    if ( result ) {

      if ( ! key ) { key = result->CreateKey(); }

      else {
        const FairDbValRecord& vrec = result->GetValidityRec();
        key->AddVRecKey(vrec.GetSeqNo(),vrec.GetCreationDate());
      }
    }
  }


  if ( ! key ) { key = new FairDbResultKey(); }

  return key;

}

const FairDbObjTableMap* FairDbResultCombo::GetObjTableMap(UInt_t row) const
{

  return  ( row >= fRowKeys.size() ) ? 0 : fRowKeys[row];

}


const FairDbValRecord& FairDbResultCombo::GetValidityRec(
  const FairDbObjTableMap* row) const
{

  if ( ! row ) { return this->GetValidityRecGlobal(); }
  FairDbResult* owner = row->GetOwner();
  return owner ? owner->GetValidityRecGlobal() : this->GetValidityRecGlobal();

}

Bool_t FairDbResultCombo::Satisfies(const string& sqlQualifiers)
{
  DBLOG("FairDb",FairDbLog::kInfo)
      << "Trying to satisfy: SQL: " << sqlQualifiers
      << "\n with CanReuse: " << this->CanReuse()
      << " sqlQualifiers: " << this->GetSqlQualifiers()
      << endl;
  return    this->CanReuse()
            && this->GetSqlQualifiers() == sqlQualifiers;
}

void FairDbResultCombo::Streamer(FairDbBufferFile& bf)
{

  vector<const FairDbResult*>::const_iterator itr = fResults.begin();
  vector<const FairDbResult*>::const_iterator end = fResults.end();

  UInt_t numNonAgg = 0;
  for (; itr != end; ++itr) {
    const FairDbResultNonCombo* rna = dynamic_cast<const FairDbResultNonCombo*>(*itr);
    if ( rna && ! rna->GetValidityRecGlobal().IsGap() ) { ++numNonAgg; }
  }
  bf << numNonAgg;


  for (itr = fResults.begin(); itr != end; ++itr) {
    const FairDbResultNonCombo* rna = dynamic_cast<const FairDbResultNonCombo*>(*itr);
    if ( rna && ! rna->GetValidityRecGlobal().IsGap() ) { bf << *rna; }
  }
}


//------------------------------------- FairDbResult Generic Implemenation --------------//


ClassImp(FairDbResult)

Int_t FairDbResult::fgLastID(0);

FairDbBufferFile& operator<<(FairDbBufferFile& bf, const FairDbResult& res)
{
// Writing is a const operation, but uses a non-const method, so cast away const.
  FairDbResult& res_tmp = const_cast< FairDbResult&>(res);
  res_tmp.Streamer(bf);
  return bf;
}


FairDbBufferFile& operator>>(FairDbBufferFile& bf, FairDbResult& res)
{

  res.Streamer(bf);
  return bf;
}


FairDbResult::FairDbResult(FairDbResultPool* resultSet,
                           const FairDbValRecord* vrec,
                           const string& sqlQualifiers) :
  fID(++fgLastID),
  fCanReuse(kTRUE),
  fEffVRec(0),
  fIndexKeys(),
  fKey(0),
  fResultsFromDb(kFALSE),
  fNumClients(0),
  fTableName("Unknown"),
  fSqlQualifiers(sqlQualifiers),
  fExceptionLog()
{

  if ( vrec ) { fEffVRec = *vrec; }
  if ( resultSet ) { fTableName = resultSet->TableNameTc(); }

}

FairDbResult::FairDbResult(const FairDbResult& from)
  : fID(from.fID),
    fCanReuse(from.fCanReuse),
    fEffVRec(from.fEffVRec),
    fIndexKeys(from.fIndexKeys),
    fKey(from.fKey),
    fResultsFromDb(from.fResultsFromDb),
    fNumClients(from.fNumClients),
    fTableName(from.fTableName),
    fSqlQualifiers(from.fSqlQualifiers),
    fExceptionLog(from.fExceptionLog)
{

}

FairDbResult::~FairDbResult()
{
  if ( fNumClients ) {
    DBLOG("FairDb",FairDbLog::kWarning)   << "Destroying FairDbResult with " << fNumClients
                                          << " clients " << endl;
  }

  this->DeRegisterKey();

}

void FairDbResult::CaptureExceptionLog(UInt_t startFrom)
{

  fExceptionLog.Clear();
  FairDbExceptionLog::GetGELog().Copy(fExceptionLog,startFrom);

}



void FairDbResult::BuildLookUpTable() const
{
  Bool_t duplicatesOK = this->IsExtendedContext();

  DBLOG("FairDb",FairDbLog::kInfo)   << "Building lookup Table. Duplication Allowed: "
                                     << duplicatesOK << endl;

  for ( Int_t rowNo = this->GetNumRows()-1;
        rowNo >= 0;
        --rowNo ) {
    const FairDbObjTableMap* row  = this->GetObjTableMap(rowNo);
    UInt_t index            = row->GetIndex(rowNo);
    const FairDbObjTableMap* row2 = this->FairDbResult::GetObjTableMapByIndex(index);

    DBLOG("FairDb",FairDbLog::kInfo)
        << "Look-up. Row no " << rowNo
        << " index " << index
        << " row,row2 " << (void*) row << "," << (void*) row2 << endl;

    if ( row2 != 0 && row2 != row && ! duplicatesOK ) {
      std::ostringstream msg;
      msg << "Duplicated row natural index: " << index
          << " Found at row " <<  rowNo
          << " of table " <<  this->TableName()
          << ":\n     index of combo# " <<  row->GetAggregateNo();
      if ( row->GetOwner() ) { msg << "(SEQNO " << row->GetOwner()->GetValidityRec(row).GetSeqNo() << ")"; }
      msg << " matches combo# " <<  row2->GetAggregateNo();
      if ( row2->GetOwner() ) { msg << "(SEQNO " << row2->GetOwner()->GetValidityRec(row2).GetSeqNo() << ")"; }
      MAXDBLOG("FairDb",FairDbLog::kError,20) << msg.str() << endl;
    }

    else { fIndexKeys[index] = row; }
  }

}


Bool_t FairDbResult::CanDelete(const FairDbResult* res)
{
  if (     res
           && this->CanReuse()
           && this->GetValidityRec().HasExpired(res->GetValidityRec())
     ) { this->SetCanReuse(kFALSE); }

  return ! this->GetNumClients() && ! this->CanReuse();
}

void FairDbResult::DeRegisterKey()
{
  if ( ! fKey ) { return; }
}

const FairDbResultKey* FairDbResult::GetKey() const
{
  return fKey ? fKey : FairDbResultKey::GetEmptyKey();
}

const FairDbObjTableMap* FairDbResult::GetObjTableMapByIndex(UInt_t index) const
{
  IndexToRow_t::const_iterator idx = fIndexKeys.find(index);
  return ( idx == fIndexKeys.end() ) ? 0 : (*idx).second;

}

void FairDbResult::RegisterKey()
{
  if ( fKey || this->GetNumRows() == 0) { return; }

  FairDbResultKey* key = this->CreateKey();
  fKey = key;

}


Bool_t FairDbResult::Satisfies(const ValCondition& vc,
                               const FairDb::Version& task)
{

  Bool_t isExtendedContext = this->IsExtendedContext();
  Bool_t canReuse          = this->CanReuse();
  Bool_t isCompatible      = this->GetValidityRec().IsCompatible(vc,task);
  Bool_t hasExpired        = this->GetValidityRec().HasExpired(vc,task);
  UInt_t numClients        = this->GetNumClients();

  DBLOG("FairDb",FairDbLog::kInfo)
      << "    Checking result with FairDbValRecord:- \n      " << this->GetValidityRec()
      << "  With extended context: " << isExtendedContext
      << " CanReuse: " << canReuse
      << " Is Compatible: " << isCompatible
      << " HasExpired: " <<  hasExpired
      << " number of clients: " << numClients
      << endl;

  if ( isExtendedContext ) { return kFALSE; }

  if ( canReuse && isCompatible ) { return kTRUE; }



  if ( canReuse && hasExpired && numClients == 0 )  {
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Marking result as not reusable" << endl;
    this-> SetCanReuse(kFALSE);
  }

  return kFALSE;

}

void FairDbResult::Streamer(FairDbBufferFile& file)
{

  if ( file.IsReading() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Restoring FairDbResult ..." << endl;
    file >> fCanReuse;
    fEffVRec.Streamer(file);
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Restored " << fEffVRec << endl;
    fResultsFromDb = kFALSE;
    fNumClients    = 0;
    file >> fTableName;
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Restored string " << fTableName << endl;
  } else if ( file.IsWriting() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Saving FairDbResult ..." << endl;
    file << fCanReuse;
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Saving " << fEffVRec << endl;
    fEffVRec.Streamer(file);
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Saving string " << fTableName << endl;
    file << fTableName;
  }
}


ClassImp(FairDbResultNonCombo)

FairDbResultNonCombo::FairDbResultNonCombo(FairDbResultPool* resultSet,
    const FairDbObjTableMap* tableRow,
    const FairDbValRecord* vrec,
    Bool_t dropSeqNo,
    const string& sqlQualifiers)
  : FairDbResult(resultSet,vrec,sqlQualifiers),
    fRows(),
    fBuffer(NULL)
{


  this->DebugCtor();

  // cout << " 1 " << endl;

  if ( ! resultSet || resultSet->IsExhausted() || ! tableRow ) {
    //cout << "-E- FairDbResultNonCombo incomplet IO -->  resultset: "
    //   << resultSet << " exhausted " << resultSet->IsExhausted() << " tableRow " << tableRow <<  endl;
    return;
  }

  // cout << " 2 " << endl;

  if ( vrec ) { FairDbStopWatchManager::gStopWatchManager.RecFillAgg(vrec->GetAggregateNo()); }

//Move to first row if result set not yet started.
  FairDbResultPool& rs = *resultSet;
  if ( rs.IsBeforeFirst() ) { rs.FetchRow(); }
  if ( rs.IsExhausted() ) { return; }

  // cout << " 3 " << endl;

//Check and load sequence number if necessary.
  Int_t seqNo = 0;
  if ( dropSeqNo && rs.CurColName() == "SEQNO" ) {
    rs >> seqNo;
    rs.DecrementCurCol();
  }

// Check for ROW_ID (which has to be ignored when reading).
  bool hasRowCounter = rs.HasRowCounter();

// Create and fill table row object and move result set onto next row.

  while ( ! rs.IsExhausted() ) {

//  If stripping off sequence numbers check the next and quit,
//  having restored the last, if it changes.
    if ( seqNo != 0 ) {
      Int_t nextSeqNo;
      rs >> nextSeqNo;
      if ( nextSeqNo != seqNo ) {
        rs.DecrementCurCol();
        break;
      }
    }

// Strip off ROW_ID if present.
    if ( hasRowCounter ) { rs.IncrementCurCol(); }
    FairDbObjTableMap* row = tableRow->CreateObjTableMap();
    if ( vrec) { FairDbStopWatchManager::gStopWatchManager.StartSubWatch(3); }
    row->SetOwner(this);

    //cout << " -I- FairDbResultNonCombo:: ObjTableMap::Fill() called  " << endl;
    row->Fill(rs,vrec);
    //cout << " -I- FairDbResultNonCombo:: ObjTableMap::Fill() IO done ...  " << endl;

    if ( vrec) { FairDbStopWatchManager::gStopWatchManager.StartSubWatch(2); }
    fRows.push_back(row);
    rs.FetchRow();
    if ( vrec) { FairDbStopWatchManager::gStopWatchManager.StartSubWatch(1); }
  }

  //Flag that data was read from Database.
  this->SetResultsFromDb();
  if ( seqNo  == 0 )
    DBLOG("FairDb",FairDbLog::kInfo)  << "Created non composite Validity result set no. of rows: "
                                      << this->GetNumRows() << endl;
  else   DBLOG("FairDb",FairDbLog::kInfo)  << "Created non composite result set for SeqNo: " << seqNo
        << " no. of rows: " << this->GetNumRows() << endl;

}


FairDbResultNonCombo::~FairDbResultNonCombo()
{
  if ( !fBuffer ) for ( vector<FairDbObjTableMap*>::iterator itr = fRows.begin();
                          itr != fRows.end();
                          ++itr) { if(*itr) {delete *itr; *itr=NULL;} }
  else {
    delete [] fBuffer;
    fBuffer = 0;
  }
}

FairDbResultKey* FairDbResultNonCombo::CreateKey() const
{

  string rowName("empty_table");
  const FairDbObjTableMap* row = this->GetObjTableMap(0);
  if ( row ) { rowName = row->GetName(); }
  const FairDbValRecord& vrec = this->GetValidityRec();
  return new FairDbResultKey(this->TableName(),
                             rowName,
                             vrec.GetSeqNo(),
                             vrec.GetCreationDate() );

}

void FairDbResultNonCombo::DebugCtor() const
{
  static const FairDbResultNonCombo* that = 0;
  if ( this == that ) {
    DBLOG("FairDb",FairDbLog::kInfo) << "debug " << (void*) this << endl;
  }
}


const FairDbObjTableMap* FairDbResultNonCombo::GetObjTableMap(UInt_t rowNum) const
{
  if ( rowNum >= fRows.size() ) { return 0; }
  return fRows[rowNum];
}
const FairDbObjTableMap* FairDbResultNonCombo::GetObjTableMapByIndex(UInt_t index) const
{

  if ( ! this->LookUpBuilt() ) { this->BuildLookUpTable(); }

  return this->FairDbResult::GetObjTableMapByIndex(index);

}

Bool_t FairDbResultNonCombo::Owns(const FairDbObjTableMap* row ) const
{
  vector<FairDbObjTableMap*>::const_iterator itr    = fRows.begin();
  vector<FairDbObjTableMap*>::const_iterator itrEnd = fRows.end();

  for (; itr != itrEnd; ++itr) if ( *itr == row ) { return kTRUE; }

  return kFALSE;


}

Bool_t FairDbResultNonCombo::Satisfies(const FairDbValRecord& vrec,
                                       const string& sqlQualifiers)
{
  DBLOG("FairDb",FairDbLog::kInfo)   << "Trying to satisfy: Vrec " << vrec << " SQL: " << sqlQualifiers
                                     << "\n with CanReuse: " << this->CanReuse()
                                     << " vrec: " << this->GetValidityRec()
                                     << " sqlQualifiers: " << this->GetSqlQualifiers()
                                     << endl;

  if ( this->CanReuse() ) {
    const FairDbValRecord& this_vrec = this->GetValidityRec();
    if (    sqlQualifiers           == this->GetSqlQualifiers()
            && vrec.GetSeqNo()         == this_vrec.GetSeqNo()
            && vrec.GetCreationDate()  == this_vrec.GetCreationDate()
       ) { return kTRUE; }
  }

  return kFALSE;

}

void FairDbResultNonCombo::Streamer(FairDbBufferFile& file)
{

  if ( file.IsReading() ) {
    this->FairDbResult::Streamer(file);
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Restoring FairDbResultNonCombo ..." << endl;
    file >> fRows;
    fBuffer = file.ReleaseArrayBuffer();
    this->BuildLookUpTable();
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Restored FairDbResultNonCombo. Size:"
                                      << fRows.size() << " rows" << endl;
  } else if ( file.IsWriting() ) {
    this->FairDbResult::Streamer(file);
    DBLOG("FairDb",FairDbLog::kInfo)  << "    Saving FairDbResultNonCombo. Size:"
                                      << fRows.size() << " rows" << endl;
    file << fRows;
  }
}

