/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConnection.h"
#include "FairDbLogService.h"
#include "Riosfwd.h"                    // for ostream
#include "TSQLServer.h"                 // for TSQLServer
#include "TSQLStatement.h"              // for TSQLStatement
#include "TSystem.h"                    // for TSystem, gSystem
#include "TObjArray.h"
#include "TObjString.h"

#include <algorithm>                    // for transform
#include <cctype>                       // for toupper
#include <cstdlib>                      // for NULL, exit
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>
#include <string>                       // for string, basic_string, etc

using namespace std;

ClassImp(FairDbConnection)

FairDbConnection::FairDbConnection(
  const string& url,
  const string& user,
  const string& password)
  : fDbName(),
    fUser(user),
    fPassword(password),
    fExistingTableList(),
    fSchema(""),
    fNumConnectedStatements(0),
    fUrl(url.c_str()),
    fUrlValidated(kFALSE),
    fIsTemporary(kTRUE),
    fDbType(FairDb::kUnknownDbType),
    fServer(NULL),
    fExceptionLog()
{

// Wrapper to a DB connection
  DBLOG("FairDb",FairDbLog::kInfo) << "Creating a DB connection" << endl;

  // Get Eventually a Schema (PgSQL)
  TString aUrl(this->GetUrl());
  TObjArray* ll = aUrl.Tokenize("/");
  Int_t n_tok = ll->GetEntries();
  TObjString* o_str = (TObjString*) ll->At(n_tok-1);
  fSchema = o_str->GetString();


  if ( this->Open() ) {

    DBLOG("FairDb",FairDbLog::kInfo)  << "successfully opened connection to: "
                                      << this->GetUrl() << endl;
    fUrlValidated =  kTRUE;

    // First get which server do we use ...
    string productName(fServer->GetDBMS());
    // Get the c_strbase type
    if( productName == "MySQL" ) { fDbType = FairDb::kMySQL; }
    else if ( productName == "Oracle" ) { fDbType = FairDb::kOracle; }
    else if ( productName == "PgSQL" ) { fDbType = FairDb::kPostgreSQL;}
    else if ( productName == "SQLite" ) { fDbType = FairDb::kSQLite;}

    else {
      MAXDBLOG("FairDb",FairDbLog::kError,20) << " Cannot determine DB type from name: "
                                              <<  productName
                                              << "\nWill assuming MySql database " << endl;
      fDbType = FairDb::kMySQL;
    }


    // Initialise the list existing supported tables.
    // Here all existing tables from the database will be added to the
    // central list of existing tables;

    this->SetTableExists();

    // Check if one can use prepared statement on the server
    if ( fUrlValidated ) {
      if ( ! fServer->HasStatement() ) {
        DBLOG("FairDb",FairDbLog::kError)  << " This client does not support prepared statements." << endl;
        fUrlValidated = kFALSE;
      }
      string serverInfo(fServer->ServerInfo());
      if ( fDbType == FairDb::kMySQL &&  serverInfo < "4.1" ) {
        DBLOG("FairDb",FairDbLog::kInfo)  << " this MySQL server (" << serverInfo
                                          << ") does not support prepared statements." << endl;
        fUrlValidated = kFALSE;
      }

      if ( fUrlValidated ) {
        if (fDbType == FairDb::kMySQL)
          DBLOG("FairDb",FairDbLog::kInfo)  << " this client, and MySQL server ("
                                            << serverInfo
                                            << ") does support prepared statements." << endl;
        else if (fDbType == FairDb::kPostgreSQL)
          DBLOG("FairDb",FairDbLog::kInfo)  << " this client, and PostgreSQL server ("
                                            << serverInfo
                                            << ") does support prepared statements." << endl;
        else if (fDbType == FairDb::kSQLite)
          DBLOG("FairDb",FairDbLog::kInfo)  << " this client, and SQLite server ("
                                            << serverInfo
                                            << ") does support prepared statements." << endl;

      } else {

        if (fDbType == FairDb::kMySQL)
          DBLOG("FairDb",FairDbLog::kError) << "\n"
                                            << "This version of MySQL does not support prepared statements.\n"
                                            << "\n"
                                            << "Please upgrade to MySQL (client and server) version 4.1 or greater \n"
                                            << "\n"
                                            << endl;
        else if (fDbType == FairDb::kPostgreSQL)
          DBLOG("FairDb",FairDbLog::kError) << "\n"
                                            << "This version of PostgreSQL does not support prepared statements.\n"
                                            << "\n"
                                            << "Please upgrade to PostgreSQL (client and server) version 9.2 or greater \n"
                                            << "\n"
                                            << endl;

        else if (fDbType == FairDb::kSQLite)
          DBLOG("FairDb",FairDbLog::kError) << "\n"
                                            << "This version of SQLite does not support prepared statements.\n"
                                            << "\n"
                                            << "Please upgrade to SQLite (client and server) version 3.8 or greater \n"
                                            << "\n"
                                            << endl;


      }

    }//! fUrlValidated

    if ( ! fUrlValidated ) {
      DBLOG("FairDb",FairDbLog::kFatal) << "Aborting due to above errors" << endl;
      exit(1);
    }
  }

  // Get Db Name
  fDbName = fUrl.GetFile();


}


