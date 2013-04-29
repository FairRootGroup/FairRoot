#ifndef FAIRDBSTATEMENT
#define FAIRDBSTATEMENT



#include <list>

#include "TList.h"
#include "TString.h"
#include "TSQLStatement.h"

#include "FairDb.h"
#include "FairDbConnection.h"
#include "FairDbExceptionLog.h"

class FairDbStatement
{
  public:

// Constructors and destructors.
    FairDbStatement(FairDbConnection& conDb);
    virtual ~FairDbStatement();


    FairDb::DbTypes GetDBType() const { return fDbType; }
    std::list<TString> TestTranslateSQL(const TString& sql, FairDb::DbTypes type);

    TSQLStatement* ExecuteQuery(const TString& sql="");
    Bool_t ExecuteUpdate( const TString& sql="");
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

    ClassDef(FairDbStatement,0)     // Managed TSQL_Statement

};

#endif // FAIRDBSTATEMENT
