/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConnectionPool.h"

#include "FairDb.h"                     // for GetValDefinition, etc
#include "FairDbLogService.h"
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbStatement.h"            // for FairDbStatement
#include "FairDbString.h"               // for FairDbString, StringTok, etc

#include "TSQLStatement.h"              // for TSQLStatement
#include "TString.h"                    // for TString
#include "TSystem.h"                    // for TSystem, gSystem

#include <ctype.h>                      // for islower
#include <cstdlib>                      // for exit
#include <iostream>                     // for cout
#include <memory>                       // for auto_ptr, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;
using std::ostringstream;
using std::map;
using std::auto_ptr;
using std::string;

ClassImp(FairDbConnectionPool)

FairDbConnectionPool::FairDbConnectionPool():
  fGlobalSeqNoDbNo(-1),
  fConnections(),
  fTemporaryTables()
{

//  Environment variables defined at initialization:
//
//    FAIRDB_DB_URL             a semi-colon separated list of URLs
//    FAIRDB_DB_USER            user name (one or a semi-colon separated list)
//    FAIRDB_DB_PSWD            password (one or a semi-colon separated list)

// Extract arguments from  FAIRDB_DB environmental variables
  const char*      strUser = gSystem->Getenv("FAIRDB_TSQL_UPDATE_USER");
  if ( ! strUser ) { strUser = gSystem->Getenv("FAIRDB_TSQL_USER"); }
  const char*      strPswd = gSystem->Getenv("FAIRDB_TSQL_UPDATE_PSWD");
  if ( ! strPswd ) { strPswd = gSystem->Getenv("FAIRDB_TSQL_PSWD"); }
  const char*       strUrl = gSystem->Getenv("FAIRDB_TSQL_UPDATE_URL");
  if ( !strUrl ) { strUrl = gSystem->Getenv("FAIRDB_TSQL_URL"); }
  string userList     = ( strUser ) ? strUser : "";
  string pswdList     = ( strPswd ) ? strPswd : "";
  string urlList      = ( strUrl  ) ? strUrl  : "";

  if ( urlList == "" || userList == "" || pswdList == "" ) {
    DBLOG("FairDbLog",FairDbLog::kFatal)
        << "Cannnot open a Database cascade;\n"
        << "   the environmental variables FAIRDB_DB_*:-" << endl
        << "USER: \"" << userList << "\" PSWD:\"" << pswdList
        << "\" URL:\"" << urlList << endl
        << " are either not defined or empty.\n"
        << "   Please check your settings of FAIRDB_DB_USER,"
        << " FAIRDB_DB_PSWD and FAIRDB_DB_URL\n"
        << "Aborting due to above errors ... " << endl;
    exit(1);
  }

  std::vector<std::string> users, pswds, urls;
  FairUtilString::StringTok(users, userList, ";");
  FairUtilString::StringTok(pswds, pswdList, ";");
  FairUtilString::StringTok(urls,  urlList,  ";");

  bool fail = false;

  for (unsigned entry = 0; entry < urls.size(); ++entry ) {
    string url  = urls[entry];
    string user = ( entry >= users.size() ) ? users[0] : users[entry];
    string pswd = ( entry >= pswds.size() ) ? pswds[0] : pswds[entry];

    // Empty password designated as '\0'
    if ( pswd == "\\0" ) { pswd = ""; }

    FairDbConnection* con = new FairDbConnection(url,user,pswd);
    fConnections.push_back(con);
    if ( ! con->Open() ) {
      fail = true;
      continue;
    }

    // Try locate first Global Seq. No. in FAIRDBGLOBALSEQNO table.
    if ( fGlobalSeqNoDbNo != -1 ) { continue; }

    auto_ptr<FairDbStatement>  stmtDb(new FairDbStatement(*con));
    // First check
    if ( ! stmtDb.get() ) { continue; }

    // Apply
    TSQLStatement* stmt = NULL;
    size_t found = url.find("sqlite://");
    if (found!=string::npos) {
      stmt=stmtDb->ExecuteQuery("SELECT name FROM sqlite_master WHERE type='table' AND name='FAIRDBGLOBALSEQNO'");
    } else {
      stmt=stmtDb->ExecuteQuery("select * from FAIRDBGLOBALSEQNO where 1=0");
    }

    if ( stmt ) {
      fGlobalSeqNoDbNo = fConnections.size()-1;
      delete stmt;
      stmt = 0;
    }
    cout << "-I- FAIRDbConnectionPool  fGlobalSeqNoDbNo  " <<  fGlobalSeqNoDbNo << endl;

    //  Check for presence of a DB_STATE_FLAGS table
    if ( this->GetTableDbNo("FAIRDB_STATE_FLAGS",entry) != -1 ) {
      DBLOG("FairDbLog",FairDbLog::kFatal)  << " POSSIBLE MIXED/CUT VERSION DETECTED !!!\n"
                                            << "    The FAIRDB_STATE_FLAGS table is present on DB entry "
                                            << entry << ".  This table will\n"
                                            << "    only be introduced to manage backward incompatible changes that could lead\n"
                                            << "    to version shear between the code and the database.  This version of the\n"
                                            << "    code does not support the change the presence of that table indicates\n"
                                            << "    so has to shut down. \n";
      fail = true;
    }

  } //! DB entries

// Here print a server status
  DBLOG("FairDb",FairDbLog::kInfo) << *this;

//  Abort if failures
  if ( fail ) {
    DBLOG("FairDb",FairDbLog::kFatal) << "Aborting due to above errors" << endl;
    exit(1);
  }

}


