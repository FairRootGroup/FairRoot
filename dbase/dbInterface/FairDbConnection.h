#ifndef FAIRDBCONNECTION
#define FAIRDBCONNECTION

#include "TSQLServer.h"
#include "TSQLStatement.h"
#include "TUrl.h"
#include "TString.h"

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif

#include <string>
#include "FairDb.h"
#include "FairDbExceptionLog.h"

using namespace std;

class FairDbConnection
{
  public:
    FairDbConnection(const string& url = "",
                     const string& user = "",
                     const string& password = "");
    virtual ~FairDbConnection();


    // Standard connectivity functions
    FairDb::DbTypes GetDbType() const { return fDbType; }
    const string& GetDbName() const { return fDbName; }
    const string& GetPassword() const { return fPassword; }
    const string& GetUrl() const;
    const string& GetUser() const { return fUser; }


    // connection itself
    Bool_t Close(Bool_t force = kFALSE);
    Bool_t Open();
    TSQLServer* GetServer();
    TSQLStatement* CreatePreparedStatement(const string& sql);
    Bool_t IsTemporary() const { return fIsTemporary; }
    Bool_t TableExists(const string& tableName) const;
    void SetTableExists(const string& tableName = "");
    void Connect()    { this->ConnectStatement();}
    void DisConnect() { this->DisConnectStatement(); }
    void ConnectStatement() { ++fNumConnectedStatements; }
    void DisConnectStatement() {
      --fNumConnectedStatements;
      if ( ! fNumConnectedStatements ) { this->CloseIdleConnection(); }
    }
    void SetPermanent(Bool_t permanent = kTRUE) { fIsTemporary = ! permanent; }


    Bool_t IsClosed() const { return ! (fServer); }
    const FairDbExceptionLog& GetExceptionLog() const { return fExceptionLog; }
    void ClearExceptionLog() { fExceptionLog.Clear(); }
/// Print exceptions at level of above and return true if any
    Bool_t PrintExceptionLog(Int_t level = 3) const;
    void RecordException();
  protected:
    string fDbName;
    string fUser;
    string fPassword;
    string fExistingTableList;
    Int_t fNumConnectedStatements;
    TUrl fUrl;
    Bool_t fUrlValidated;
    Bool_t fIsTemporary;
    FairDb::DbTypes fDbType;
    TSQLServer* fServer;
    FairDbExceptionLog fExceptionLog;
    void CloseIdleConnection();

    FairDbConnection(const FairDbConnection&);
    FairDbConnection operator=(const FairDbConnection&);

    ClassDef(FairDbConnection,0)
};

#endif

