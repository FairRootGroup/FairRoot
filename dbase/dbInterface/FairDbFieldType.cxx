/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbFieldType.h"
#include "FairDbLogService.h"
#include "Riosfwd.h"                    // for ostream
#include "TSQLServer.h"                 // for TSQLServer, etc
#include "TString.h"                    // for operator==, TString

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>                      // IWYU pragma: keep
// for ostringstream

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

ClassImp(FairDbFieldType)

FairDbFieldType::FairDbFieldType(Int_t type /* = FairDb::kInt */)
  : fConcept(0),
    fSize(0),
    fType(0)
{
  this->Init(type);
}

FairDbFieldType::FairDbFieldType(Int_t type,
                                 Int_t size,
                                 const char* typeName)
  : fConcept(0),
    fSize(0),
    fType(0)
{

  TString name(typeName);
  name.ToUpper();

  // Integer types.
  if ( type == TSQLServer::kSQL_INTEGER || type == TSQLServer::kSQL_NUMERIC ) {

    if ( name.BeginsWith("INT") ) { size = kMaxInt; }
    if      ( size <= kMaxTinyInt  ) { this->Init(FairDb::kTiny);  return; }
    else if ( size <= kMaxSmallInt ) { this->Init(FairDb::kShort); return; }
    else if ( size <= kMaxInt      ) { this->Init(FairDb::kInt);   return; }
    else                             { this->Init(FairDb::kLong);  return; }

  }

  // Floating point types
  if ( type == TSQLServer::kSQL_FLOAT  ) { this->Init(FairDb::kFloat);  return; }
  if ( type == TSQLServer::kSQL_DOUBLE ) { this->Init(FairDb::kDouble);  return; }

  // Cases where type is determined uniquely by type name.

  if ( name == "BINARY_FLOAT" )  { this->Init(FairDb::kFloat);  return; }
  if ( name == "BINARY_DOUBLE" ) { this->Init(FairDb::kDouble); return; }
  if ( name == "TINYTEXT" )      { this->Init(FairDb::kString,kMaxMySQLVarchar);   return; }
  if ( name == "TEXT" )          { this->Init(FairDb::kString,kMaxMySQLText);   return; }
  if ( name == "DATE" )          { this->Init(FairDb::kDate);   return; }
  if ( name == "DATETIME" )      { this->Init(FairDb::kDate);   return; }
  if ( name == "TIMESTAMP" )     { this->Init(FairDb::kDate);   return; }

  //SQLite add on specs
  if ( name == "INTEGER" )       { this->Init(FairDb::kInt);  return; }
  if ( name == "REAL" )       { this->Init(FairDb::kFloat);  return; }

  // Character types
  if ( type == TSQLServer::kSQL_CHAR && size <= kMaxChar ) {
    this->Init(FairDb::kChar,size);
    return;
  }
  if ( type == TSQLServer::kSQL_CHAR || type == TSQLServer::kSQL_VARCHAR ) {
    if ( size < kMaxMySQLVarchar ) { Init(FairDb::kString,size); }
    else { Init(FairDb::kString,kMaxMySQLText); }
    return;
  }

  MAXDBLOG("FairDb",FairDbLog::kError,20)
      << "Unable to define a SQL FairDbFieldType from: " << type << endl;
  this->Init(FairDb::kUnknown);

}


FairDbFieldType::FairDbFieldType(const FairDbFieldType& from)
  : fConcept(from.fConcept),
    fSize(from.fSize),
    fType(from.fType)
{
  *this = from;
}


