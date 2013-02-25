
#include <cassert>
#include <cctype>
#include <sstream>

#include "TString.h"

#include "FairDb.h"
#include "FairDbString.h"
#include "FairDbTableMetaData.h"

ClassImp(FairDbTableMetaData)


FairDbTableMetaData::ColumnAttributes FairDbTableMetaData::fgDummy;

FairDbTableMetaData::FairDbTableMetaData(const string& tableName) :
  fColAttr(),
  fNumCols(0),
  fTableName(tableName)
{

}


FairDbTableMetaData::~FairDbTableMetaData()
{

}


void FairDbTableMetaData::Clear()
{

  fColAttr.clear();
  fNumCols = 0;

}


void FairDbTableMetaData::ExpandTo(UInt_t colNum)
{

  assert ( colNum < MAXCOL );
  while ( fNumCols < colNum ) {
    fColAttr.push_back(ColumnAttributes());
    ++fNumCols;
  }
}


const  FairDbTableMetaData::ColumnAttributes&  FairDbTableMetaData::GetAttributes(Int_t colNum) const
{

  if ( colNum > 0 && colNum <= (signed) fNumCols ) { return fColAttr[colNum-1]; }
  fgDummy.SetDefault();
  return fgDummy;

}


string FairDbTableMetaData::GetToken(const char*& strPtr)
{
  string token;

// Skip white space and quit if at EOS.
  while ( isspace(*strPtr) ) { ++strPtr; }
  if ( *strPtr == 0 ) { return token; }

// Collect the first character whatever it is.
  char firstChar = *strPtr++;
  token = firstChar;
  if ( ! isalnum(firstChar) && firstChar != '_' ) { return token; }

// Collect more if collecting alphanumeric + underscore string
  while ( isalnum(*strPtr) || *strPtr == '_' ) { token += *strPtr++; }
  return token;

}
FairDbTableMetaData::ColumnAttributes& FairDbTableMetaData::SetAttributes(Int_t colNum)
{

  // Return a column attributes
  //(will be dummy entry if requesting invalid column)
  this->ExpandTo(colNum);
  // Using const metho so must cast away constness.
  return const_cast<FairDbTableMetaData::ColumnAttributes&>(this->GetAttributes(colNum));

}

void FairDbTableMetaData::SetColFieldType(const FairDbFieldType& fieldType,
    Int_t colNum)
{
  ColumnAttributes&  attrib(this->SetAttributes(colNum));
  UInt_t concept     = fieldType.GetConcept();
  attrib.Type        = fieldType;
  attrib.MustDelimit = concept == FairDb::kString || concept == FairDb::kDate || concept == FairDb::kChar;
  attrib.Concept     = concept;

}

void FairDbTableMetaData::SetFromSql(const string& sql)
{

  TString SqlUpper(sql);
  SqlUpper.ToUpper();

  const char* strPtr = SqlUpper.Data();

  string token1(FairDbTableMetaData::GetToken(strPtr));
  string token2(FairDbTableMetaData::GetToken(strPtr));
  string token3(FairDbTableMetaData::GetToken(strPtr));
  string token4(FairDbTableMetaData::GetToken(strPtr));

  if ( token1 != "CREATE" || token2 != "TABLE" || token4 != "(" ) {
    cout << "Cannot recreate: SQL " << SqlUpper
         << " does not start CREATE TABLE ... (" << endl;
    return;
  }

  this->Clear();
  fTableName = token3;
  cout << "Recreating  FairDbTableMetaData for table " << fTableName << endl;

// Loop processing column specifications.
  Int_t col = 0;

  string delim;
  while ( delim != ")" ) {
    string name = FairDbTableMetaData::GetToken(strPtr);

//  Deal with INDEX and PRIMARY KEY
    if ( name == "INDEX" ||  name == "KEY" || name == "PRIMARY" ) {
      if ( name == "PRIMARY" || name == "KEY" ) { delim = FairDbTableMetaData::GetToken(strPtr); }
      delim = FairDbTableMetaData::GetToken(strPtr);
      if ( delim == "(" ) while ( delim != ")" ) { delim = FairDbTableMetaData::GetToken(strPtr); }
      delim = FairDbTableMetaData::GetToken(strPtr);
      continue;
    }

//  Collect name and type.
    ++col;
    this->SetColName(name,col);
    this->SetColIsNullable(col);

    string type = FairDbTableMetaData::GetToken(strPtr);
    int precision = 0;
    delim = FairDbTableMetaData::GetToken(strPtr);
    if ( delim == "(" ) {
      delim = FairDbTableMetaData::GetToken(strPtr);
      istringstream is(delim);
      is >> precision;
      delim = FairDbTableMetaData::GetToken(strPtr);
      delim = FairDbTableMetaData::GetToken(strPtr);
    }
    FairDbFieldType ft(type,precision);
    this->SetColFieldType(ft,col);
    cout << "  Column: " << col << " name " << this->ColName(col)
         << " type " << this->ColFieldType(col).AsString()
         << " precision " << precision << endl;

//  Collect optional qualifiers.

    while ( delim != ","  &&  delim != ")" ) {
      string opt2 = FairDbTableMetaData::GetToken(strPtr);
      if ( delim == "NOT" && opt2 == "NULL") {
        this->SetColIsNullable(col,false);
        delim = FairDbTableMetaData::GetToken(strPtr);
      } else if ( delim == "PRIMARY" && opt2 == "KEY") {
        delim = FairDbTableMetaData::GetToken(strPtr);
      } else if ( delim == "AUTO_INCREMENT") {
        delim = opt2;
      } else if ( delim == "UNSIGNED") {
        delim = opt2;
      } else {
        cout <<"Column: " << col << " name " << name << " type " << ft.AsString()
             << " ignoring unknown option: " << delim << endl;
        delim = opt2;
      }
    }
  }

}


