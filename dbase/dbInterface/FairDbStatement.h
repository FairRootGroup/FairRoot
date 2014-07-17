/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBSTATEMENT
#define FAIRDBSTATEMENT

#include "FairDb.h"                     // for DbTypes
#include "FairDbConnection.h"           // for FairDbConnection
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog

#include "Rtypes.h"                     // for Bool_t, etc
#include "TString.h"                    // for TString

#include <list>                         // for list

class FairDbException;
class TSQLStatement;
class FairDbStatement
{
  public:

    FairDbStatement(FairDbConnection& conDb);
    virtual ~FairDbStatement();

    FairDb::DbTypes GetDBType() const { return fDbType; }
    std::list<TString> TestTranslateSQL(const TString& sql, FairDb::DbTypes type);

    TSQLStatement* ExecuteQuery(const TString& sql="");
    Bool_t ExecuteUpdate( const TString& sql="");
    Bool_t Commit(const TString& sql) {return ExecuteUpdate(sql);}
    Bool_t PrintExceptions(Int_t level = 3) const;
    const FairDbExceptionLog& GetExceptionLog() const { return fExceptionLog; }
  private:
    void AppendExceptionLog(FairDbException* e)  { if ( e ) { fExceptionLog.AddEntry(*e); } }
    void AppendExceptionLog(TSQLStatement* s) { if ( s ) { fExceptionLog.AddEntry(*s); } }
    void AppendExceptionLog(FairDbConnection& c) {          fExceptionLog.AddLog(c.GetExceptionLog()); }
    void ClearExceptionLog()                  { fExceptionLog.Clear(); }
    // functions
    TSQLStatement* CreateProcessedStatement(const TString& sql="");
    std::list<TString> TranslateSQL(const TString& sql);

    // data
    FairDbConnection& fConDb;
    FairDb::DbTypes fDbType;
    FairDbExceptionLog fExceptionLog;

    ClassDef(FairDbStatement,0)     // Customized TSQL_Statement

};

#endif // FAIRDBSTATEMENT
