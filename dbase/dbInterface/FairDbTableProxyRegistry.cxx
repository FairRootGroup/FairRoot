#include "FairDbTableProxyRegistry.h"
#include "FairDbLogService.h"
#include "FairDbBinaryFile.h"           // for FairDbBinaryFile
#include "FairDbCache.h"                // for string, FairDbCache
#include "FairDbConfigSet.h"            // for FairDbConfigSet
#include "FairDbExceptionLog.h"         // for FairDbExceptionLog
#include "FairDbMultConnector.h"        // for FairDbMultConnector, etc
#include "FairDbServices.h"             // for FairDbServices, etc
#include "FairDbString.h"               // for StringTok, ToUpper
#include "FairDbTableMetaData.h"        // for FairDbTableMetaData
#include "FairDbTableProxy.h"           // for FairDbTableProxy
#include "FairDbTableRow.h"             // for FairDbTableRow
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

ClassImp(FairDbTableProxyRegistry)


FairDbTableProxyRegistry* FairDbTableProxyRegistry::fgInstance       = 0;
int                    FairDbTableProxyRegistry::Cleaner::fgCount = 0;


FairDbTableProxyRegistry::FairDbTableProxyRegistry()
  : FairDbConfigurable(),
    fMultConnector(NULL),
    fSqlCondition(),
    fTPmap(),
    fRollbackDates(),
    fSimFlagAss()
{

  this->SetConfigFromEnvironment();
  this->SetLoggingStreams();

  DBLOG("FairDb",FairDbLog::kDebug) << "FairDbTableProxyRegistry singleton is created  \n"<< endl;

  fMultConnector = new FairDbMultConnector;


  // Shutdown modus
  // Set("Shutdown = 1");
}

