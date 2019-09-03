/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairOnlineSink.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairOnlineSink.h"

#include "FairMQRunDevice.h"

#include <FairMQLogger.h>

FairOnlineSink::FairOnlineSink()
  : FairSink()
  , fMQRunDevice(nullptr)
{
}

FairOnlineSink::FairOnlineSink(const FairOnlineSink&)
  : FairSink()
  , fMQRunDevice(nullptr)
{
}

FairOnlineSink::~FairOnlineSink()
{
}

//_____________________________________________________________________________
void FairOnlineSink::RegisterImpl(const char* , const char* , void* )
{
  return;
}

//_____________________________________________________________________________
void FairOnlineSink::RegisterAny(const char* /* brname */, const std::type_info &/* oi */, const std::type_info &/* pi */, void* /* obj */)
{
  return;
}

void  FairOnlineSink::Fill()
{
  /// Fill the Root tree.
  LOG(debug) << "[" << FairRootManager::Instance()->GetInstanceId() << "] called FairOnlineSink::Fill()!!!!";
  
  if ( fMQRunDevice )
      fMQRunDevice->SendBranches();
}
 
Bool_t FairOnlineSink::InitSink()
{
    return kTRUE;
}

//_____________________________________________________________________________
FairSink*  FairOnlineSink::CloneSink() {
    FairRootManager* tempMan = FairRootManager::Instance();
    FairOnlineSink* newSink = new FairOnlineSink(*this);
    newSink->SetMQRunDevice(this->GetMQRunDevice());
    LOG(info) << "[" << tempMan->GetInstanceId() << "] FairOnlineSink::CloneSink() setting MQRunDevice to " << this->GetMQRunDevice();

    return newSink;
}
//_____________________________________________________________________________