string FairDbTableMetaData::Sql(FairDb::DbTypes dbType_target) const
{

  Bool_t mainTable = fTableName.substr(fTableName.size()-3,3) != "VAL";
  bool hasRowCounter = false;

  string tableName = fTableName;
  FairDbString sql;
  sql.GetString() = "";
  sql << "create table " << tableName << "(";

//  Assemble columns.
  int numCols = this->NumCols();
  for(int i=1; i<= numCols; i++) {

    if ( this->ColName(i) == "ROW_COUNTER" ) { hasRowCounter = true; }
    sql << this->ColName(i) << " " ;
    sql << this->ColFieldType(i).AsSQLString(dbType_target);

    if(    dbType_target == FairDb::kMySQL
           && this->ColName(i) == "SEQNO"
           && ! mainTable ) { sql << " not null primary key" ; }

    else if( ! this->ColIsNullable(i)
             || this->ColName(i) == "SEQNO"
             || this->ColName(i) == "ROW_COUNTER"
           ) { sql << " not null" ; }

    if (i < numCols) { sql << ", "; }

  }

// Deal with key/index/constraint.

// Nothing to do for the special xxxSEQNO tables.
  if ( fTableName == "GLOBALSEQNO" ||  fTableName == "LOCALSEQNO" ) {
    sql << ")";
  }

// Deal with MySQL
  else if (dbType_target == FairDb::kMySQL ) {
    if ( mainTable ) {
      if ( hasRowCounter ) { sql << ", primary key (SEQNO,ROW_COUNTER)"; }
      else { sql << ", index (SEQNO)"; }
    } else {
      sql << ", key TIMESTART (TIMESTART), key TIMEEND (TIMEEND)";
    }
    sql << ")";
  }

// Deal with ORACLE
  else {
    if ( mainTable ) {
      sql << ", constraint FK_" << fTableName << " foreign key(SEQNO) references "
          << fTableName << "VAL(SEQNO)";
      if ( hasRowCounter )
        sql << ", constraint PK_" << fTableName
            << "VAL primary key(SEQNO,ROW_COUNTER) using index tablespace R3B_DEV_IDX";
    } else {
      sql << ", constraint PK_" << fTableName
          << "VAL primary key(SEQNO) using index tablespace R3B_DEV_IDX";
    }
    sql << ")tablespace R3B_DEV_DATA";

    if ( mainTable) {
      if ( ! hasRowCounter )
        sql << "; create index " << tableName << "_idx  on "
            << tableName << "(seqno) tablespace R3B_DEV_IDX";
      sql << "; create index " << fTableName << "VAL_idx2 on "
          << fTableName << "VAL(TIMESTART) tablespace R3B_DEV_IDX";
      sql << "; create index " << fTableName << "VAL_idx3 on "
          << fTableName << "VAL(TIMEEND) tablespace R3B_DEV_IDX";
    } else {

    }
  }

// For ORACLE, create public synonym and grant access.

  if ( dbType_target == FairDb::kOracle ) {
    sql << "; create public synonym " << tableName << " for " << tableName;
    sql << "; grant  select on " << tableName << " to r3b_reader";
    sql << "; grant  select,insert,update on " << tableName << " to r3b_writer";
  }

  return sql.GetString();

}