FairDbFieldType::FairDbFieldType(const string& sql,
                                 Int_t size )
  : fConcept(0),
    fSize(0),
    fType(0)
{


  if (         sql == "TINYINT" ) { this->Init(FairDb::kTiny); }

  else if (    sql == "SMALLINT" ) { this->Init(FairDb::kShort); }

  else if (    sql == "INT"
               || sql == "INTEGER"
               || sql == "NUMERIC" ) { this->Init(FairDb::kInt); }

  else if (     sql == "BIGINT" ) { this->Init(FairDb::kLong); }

  else if (    sql == "FLOAT"
               || sql == "REAL") { this->Init(FairDb::kFloat); }

  else if (    sql == "DOUBLE" ) { this->Init(FairDb::kDouble); }

  else if (    sql == "CHAR"
               || sql == "VARCHAR"
               || sql == "TEXT"
               || sql == "TINYTEXT" ) {

    if      ( sql == "TINYTEXT" ) { size = kMaxMySQLVarchar; }
    else if ( sql == "TEXT"     ) { size = kMaxMySQLText; }
    else {
      if ( size < 0 ) {
        if ( sql == "CHAR" ) { size = 1; }
        else { size = kMaxMySQLVarchar -1; }
      }
    }
    if ( fSize <= kMaxChar ) { this->Init(FairDb::kChar,size); }
    else { this->Init(FairDb::kString,size); }

  }

  else if ( sql == "DATETIME" )  { this->Init(FairDb::kDate); }
  else if ( sql == "TIMESTAMP" ) { this->Init(FairDb::kDate); }


  else {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Unable to do typing from SQL: " << sql << endl;
    this->Init(FairDb::kUnknown);
  }

}


FairDbFieldType::~FairDbFieldType()
{
}


string FairDbFieldType::AsString() const
{

  switch ( fType ) {

  case  FairDb::kBool    :
    return "Bool";
  case  FairDb::kChar    :
    return "Char";
  case  FairDb::kUChar   :
    return "UChar";
  case  FairDb::kTiny    :
    return "Tiny";
  case  FairDb::kUTiny   :
    return "UTiny";
  case  FairDb::kShort   :
    return "Short";
  case  FairDb::kUShort  :
    return "UShort";
  case  FairDb::kInt     :
    return "Int";
  case  FairDb::kUInt    :
    return "UInt";
  case  FairDb::kLong    :
    return "Long";
  case  FairDb::kULong   :
    return "ULong";
  case  FairDb::kFloat   :
    return "Float";
  case  FairDb::kDouble  :
    return "Double";
  case  FairDb::kString  :
    return "String";
  case  FairDb::kTString :
    return "TString";
  case  FairDb::kDate    :
    return "Date";
  }
  return "Unknown";
}