FairDbConnection::~FairDbConnection()
{
  DBLOG("FairDb",FairDbLog::kInfo)  <<" Droping Connection" << endl;
  this->Close(kTRUE);
}

Bool_t FairDbConnection::Open()
{

  this->ClearExceptionLog();

  if ( !this->IsClosed() ) { return kTRUE;}


  if ( ! fUrl.IsValid() ) {
    ostringstream oss;
    oss << "Unable to open connection: URL '" << fUrl.GetUrl() << "' is invalid";
    MAXDBLOG("FairDb",FairDbLog::kError,20) << oss.str() << endl;
    fExceptionLog.AddEntry(oss.str());
    return kFALSE;
  }

  Int_t maxAttempt = fUrlValidated ? 100 : 20;
  for (Int_t attempt = 1; attempt <= maxAttempt; ++attempt) {

    TString url_cstr = fUrl.GetUrl();
    // Main Connection call
    if (url_cstr.Contains("sqlite://")) {

      // Remove the tail from Url string
      TString aFile(this->GetUrl());
      aFile.Resize(aFile.Length()-1);
      //cout << " SQLite file " << aFile << endl;

      fServer = TSQLServer::Connect(
                  aFile.Data(),
                  fUser.c_str(),
                  fPassword.c_str());


    } else {
      fServer = TSQLServer::Connect(
                  fUrl.GetUrl(),
                  fUser.c_str(),
                  fPassword.c_str());
    }

    if ( ! fServer ) {
      ostringstream oss;
      oss  << "-I- FairDbConnection::Open() Failing to open: " <<
           fUrl.GetUrl() << " for user "
           << fUser << " and password "
           << fPassword << " (attempt "
           << attempt << ")";

      fExceptionLog.AddEntry(oss.str());

      if ( attempt == 1 ) {
        MAXDBLOG("FairDb",FairDbLog::kError,20) << oss.str() <<"retrying ..." << endl;
      }
      gSystem->Sleep(attempt*1000);
    } else {
      fServer->EnableErrorOutput(kTRUE);
      if ( attempt > 1 ) {
        DBLOG("FairDb",FairDbLog::kInfo) << "Connection opened on attempt "
                                         << attempt << endl;
      }
      DBLOG("FairDb",FairDbLog::kInfo)  << "Successfully opened connection to: "
                                        << fUrl.GetUrl() << endl;

      // <DB> Check me about !!!
      // ASCII database, populate it and make the connection permanent
      // unless even ASCII DB connections are temporary.
      return kTRUE;
    }
  }//! for on attempt

  MAXDBLOG("FairDb",FairDbLog::kError,20)   <<  "Failed to open a connection to: "
      << fUrl.GetUrl()
      << " for user " << fUser << " and pwd " << fPassword << endl;

  return kFALSE;
}

Bool_t FairDbConnection::Close(Bool_t force)
{

  this->ClearExceptionLog();

  if ( this->IsClosed() ) { return kTRUE; }

  if ( fNumConnectedStatements ) {
    if ( ! force ) {
      DBLOG("FairDb",FairDbLog::kInfo)<< "Unable to close connection: "
                                      << this->GetUrl()
                                      << "; it still has  "
                                      << fNumConnectedStatements << "active statements. " << endl;
      return kFALSE;
    }
    DBLOG("FairDb",FairDbLog::kInfo)<< "closing connection: "
                                    << this->GetUrl()
                                    << "; even though it still has "
                                    << fNumConnectedStatements << "active statements. " << endl;
  }

  delete fServer;
  fServer = NULL;
  DBLOG("FairDb",FairDbLog::kInfo)<< "closed connection: "
                                  << this->GetUrl() << endl;
  return kTRUE;
}

