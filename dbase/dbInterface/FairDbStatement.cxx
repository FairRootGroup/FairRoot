/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbStatement.h"
#include "FairDbLogService.h"
#include "FairDbString.h"               // for StringTok
#include "FairDbTableMetaData.h"        // for string, FairDbTableMetaData

#include "Riosfwd.h"                    // for ostream
#include "TSQLServer.h"                 // for TSQLServer
#include "TSQLStatement.h"              // for TSQLStatement
#include "TString.h"                    // for TString, operator<<, etc

#include <ctype.h>                      // for isalnum, isspace
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>
#include <string>                       // for string, allocator, etc
#include <vector>                       // for vector, etc

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

ClassImp(FairDbStatement)

FairDbStatement::FairDbStatement(FairDbConnection& conDb) :
  fConDb(conDb),
  fDbType(conDb.GetDbType()),
  fExceptionLog()
{
  fConDb.ConnectStatement();
}


FairDbStatement::~FairDbStatement()
{
  fConDb.DisConnectStatement();
}

TSQLStatement* FairDbStatement::CreateProcessedStatement(const TString& sql)
{
  TSQLStatement* stmt = fConDb.CreatePreparedStatement(sql.Data());
  if ( !stmt ) {
    this->AppendExceptionLog(fConDb);
    return 0;
  }
  if ( stmt->Process() ) { return stmt; }
  //<DB> Check me
  if ( fDbType != FairDb::kSQLite ) { this->AppendExceptionLog(stmt); }

  delete stmt;
  stmt = 0;
  return 0;

}

TSQLStatement* FairDbStatement::ExecuteQuery( const TString& sql)
{
  this->ClearExceptionLog();

  std::list<TString> sqlList(this->TranslateSQL(sql));
  std::list<TString>::const_iterator itr(sqlList.begin()), itrEnd(sqlList.end());

  TSQLStatement* stmt = 0;
  while (itr != itrEnd) {
    const TString& sql1 = *itr++;
    DBLOG("FairDb",FairDbLog::kInfo) <<"Server:" << fConDb.GetDbName() << " SQL:" << sql1 << endl;

    delete stmt;
    stmt = this->CreateProcessedStatement(sql1);

    if ( !stmt ) { return 0; }
  }

  if ( stmt && ! stmt->StoreResult() ) {
    this->AppendExceptionLog(stmt);
    delete stmt;
    stmt = 0;
  }

  // <DB> here should be some checks
  // implemented

  if ( stmt ) {
    if ( ! fExceptionLog.IsEmpty() ) {
      delete stmt;
      stmt = 0;
    }
  } else if ( fExceptionLog.IsEmpty() ) {
    ostringstream oss;
    oss << "Unknown failure (no exception but no TSQLStatement either executing " << sql;
    fExceptionLog.AddEntry(oss.str().c_str());
  }

  return stmt;

}



Bool_t FairDbStatement::ExecuteUpdate( const TString& sql)
{
  this->ClearExceptionLog();
  std::list<TString> sqlList(this->TranslateSQL(sql));
  std::list<TString>::const_iterator itr(sqlList.begin()), itrEnd(sqlList.end());

  while (itr != itrEnd) {
    const TString& sql1 = *itr++;
    DBLOG("FairDb",FairDbLog::kInfo) << "ExecuteUpdate: executing  SQL stmts:" << fConDb.GetDbName() << ":" << sql1 << endl;
    bool ok = fConDb.GetServer()->Exec(sql1.Data());
    if ( ! ok ) {
      fConDb.RecordException();
      this->AppendExceptionLog(fConDb);
      return kFALSE;
    }
  }
  return fExceptionLog.IsEmpty();
}

Bool_t FairDbStatement::PrintExceptions(Int_t level) const
{
  const FairDbExceptionLog& el(this->GetExceptionLog());
  if ( el.IsEmpty() ) { return false; }
  FairDbExceptionLog::GetGELog().AddLog(el);
  return true;

}

std::list<TString>  FairDbStatement::TestTranslateSQL(const TString& sql, FairDb::DbTypes type)
{

  FairDb::DbTypes fDbTypeSave = fDbType;
  fDbType = type;
  std::list<TString> sqlTrans(this->TranslateSQL(sql));
  fDbType = fDbTypeSave;
  return sqlTrans;

}



