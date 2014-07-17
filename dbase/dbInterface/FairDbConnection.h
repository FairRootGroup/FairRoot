/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCONNECTION
#define FAIRDBCONNECTION

#include "FairDb.h"                     // for DbTypes
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for Bool_t, etc
#endif
#endif
#include "TUrl.h"                       // for TUrl

#include <string>                       // for string

class TSQLServer;
class TSQLStatement;

// IWYU pragma: no_include "Rtypes.h"

class FairDbConnection
{
  public:
    FairDbConnection(const std::string& url = "",
                     const std::string& user = "",
                     const std::string& password = "");

    virtual ~FairDbConnection();

    FairDb::DbTypes GetDbType() const { return fDbType; }
    const std::string& GetDbName() const { return fDbName; }
    const std::string& GetPassword() const { return fPassword; }
    const std::string& GetUrl() const;
    const std::string& GetUser() const { return fUser; }

    Bool_t Close(Bool_t force = kFALSE);
    Bool_t Open();
    TSQLServer* GetServer();
    TSQLStatement* CreatePreparedStatement(const std::string& sql);
    Bool_t IsTemporary() const { return fIsTemporary; }
    Bool_t TableExists(const std::string& tableName) const;
    void SetTableExists(const std::string& tableName = "");
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
    Bool_t PrintExceptionLog(Int_t level = 3) const;
    void RecordException();
    void RefreshExistingTables(){fExistingTableList.clear();SetTableExists();}
  protected:
    std::string fDbName;
    std::string fUser;
    std::string fPassword;
    std::string fExistingTableList;

    // Add Info about Schema
    TString fSchema;

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