void FairDbConnection::CloseIdleConnection()
{
  if ( fIsTemporary &&  fNumConnectedStatements == 0 ) { this->Close(); }
}



TSQLStatement* FairDbConnection::CreatePreparedStatement(const string& sql)
{

  TSQLStatement* stmt = 0;
  if ( ! this->Open() ) { return stmt; }
  stmt = fServer->Statement(sql.c_str());

  if ( ! stmt ) {
    DBLOG("FairDb",FairDbLog::kInfo)<< "CreatePreparedStatement "
                                    << " no Statement created " << endl;
    //<DB> check me !! SQLite ptr fServer not valid
    if(fDbType != FairDb::kSQLite) { fExceptionLog.AddEntry(*fServer); }

  } else { stmt->EnableErrorOutput(kFALSE); }

  return stmt;
}


TSQLServer* FairDbConnection::GetServer()
{
  if ( ! this->Open() ) { return 0; }
  return fServer;
}

const string& FairDbConnection::GetUrl() const
{
  static string url;
  url = const_cast<FairDbConnection*>(this)->fUrl.GetUrl();
  return url;

}

void  FairDbConnection::SetTableExists(const string& tableName)
{

  // cout << "-I- FairDbConnection::SetTableExists()  ... " <<  tableName << endl;

  // Add name to list of existing tables
  // (necessary when creating tables)
  //  Note: If tableName is null refresh list from the database.

  if ( tableName == "" ) {
    TSQLStatement* stmt=NULL;
    if ( fDbType == FairDb::kMySQL || fDbType == FairDb::kOracle ) {
      // MYSQL or Oracle
      stmt =  CreatePreparedStatement("show tables");
    } else if ( fDbType == FairDb::kPostgreSQL ) {
      // PostGres using public only as schema
      TString sql_cmd = "SELECT table_name FROM information_schema.tables WHERE table_schema = 'public' or table_schema = '" + fSchema + "';";
      //cout << " sql_cmd -->" << sql_cmd << endl;
      stmt =  CreatePreparedStatement(sql_cmd.Data());
    } else if ( fDbType == FairDb::kSQLite ) {
      //SQLite
      stmt =  CreatePreparedStatement("SELECT name FROM sqlite_master WHERE type = 'table'");
    } else {
      DBLOG("FairDb",FairDbLog::kFatal)<< "Unknown SQL Server type:"<< fDbType << endl;
    }

    if ( stmt ) {
      if (stmt->Process()) {
        stmt->StoreResult();
        while (stmt->NextResultRow()) {
          string tn(stmt->GetString(0));
          std::transform(tn.begin(), tn.end(), tn.begin(), ::toupper);
          //cout << " -I FairDbConnection::SetTableExists table name: " << tn << endl;
          this->SetTableExists(tn);
        }
      }
      delete stmt;
      stmt = 0;
    }
  } else {
    if ( ! this->TableExists(tableName) ) {
      fExistingTableList += ",'";
      fExistingTableList += tableName;
      fExistingTableList += "'";
      //cout << "-I- FairDbConnection::Table Registered  ... " <<  tableName << endl;
    }
  }
  //  cout << "-I- FairDbConnection:: End of table exists ... " << endl;
}


Bool_t  FairDbConnection::TableExists(const string& tableName) const
{
//
//  Check to see table exists in connected database.

  string test("'");
  test += tableName;
  test += "'";
  Bool_t btest =  fExistingTableList.find(test) != std::string::npos;
  //cout << "-I- FairDbConnection: Table exists " << fExistingTableList << endl;
  return btest;
}




Bool_t FairDbConnection::PrintExceptionLog(Int_t level) const
{

  DBLOG("FairDb",level) << fExceptionLog;
  return fExceptionLog.Size() != 0;
}

void  FairDbConnection::RecordException()
{
  fExceptionLog.AddEntry(*fServer);
}