std::list<TString>  FairDbStatement::TranslateSQL(const TString& sql)
{
//  Translate  MySQL specific to other dialects of SQL.


  std::list<TString> sqlTransList;

  if ( fDbType == FairDb::kMySQL ) {
    sqlTransList.push_back(sql);
    return sqlTransList;

  } else {

    // Translation completion flag
    Bool_t translated = kFALSE;
    // Sql modification flag , further translation ongoing.
    Bool_t modified  = kFALSE;

    TString sqlTrans(sql);
    sqlTrans.ToUpper();


    if ( fDbType == FairDb::kOracle ) {

      // Format Date compatible with MySQL.
      sqlTransList.push_back("ALTER SESSION SET NLS_DATE_FORMAT='YYYY-MM-DD hh24:mi:ss'");

      // Translate NOW()
      if ( sqlTrans.Index("NOW()") != kNPOS ) {
        sqlTrans.ReplaceAll("NOW()","SYSDATE");
        modified = kTRUE;
      }

      // Translate SHOW TABLES
      if (sqlTrans == "SHOW TABLES" ) {
        sqlTrans = "SELECT TABLE_NAME FROM ALL_TABLES";
        sqlTransList.push_back(sqlTrans);
        translated = kTRUE;
      }

      TString sqlIncant;

      // Translate DROP TABLE commands.
      Ssiz_t dropTableIndex = sqlTrans.Index("DROP TABLE",0,TString::kIgnoreCase );
      if ( ! translated && dropTableIndex != kNPOS ) {
        // Remove added  "IF EXISTS"
        sqlTrans.ReplaceAll(" IF EXISTS ",    " ");

        //add the drop table command, then work on the synonym
        sqlTransList.push_back(sqlTrans);

        // Extract the table name
        Ssiz_t startIndex = dropTableIndex + 10;
        while ( isspace(sqlTrans[startIndex]) ) { ++startIndex; }
        Ssiz_t endIndex = startIndex + 1;
        Ssiz_t endIndexMax = sqlTrans.Length();
        while (     endIndex < endIndexMax
                    && (isalnum(sqlTrans[endIndex]) || sqlTrans[endIndex] == '_')
              ) { ++endIndex; }
        TString name(sqlTrans.Data()+startIndex,endIndex-startIndex);
        translated = kTRUE;

        // Add extra ORACLE statmenent for a public synonym
        TString sqlIncant1("DROP PUBLIC SYNONYM ");
        sqlIncant1  += name ;
        sqlTransList.push_back(sqlIncant1);
      }

      Ssiz_t whereStart = sqlTrans.Index("INSERT INTO",0,TString::kIgnoreCase );
      if ( whereStart == kNPOS ) { whereStart = 0; }
      else {
        Ssiz_t whereStartMax = sqlTrans.Length();
        whereStart = sqlTrans.Index("(",whereStart,TString::kIgnoreCase );
        if ( whereStart == kNPOS ) { whereStart = whereStartMax; }
        else { ++whereStart; }
        int level = 1;
        while ( whereStart < whereStartMax && level ) {
          char chr = sqlTrans[whereStart++];
          if ( chr == '(' ) { ++level; }
          if ( chr == ')' ) { --level; }
        }
      }

      Ssiz_t whereIndex = sqlTrans.Index(" WHERE ",whereStart,TString::kIgnoreCase );
      if ( ! translated && whereIndex != kNPOS ) {
        ++whereIndex;
        Ssiz_t whereEnd = sqlTrans.Length();
        std::string whereDelim[] = { "GROUP BY", "HAVING", "ORDER BY", "LIMIT" };
        int numDelims = sizeof(whereDelim)/sizeof(string);
        for (int iDelim = 0; iDelim < numDelims; ++iDelim ) {
          const string& delimName = whereDelim[iDelim];
          Ssiz_t delimIndex = sqlTrans.Index(delimName.c_str(), delimName.size(), whereIndex + 5, TString::kIgnoreCase );
          if (delimIndex != kNPOS && delimIndex < whereEnd) { whereEnd = delimIndex; }
        }

        // Translate all bitwise and expressions within the WHERE clause.
        TString whereClause(sql.Data()+whereIndex,whereEnd-whereIndex);
        // Convert \n to space so that tokenising works.
        whereClause.ReplaceAll("\n"," ");

        std::vector<std::string> tokens;
        FairUtilString::StringTok(tokens,whereClause.Data()," ");
        int numTokens = tokens.size();
        for (int ithToken = 1; ithToken < numTokens-1; ++ithToken ) {
          if ( tokens[ithToken] == "&" ) {
            string tmp("bitand(");
            tmp += tokens[ithToken-1] + "," +  tokens[ithToken+1] + ") != 0";
            tokens[ithToken] = tmp;
            tokens[ithToken-1] = "";
            tokens[ithToken+1] = "";
          }
        }

        sqlTrans = sql(0,whereIndex);
        for (int ithToken = 0; ithToken < numTokens; ++ithToken ) {
          sqlTrans += " ";
          sqlTrans += tokens[ithToken].c_str();
        }
        sqlTrans += " " + sql(whereEnd,999999);
        modified = kTRUE;
      }

      if ( ! translated && sqlTrans.Index("\\\'") != kNPOS ) {

        if ( not modified ) { sqlTrans = sql; }
        sqlTrans.ReplaceAll("\\\'","\'\'");
        modified = kTRUE;
      }

      // PGSQL ------------------------------------------------------
    } else if (  fDbType == FairDb::kPostgreSQL  ) {
      // Translate SHOW TABLES
      if (sqlTrans == "SHOW TABLES" ) {
        sqlTrans = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'PUBLIC'";
        sqlTransList.push_back(sqlTrans);
        translated = kTRUE;
      }

      // Boolean types
      Ssiz_t whereStart = sqlTrans.Index("INSERT INTO",0,TString::kIgnoreCase );
      if ( whereStart == kNPOS ) { whereStart = 0; }
      else {
        Ssiz_t whereStartMax = sqlTrans.Length();
        whereStart = sqlTrans.Index("(",whereStart,TString::kIgnoreCase );
        if ( whereStart == kNPOS ) { whereStart = whereStartMax; }
        else { ++whereStart; }
        int level = 1;
        while ( whereStart < whereStartMax && level ) {
          char chr = sqlTrans[whereStart++];
          if ( chr == '(' ) { ++level; }
          if ( chr == ')' ) { --level; }
        }
      }

      Ssiz_t whereIndex = sqlTrans.Index(" WHERE ",whereStart,TString::kIgnoreCase );
      if ( ! translated && whereIndex != kNPOS ) {
        ++whereIndex;
        Ssiz_t whereEnd = sqlTrans.Length();
        std::string whereDelim[] = { "GROUP BY", "HAVING", "ORDER BY", "LIMIT" };
        int numDelims = sizeof(whereDelim)/sizeof(string);
        for (int iDelim = 0; iDelim < numDelims; ++iDelim ) {
          const string& delimName = whereDelim[iDelim];
          Ssiz_t delimIndex = sqlTrans.Index(delimName.c_str(), delimName.size(),
                                             whereIndex + 5, TString::kIgnoreCase );
          if (delimIndex != kNPOS && delimIndex < whereEnd) { whereEnd = delimIndex; }
        }

        // Translate all bitwise and expressions within the WHERE clause.
        TString whereClause(sql.Data()+whereIndex,whereEnd-whereIndex);
        // Convert \n to space so that tokenising works.
        whereClause.ReplaceAll("\n"," ");

        std::vector<std::string> tokens;
        FairUtilString::StringTok(tokens,whereClause.Data()," ");
        int numTokens = tokens.size();
        for (int ithToken = 1; ithToken < numTokens-1; ++ithToken ) {
          if ( tokens[ithToken] == "&" ) {
            string tmp("cast((");
            tmp += tokens[ithToken-1] + " & " +  tokens[ithToken+1] + ") As Boolean)";
            tokens[ithToken] = tmp;
            tokens[ithToken-1] = "";
            tokens[ithToken+1] = "";
          }
        }

        sqlTrans = sql(0,whereIndex);
        for (int ithToken = 0; ithToken < numTokens; ++ithToken ) {
          sqlTrans += " ";
          sqlTrans += tokens[ithToken].c_str();
        }
        sqlTrans += " " + sql(whereEnd,999999);
        modified = kTRUE;

      }

    } //! PGSQL

    else if (  fDbType == FairDb::kSQLite  ) {
	  // cout << "-I-  FairDbStatement::TranslateSQL called for SQLite:" << sql <<  endl;
	  
    }//! (SQLite)


    // Translate CREATE TABLE commands using FairDbTableMetaData.
    Ssiz_t createTableIndex = sqlTrans.Index("CREATE TABLE",0,TString::kIgnoreCase );

    if ( ! translated && createTableIndex != kNPOS ) {
      FairDbTableMetaData tmd;
      tmd.SetFromSql(sql.Data(), fDbType);
      std::vector<std::string> sql_list;
      FairUtilString::StringTok(sql_list,tmd.Sql(fDbType),";");
      std::vector<std::string>::const_iterator itr(sql_list.begin()), itrEnd(sql_list.end());
      while ( itr != itrEnd ) {
        sqlTransList.push_back(*itr);
        ++itr;
      }
      translated = kTRUE;
    }

    // Finalizing translation
    if ( modified && ! translated ) {
      sqlTransList.push_back(sqlTrans);
      translated = kTRUE;
    }

    if ( translated ) {
      DBLOG("FairDb",FairDbLog::kInfo)<< "TranslateSQL  sql: " << sql  << endl
                                      << "translates to " << sqlTransList.size()
                                      << " statements:- \n";
      std::list<TString>::const_iterator itr(sqlTransList.begin()), itrEnd(sqlTransList.end());
      while (itr != itrEnd) { DBLOG("FairDb",FairDbLog::kInfo) <<"TranslateSQL " << "   " << *itr << endl; ++itr;}
    } else {
      sqlTransList.push_back(sql);
    }

    return sqlTransList;
  }
}