FairDbConnectionPool::FairDbConnectionPool(const FairDbConnectionPool& conn)
  :   fGlobalSeqNoDbNo(conn.fGlobalSeqNoDbNo),
      fConnections(conn.fConnections),
      fTemporaryTables(conn.fTemporaryTables)
{
  /*
  fGlobalSeqNoDbNo=conn.fGlobalSeqNoDbNo;
  fConnections=conn.fConnections;
  fTemporaryTables=conn.fTemporaryTables;
  */
}


FairDbConnectionPool::~FairDbConnectionPool()
{

  DBLOG("FairDb",FairDbLog::kDebug)  << " Destroying FairDbConnectionPool"
                                     << endl;
  for (Int_t dbNo = this->GetNumDb()-1; dbNo >= 0; --dbNo) {
    if (fConnections[dbNo]) {delete fConnections[dbNo]; fConnections[dbNo]=NULL;}
  }

}



ostream& operator<<(ostream& os, const FairDbConnectionPool& cascader)
{
  os << endl;
  os << endl << "                                   FairDbConnectionPool:: Server Status : "     << endl
     << "                                                          Status   URL: " ;

  int maxDb = cascader.GetNumDb();
  for (Int_t dbNo = 0; dbNo < maxDb; ++dbNo)
    os << cascader.GetStatusAsString(dbNo) << " "
       << ( ( dbNo == cascader.fGlobalSeqNoDbNo ) ? "(auth)  " : "        ")
       << cascader.GetURL(dbNo) << endl;
  os << endl;
  return os;

}



Int_t FairDbConnectionPool::AllocateSeqNo(const string& tableName,
    Int_t requireGlobal,
    Int_t dbNo ) const
{
  bool isTemporary = IsTemporaryTable(tableName,dbNo);

  // Global requests.
  if (     requireGlobal > 0
           || ( requireGlobal == 0 && dbNo == fGlobalSeqNoDbNo && ! isTemporary ) ) {
    if ( fGlobalSeqNoDbNo < 0 ) {
      DBLOG("FairDb",FairDbLog::kWarning) << "Unable to issue global SEQNO - no authorising DB in the Db list\n"
                                          << "  will issue local one instead" << endl;
    } else if ( isTemporary ) {
      DBLOG("FairDb",FairDbLog::kWarning) << "Unable to issue global SEQNO - " << tableName << " is temporary\n"
                                          << "  will issue local one instead" << endl;
    } else { return this->ReserveNextSeqNo(tableName,true,fGlobalSeqNoDbNo); }
  }

  return this->ReserveNextSeqNo(tableName,false,dbNo);
}

FairDbStatement* FairDbConnectionPool::CreateStatement(UInt_t dbNo) const
{

  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  FairDbConnection& conDb = *fConnections[dbNo];
  FairDbStatement* stmtDb = new FairDbStatement(conDb);
  stmtDb->PrintExceptions();
  return stmtDb;

}