string FairDbFieldType::AsSQLString(FairDb::DbTypes dbType) const
{

  ostringstream os;

//  Deal with MySQL ddl

  if ( dbType == FairDb::kMySQL ) {
    switch ( fType ) {

    case  FairDb::kBool    :
      os << "CHAR";
      break;

    case  FairDb::kUTiny   :
    case  FairDb::kTiny    :
      os << "TINYINT";
      break;

    case  FairDb::kShort   :
    case  FairDb::kUShort  :
      os << "SMALLINT";
      break;

    case  FairDb::kInt     :
    case  FairDb::kUInt    :
      os << "INT";
      break;

    case  FairDb::kLong    :
    case  FairDb::kULong   :
      os << "BIGINT";
      break;

    case  FairDb::kFloat   :
      os << "FLOAT";
      break;

    case  FairDb::kDouble  :
      os << "DOUBLE";
      break;

    case  FairDb::kChar    :
    case  FairDb::kUChar   :
    case  FairDb::kString  :
    case  FairDb::kTString :
      if      ( fSize == 1) { os << "CHAR"; }
      else if ( fSize <= kMaxChar) { os << "CHAR("    << fSize << ')'; }
      else if ( fSize <  kMaxMySQLVarchar) { os << "VARCHAR(" << fSize << ')'; }
      else if ( fSize == kMaxMySQLVarchar) { os << "TINYTEXT"; }
      else { os << "TEXT"; }
      break;

    case  FairDb::kDate    :
      os << "DATETIME";
      break;

    default :
      os << "Unknown";

    }
  }

//  Deal with SQLLite
  else if ( dbType == FairDb::kSQLite) {

    int size = fSize;

    switch ( fType ) {

    case  FairDb::kBool    :
      os << "NUMERIC";
      break;

    case  FairDb::kUTiny   :
    case  FairDb::kTiny    :
      os << "INTEGER";
      break;

    case  FairDb::kShort   :
    case  FairDb::kUShort  :
      os << "INTEGER";
      break;

    case  FairDb::kInt     :
    case  FairDb::kUInt    :
      os << "INTEGER";
      break;

    case  FairDb::kLong    :
    case  FairDb::kULong   :
      os << "INTEGER";
      break;

    case  FairDb::kFloat   :
      os << "REAL";
      break;

    case  FairDb::kDouble  :
      os << "REAL";
      break;

    case  FairDb::kChar    :
    case  FairDb::kUChar   :
    case  FairDb::kString  :
    case  FairDb::kTString :
      os << "TEXT";
      break;

    case  FairDb::kDate    :
      os << "DATETIME";
      break;

    default :
      os << "Unknown";

    }
  }

//  Deal with PostgreSQL
  else if ( dbType == FairDb::kPostgreSQL) {

    int size = fSize;
    if ( fSize < kMaxOracleVarchar ) { size = kMaxOracleVarchar; }

    switch ( fType ) {

    case  FairDb::kBool    :
      os << "CHAR";
      break;

    case  FairDb::kUTiny   :
    case  FairDb::kTiny    :
      os << "SMALLINT";
      break;

    case  FairDb::kShort   :
    case  FairDb::kUShort  :
      os << "SMALLINT";
      break;

    case  FairDb::kInt     :
    case  FairDb::kUInt    :
      os << "INT";
      break;

    case  FairDb::kLong    :
    case  FairDb::kULong   :
      os << "BIGINT";
      break;

    case  FairDb::kFloat   :
      os << "REAL";
      break;

    case  FairDb::kDouble  :
      os << "DOUBLE PRECISION";
      break;

    case  FairDb::kChar    :
    case  FairDb::kUChar   :
    case  FairDb::kString  :
    case  FairDb::kTString :
      if      ( size == 1) { os << "CHAR"; }
      else if ( size <= kMaxChar) { os << "CHAR("    << size << ')'; }
      else { os << "VARCHAR(" << size << ')'; }
      break;

    case  FairDb::kDate    :
      os << "TIMESTAMP WITHOUT TIME ZONE";
      break;

    default :
      os << "Unknown";

    }
  }

//  Deal with ORACLE ddl
  else if ( dbType == FairDb::kOracle) {

    int size = fSize;
    if ( fSize < kMaxOracleVarchar ) { size = kMaxOracleVarchar; }

    switch ( fType ) {

    case  FairDb::kBool    :
      os << "CHAR";
      break;

    case  FairDb::kUTiny   :
    case  FairDb::kTiny    :
      os << "NUMBER(4)";
      break;

    case  FairDb::kShort   :
    case  FairDb::kUShort  :
      os << "NUMBER(6)";
      break;

    case  FairDb::kInt     :
    case  FairDb::kUInt    :
      os << "NUMBER(11)";
      break;

    case  FairDb::kLong    :
    case  FairDb::kULong   :
      os << "NUMBER(20)";
      break;

    case  FairDb::kFloat   :
      os << "BINARY_FLOAT";
      break;

    case  FairDb::kDouble  :
      os << "BINARY_DOUBLE";
      break;

    case  FairDb::kChar    :
    case  FairDb::kUChar   :
    case  FairDb::kString  :
    case  FairDb::kTString :
      if      ( size == 1) { os << "CHAR"; }
      else if ( size <= kMaxChar) { os << "CHAR("    << size << ')'; }
      else { os << "VARCHAR(" << size << ')'; }
      break;

    case  FairDb::kDate    :
      os << "DATE";
      break;

    default :
      os << "Unknown";

    }
  }

  return os.str();
}



