/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbTableInterfaceStore.h"
#include "FairDbLogService.h"
#include "FairDbBufferFile.h"           // for FairDbBufferFile
#include "FairDbCache.h"                // for string, FairDbCache
#include "FairDbConfigData.h"            // for FairDbConfigData
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbConnectionPool.h"        // for FairDbConnectionPool, etc
#include "FairDbUtils.h"             // for FairDbUtils, etc
#include "FairDbString.h"               // for StringTok, ToUpper
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbTableInterface.h"           // for FairDbTableInterface
#include "FairDbObjTableMap.h"             // for FairDbObjTableMap
#include "FairRegistry.h"               // for FairRegistry, etc

#include "FairDbLogFormat.h"
#include "FairDbLogService.h"

#include "Riosfwd.h"                    // for ostream
#include "TString.h"                    // for TString
#include "TSystem.h"                    // for TSystem, gSystem

#include <string.h>                     // for strcmp, strlen
#include <cstdlib>                      // for abort, NULL
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <utility>                      // for pair
#include <vector>                       // for vector

using std::cout;
using std::endl;
using std::string;

ClassImp(FairDbTableInterfaceStore)


FairDbTableInterfaceStore* FairDbTableInterfaceStore::fgInstance       = 0;
int                    FairDbTableInterfaceStore::Cleaner::fgCount = 0;


FairDbTableInterfaceStore::FairDbTableInterfaceStore()
  : FairDbConfigurable(),
    fConnectionPool(NULL),
    fSqlCondition(),
    fTPmap(),
    fRollbackTimes(),
    fDataTypeAss(),
    fLogName(""),
    fVerbosity(1)
{

  fVerbosity = 1;
  this->SetConfigFromEnvironment();
  this->SetLoggingStreams();


  DBLOG("FairDb",FairDbLog::kDebug) << "FairDbTableInterfaceStore singleton is created  \n"<< endl;

  fConnectionPool = new FairDbConnectionPool;

  fVerbosity = 0;
  this->SetLoggingStreams();
}