Int_t FairDbConnectionPool::CreateTemporaryTable(const string& tableNameMc,
    const string& tableDescr)
{

  string tableName = FairUtilString::ToUpper(tableNameMc);
  if (    tableName == ""
          || tableDescr[0] != '('
          || tableDescr[tableDescr.size()-1] != ')' ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Illegal input args:-" << endl
                                            << "     Table Name: " << tableName
                                            << "  Table Description: " << tableDescr
                                            <<endl;
    return -1;
  }

// Find a DB that will accept the command.
  string sqlMakeTable;

  Int_t dbNoAcc       = -1;
  auto_ptr<FairDbStatement> stmtDb;
  for (UInt_t dbNoTry = 0; dbNoTry < fConnections.size(); ++dbNoTry ) {
    stmtDb.reset(this->CreateStatement(dbNoTry));
    if ( stmtDb.get() ) {
      sqlMakeTable = " create temporary table ";
      sqlMakeTable += tableName;
      sqlMakeTable += " ";
      sqlMakeTable += tableDescr;
      sqlMakeTable += ";";
      stmtDb->ExecuteUpdate(sqlMakeTable.c_str());
      if ( stmtDb->GetExceptionLog().IsEmpty() ) {
        dbNoAcc = dbNoTry;
        this->GetConnection(dbNoAcc)->SetTableExists(tableName);
        break;
      }
      // Print exceptions if needed
      if (FairDbLogService::Instance()->IsActive("FairDb",FairDbLog::kWarning)) { stmtDb->PrintExceptions(); }
    }
  }

  if ( dbNoAcc < 0 ) {
    if ( stmtDb.get()) { stmtDb->PrintExceptions(); }
    return -1;
  }

// Make connection permanent if not already.
  FairDbConnection& conDb = *fConnections[dbNoAcc];
  if ( conDb.IsTemporary() ) {
    conDb.SetPermanent();
    DBLOG("FairDb",FairDbLog::kWarning) << "Making connection: " << conDb.GetUrl()
                                        << " permanent to preserve temporary tables." << endl;
  }

// Create SQL to create auxillary validity table and write to same Db.
  sqlMakeTable = FairDb::GetValDefinition(tableName.c_str(),true);

  DBLOG("FairDb",FairDbLog::kWarning) << "Validity Table creation: "
                                      << " Database: " << dbNoAcc << " "
                                      << sqlMakeTable << endl;
  stmtDb->ExecuteUpdate(sqlMakeTable.c_str());
  if ( stmtDb->PrintExceptions() ) { return -1; }
  this->GetConnection(dbNoAcc)->SetTableExists(tableName+"VAL");
  fTemporaryTables[tableName] = dbNoAcc;
  return dbNoAcc;

}


const FairDbConnection* FairDbConnectionPool::GetConnection(UInt_t dbNo) const
{

  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  return fConnections[dbNo];

}


FairDbConnection* FairDbConnectionPool::GetConnection(UInt_t dbNo)
{

  if ( this->GetStatus(dbNo) == kFailed ) { return 0; }
  return fConnections[dbNo];

}

string FairDbConnectionPool::GetDbName(UInt_t dbNo) const
{

  string dbName;

  if ( dbNo < this->GetNumDb() ) { dbName = fConnections[dbNo]->GetDbName(); }
  else {  DBLOG("FairDb",FairDbLog::kInfo)  << "Database does not contain entry " << dbNo << endl; }
  return dbName;

}


