/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbTableMetaData.h"
#include "FairDbLogService.h"
#include "FairDb.h"                     // for DbTypes::kMySQL, etc
#include "FairDbString.h"               // for FairDbString

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString, operator<<

#include <cassert>                      // for assert
#include <cctype>                       // for isalnum, isspace
#include <iostream>                     // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;
using std::istringstream;
using std::string;

ClassImp(FairDbTableMetaData)


FairDbTableMetaData::ColumnAttributes FairDbTableMetaData::fgDummy;

FairDbTableMetaData::FairDbTableMetaData(const string& tableName) :
  fColAttr(),
  fNumCols(0),
  fTableName(tableName)
{
  DBLOG("FairDb",FairDbLog::kInfo) << "create for table # " << tableName << endl;
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

  //  cout << "-I- FairDbTableMetaData::GetAttributes : return dummy attributes: col#"
  //     <<  colNum << " : " << fNumCols << endl;

  fgDummy.SetDefault();
  return fgDummy;
}


string FairDbTableMetaData::GetToken(const char*& strPtr)
{
  string token;
  while ( isspace(*strPtr) ) { ++strPtr; }
  if ( *strPtr == 0 ) { return token; }

  char firstChar = *strPtr++;
  token = firstChar;
  if ( ! isalnum(firstChar) && firstChar != '_' ) { return token; }

  while ( isalnum(*strPtr) || *strPtr == '_' ) { token += *strPtr++; }
  return token;

}
FairDbTableMetaData::ColumnAttributes& FairDbTableMetaData::SetAttributes(Int_t colNum)
{
  this->ExpandTo(colNum);
  //cout << "-I-  FairDbTableMetaData::SetAttributes  Expand to:" << colNum << " : " << fNumCols << endl;
  return const_cast<FairDbTableMetaData::ColumnAttributes&>(this->GetAttributes(colNum));
}

void FairDbTableMetaData::SetColFieldType(const FairDbFieldType& fieldType,
    Int_t colNum)
{
  //cout << "-I-  FairDbTableMetaData::SetColFieldType:" << fieldType.GetConcept() << " : " << colNum << endl;
  ColumnAttributes&  attrib(this->SetAttributes(colNum));
  UInt_t concept     = fieldType.GetConcept();
  attrib.Type        = fieldType;
  attrib.MustDelimit = concept == FairDb::kString || concept == FairDb::kDate || concept == FairDb::kChar;
  attrib.Concept     = concept;
}

void FairDbTableMetaData::SetFromSql(const string& sql, FairDb::DbTypes dbType_target)
{

  //cout << "-I- <<<<<<  FairDbTableMetaData::SetFromSQL()  called  <<<<<<<" << endl;

  TString SqlUpper(sql);
  SqlUpper.ToUpper();

  const char* strPtr = SqlUpper.Data();

  string token1(FairDbTableMetaData::GetToken(strPtr));
  string token2(FairDbTableMetaData::GetToken(strPtr));
  string token3(FairDbTableMetaData::GetToken(strPtr));
  string token4(FairDbTableMetaData::GetToken(strPtr));

  if ( token1 != "CREATE" || token2 != "TABLE" || token4 != "(" ) {

    DBLOG("FairDb",FairDbLog::kError)  << "Cannot recreate: SQL " << SqlUpper
                                       << " does not start CREATE TABLE ... (" << endl;
    return;
  }

  this->Clear();
  fTableName = token3;
  DBLOG("FairDb",FairDbLog::kInfo)  << "Recreating  FairDbTableMetaData for table " << fTableName << endl;

// Loop over column specs.
  Int_t col = 0;
  string delim;
  while ( delim != ")" ) {
    string name = FairDbTableMetaData::GetToken(strPtr);

    // INDEX and PRIMARY KEY
    if ( name == "INDEX" ||  name == "KEY" || name == "PRIMARY" ) {
      if ( name == "PRIMARY" || name == "KEY" ) { delim = FairDbTableMetaData::GetToken(strPtr); }
      delim = FairDbTableMetaData::GetToken(strPtr);
      if ( delim == "(" ) while ( delim != ")" ) { delim = FairDbTableMetaData::GetToken(strPtr); }
      delim = FairDbTableMetaData::GetToken(strPtr);
      continue;
    }

    // Name and type.
    ++col;
    this->SetColName(name,col);
    this->SetColIsNullable(col);

    // Get type and init precision
    string type = FairDbTableMetaData::GetToken(strPtr);
    int precision = 0;

    delim = FairDbTableMetaData::GetToken(strPtr);

    // Check if precision is specified then store it
    if ( delim == "(" ) {
      delim = FairDbTableMetaData::GetToken(strPtr);
      istringstream is(delim);
      is >> precision;
      delim = FairDbTableMetaData::GetToken(strPtr);
      delim = FairDbTableMetaData::GetToken(strPtr);
    }


    FairDbFieldType ft(type,precision);

    this->SetColFieldType(ft,col);
    DBLOG("FairDb",FairDbLog::kInfo) << "  Column: " << col << " name " << this->ColName(col)
                                     << " type " << this->ColFieldType(col).AsString()
                                     << " precision " << precision << endl;


//  Collect optional qualifiers.
    while ( delim != ","  &&  delim != ")" ) {
      string opt2 = FairDbTableMetaData::GetToken(strPtr);
      // cout << "delim " << delim << " opt2 " << opt2 << endl;
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
        DBLOG("FairDb",FairDbLog::kInfo) <<"Column: " << col << " name " << name << " type " << ft.AsString()
                                         << " ignoring unknown option: " << delim << endl;
        delim = opt2;
      }
    } // !(while 2)

  } //! (while 1 )

}


