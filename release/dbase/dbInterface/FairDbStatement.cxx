#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "TString.h"

#include "FairDbStatement.h"
#include "FairDbTableMetaData.h"
#include "FairDbString.h"

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
  if ( ! stmt ) {
    this->AppendExceptionLog(fConDb);
    return 0;
  }
  if ( stmt->Process() ) { return stmt; }
  this->AppendExceptionLog(stmt);
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
    const TString& sql = *itr++;
    cout <<"-I- FairDbStatement SQL:" << fConDb.GetDbName() << ":" << sql << endl;
    delete stmt;
    stmt = this->CreateProcessedStatement(sql);
    if ( ! stmt ) { return 0; }
  }
  // Store results from last SQL command (when multiple commands are generated
  // the last will be the one that performs the query).
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
    oss << "Unknown failure (no execption but no TSQLStatement either executing " << sql;
    fExceptionLog.AddEntry(oss.str().c_str());
  }

  return stmt;

}

//.....................................................................

Bool_t FairDbStatement::ExecuteUpdate( const TString& sql)
{
  this->ClearExceptionLog();
  std::list<TString> sqlList(this->TranslateSQL(sql));
  std::list<TString>::const_iterator itr(sqlList.begin()), itrEnd(sqlList.end());

  while (itr != itrEnd) {
    const TString& sql = *itr++;
    cout << "-I- FairDbStatement::ExecuteUpdate SQL:" << fConDb.GetDbName() << ":" << sql << endl;
    bool ok = fConDb.GetServer()->Exec(sql.Data());
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

//.....................................................................

std::list<TString>  FairDbStatement::TranslateSQL(const TString& sql)
{
//  Translate  MySQL specific to other dialects of SQL.

//  This is NOT meant to be a general purpose SQL translator, but rather a very
//  simple translater of the SQL that the DBI employs which is dialect specific.

//  The only translations supported are as follows:-

//  1)  MySQL -> Oracle:-
//      Set date format to be compatible with MySQL.
//
//  2)  MySQL -> Oracle:-
//      Convert WHERE expressions of the form A & B to bitand(A,B) != 0
//
//  3)  MySQL -> Oracle:-
//      In CREATE TABLE
//
//      Conversion is achieved by creating a FairDbTableMetaData object
//      from the SQL and then asking it to generate the Oracle equivalent.
//      See FairDbTableMetaData for details.
//
//  4)  MySQL -> Oracle:-
//      SHOW TABLES        ->  SELECT TABLE_NAME FROM ALL_TABLES
//
//  5)  MySQL -> Oracle:-
//      \' -> '' (in general ORACLE doesn't respect escape sequences
//                except single quotes and only then as '' not \').
//
//  6)  MySQL -> Oracle:-
//      Convert now() into sysdate

  std::list<TString> sqlTransList;

  if ( fDbType != FairDb::kOracle ) {
    sqlTransList.push_back(sql);
    return sqlTransList;
  }
// Once kTRUE,  sqlTransList contains the translation. No further translation possible.
  Bool_t translated = kFALSE;
// sqlTrans has been modified, but  further translation possible.
  Bool_t modified  = kFALSE;

  TString sqlTrans(sql);
  sqlTrans.ToUpper();

// Set date format  to be compatible with MySQL.
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

// Translate CREATE TABLE commands using FairDbTableMetaData.
  Ssiz_t createTableIndex = sqlTrans.Index("CREATE TABLE",0,TString::kIgnoreCase );
  if ( ! translated && createTableIndex != kNPOS ) {
    FairDbTableMetaData tmd;
    tmd.SetFromSql(sql.Data());
    std::vector<std::string> sql_list;
    FairUtilString::StringTok(sql_list,tmd.Sql(FairDb::kOracle),";");
    std::vector<std::string>::const_iterator itr(sql_list.begin()), itrEnd(sql_list.end());
    while ( itr != itrEnd ) {
      sqlTransList.push_back(*itr);
      ++itr;
    }
    translated = kTRUE;
  }


  // Translate DROP TABLE commands.
  Ssiz_t dropTableIndex = sqlTrans.Index("DROP TABLE",0,TString::kIgnoreCase );
  if ( ! translated && dropTableIndex != kNPOS ) {
    // Remove any "IF EXISTS"
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

    // Add extra ORACLE incantations required when dropping a table with
    // a public synonym
    TString sqlIncant("DROP PUBLIC SYNONYM ");
    sqlIncant  += name ;
    sqlTransList.push_back(sqlIncant);
  }

// Translate commands with a WHERE keyword, but take care if this is
// an INSERT INTO command - it could include "where" as part of a character value!
  Ssiz_t whereStart = sqlTrans.Index("INSERT INTO",0,TString::kIgnoreCase );
  if ( whereStart == kNPOS ) { whereStart = 0; }
  else {
    // Skip to end of INSERT by looking for the trailing ")" at level 0
    // Yes, I know this can be defeated by mismatched "(" and ")" within
    // character values, but it's better than giving up on a possible WHERE clause
    // altogether.
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
  // Look for space separated WHERE (so not fooled by e.g. FABWHERE!)
  Ssiz_t whereIndex = sqlTrans.Index(" WHERE ",whereStart,TString::kIgnoreCase );
  if ( ! translated && whereIndex != kNPOS ) {

    // Set limit of WHERE clause
    ++whereIndex; // Step over leading space
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

// Translate \' to ''
  if ( ! translated && sqlTrans.Index("\\\'") != kNPOS ) {
//  Bit of a kludge, if not yet modified, undo upper case conversion
//  as quoted data is likely to contain characters.
    if ( not modified ) { sqlTrans = sql; }
    sqlTrans.ReplaceAll("\\\'","\'\'");
    modified = kTRUE;
  }

  if ( modified && ! translated ) {
    sqlTransList.push_back(sqlTrans);
    translated = kTRUE;
  }

  if ( translated ) {
    cout << "-I- FairDbStatement::TranslateSQL  sql: " << sql  << endl
         << "translates to " << sqlTransList.size()
         << " statements:- \n";
    std::list<TString>::const_iterator itr(sqlTransList.begin()), itrEnd(sqlTransList.end());
    while (itr != itrEnd) { cout <<"-I- FairDbStatement::TranslateSQL " << "   " << *itr << endl; ++itr;}
  } else {
    sqlTransList.push_back(sql);
  }

  return sqlTransList;

}
