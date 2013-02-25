#include <vector>

#include "TSystem.h"
#include "TString.h"

#include "FairDbExceptionLog.h"
#include "FairDbBinaryFile.h"
#include "FairDbCache.h"
#include "FairDbMultConnector.h"
#include "FairDbConfigSet.h"
#include "FairDbServices.h"
#include "FairDbTableProxyRegistry.h"
#include "FairDbTableProxy.h"
#include "FairDbString.h"

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

// Create cascader for database access.

  fMultConnector = new FairDbMultConnector;

// Get any environment configuration.

  this->SetConfigFromEnvironment();

// Create a FairDbRecord to record a summary of all FairDbResults in memory
// and register it as a service.
//  FairDbServices::SetRecord(new FairDbRecord);

  cout << "Creating FairDbTableProxyRegistry"
       << endl;


}

FairDbTableProxyRegistry::~FairDbTableProxyRegistry()
{

  if (  FairDbExceptionLog::GetGELog().Size() ) {
    cout << "Database Global Exception Log contains "
         << FairDbExceptionLog::GetGELog().Size() << " entries:-" << endl;;
    FairDbExceptionLog::GetGELog().Print();
  }

  int shutdown = 0;
  if (    ! this->GetConfig().Get("Shutdown",shutdown)
          || shutdown == 0 ) {
    cout << " shutdown not requested" << endl;
    return;
  }

  cout << " shutting down..." << endl;

// Destroy all owned objects.

  for ( std::map<std::string,FairDbTableProxy*>::iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    FairDbTableProxy* tp = (*itr).second;
    delete tp;
  }

  delete fMultConnector;
  fMultConnector = 0;

  //delete FairDbServices::GetRecord();
  FairDbServices::SetRecord(0);


  cout  << "Destroying FairDbTableProxyRegistry" << endl;

  cout  << " shutdown complete." << endl;
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

  //Load up SimFlag Associations and remove them from the FairRegistry.
  fSimFlagAss.Set(reg);

  //Load up Rollback dates and remove them from the FairRegistry.
  fRollbackDates.Set(reg);

  //Apply any rollback now in force.
  this->ApplySqlCondition();

  // If Level 2 cache enabled establish working directory
  // for FairDbBinaryFile.
  const char*  dir;
  if ( reg.Get("Level2Cache",dir) ) {
    // Expand any environmental variables.
    TString tmp(dir);
    //  March 2004 ExpandPathName returns false even if it works, so test for failure
    //  by looking for an unexpanded symbol.
    gSystem->ExpandPathName(tmp);
    if ( tmp.Contains("$" ) ) {
      dir = "./";
      cout << "Directory name expansion failed, using "
           << dir << " instead" << endl;
    } else {
      dir = tmp.Data();
    }

    FairDbBinaryFile::SetWorkDir(dir);
    cout << "FairDbTableProxyRegistry: Setting L2 Cache to: " << dir << endl;
  }

  // Check for request to make all cascade connections permanent
  // and remove from the Registry.

  int connectionsPermanent = 0;
  if ( reg.Get("MakeConnectionsPermanent",connectionsPermanent) ) {
    reg.RemoveKey("MakeConnectionsPermanent");
    Int_t dbNo =fMultConnector->GetNumDb();
    if ( connectionsPermanent > 0 ) {
      while ( --dbNo >= 0 ) { fMultConnector->SetPermanent(dbNo); }
      cout << "Making all database connections permanent" << endl;
      // Inform FairDbServices so that FairDbConnection can check when opening new connections.
      FairDbServices::fAsciiDBConectionsTemporary = false;
    } else {
      while ( --dbNo >= 0 ) { fMultConnector->SetPermanent(dbNo,false); }
      cout << "Forcing all connections, including ASCII DB, to be temporary" << endl;
      // Inform FairDbServices so that FairDbConnection can check when opening new connections.
      FairDbServices::fAsciiDBConectionsTemporary = true;
    }
  }

  // Check for request to order context queries and remove from the Registry.

  int OrderContextQuery = 0;
  if ( reg.Get("OrderContextQuery",OrderContextQuery) ) {
    reg.RemoveKey("OrderContextQuery");
    if ( OrderContextQuery ) {
      FairDbServices::fOrderContextQuery = true;
      cout << "Forcing ordering of all context queries" << endl;
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

      cout  << "Illegal registry item: " << foundKey << endl;
      hasUnknownKeys = true;
    }
  }

  if ( hasUnknownKeys ) {
    cout << "Aborting due to illegal registry items." << endl;
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
// Delete is handled by Cleaner class based on #include count
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
  const char* strENV_DBI = gSystem->Getenv("ENV_DB");
  if ( strENV_DBI == 0  || strlen(strENV_DBI) == 0 ) { return; }

  cout << "\nConfiguring  from the environmental "
       << "variable ENV_DB:-\n  " << strENV_DBI << endl;
  std::vector<std::string> configRequests;
  FairUtilString::StringTok(configRequests, strENV_DBI, ";");

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

  cout << "\n\nCache statistics:-\n\n"
       << "Table Name                             "
       << "    Current   Maximum     Total     Total\n"
       << "                                       "
       << "       Size      Size   Adopted    Reused" << endl;

// Loop over all owned objects.

  for ( std::map<std::string,FairDbTableProxy*>::const_iterator itr = fTPmap.begin();
        itr != fTPmap.end();
        ++itr) {
    const FairDbTableProxy* tp = (*itr).second;
    std::string name = (*itr).first;
    if ( name.size() < 40 ) { name.append(40-name.size(),' '); }
    cout << name;
//  Only want to look at cache so by-pass constness.
    // const_cast<FairDbTableProxy*>(tp)->GetCache()->ShowStatistics();
    cout << endl;
  }
  cout << "\n" << endl;

//  Only want to look at cascader so by-pass constness.

  cout << const_cast<FairDbTableProxyRegistry*>(this)->GetMultConnector();


}
