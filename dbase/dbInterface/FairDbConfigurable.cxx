#include "FairDbConfigurable.h"

#include "FairDbConf.h"                 // for FairDbConf
#include "FairDbConfDialog.h"           // for FairDbConfDialog

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

void FairDbConfigurable::Set(FairDbConfDialog* d)
{
  bool deleteDialog = false;
  if (d==0) {
    d = new FairDbConfDialog();
    deleteDialog = true;
  }

  // Set up d with the default configuration parameters
  d->SetDefault(this->DefaultConfig());
  d->SetCurrent(this->GetConfig());

  // Do the querry
  FairRegistry r = d->Query();
  this->GetConfig().UnLockValues();
  this->GetConfig().Merge(r);
  this->GetConfig().LockValues();

  // Clean up the dialog
  if (deleteDialog) { delete d; d = 0; }
}

void FairDbConfigurable::Set(const char* s)
{
  FairRegistry r;
  FairDbConf::StringToRegistry(r,s);
  this->GetConfig().UnLockValues();
  this->GetConfig().Merge(r);
  this->GetConfig().LockValues();
}

