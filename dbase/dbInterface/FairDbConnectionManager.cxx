/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