FairDbTableProxyRegistry::~FairDbTableProxyRegistry()
{
  if (  FairDbExceptionLog::GetGELog().Size() ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << "Database Global Exception Log contains "
                                      << FairDbExceptionLog::GetGELog().Size() << " entries:-" << endl;;
    FairDbExceptionLog::GetGELog().Print();
  }

  int shutdown = 0;
  if (    ! this->GetConfig().Get("Shutdown",shutdown)
          || shutdown == 0 ) {
    DBLOG("FairDb",FairDbLog::kInfo)  << " shutdown not requested" << endl;
    return;
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << " ... shutting down ..." << endl;


  for ( std::map<std::string,FairDbTableProxy*>::iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    FairDbTableProxy* tp = (*itr).second;
    delete tp;
  }

  delete fMultConnector;
  fMultConnector = 0;

  FairDbServices::SetRecord(0);


  DBLOG("FairDb",FairDbLog::kDebug) << " ~ Destroying ~ FairDbTableProxyRegistry" << endl;

  DBLOG("FairDb",FairDbLog::kInfo) << " Shutdown completed. " << endl;
  FairDbTableProxyRegistry::fgInstance = 0;

}


void FairDbTableProxyRegistry::ApplySqlCondition() const
{
  std::map<std::string,FairDbTableProxy*>::const_iterator itr = fTPmap.begin();
  std::map<std::string,FairDbTableProxy*>::const_iterator itrEnd = fTPmap.end();
  for ( ; itr != itrEnd; ++itr) { this->ApplySqlCondition(itr->second); }
}


void FairDbTableProxyRegistry::ApplySqlCondition(FairDbTableProxy* proxy) const
{
  string sqlFull = fSqlCondition;
  const string tableName(proxy->GetTableName());
  const string& date = fRollbackDates.GetDate(tableName);
  if ( date.size() ) {
    if ( sqlFull.size() ) { sqlFull += " and "; }
    sqlFull += fRollbackDates.GetType(tableName);
    sqlFull += " < \'";
    sqlFull += date;
    sqlFull += "\'";
  }

  proxy->SetSqlCondition(sqlFull);
}


void FairDbTableProxyRegistry::ClearRollbackDates()
{
  fRollbackDates.Clear();
  this->ApplySqlCondition();
}

void FairDbTableProxyRegistry::ClearSimFlagAssociation()
{
  fSimFlagAss.Clear();
}

void FairDbTableProxyRegistry::Config()
{

  FairRegistry& reg = this->GetConfig();

  fSimFlagAss.Set(reg);

  fRollbackDates.Set(reg);

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

    FairDbBinaryFile::SetWorkDir(dir);
    DBLOG("FairDb",FairDbLog::kInfo) << "FairDbTableProxyRegistry: Setting L2 Cache to: " << dir << endl;
  }

  int connectionsPermanent = 0;
  if ( reg.Get("MakeConnectionsPermanent",connectionsPermanent) ) {
    reg.RemoveKey("MakeConnectionsPermanent");
    Int_t dbNo =fMultConnector->GetNumDb();
    if ( connectionsPermanent > 0 ) {
      while ( --dbNo >= 0 ) { fMultConnector->SetPermanent(dbNo); }
      DBLOG("FairDb",FairDbLog::kInfo) << "Making all database connections permanent" << endl;
      FairDbServices::fAsciiDBConectionsTemporary = false;
    } else {
      while ( --dbNo >= 0 ) { fMultConnector->SetPermanent(dbNo,false); }
      DBLOG("FairDb",FairDbLog::kInfo) << "Forcing all connections, including ASCII DB, to be temporary" << endl;
      FairDbServices::fAsciiDBConectionsTemporary = true;
    }
  }

  // Check for request to order context queries and remove from the Registry.
  int OrderContextQuery = 0;
  if ( reg.Get("OrderContextQuery",OrderContextQuery) ) {
    reg.RemoveKey("OrderContextQuery");
    if ( OrderContextQuery ) {
      FairDbServices::fOrderContextQuery = true;
      DBLOG("FairDb",FairDbLog::kInfo) << "Forcing ordering of all context queries" << endl;
    }
  }

  // Abort if Registry contains any unknown keys
  const char* knownKeys[]   = { "Level2Cache",
                                "Shutdown"
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


FairDbTableProxy& FairDbTableProxyRegistry::GetTableProxy
(const std::string& tableNameReq,
 const FairDbTableRow* tableRow)
{

// Assume upper case name if cannot find request.
  std::string tableName = tableNameReq;
  std::string vldSuffix = "Validity";
  if ( ! fMultConnector->TableExists(tableName + vldSuffix ) ) {
    tableName = FairUtilString::ToUpper(tableName);
    vldSuffix = "VAL";
  }
  std::string proxyName = tableName;

  proxyName.append("::");
  proxyName.append(tableRow->ClassName());
  FairDbTableProxy* qpp = fTPmap[proxyName];
  if ( ! qpp ) {
    DBLOG("FairDb",FairDbLog::kInfo) <<" create a FairDbTableProxy " <<  tableRow << " proxyname# " << proxyName <<   endl;
    qpp = new FairDbTableProxy(fMultConnector,tableName,vldSuffix,tableRow);
    this->ApplySqlCondition(qpp);
    fTPmap[proxyName] = qpp;
  }

  return *qpp;

}


Bool_t FairDbTableProxyRegistry::HasRowCounter(const std::string& tableName)
{
  FairDbConfigSet cfs;
  FairDbTableProxy& tp = this->GetTableProxy(tableName,&cfs);
  return tp.GetMetaData().HasRowCounter();
}

FairDbTableProxyRegistry& FairDbTableProxyRegistry::Instance()
{
  if ( ! fgInstance ) {
    fgInstance = new FairDbTableProxyRegistry();
  }
  return *fgInstance;
}


void FairDbTableProxyRegistry::PurgeCaches()
{
  for ( std::map<std::string,FairDbTableProxy*>::iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    FairDbTableProxy* tp = (*itr).second;
    tp->GetCache()->Purge();
  }
}


void FairDbTableProxyRegistry::RefreshMetaData(const std::string& tableName)
{
  std::map<std::string,FairDbTableProxy*>::iterator itr = fTPmap.begin();
  std::map<std::string,FairDbTableProxy*>::iterator itrEnd = fTPmap.end();
  for ( ; itr != itrEnd; ++itr) {
    FairDbTableProxy* table = (*itr).second;
    if ( table && table->GetTableName() == tableName ) { table->RefreshMetaData(); }
  }
}

void FairDbTableProxyRegistry::SetConfigFromEnvironment()
{

  fLogName = gSystem->Getenv("ENV_LOGFILE_DB");


  if (fLogName.IsNull() || (fLogName.Length() == 0)) {
    const char* apwd =  gSystem->Getenv("PWD");
    TString aPwd(apwd);
    TString aLogName("/fairdbinfo.log");
    fLogName = aPwd+aLogName;
  }

  const char* strENV_DB = gSystem->Getenv("ENV_DB");
  if ( strENV_DB == 0  || strlen(strENV_DB) == 0 ) { return; }


  DBLOG("FairDb",FairDbLog::kInfo) << "\nConfiguring  from the environmental "
                                   << "variable ENV_DB:-\n  " << strENV_DB << endl;
  std::vector<std::string> configRequests;
  FairUtilString::StringTok(configRequests, strENV_DB, ";");

  for (unsigned entry = 0; entry < configRequests.size(); ++entry ) {
    this->Set(configRequests[entry].c_str());
  }


  this->Update();


}

void FairDbTableProxyRegistry::SetSqlCondition(const std::string& sql)
{
  fSqlCondition = sql;
  this->ApplySqlCondition();
}

void FairDbTableProxyRegistry::ShowStatistics() const
{
  FairDbLogStream msg = DBLOGSTREAM("FairDb",FairDbLog::kInfo);
  msg << "\n\nCache statistics:-\n\n"
      << "Table Name                             "
      << "    Current   Maximum     Total     Total\n"
      << "                                       "
      << "       Size      Size   Adopted    Reused" << endl;


  for ( std::map<std::string,FairDbTableProxy*>::const_iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    const FairDbTableProxy* tp = (*itr).second;
    std::string name = (*itr).first;
    if ( name.size() < 40 ) { name.append(40-name.size(),' '); }
    msg << name;
    const_cast<FairDbTableProxy*>(tp)->GetCache()->ShowStatistics(msg);
    msg   << endl;
  }
  msg << "\n" << endl;
  DBLOG("FairDb",FairDbLog::kInfo)  << const_cast<FairDbTableProxyRegistry*>(this)->GetMultConnector();
}


void FairDbTableProxyRegistry::SetLoggingStreams()
{
  // Set Logging mechanism
  FairDbLogService::Instance()->GetStream("FairDb")->SetLogLevel(FairDbLog::kInfo);
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kInfo,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kWarning,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kError,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kInfo,"cout");
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kWarning,"cout");
  FairDbLogService::Instance()->GetStream("FairDb")->DetachOStream(FairDbLog::kError,"cout");

  FairDbLogService::Instance()->GetStream("FairDb")->AttachOStream(FairDbLog::kWarning,fLogName.Data());
  FairDbLogService::Instance()->GetStream("FairDb")->AttachOStream(FairDbLog::kInfo,fLogName.Data());
  FairDbLogService::Instance()->GetStream("FairDb")->AttachOStream(FairDbLog::kError,fLogName.Data());

  FairDbLogService::Instance()->GetStream("FairDb:Validation")->SetLogLevel(FairDbLog::kInfo);
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kInfo,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kWarning,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kError,"cerr");
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kInfo,"cout");
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kWarning,"cout");
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->DetachOStream(FairDbLog::kError,"cout");

  FairDbLogService::Instance()->GetStream("FairDb:Validation")->AttachOStream(FairDbLog::kWarning,fLogName.Data());
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->AttachOStream(FairDbLog::kInfo,fLogName.Data());
  FairDbLogService::Instance()->GetStream("FairDb:Validation")->AttachOStream(FairDbLog::kError,fLogName.Data());

  DBLOG("FairDb",FairDbLog::kInfo) << "FairDb Logging service: opened. "<< endl;

}

