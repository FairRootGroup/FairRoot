#include <sstream>

#include "FairDbBinaryFile.h"
#include "FairDbResult.h"
#include "FairDbServices.h"
#include "FairDbTableRow.h"
#include "FairDbFieldType.h"
#include "FairDbString.h"
#include "FairDbStatement.h"
#include "FairDbTableMetaData.h"
#include "FairDbProxy.h"
#include "FairDbCache.h"
#include "FairDbTimerManager.h"
#include "FairDbValidityRecBuilder.h"
#include "FairDbExceptionLog.h"


#include "ValTimeStamp.h"



// ------------------------- Result Set  Implementation ---------------------------------\\

ClassImp(FairDbResultSet)


FairDbResultSet::FairDbResultSet(FairDbStatement* stmtDb,
                                 const FairDbString& sql,
                                 const FairDbTableMetaData* metaData,
                                 const FairDbTableProxy* tableProxy,
                                 UInt_t dbNo,
                                 const string& fillOpts) :
  FairDbRowStream(metaData),
  fCurRow(0),
  fDbNo(dbNo),
  fDbType(FairDb::kMySQL),
  fStatement(stmtDb),
  fTSQLStatement(0),
  fExhausted(true),
  fTableProxy(tableProxy),
  fValString(),
  fFillOpts(fillOpts)
{

  if ( stmtDb ) {
    fDbType = stmtDb->GetDBType();
    fTSQLStatement = stmtDb->ExecuteQuery(sql.c_str());
    if ( fTSQLStatement && fTSQLStatement->NextResultRow() ) { fExhausted = false; }
  }

}

FairDbResultSet::~FairDbResultSet()
{
  delete fTSQLStatement;
  fTSQLStatement = 0;
  delete fStatement;
  fStatement = 0;

}

#define IN(t) istringstream in(AsString(t)); in
// On first row use AsString to force type checking.
// On subsequent rows use binary interface for speed.
// Caution: Column numbering in TSQLStatement starts at 0.
#define IN2(t,m)                            \
  int col = CurColNum()-1;                  \
  if ( CurRowNum() == 0 ) {                 \
    istringstream in(AsString(t));          \
    in >> dest;                             \
  }                                         \
  else {                                    \
    dest = fTSQLStatement->m(col);          \
    IncrementCurCol();                      \
  }                                         \
 
// Handling reading of unsigned application data stored as signed database data.
// Both GetInt(int) and GetString(int) return the signed data correctly.
// So first read into signed equivalent, then copy and finally
// trim off leading extended sign bits beyond the capacity of
// the database column.
// For BIGINT (size 8) make an exception.  It's used only as
// an alternative to unsigned int and getUInt(int) (but not GetInt(int))
// returns it correctly so can load directly into destination
// Caution: Column numbering in TSQLStatement starts at 0.
#define IN3(t)                                                      \
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
 
