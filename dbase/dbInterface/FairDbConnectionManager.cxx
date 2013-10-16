#include "FairDbConnectionPool.h"
#include "FairDbConnectionManager.h"

ClassImp(FairDbConnectionManager)

FairDbConnectionManager::FairDbConnectionManager(FairDbConnectionPool* connect) : fConnectPool(connect)
{
  if ( fConnectPool ) { fConnectPool->HoldConnections(); }
}


FairDbConnectionManager::~FairDbConnectionManager()
{
  if ( fConnectPool ) { fConnectPool->ReleaseConnections(); }
}