Int_t FairDbConnectionPool::GetDbNo(const string& dbName) const
{
  for ( unsigned dbNo = 0; dbNo < this->GetNumDb(); ++dbNo) {
    if ( dbName == fConnections[dbNo]->GetDbName() ) { return dbNo; }
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "Database does not contain entry " << dbName << endl;
  return -1;

}


string FairDbConnectionPool::GetStatusAsString(UInt_t dbNo) const
{

  Int_t status = GetStatus(dbNo);

  switch ( status ) {
  case kClosed:
    return "Closed";
  case kOpen:
    return "Open  ";
  default:
    return "Failed";
  }

}
Int_t FairDbConnectionPool::GetTableDbNo(const string& tableName,
    Int_t selectDbNo /* -1 */) const
{
  string::const_iterator itr    = tableName.begin();
  string::const_iterator itrEnd = tableName.end();
  while ( itr != itrEnd ) if ( islower(*itr++) ) { return -1; }

// Loop over databases list
  for (UInt_t dbNoTry = 0; dbNoTry < fConnections.size(); ++dbNoTry ) {
    if ( selectDbNo >= 0 && (UInt_t) selectDbNo != dbNoTry ) { continue; }
    const FairDbConnection* con =  this->GetConnection(dbNoTry);
    if ( con && con->TableExists(tableName) ) { return dbNoTry; }
  }

  return -1;

}


void FairDbConnectionPool::HoldConnections()
{

  for (UInt_t dbNo = 0; dbNo < fConnections.size(); ++dbNo ) {
    fConnections[dbNo]->ConnectStatement();
  }
}

Bool_t FairDbConnectionPool::IsTemporaryTable(const string& tableName,
    Int_t dbNo) const
{

  map<string,Int_t>::const_iterator itr
  = fTemporaryTables.find(tableName);
  return (     itr != fTemporaryTables.end()
               &&  (*itr).second == dbNo );

}



FairDbConnectionPool::BLock::BLock(FairDbStatement* stmtDB, const string& seqnoTable, const string& dataTable) :
  fStmt(stmtDB),
  fSeqnoTableName(seqnoTable),
  fDataTableName(dataTable),
  fLocked(kFALSE)
{
  if ( ! fStmt ) {
    DBLOG("FairDb",FairDbLog::kError)<< "Block  Cannot obtain statment to set lock" << endl;
    return;
  }

  this->SetBLock(kTRUE);

}

FairDbConnectionPool::BLock::~BLock()
{

  this->SetBLock(kFALSE);
  delete fStmt;
  fStmt = 0;

}

void FairDbConnectionPool::BLock::SetBLock(Bool_t setting)
{
  if ( setting == fLocked || ! fStmt ) { return; }

  if ( fStmt->GetDBType() != FairDb::kMySQL ) {
    fLocked = setting;
    return;
  }

  string sql;

  if ( setting ) {
    sql = "LOCK TABLES ";
    sql += fSeqnoTableName + " WRITE";
    if ( fDataTableName != "" ) { sql += ", " + fDataTableName  + "VAL WRITE"; }
  } else {
    sql = "UNLOCK TABLES;";
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "Lock requested: " << setting
                                   << " issuing lock command: " << sql << endl;
  fStmt->ExecuteUpdate(sql.c_str());
  if ( fStmt->GetExceptionLog().IsEmpty() ) { fLocked = setting; }
  fStmt->PrintExceptions();

}

void FairDbConnectionPool::ReleaseConnections()
{

  for (UInt_t dbNo = 0; dbNo < fConnections.size(); ++dbNo ) {
    fConnections[dbNo]->DisConnectStatement();
  }
}

Int_t FairDbConnectionPool::ReserveNextSeqNo(const string& tableName,
    Bool_t isGlobal,
    UInt_t dbNo) const
{

  FairDbString sql;

  string seqnoTableName = isGlobal ? "FAIRDBGLOBALSEQNO" : "FAIRDBLOCALSEQNO";
  bool seqnoTableNameExists = this->TableExists(seqnoTableName,dbNo);
  bool tableNameExists      = this->TableExists(tableName,dbNo);

  auto_ptr<FairDbStatement> stmtDb(this->CreateStatement(dbNo) );
  if ( ! stmtDb.get() ) { return 0; }

  // Check that required SEQNO table exists.
  if ( isGlobal ) {
    if ( ! seqnoTableNameExists ) {
      DBLOG("FairDb",FairDbLog::kInfo)<< "Unable to issue global SEQNO - " << dbNo
                                      << " is not an authorising DB" << endl;
      return 0;
    }
  } else {
    if ( ! seqnoTableNameExists ) {
      sql.Clear();
      sql << "CREATE TABLE " << seqnoTableName
          << "(TABLENAME      CHAR(64) NOT NULL PRIMARY KEY,\n"
          << " LASTUSEDSEQNO  INT )";

      DBLOG("FairDb",FairDbLog::kInfo)<< "Database: " << dbNo
                                      << " create local SEQNO table query: " << sql.c_str() << endl;
      stmtDb->ExecuteUpdate(sql.c_str());
      if ( stmtDb->PrintExceptions() ) { return 0; }
      sql.Clear();
      sql << "INSERT INTO " <<  seqnoTableName << " VALUES ('*',0)";
      DBLOG("FairDb",FairDbLog::kInfo)<< "Database: " << dbNo
                                      << " prime local SEQNO table query: " << sql.c_str() << endl;
      stmtDb->ExecuteUpdate(sql.c_str());
      if ( stmtDb->PrintExceptions() ) { return 0; }
    }
  }


  string dataTable;

  if (  ! this->IsTemporaryTable(tableName,dbNo)
        && tableNameExists ) { dataTable = tableName; }
  BLock Block(this->CreateStatement(dbNo),seqnoTableName,dataTable);
  if ( ! Block.IsBLocked() ) {
    DBLOG("FairDb",FairDbLog::kInfo)<< "Unable to lock " << seqnoTableName << endl;
    return 0;
  }


  sql.Clear();
  sql << "select * from " << seqnoTableName << " where TABLENAME = '*' or TABLENAME = '";
  sql << tableName + "' order by TABLENAME";
  DBLOG("FairDb",FairDbLog::kInfo)<< " tablename: "<< seqnoTableName << " query: " << sql.c_str() << endl;
  TSQLStatement* stmt = stmtDb->ExecuteQuery(sql.c_str());
  stmtDb->PrintExceptions(FairDbLog::kDebug);
  Int_t seqNoDefault = 0;
  if ( stmt && stmt->NextResultRow() ) {
    seqNoDefault = stmt->GetInt(1);
  } else {
    DBLOG("FairDb",FairDbLog::kInfo)<< "Unable to find default SeqNo"
                                    << " due to above error" << endl;
    delete stmt;
    stmt = 0;
    return 0;
  }
  Int_t seqNoTable = seqNoDefault;
  if ( stmt->NextResultRow() ) {
    seqNoTable = stmt->GetInt(1);
  }
  delete stmt;
  stmt = 0;
  DBLOG("FairDb",FairDbLog::kInfo)<< "query returned last generated seqno: " << seqNoTable << endl;


  static std::string checkedCombinations;
  ostringstream combination;
  combination << ":" << tableName << isGlobal << dbNo << ":";
  bool notChecked = checkedCombinations.find(combination.str()) == std::string::npos;
  if ( notChecked ) { checkedCombinations += combination.str(); }
  if ( tableNameExists && notChecked ) {
    Int_t seqNoMin = seqNoDefault;
    Int_t seqNoMax = seqNoDefault + FairDb::kMAXLOCALSEQNO;
    sql.Clear();
    sql << "select max(SEQNO) from " << tableName << "VAL"
        << " where SEQNO between " << seqNoMin << " and " << seqNoMax;
    DBLOG("FairDb",FairDbLog::kInfo)<< "Database: " << dbNo
                                    << " max  SEQNO query: " << sql.c_str() << endl;
    stmt  =  stmtDb->ExecuteQuery(sql.c_str());
    if ( stmtDb->PrintExceptions() ) { return 0; }
    Int_t  minValue = 0;
    // Queries returning group function results can be null.
    if (  stmt && stmt->NextResultRow() && ! stmt->IsNull(0) ) {
      minValue = stmt->GetInt(0);
      if ( minValue <= 0 ) { minValue = 0; }  // Should never happen.
    }
    delete stmt;
    stmt = 0;

    if ( minValue > seqNoTable ) {
      DBLOG("FairDb",FairDbLog::kInfo)
          << "Database: " << dbNo << " "
          << seqnoTableName << " has last used SEQNO of "
          << seqNoTable << " for table " << tableName
          << ",\n    but the highest SEQNO in the band " << seqNoMin << " to " << seqNoMax
          << " is " <<  minValue << " for that table\n    "
          << seqnoTableName << " is out of date! It will be updated for " << tableName << endl;
      seqNoTable = minValue;
    }
  }


  sql.Clear();
  sql << "delete from " << seqnoTableName << " where TABLENAME='";
  sql << tableName + "'";
  DBLOG("FairDb",FairDbLog::kInfo)<< "SEQNO entry removal: "
                                  << sql.c_str() << endl;
  stmtDb->ExecuteUpdate(sql.c_str());
  if ( stmtDb->PrintExceptions() ) { return 0; }

  seqNoTable++;

  sql.Clear();
  sql << "insert into  " << seqnoTableName << " values('";
  sql << tableName + "'," << seqNoTable << ")";
  DBLOG("FairDb",FairDbLog::kInfo)<< "SEQNO entry add: "
                                  << sql.c_str() << endl;
  stmtDb->ExecuteUpdate(sql.c_str());
  if ( stmtDb->PrintExceptions() ) { return 0; }

  return seqNoTable;

}

void FairDbConnectionPool::SetPermanent(UInt_t dbNo,
                                        Bool_t permanent  )
{
  if ( dbNo < fConnections.size() ) {
    fConnections[dbNo]->SetPermanent(permanent);
  }
}

Int_t FairDbConnectionPool::CreateTransientTable(const std::string& tableName,
    const std::string& tableDescr)
{
  // create transient table
  return  CreateTemporaryTable(tableName,tableDescr);
}
