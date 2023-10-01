/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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
#include "FairRootManager.h"

#include <fairlogger/Logger.h>

//_____________________________________________________________________________
void FairOnlineSink::RegisterImpl(const char*, const char*, void*) {}

//_____________________________________________________________________________
void FairOnlineSink::RegisterAny(const char* brname, const std::type_info& oi, const std::type_info& pi, void* obj)
{
    fPersistentBranchesMap[brname] = std::unique_ptr<TypeAddressPair const>(new TypeAddressPair(oi, pi, obj));
}

//_____________________________________________________________________________
bool FairOnlineSink::IsPersistentBranchAny(const char* name)
{
    return fPersistentBranchesMap.find(name) != fPersistentBranchesMap.end();
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

    if (fMQRunDevice) {
        fMQRunDevice->SendBranches(*this);
    }
}

//_____________________________________________________________________________
FairSink* FairOnlineSink::CloneSink()
{
    FairRootManager* tempMan = FairRootManager::Instance();
    auto newSink = new FairOnlineSink(*this);
    LOG(info) << "[" << tempMan->GetInstanceId() << "] FairOnlineSink::CloneSink() setting MQRunDevice to "
              << this->GetMQRunDevice();

    return newSink;
}
//_____________________________________________________________________________
