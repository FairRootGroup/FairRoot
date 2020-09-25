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

#include "FairMQRunDevice.h"   // for FairMQRunDevice
#include "FairRootManager.h"   // for FairRootManager

#include <fairlogger/Logger.h>   // for Logger, LOG
#include <iosfwd>                // for string
#include <string>                // for operator<

FairOnlineSink::FairOnlineSink()
    : FairSink()
    , fMQRunDevice(nullptr)
{}

FairOnlineSink::FairOnlineSink(const FairOnlineSink&)
    : FairSink()
    , fMQRunDevice(nullptr)
{}

//_____________________________________________________________________________
void FairOnlineSink::RegisterImpl(const char*, const char*, void*) { return; }

//_____________________________________________________________________________
void FairOnlineSink::RegisterAny(const char* brname, const std::type_info& oi, const std::type_info& pi, void* obj)
{
    fPersistentBranchesMap[brname] = std::unique_ptr<TypeAddressPair const>(new TypeAddressPair(oi, pi, obj));
}

//_____________________________________________________________________________
bool FairOnlineSink::IsPersistentBranchAny(const char* name)
{
    if (fPersistentBranchesMap.find(name) == fPersistentBranchesMap.end()) {
        return false;
    }
    return true;
}

//_____________________________________________________________________________
void FairOnlineSink::EmitPersistentBranchWrongTypeWarning(const char* brname,
                                                          const char* type1,
                                                          const char* type2) const
{
    LOG(warn) << "Trying to read from persistent branch " << brname << " with wrong type " << type1
              << " (expexted: " << type2 << " )";
}

//_____________________________________________________________________________
void FairOnlineSink::Fill()
{
    /// Fill the Root tree.
    LOG(debug) << "[" << FairRootManager::Instance()->GetInstanceId() << "] called FairOnlineSink::Fill()!!!!";

    if (fMQRunDevice)
        fMQRunDevice->SendBranches();
}

//_____________________________________________________________________________
FairSink* FairOnlineSink::CloneSink()
{
    FairRootManager* tempMan = FairRootManager::Instance();
    FairOnlineSink* newSink = new FairOnlineSink(*this);
    newSink->SetMQRunDevice(this->GetMQRunDevice());
    LOG(info) << "[" << tempMan->GetInstanceId() << "] FairOnlineSink::CloneSink() setting MQRunDevice to "
              << this->GetMQRunDevice();

    return newSink;
}
//_____________________________________________________________________________