FairDbResultSet& FairDbResultSet::operator>>(Bool_t& dest)
{
  IN(FairDb::kBool) >> dest;
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Char_t& dest)
{
  IN(FairDb::kChar) >> dest;
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Short_t& dest)
{
  IN2(FairDb::kInt,GetInt);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(UShort_t& dest)
{
  IN3(Short_t);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Int_t& dest)
{
  IN2(FairDb::kInt,GetInt);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(UInt_t& dest)
{
  IN3(Int_t);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Long_t& dest)
{
  IN2(FairDb::kLong, GetLong);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(ULong_t& dest)
{
  IN3(Long_t);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Float_t& dest)
{
  IN2(FairDb::kFloat,GetDouble);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(Double_t& dest)
{
  IN2(FairDb::kDouble,GetDouble);
  return *this;
}

// Also use AsString() for string and ValTimeStamp; conversion to string
// is needed in any case.
FairDbResultSet& FairDbResultSet::operator>>(string& dest)
{
  dest = AsString(FairDb::kString);
  return *this;
}
FairDbResultSet& FairDbResultSet::operator>>(ValTimeStamp& dest)
{
  dest=FairDb::MakeTimeStamp(AsString(FairDb::kDate));
  return *this;
}

string& FairDbResultSet::AsString(FairDb::DataTypes type)
{

  FairDbFieldType  reqdt(type);

//  Place table value string in value string buffer.
  Bool_t fail = ! LoadCurValue();
// Internally columns number from zero.
  UInt_t col = CurColNum();
  IncrementCurCol();

  if ( fail ) {
    string udef = reqdt.UndefinedValue();
    cout << "-I- FairDbResultSet "
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

      cout << "-I- FairDbResultSet "
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
    cout << "-I- FairDbResultSet "
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

Bool_t FairDbResultSet::CurColExists() const
{

  Int_t col = CurColNum();

  if ( IsExhausted() ) {
    cout << "-I- FairDbResultSet "
         << "In table " << TableNameTc()
         << " attempting to access row " << fCurRow
         << " column " << col
         << " but only " << fCurRow << " rows in table."  << endl;
    return kFALSE;
  }

  int numCols = NumCols();
  if ( col > numCols ) {
    cout << "-I- FairDbResultSet "
         << "In table " << TableNameTc()
         << " row " << fCurRow
         << " attempting to access column "<< col
         << " but only " << NumCols() << " in table ."  << endl;
    return kFALSE;
  }

  return kTRUE;

}
string FairDbResultSet::CurColString() const
{

  if ( ! CurColExists() ) { return ""; }

  TString valStr = this->GetStringFromTSQL(CurColNum());
  return valStr.Data();

}

Bool_t FairDbResultSet::FetchRow()
{
  ClearCurCol();
  if ( IsExhausted() ) { return kFALSE; }
  ++fCurRow;
  if ( ! fTSQLStatement->NextResultRow() ) { fExhausted = true; }
  return ! fExhausted;

}
TString FairDbResultSet::GetStringFromTSQL(Int_t col) const
{
  TString valStr = fTSQLStatement->GetString(col-1);
  if (    this->GetDBType() == FairDb::kOracle
          && this->ColFieldType(col).GetConcept() == FairDb::kString ) {
    cout << "-I- FairDbResultSet" <<
         "ORACLE string conversion from: " << valStr << endl;
    valStr.ReplaceAll("\\n", "\n");
    valStr.ReplaceAll("\\t", "\t");
    valStr.ReplaceAll("\\\'","\'");
    valStr.ReplaceAll("\\\"","\"");
    valStr.ReplaceAll("\\\\","\\");
    cout << "                           to: " << valStr <<endl;
  }
  return valStr;
}
Bool_t FairDbResultSet::LoadCurValue() const
{

  fValString.clear();

  if ( ! CurColExists() ) { return kFALSE; }

  Int_t col = CurColNum();
  TString valStr = this->GetStringFromTSQL(col);

  // For floating point, use binary interface to preserve precision
  // e.g.-1.234567890123457e-100 as string is -0.000000
  if ( CurColFieldType().GetConcept() == FairDb::kFloat ) {
    ostringstream out;
//    out << ;
    if ( CurColFieldType().GetType() == FairDb::kDouble ) { ; }
//  Caution: Column numbering in TSQLStatement starts at 0.
    out << fTSQLStatement->GetDouble(col-1);
    valStr = out.str().c_str();
  }
  int len = valStr.Length();



  const char* pVal = valStr.Data();
  // Remove leading and trailing quotes if dealing with a string.
  if (    len >= 2
          && ( *pVal == *(pVal+len-1) )
          && ( *pVal == '\'' || *pVal == '"' ) ) {
    ++pVal;
    len -= 2;
  }
  fValString.assign(pVal,len);

  return kTRUE;

}
void FairDbResultSet::RowAsCsv(string& row) const
{
  const FairDbTableMetaData* md = this->MetaData();

  Int_t maxCol = this->NumCols();
  for (Int_t col = 1; col <= maxCol; ++col) {
    // Deal with NULL values.  Caution: Column numbering in TSQLStatement starts at 0.
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

    // Make strings printable.
    if ( concept == FairDb::kString ) { FairUtilString::MakePrintable(value,row); }

    // For floating point, use binary interface to preserve precision
    // e.g.-1.234567890123457e-100 as string is -0.000000
    else if ( concept == FairDb::kFloat ) {
      ostringstream out;
      //out << setprecision(8);
      if ( md->ColFieldType(col).GetType() == FairDb::kDouble ) { ; } //out << setprecision(16);
      out << fTSQLStatement->GetDouble(col-1);
      row += out.str();
    }

    // Everything else (!) is O.K.
    else { row += value; }

    if ( mustDelimit ) { row += '\''; }
    if ( col < maxCol ) { row += ','; }
  }
}

//----------------------------- Result Key Implementation  ------------------------------------//

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

///.....................................................................

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

//.....................................................................

FairDbResultKey::~FairDbResultKey()
{

}

//.....................................................................

void FairDbResultKey::AddVRecKey(UInt_t seqno, ValTimeStamp ts)
{

  fVRecKeys.push_back(VRecKey(seqno,ts));
  ++fNumVRecKeys;

}

//.....................................................................

std::string FairDbResultKey::AsString() const
{
//
//
//   Return a string that summarises this key giving:-
//            1)  The table and row names.
//            2)  The number of validity records (aggregates)
//            3)  The range of SEQNOs
//            4)  The range of CREATIONDATEs.

  ostringstream os;
  os << "Table:" << fTableName << " row:" << fRowName;
  if ( fVRecKeys.empty() ) { os << " No vrecs"; }
  else {
    os << ".  " << fNumVRecKeys << " vrec";
    if ( fNumVRecKeys > 1 ) { os << "s (seqno min..max;creationdate min..max):"; }
    else { os << " (seqno;creationdate):"; }
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
//.....................................................................

Float_t FairDbResultKey::Compare(const FairDbResultKey* that) const
{

  // Check in table and row names.
  if ( fTableName != that->fTableName ) { return -2.; }
  if ( fRowName   != that->fRowName   ) { return -1.; }

  // Pick the key with the most entries and compare the other to it.

  cout << "Comparing " << *this << " to "
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
    cout << "Comparing seqno " << itr->SeqNo << " with creation date " << itr->CreationDate
         << " to " <<  seqnoToCreationDate[itr->SeqNo] << endl;
    if ( seqnoToCreationDate[itr->SeqNo] == itr->CreationDate ) { ++match; }
  }
  cout << "Match results: " << match << " out of " << numVrecs << endl;

  return match/numVrecs;

}


std::string FairDbResultKey::GetTableRowName() const
{
  ostringstream os;
  os << fTableName << "::" << fRowName;
  return os.str();

}

//--------------------------------- Result Aggregat Implementation --------------------------//



ClassImp(FairDbResultAgg)

typedef vector<const FairDbResult*>::const_iterator ConstResultItr_t;

FairDbResultAgg::FairDbResultAgg(const string& tableName,
                                 const FairDbTableRow* tableRow,
                                 FairDbCache* cache,
                                 const FairDbValidityRecBuilder* vrecBuilder,
                                 const FairDbProxy* proxy,
                                 const string& sqlQualifiers) :
  FairDbResult(0,0,sqlQualifiers),
  fResults(),
  fRowKeys(),
  fSize(0)
{
  typedef map<UInt_t,UInt_t> seqToRow_t;

  SetTableName(tableName);
  if ( ! tableRow || ! cache || ! vrecBuilder || ! proxy ) { return; }

// Unpack the extended context SQL qualifiers.
// Don't use StringTok - it eats null strings
// e.g. abc;;def gives 2 substrings.

  string::size_type loc  = sqlQualifiers.find(';');
  string::size_type loc2 = sqlQualifiers.find(';',loc+1);
  string sqlData  = string(sqlQualifiers,loc+1,loc2-loc-1);
  string fillOpts = string(sqlQualifiers,loc2+1);

//Loop over all rows looking to see if they are already in
//the cache, and if not, recording their associated sequence numbers

  vector<UInt_t> reqSeqNos;  // Sequence numbers required from DB.
  seqToRow_t seqToRow;       // Map SeqNo - > RowNo.
//  Set up a Default database number, it will be updated if anything
//  needs to be read from the database.
  UInt_t dbNo = 0;
  Int_t maxRowNo = vrecBuilder->GetNumValidityRec() - 1;

//Ignore the first entry from the validity rec builder, it will be
//for Agg No = -1, which should not be present for aggregated data.
  for ( Int_t rowNo = 1; rowNo <= maxRowNo; ++rowNo ) {
    const FairDbValidityRec& vrecRow = vrecBuilder->GetValidityRec(rowNo);

//  If its already in the cache, then just connect it in.
    const FairDbResult* res = cache->Search(vrecRow,sqlQualifiers);
    cout << "Checking validity rec " << rowNo
         << " " << vrecRow
         << "SQL qual: " << sqlQualifiers
         << " cache search: " << (void*) res << endl;
    if ( res ) {
      fResults.push_back(res);
      res->Connect();
      fSize += res->GetNumRows();
    }

//  If its not in the cache, but represents a gap, then create an empty
//  FairDbResult and add it to the cache.
    else if ( vrecRow.IsGap() ) {
      FairDbResult* newRes = new FairDbResultNonAgg(0, tableRow, &vrecRow);
      cache->Adopt(newRes,false);
      fResults.push_back(newRes);
      newRes->Connect();
    }

//  Neither in cache, nor a gap, so record its sequence number.
    else {
      UInt_t seqNo = vrecRow.GetSeqNo();
      reqSeqNos.push_back(seqNo);
      seqToRow[seqNo] = rowNo;
      fResults.push_back(0);
//    All data must come from a single database, so any vrec will
//    do to define which one.
      dbNo = vrecRow.GetDbNo();
    }
  }

//If there are required sequence numbers, then read them from the
//database and build FairDbResults for each.

  if ( reqSeqNos.size() ) {
//  Sort into ascending order; it may simplify the query which will
//  block ranges of sequence numbers together.
    sort(reqSeqNos.begin(),reqSeqNos.end());
    FairDbResultSet* rs = proxy->QuerySeqNos(reqSeqNos,dbNo,sqlData,fillOpts);
//  Flag that data was read from Database.
    this->SetResultsFromDb();
    FairDbTimerManager::gTimerManager.StartSubWatch(1);
    while ( ! rs->IsExhausted() ) {
      Int_t seqNo;
      *rs >> seqNo;
      rs->DecrementCurCol();
      Int_t rowNo = -2;
      if ( seqToRow.find(seqNo) == seqToRow.end() ) {

        cout  << "Unexpected SeqNo: " << seqNo << endl;

      } else {
        rowNo = seqToRow[seqNo];
        cout
            << "Procesing SeqNo: " << seqNo
            << " for row " << rowNo << endl;
      }

      const FairDbValidityRec& vrecRow = vrecBuilder->GetValidityRec(rowNo);
      FairDbResultNonAgg* newRes = new FairDbResultNonAgg(rs,tableRow,&vrecRow);
//    Don't allow results from Extended Context queries to be reused.
      if ( this->IsExtendedContext() ) { newRes->SetCanReuse(false); }
      if ( rowNo == -2 ) {
        delete newRes;
      } else {
        cout
            << "SeqNo: " << seqNo
            << " produced " << newRes->GetNumRows() << " rows" << endl;
//      Adopt but don't register key for this component, only the overall FairDbResultAgg
//      will have a registered key.
        cache->Adopt(newRes,false);
        fResults[rowNo-1] = newRes;
        newRes->Connect();
        fSize += newRes->GetNumRows();
      }
    }

//  FairDbResultSet fully processed, so delete it.
    delete rs;
  }

//All component FairDbResultNonAgg objects have now been located and
//connected in, so set up their access keys and determine the validty
//range by ANDing the time windows together.

  fRowKeys.reserve(fSize);

  FairDbValidityRec vRec = vrecBuilder->GetValidityRec(1);
  for ( Int_t rowNo = 1; rowNo <= maxRowNo; ++rowNo ) {

    const FairDbValidityRec& vrecRow = vrecBuilder->GetValidityRec(rowNo);
    ValRange r = vrecRow.GetValRange();
    vRec.AndTimeWindow(r.GetTimeStart(),r.GetTimeEnd());

    const FairDbResult* res = fResults[rowNo-1];
    if ( res ) {
      UInt_t numEnt = res->GetNumRows();
      for (UInt_t entNo = 0; entNo < numEnt; ++entNo ) {
        fRowKeys.push_back(res->GetTableRow(entNo));
      }
    }
  }

// Now that the row look-up table has been built the natural index
// look-up table can be filled in.
  this->BuildLookUpTable();

// Set aggregate number to -1 to show that it has multiple aggregates
  vRec.SetAggregateNo(-1);
  SetValidityRec(vRec);

  cout
      << "Aggregate contains " << fSize  << " entries.  vRec:-" << endl
      << vRec << endl;

  cout << "Created aggregated result set no. of rows: "
       << this->GetNumRows() << endl;

}
FairDbResultAgg::~FairDbResultAgg()
{

  for ( ConstResultItr_t itr = fResults.begin();
        itr != fResults.end();
        ++itr) if ( *itr ) { (*itr)->Disconnect(); }

}
//.....................................................................

FairDbResultKey* FairDbResultAgg::CreateKey() const
{
//
//
//  Purpose:  Create a key that corresponds to this result.
//            Caller must take ownership.

  FairDbResultKey* key = 0;
  for ( ConstResultItr_t itr = fResults.begin();
        itr != fResults.end();
        ++itr ) {
    const FairDbResult* result = *itr;
    if ( result ) {
      // Create key from first result.
      if ( ! key ) { key = result->CreateKey(); }
      // Extend key from the remainder.
      else {
        const FairDbValidityRec& vrec = result->GetValidityRec();
        key->AddVRecKey(vrec.GetSeqNo(),vrec.GetCreationDate());
      }
    }
  }

// Should not have an empty set, but just in case.
  if ( ! key ) { key = new FairDbResultKey(); }

  return key;

}

const FairDbTableRow* FairDbResultAgg::GetTableRow(UInt_t row) const
{

  return  ( row >= fRowKeys.size() ) ? 0 : fRowKeys[row];

}


const FairDbValidityRec& FairDbResultAgg::GetValidityRec(
  const FairDbTableRow* row) const
{

  if ( ! row ) { return this->GetValidityRecGlobal(); }
  FairDbResult* owner = row->GetOwner();
  return owner ? owner->GetValidityRecGlobal() : this->GetValidityRecGlobal();

}

Bool_t FairDbResultAgg::Satisfies(const string& sqlQualifiers)
{
  cout
      << "Trying to satisfy: SQL: " << sqlQualifiers
      << "\n with CanReuse: " << this->CanReuse()
      << " sqlQualifiers: " << this->GetSqlQualifiers()
      << endl;
  return    this->CanReuse()
            && this->GetSqlQualifiers() == sqlQualifiers;
}

void FairDbResultAgg::Streamer(FairDbBinaryFile& bf)
{

  vector<const FairDbResult*>::const_iterator itr = fResults.begin();
  vector<const FairDbResult*>::const_iterator end = fResults.end();

  UInt_t numNonAgg = 0;
  for (; itr != end; ++itr) {
    const FairDbResultNonAgg* rna = dynamic_cast<const FairDbResultNonAgg*>(*itr);
    if ( rna && ! rna->GetValidityRecGlobal().IsGap() ) { ++numNonAgg; }
  }
  bf << numNonAgg;


  for (itr = fResults.begin(); itr != end; ++itr) {
    const FairDbResultNonAgg* rna = dynamic_cast<const FairDbResultNonAgg*>(*itr);
    if ( rna && ! rna->GetValidityRecGlobal().IsGap() ) { bf << *rna; }
  }
}





//------------------------------------- FairDbResult Generic Implemenation --------------//


ClassImp(FairDbResult)

Int_t FairDbResult::fgLastID(0);

FairDbBinaryFile& operator<<(FairDbBinaryFile& bf, const FairDbResult& res)
{
// Writing is a const operation, but uses a non-const method, so cast away const.
  FairDbResult& res_tmp = const_cast< FairDbResult&>(res);
  res_tmp.Streamer(bf);
  return bf;
}


FairDbBinaryFile& operator>>(FairDbBinaryFile& bf, FairDbResult& res)
{

  res.Streamer(bf);
  return bf;
}


FairDbResult::FairDbResult(FairDbResultSet* resultSet,
                           const FairDbValidityRec* vrec,
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
  //TODO: should fKey be a deep copy???

}

FairDbResult::~FairDbResult()
{
  if ( fNumClients ) {
    cout << "Warning: Destroying FairDbResult with " << fNumClients
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

  cout << "Building look-uptable. Allow duplicates: "
       << duplicatesOK << endl;

  for ( Int_t rowNo = this->GetNumRows()-1;
        rowNo >= 0;
        --rowNo ) {
    const FairDbTableRow* row  = this->GetTableRow(rowNo);
    UInt_t index            = row->GetIndex(rowNo);
//  Ensure we use this class's GetTableRowByIndex, the method is
//  virtual but if the subclass has called this method then it must
//  be the right one to use. [Actually FairDbResultAgg overrides
//  GetTableRowByIndex, but only to make building lazy].
    const FairDbTableRow* row2 = this->FairDbResult::GetTableRowByIndex(index);

    cout
        << "Look-up. Row no " << rowNo
        << " index " << index
        << " row,row2 " << (void*) row << "," << (void*) row2 << endl;

    if ( row2 != 0 && row2 != row && ! duplicatesOK ) {
      std::ostringstream msg;
      msg << "Duplicated row natural index: " << index
          << " Found at row " <<  rowNo
          << " of table " <<  this->TableName()
          << ":-\n     index of agg " <<  row->GetAggregateNo();
      if ( row->GetOwner() ) { msg << "(SEQNO " << row->GetOwner()->GetValidityRec(row).GetSeqNo() << ")"; }
      msg << " matches agg " <<  row2->GetAggregateNo();
      if ( row2->GetOwner() ) { msg << "(SEQNO " << row2->GetOwner()->GetValidityRec(row2).GetSeqNo() << ")"; }
      cout << msg.str() << endl;
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

// FairDbRecord* record = FairDbServices::GetRecord();
//  if ( ! record ) {
//    cout << "Attempting to deregister FairDbResultKey at " << (void*) fKey
//          << " but owning FairDbRecord cannot be found." << endl;
//  }
//  else {
//    record->DeleteKey(fKey);
//    fKey = 0;
//  }

}
const FairDbResultKey* FairDbResult::GetKey() const
{

  return fKey ? fKey : FairDbResultKey::GetEmptyKey();

}

const FairDbTableRow* FairDbResult::GetTableRowByIndex(UInt_t index) const
{
  IndexToRow_t::const_iterator idx = fIndexKeys.find(index);
  return ( idx == fIndexKeys.end() ) ? 0 : (*idx).second;

}

void FairDbResult::RegisterKey()
{
  if ( fKey || this->GetNumRows() == 0) { return; }

//  FairDbRecord* record = FairDbServices::GetRecord();
//  if ( ! record ) {
//    cout << "cannot create and register key"
//           << ", owning FairDbRecord cannot be found." << endl;
//  }
//  else {
  FairDbResultKey* key = this->CreateKey();
//    record->AdoptKey(key);
  fKey = key;
//  }

}







Bool_t FairDbResult::Satisfies(const ValContext& vc,
                               const FairDb::Task& task)
{

  Bool_t isExtendedContext = this->IsExtendedContext();
  Bool_t canReuse          = this->CanReuse();
  Bool_t isCompatible      = this->GetValidityRec().IsCompatible(vc,task);
  Bool_t hasExpired        = this->GetValidityRec().HasExpired(vc,task);
  UInt_t numClients        = this->GetNumClients();
  cout
      << "    Checking result with FairDbValidityRec:- \n      " << this->GetValidityRec()
      << "  With extended context: " << isExtendedContext
      << " CanReuse: " << canReuse
      << " Is Compatible: " << isCompatible
      << " HasExpired: " <<  hasExpired
      << " number of clients: " << numClients
      << endl;

  if ( isExtendedContext ) { return kFALSE; }

  if ( canReuse && isCompatible ) { return kTRUE; }

//  If the query would be satisfied apart from the date, then
//  assume we have moved out of the validity window, never
//  to return!

  if ( canReuse && hasExpired && numClients == 0 )  {
    cout << "    Marking result as not reusable" << endl;
    this-> SetCanReuse(kFALSE);
  }

  return kFALSE;

}

void FairDbResult::Streamer(FairDbBinaryFile& file)
{

  if ( file.IsReading() ) {
    cout << "    Restoring FairDbResult ..." << endl;
    file >> fCanReuse;
    fEffVRec.Streamer(file);
    cout << "    Restored " << fEffVRec << endl;
    fResultsFromDb = kFALSE;
    fNumClients    = 0;
    file >> fTableName;
    cout << "    Restored string " << fTableName << endl;
  } else if ( file.IsWriting() ) {
    cout << "    Saving FairDbResult ..." << endl;
    file << fCanReuse;
    cout << "    Saving " << fEffVRec << endl;
    fEffVRec.Streamer(file);
    cout << "    Saving string " << fTableName << endl;
    file << fTableName;
  }
}


ClassImp(FairDbResultNonAgg)

FairDbResultNonAgg::FairDbResultNonAgg(FairDbResultSet* resultSet,
                                       const FairDbTableRow* tableRow,
                                       const FairDbValidityRec* vrec,
                                       Bool_t dropSeqNo,
                                       const string& sqlQualifiers)
  : FairDbResult(resultSet,vrec,sqlQualifiers),
    fRows(),
    fBuffer(NULL)
{
  this->DebugCtor();

  if ( ! resultSet || resultSet->IsExhausted() || ! tableRow ) { return; }

  if ( vrec ) { FairDbTimerManager::gTimerManager.RecFillAgg(vrec->GetAggregateNo()); }

//Move to first row if result set not yet started.
  FairDbResultSet& rs = *resultSet;
  if ( rs.IsBeforeFirst() ) { rs.FetchRow(); }
  if ( rs.IsExhausted() ) { return; }

//Check and load sequence number if necessary.
  Int_t seqNo = 0;
  if ( dropSeqNo && rs.CurColName() == "SEQNO" ) {
    rs >> seqNo;
    rs.DecrementCurCol();
  }

// Check for ROW_COUNTER (which has to be ignored when reading).
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

// Strip off ROW_COUNTER if present.
    if ( hasRowCounter ) { rs.IncrementCurCol(); }
    FairDbTableRow* row = tableRow->CreateTableRow();
    if ( vrec) { FairDbTimerManager::gTimerManager.StartSubWatch(3); }
    row->SetOwner(this);
    row->Fill(rs,vrec);
    if ( vrec) { FairDbTimerManager::gTimerManager.StartSubWatch(2); }
    fRows.push_back(row);
    rs.FetchRow();
    if ( vrec) { FairDbTimerManager::gTimerManager.StartSubWatch(1); }
  }

  //Flag that data was read from Database.
  this->SetResultsFromDb();
  if ( seqNo  == 0 )
    cout << "Created unaggregated VAL result set no. of rows: "
         << this->GetNumRows() << endl;
  else  cout << "Created unaggregated result set for SeqNo: " << seqNo
               << " no. of rows: " << this->GetNumRows() << endl;

}


FairDbResultNonAgg::~FairDbResultNonAgg()
{

  if ( ! fBuffer ) for ( vector<FairDbTableRow*>::iterator itr = fRows.begin();
                           itr != fRows.end();
                           ++itr) { delete *itr; }
  else {
    delete [] fBuffer;
    fBuffer = 0;
  }
}

FairDbResultKey* FairDbResultNonAgg::CreateKey() const
{

  string rowName("empty_table");
  const FairDbTableRow* row = this->GetTableRow(0);
  if ( row ) { rowName = row->GetName(); }
  const FairDbValidityRec& vrec = this->GetValidityRec();
  return new FairDbResultKey(this->TableName(),
                             rowName,
                             vrec.GetSeqNo(),
                             vrec.GetCreationDate() );

}
void FairDbResultNonAgg::DebugCtor() const
{
  static const FairDbResultNonAgg* that = 0;
  if ( this == that ) {
    cout << "debug " << (void*) this << endl;
  }
}
//.....................................................................

const FairDbTableRow* FairDbResultNonAgg::GetTableRow(UInt_t rowNum) const
{
  if ( rowNum >= fRows.size() ) { return 0; }
  return fRows[rowNum];
}
const FairDbTableRow* FairDbResultNonAgg::GetTableRowByIndex(UInt_t index) const
{

  if ( ! this->LookUpBuilt() ) { this->BuildLookUpTable(); }

  return this->FairDbResult::GetTableRowByIndex(index);

}
Bool_t FairDbResultNonAgg::Owns(const FairDbTableRow* row ) const
{
  vector<FairDbTableRow*>::const_iterator itr    = fRows.begin();
  vector<FairDbTableRow*>::const_iterator itrEnd = fRows.end();

  for (; itr != itrEnd; ++itr) if ( *itr == row ) { return kTRUE; }

  return kFALSE;


}

Bool_t FairDbResultNonAgg::Satisfies(const FairDbValidityRec& vrec,
                                     const string& sqlQualifiers)
{
  cout  << "Trying to satisfy: Vrec " << vrec << " SQL: " << sqlQualifiers
        << "\n with CanReuse: " << this->CanReuse()
        << " vrec: " << this->GetValidityRec()
        << " sqlQualifiers: " << this->GetSqlQualifiers()
        << endl;

  if ( this->CanReuse() ) {
    const FairDbValidityRec& this_vrec = this->GetValidityRec();
    if (    sqlQualifiers           == this->GetSqlQualifiers()
            && vrec.GetSeqNo()         == this_vrec.GetSeqNo()
            && vrec.GetCreationDate()  == this_vrec.GetCreationDate()
       ) { return kTRUE; }
  }

  return kFALSE;

}
void FairDbResultNonAgg::Streamer(FairDbBinaryFile& file)
{

  if ( file.IsReading() ) {
    this->FairDbResult::Streamer(file);
    cout << "    Restoring FairDbResultNonAgg ..." << endl;
    file >> fRows;
//  Take ownership of the memory holding the array.
    fBuffer = file.ReleaseArrayBuffer();
    this->BuildLookUpTable();
    cout << "    Restored FairDbResultNonAgg. Size:"
         << fRows.size() << " rows" << endl;
  } else if ( file.IsWriting() ) {
    this->FairDbResult::Streamer(file);
    cout << "    Saving FairDbResultNonAgg. Size:"
         << fRows.size() << " rows" << endl;
    file << fRows;
  }
}