string FairDbTableMetaData::Sql(FairDb::DbTypes dbType_target) const
{
  //cout << "-I- <<<<<<  FairDbTableMetaData::SQL()  called  <<<<<<<" << endl;

  Bool_t mainTable = fTableName.substr(fTableName.size()-3,3) != "VAL";
  bool hasRowCounter = false;
  string tableName = fTableName;
  FairDbString sql;

  sql.GetString() = "";
  sql << "create table " << tableName << "(";

//  Assemble columns.
  int numCols = this->NumCols();
  for(int i=1; i<= numCols; i++) {

    if ( this->ColName(i) == "ROW_ID" ) { hasRowCounter = true; }
    sql << this->ColName(i) << " " ;

    // Change Primary key definition in PgSQL
    if(   dbType_target == FairDb::kPostgreSQL
          && this->ColName(i) == "SEQNO"
          && ! mainTable ) {
      sql << " bigserial primary key" ;
    } else if(dbType_target == FairDb::kSQLite
              && this->ColName(i) == "SEQNO"
              && ! mainTable ) {
      sql << " integer primary key autoincrement" ;
    } else {
      sql << this->ColFieldType(i).AsSQLString(dbType_target);
      if(    dbType_target == FairDb::kMySQL
             && this->ColName(i) == "SEQNO"
             && ! mainTable ) { sql << " not null primary key" ; }

      else if( ! this->ColIsNullable(i)
               || this->ColName(i) == "SEQNO"
               || this->ColName(i) == "ROW_ID"
             ) { sql << " not null" ; }
    }
    if (i < numCols) { sql << ", "; }

  }

// Deal with key/index/constraint.
// nothing here done
  if ( fTableName == "FAIRDBGLOBALSEQNO" ||  fTableName == "FAIRDBLOCALSEQNO" ) {
    sql << ")";
  }

// MySQL specs
  else if (dbType_target == FairDb::kMySQL ) {
    if ( mainTable ) {
      if ( hasRowCounter ) { sql << ", primary key (SEQNO,ROW_ID)"; }
      else { sql << ", index (SEQNO)"; }
    } else {
      sql << ", key TIMESTART (TIMESTART), key TIMEEND (TIMEEND)";
    }
    sql << ")";
  }


// Deal with PostgreSQL
  else if (dbType_target == FairDb::kPostgreSQL) {
    if ( mainTable ) {
      if ( hasRowCounter ) { sql << ", primary key (SEQNO,ROW_ID)"; }
    }

    sql << ") ";

    if ( mainTable) {
      if ( ! hasRowCounter )
        sql << "; create index " << tableName << "_idx  on "
            << tableName << "(seqno)";
    } else {
      sql << "; create index " << tableName << "VAL_idx2 on "
          << tableName << "(TIMESTART);";
      sql << "; create index " << tableName << "VAL_idx3 on "
          << tableName << "(TIMEEND);";
    }
  }


// Deal with SQLite
  else if (dbType_target == FairDb::kSQLite) {
    if ( mainTable ) {
      if ( hasRowCounter ) { sql << ", primary key (SEQNO,ROW_ID)"; }
    }

    sql << ") ";

    if ( mainTable) {
      if ( ! hasRowCounter )
        sql << "; create index " << tableName << "_idx  on "
            << tableName << "(seqno)";
    } else {
      sql << "; create index " << tableName << "VAL_idx2 on "
          << tableName << "(TIMESTART);";
      sql << "; create index " << tableName << "VAL_idx3 on "
          << tableName << "(TIMEEND);";
    }
  }

// ORACLE specs
  else if (dbType_target == FairDb::kOracle) {

    if ( mainTable ) {
      sql << ", constraint FK_" << fTableName << " foreign key(SEQNO) references "
          << fTableName << "VAL(SEQNO)";
      if ( hasRowCounter )
        sql << ", constraint PK_" << fTableName
            << "VAL primary key(SEQNO,ROW_ID) using index tablespace R3B_DEV_IDX";
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

// ORACLE specs: create public synonym and grant access.
  if ( dbType_target == FairDb::kOracle ) {
    sql << "; create public synonym " << tableName << " for " << tableName;
    sql << "; grant  select on " << tableName << " to r3b_reader";
    sql << "; grant  select,insert,update on " << tableName << " to r3b_writer";
  }
  return sql.GetString();
}