FairDbTableInterfaceStore::~FairDbTableInterfaceStore()
{

  int shutdown = 0;
  if (    ! this->GetConfig().Get("Shutdown",shutdown)
          || shutdown == 0 ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << " shutdown not requested" << endl;
    return;
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << " ... shutting down ..." << endl;


  for ( std::map<std::string,FairDbTableInterface*>::iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    FairDbTableInterface* tp = (*itr).second;
    if (tp) { delete tp; }
  }

  if (fConnectionPool) {
    // Deletion is done primarily by TSQLIO interface
    //delete fConnectionPool;
    //       fConnectionPool = 0;
  }

  FairDbUtils::SetRecord(0);

  DBLOG("FairDb",FairDbLog::kDebug) << " ~ Destroying ~ FairDbTableInterfaceStore" << endl;

  DBLOG("FairDb",FairDbLog::kInfo) << " Shutdown completed. " << endl;
  FairDbTableInterfaceStore::fgInstance = 0;

}


void FairDbTableInterfaceStore::ApplySqlCondition() const
{
  std::map<std::string,FairDbTableInterface*>::const_iterator itr = fTPmap.begin();
  std::map<std::string,FairDbTableInterface*>::const_iterator itrEnd = fTPmap.end();
  for ( ; itr != itrEnd; ++itr) { this->ApplySqlCondition(itr->second); }
}


void FairDbTableInterfaceStore::ApplySqlCondition(FairDbTableInterface* proxy) const
{
  string sqlFull = fSqlCondition;
  const string tableName(proxy->GetTableName());
  const string& date = fRollbackTimes.GetDate(tableName);
  if ( date.size() ) {
    if ( sqlFull.size() ) { sqlFull += " and "; }
    sqlFull += fRollbackTimes.GetType(tableName);
    sqlFull += " < \'";
    sqlFull += date;
    sqlFull += "\'";
  }

  proxy->SetSqlCondition(sqlFull);
}


void FairDbTableInterfaceStore::ClearRollbackTimes()
{
  fRollbackTimes.Clear();
  this->ApplySqlCondition();
}

void FairDbTableInterfaceStore::ClearDataTypeUnion()
{
  fDataTypeAss.Clear();
}

void FairDbTableInterfaceStore::Config()
{

  FairRegistry& reg = this->GetConfig();

  fDataTypeAss.Set(reg);

  fRollbackTimes.Set(reg);

  this->ApplySqlCondition();

  const char*  dir;
  if ( reg.Get("Level2Cache",dir) ) {
    TString tmp(dir);
    gSystem->ExpandPathName(tmp);
    if ( tmp.Contains("$" ) ) {
      dir = "./";
      DBLOG("FairDb",FairDbLog::kWarning)<< "Directory name expansion failed, using "
                                         << dir << " instead" << endl;
    } else {
      dir = tmp.Data();
    }

    FairDbBufferFile::SetWorkDir(dir);
    DBLOG("FairDb",FairDbLog::kInfo) << "FairDbTableInterfaceStore: Setting L2 Cache to: " << dir << endl;
  }

  int connectionsPermanent = 0;
  if ( reg.Get("MakeConnectionsPermanent",connectionsPermanent) ) {
    reg.RemoveKey("MakeConnectionsPermanent");
    Int_t dbNo =fConnectionPool->GetNumDb();
    if ( connectionsPermanent > 0 ) {
      while ( --dbNo >= 0 ) { fConnectionPool->SetPermanent(dbNo); }
      DBLOG("FairDb",FairDbLog::kInfo) << "Making all database connections permanent" << endl;
      FairDbUtils::fAsciiDBConectionsTemporary = false;
    } else {
      while ( --dbNo >= 0 ) { fConnectionPool->SetPermanent(dbNo,false); }
      DBLOG("FairDb",FairDbLog::kInfo) << "Forcing all connections, including ASCII DB, to be temporary" << endl;
      FairDbUtils::fAsciiDBConectionsTemporary = true;
    }
  }

  // Check for request to order context queries and remove from the Registry.
  int OrderContextQuery = 0;
  if ( reg.Get("OrderContextQuery",OrderContextQuery) ) {
    reg.RemoveKey("OrderContextQuery");
    if ( OrderContextQuery ) {
      FairDbUtils::fOrderContextQuery = true;
      DBLOG("FairDb",FairDbLog::kInfo) << "Forcing ordering of all context queries" << endl;
    }
  }

  // Abort if Registry contains any unknown keys
  const char* knownKeys[]   = { "Level2Cache",
                                "Shutdown",
                              };
  int numKnownKeys          = sizeof(knownKeys)/sizeof(char*);
  bool hasUnknownKeys       = false;

  FairRegistry::FairRegistryKey keyItr(&this->GetConfig());
  while ( const char* foundKey = keyItr() ) {
    bool keyUnknown = true;
    for (int keyNum = 0; keyNum < numKnownKeys; ++keyNum ) {
      if ( ! strcmp(foundKey,knownKeys[keyNum]) ) { keyUnknown = false; }
    }
    if ( keyUnknown ) {
      DBLOG("FairDb",FairDbLog::kInfo)  << "Illegal registry item: " << foundKey << endl;
      hasUnknownKeys = true;
    }
  }

  if ( hasUnknownKeys ) {
    DBLOG("FairDb",FairDbLog::kInfo) << "Aborting due to illegal registry items." << endl;
    abort();
  }
}


FairDbTableInterface& FairDbTableInterfaceStore::GetTableInterface
(const std::string& tableNameReq,
 const FairDbObjTableMap* tableRow)
{

// Assume upper case name if cannot find request.
  std::string tableName = tableNameReq;
  std::string vldSuffix = "Validity";
  if ( ! fConnectionPool->TableExists(tableName + vldSuffix ) ) {
    tableName = FairUtilString::ToUpper(tableName);
    vldSuffix = "VAL";
  }
  std::string proxyName = tableName;

  proxyName.append("::");
  proxyName.append(tableRow->ClassName());
  FairDbTableInterface* qpp = fTPmap[proxyName];
  if ( ! qpp ) {
    DBLOG("FairDb",FairDbLog::kInfo) <<" create a FairDbTableInterface " <<  tableRow << " proxyname# " << proxyName <<   endl;
    qpp = new FairDbTableInterface(fConnectionPool,tableName,vldSuffix,tableRow);
    this->ApplySqlCondition(qpp);
    fTPmap[proxyName] = qpp;
  }

  return *qpp;

}


Bool_t FairDbTableInterfaceStore::HasRowCounter(const std::string& tableName)
{
  FairDbConfigData cfs;
  FairDbTableInterface& tp = this->GetTableInterface(tableName,&cfs);
  return tp.GetMetaData().HasRowCounter();
}

FairDbTableInterfaceStore& FairDbTableInterfaceStore::Instance()
{
  if ( ! fgInstance ) {
    fgInstance = new FairDbTableInterfaceStore();
  }
  return *fgInstance;
}


void FairDbTableInterfaceStore::PurgeCaches()
{
  for ( std::map<std::string,FairDbTableInterface*>::iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    FairDbTableInterface* tp = (*itr).second;
    tp->GetCache()->Purge();
  }
}


void FairDbTableInterfaceStore::RefreshMetaData(const std::string& tableName)
{
  std::map<std::string,FairDbTableInterface*>::iterator itr = fTPmap.begin();
  std::map<std::string,FairDbTableInterface*>::iterator itrEnd = fTPmap.end();
  for ( ; itr != itrEnd; ++itr) {
    FairDbTableInterface* table = (*itr).second;
    if ( table && table->GetTableName() == tableName ) { table->RefreshMetaData(); }
  }
}

void FairDbTableInterfaceStore::SetConfigFromEnvironment()
{

  fLogName = gSystem->Getenv("FAIRDB_LOGFILE_DB");


  if (fLogName.IsNull() || (fLogName.Length() == 0)) {
    const char* apwd =  gSystem->Getenv("PWD");
    TString aPwd(apwd);
    TString aLogName("/fairdbinfo.log");
    fLogName = aPwd+aLogName;
  }

  const char* strFAIRDB_DB = gSystem->Getenv("FAIRDB_DB");
  if ( strFAIRDB_DB == 0  || strlen(strFAIRDB_DB) == 0 ) { return; }


  DBLOG("FairDb",FairDbLog::kInfo) << "\nConfiguring  from the environmental "
                                   << "variable FAIRDB_DB:\n  " << strFAIRDB_DB << endl;
  std::vector<std::string> configRequests;
  FairUtilString::StringTok(configRequests, strFAIRDB_DB, ";");

  for (unsigned entry = 0; entry < configRequests.size(); ++entry ) {
    this->Set(configRequests[entry].c_str());
  }


  this->Update();


}

void FairDbTableInterfaceStore::SetSqlCondition(const std::string& sql)
{
  fSqlCondition = sql;
  this->ApplySqlCondition();
}

void FairDbTableInterfaceStore::ShowStatistics() const
{
  FairDbLogStream msg = DBLOGSTREAM("FairDb",FairDbLog::kInfo);
  msg << "\n\nCache statistics:-\n\n"
      << "Table Name                             "
      << "    Current   Maximum     Total     Total\n"
      << "                                       "
      << "       Size      Size   Adopted    Reused" << endl;


  for ( std::map<std::string,FairDbTableInterface*>::const_iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    const FairDbTableInterface* tp = (*itr).second;
    std::string name = (*itr).first;
    if ( name.size() < 40 ) { name.append(40-name.size(),' '); }
    msg << name;
    const_cast<FairDbTableInterface*>(tp)->GetCache()->ShowStatistics(msg);
    msg   << endl;
  }
  msg << "\n" << endl;
  DBLOG("FairDb",FairDbLog::kInfo)  << const_cast<FairDbTableInterfaceStore*>(this)->GetConnectionPool();
}


void FairDbTableInterfaceStore::SetLoggingStreams()
{
// Set Logging mechanism
  if (fVerbosity == 0 ) {

    FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(FairDbLog::kWarning);
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kError,fLogName.Data());

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->SetLogLevel(FairDbLog::kWarning);
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kError,fLogName.Data());

  } else if ( fVerbosity == 1 ) {

    FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(FairDbLog::kInfo);
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kError,fLogName.Data());

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->SetLogLevel(FairDbLog::kInfo);
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kError,fLogName.Data());

  } else if ( fVerbosity == 2 ) {
    FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(FairDbLog::kDebug);
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kDebug,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kDebug,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kDebug,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kError,fLogName.Data());

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->SetLogLevel(FairDbLog::kDebug);
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kDebug,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cerr");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kDebug,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kInfo,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kWarning,"cout");
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->DisconnectOStream(FairDbLog::kError,"cout");

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kDebug,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kError,fLogName.Data());

  } else if ( fVerbosity == 3 ) {
    FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(FairDbLog::kInfo);

    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb")->ConnectOStream(FairDbLog::kError,fLogName.Data());

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->SetLogLevel(FairDbLog::kInfo);

    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kWarning,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kInfo,fLogName.Data());
    FairDbLogService::Instance()->GetStream("FairDb:Validation")->ConnectOStream(FairDbLog::kError,fLogName.Data());

  }

  DBLOG("FairDb",FairDbLog::kInfo) << "FairDb Logging service: opened. "<< endl;

}

