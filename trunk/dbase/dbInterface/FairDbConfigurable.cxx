#include "FairDbConfigurable.h"
#include "FairDbConf.h"
#include "FairDbConfDialog.h"
#include "FairDb.h"

ClassImp(FairDbConfigurable)

//......................................................................

FairDbConfigurable::FairDbConfigurable() : fDefConfig(), fConfig(false) { }

//......................................................................

FairDbConfigurable::~FairDbConfigurable() { }

//......................................................................

void FairDbConfigurable::CommitDefaultConfig(const FairRegistry& r)
{
///======================================================================
/// Subclass must call this before the Configurable can have
/// meaningful entries
///======================================================================
  fDefConfig = r;
}

//......................................................................

const FairRegistry& FairDbConfigurable::DefaultConfig() const
{
///======================================================================
/// Eventually this might go in the database and load the
/// configuration. This would take a name or something.
///======================================================================
  return fDefConfig;
}

FairRegistry& FairDbConfigurable::GetConfig()
{
///======================================================================
/// Returns the configuration FairRegistry, this is non-const as the user
/// is user is free to modify
///======================================================================
  return fConfig;
}

const FairRegistry& FairDbConfigurable::GetConfig() const
{
///======================================================================
/// Returns the configuration FairRegistry.  This const version denies
/// the user any freedom to modify it, but does mean that a
/// configurable object can use it in a const method.
///======================================================================
  return fConfig;
}

//......................................................................

int FairDbConfigurable::Update()
{
///======================================================================
/// Update the class's state given the current configuration. If there
/// is nothing to do just return w/o taking any action. Return's 0 if
/// no action was taken, >0 if the object was reconfigured.
///======================================================================
  if (! fConfig.IsDirty()) { return 0; }  // Nothing to do if config is current
  this->Config();               // Send the "reconfig" message
  fConfig.SetDirty(false);      // Mark the config. as current
  return 1;
}

//......................................................................

void FairDbConfigurable::Set(FairDbConfDialog* d)
{
//======================================================================
// Update the configuration parameters. Allow a FairDbDialog object to be
// passed in. If none is passed in use the default, text based dialog
// object.
//======================================================================
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

//......................................................................

void FairDbConfigurable::Set(const char* s)
{
///======================================================================
/// Update the configuration given a text string s. Format:
/// "key1=true, key2=10, key3=11.1, key4='A string'"
///======================================================================
  FairRegistry r;
  FairDbConf::StringToRegistry(r,s);
  this->GetConfig().UnLockValues();
  this->GetConfig().Merge(r);
  this->GetConfig().LockValues();
}

////////////////////////////////////////////////////////////////////////
