/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbConfigurable.h"

#include "FairDbConfig.h"                 // for FairDbConfig
#include "FairDbConfigNotice.h"           // for FairDbConfigNotice

ClassImp(FairDbConfigurable)

FairDbConfigurable::FairDbConfigurable() : fDefConfig(), fConfig(false) { }

FairDbConfigurable::~FairDbConfigurable() { }

void FairDbConfigurable::CommitDefaultConfig(const FairRegistry& r)
{
  fDefConfig = r;
}

const FairRegistry& FairDbConfigurable::DefaultConfig() const
{
  return fDefConfig;
}

FairRegistry& FairDbConfigurable::GetConfig()
{
  return fConfig;
}

const FairRegistry& FairDbConfigurable::GetConfig() const
{
  return fConfig;
}

int FairDbConfigurable::Update()
{
  // Nothing to do if config is current
  if (! fConfig.IsDirty()) { return 0; }
  // Send the "reconfig" message
  this->Config();
  // Mark the config. as current
  fConfig.SetDirty(false);
  return 1;
}

void FairDbConfigurable::Set(FairDbConfigNotice* d)
{
  bool deleteNotice = false;
  if (d==0) {
    d = new FairDbConfigNotice();
    deleteNotice = true;
  }


  d->SetDefault(this->DefaultConfig());
  d->SetCurrent(this->GetConfig());

  // Query
  FairRegistry r = d->Query();
  this->GetConfig().UnLockValues();
  this->GetConfig().Merge(r);
  this->GetConfig().LockValues();

  // Clean up the notice
  if (deleteNotice) { delete d; d = 0; }
}

void FairDbConfigurable::Set(const char* s)
{
  FairRegistry r;
  FairDbConfig::StringToRegistry(r,s);
  this->GetConfig().UnLockValues();
  this->GetConfig().Merge(r);
  this->GetConfig().LockValues();
}