void FairDbFieldType::Init(Int_t type,
                           Int_t size  )
{

  switch ( type ) {

  case FairDb::kBool :
    fType      = FairDb::kBool;
    fConcept   = FairDb::kBool;
    fSize      = 1;
    break;

  case FairDb::kChar :
    fType      = FairDb::kChar;
    fConcept   = FairDb::kChar;
    fSize      = 1;
    break;

  case FairDb::kUChar :
    fType      = FairDb::kUChar;
    fConcept   = FairDb::kUChar;
    fSize      = 1;
    break;

  case FairDb::kTiny :
    fType      = FairDb::kTiny;
    fConcept   = FairDb::kInt;
    fSize      = 1;
    break;

  case FairDb::kUTiny :
    fType      = FairDb::kUTiny;
    fConcept   = FairDb::kUInt;
    fSize      = 1;
    break;

  case FairDb::kShort :
    fType      = FairDb::kShort;
    fConcept   = FairDb::kInt;
    fSize      = 2;
    break;

  case FairDb::kUShort :
    fType      = FairDb::kUShort;
    fConcept   = FairDb::kUInt;
    fSize      = 2;
    break;

  case FairDb::kInt :
    fType      = FairDb::kInt;
    fConcept   = FairDb::kInt;
    fSize      =  size = 4;
    break;

  case FairDb::kUInt :
    fType      = FairDb::kUInt;
    fConcept   = FairDb::kUInt;
    fSize      = 4;
    break;

  case FairDb::kLong :
    fType    = FairDb::kLong;
    fConcept = FairDb::kInt;
    fSize    = 8;
    break;

  case FairDb::kULong :
    fType    = FairDb::kULong;
    fConcept = FairDb::kUInt;
    fSize    = 8;
    break;

  case FairDb::kFloat :
    fType      = FairDb::kFloat;
    fConcept   = FairDb::kFloat;
    fSize      = 4;
    break;

  case FairDb::kDouble :
    fType      = FairDb::kDouble;
    fConcept   = FairDb::kFloat;
    fSize      = 8;
    break;

  case FairDb::kString :
    fType      = FairDb::kString;
    fConcept   = FairDb::kString;
    fSize      = 65535;
    break;

  case FairDb::kTString :
    fType      = FairDb::kTString;
    fConcept   = FairDb::kString;
    fSize      = 65535;
    break;

  case FairDb::kDate :
    fType      = FairDb::kDate;
    fConcept   = FairDb::kDate;
    fSize      = 4;
    break;

  case FairDb::kUnknown :
    fType      = FairDb::kUnknown;
    fConcept   = FairDb::kUnknown;
    break;

  default :
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Unable to form Root FairDbFieldType from: " << type << endl;
    fType      = FairDb::kUnknown;
    fConcept   = FairDb::kUnknown;
    fSize      = 0;
  }

  if ( size      >= 0  ) { fSize      = size; }

}


Bool_t FairDbFieldType::IsCompatible(const FairDbFieldType& other) const
{

#define MATCHES(x,y)  \
     (fConcept == x) && (concept == y) \
  || (fConcept == y) && (concept == x)

  UInt_t concept = other.GetConcept();
  if ( fConcept == concept ) { return kTRUE; }
  if ( MATCHES(FairDb::kBool,  FairDb::kChar)  ) { return kTRUE; }
  if ( MATCHES(FairDb::kBool,  FairDb::kUChar) ) { return kTRUE; }
  if ( MATCHES(FairDb::kInt,   FairDb::kChar)  ) { return kTRUE; }
  if ( MATCHES(FairDb::kUInt,  FairDb::kUChar) ) { return kTRUE; }
  if ( MATCHES(FairDb::kUInt,  FairDb::kInt)   ) { return kTRUE; }
  if ( concept == FairDb::kChar && fConcept == FairDb::kString ) { return kTRUE; }

  //  cout << " -I- FairDbFieldType compatibility: " << fConcept << " : " << concept << endl;

  return kFALSE;
}

string FairDbFieldType::UndefinedValue() const
{
  switch ( fConcept ) {
  case FairDb::kBool   :
    return "0";
  case FairDb::kChar   :
    return "";
  case FairDb::kUChar  :
    return "";
  case FairDb::kInt    :
    return "-999";
  case FairDb::kUInt   :
    return " 999";
  case FairDb::kFloat  :
    return "-999.";
  case FairDb::kString :
    return "";
  case FairDb::kDate   :
    return "1980-00-00 00:00:00";

  default :
    MAXDBLOG("FairDb",FairDbLog::kError,20)<< "Unable to define undefined type for: "
                                           << fConcept << endl;
    return "";
  }
}
