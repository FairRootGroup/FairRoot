/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQRunDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQRunDevice.h"

#include "FairOnlineSink.h"
#include "FairRootManager.h"
#include "RootSerializer.h"

#include <Rtypes.h>
#include <TList.h>
#include <TObjString.h>
#include <cstdio>   // printf
#include <fairlogger/Logger.h>

using namespace std;

#include <mutex>   // std::mutex
std::mutex mtx;    // mutex for critical section

void FairMQRunDevice::SendObject(TObject* obj, const std::string& chan)
{
    auto mess(NewMessage());
    RootSerializer().Serialize(*mess, obj);

    auto rep(NewMessage());

    printf("sending %s", obj->GetName());
    if (Send(mess, chan) > 0) {
        if (Receive(rep, chan) > 0) {
            std::string repString = string(static_cast<char*>(rep->GetData()), rep->GetSize());
            LOG(info) << " -> " << repString.data();
        }
    }
}

void FairMQRunDevice::SendBranches()
{
    /// Fill the Root tree.
    LOG(debug) << "called FairMQRunDevice::SendBranches()!!!!";

    TList* branchNameList = FairRootManager::Instance()->GetBranchNameList();
    TObjString* ObjStr;

    for (auto& mi : fChannels) {
        LOG(debug) << "trying channel >" << mi.first.data() << "<";

        fair::mq::Parts parts;

        for (Int_t t = 0; t < branchNameList->GetEntries(); t++) {
            ObjStr = static_cast<TObjString*>(branchNameList->TList::At(t));
            LOG(debug) << "              branch >" << ObjStr->GetString().Data() << "<";
            std::string modifiedBranchName = std::string("#") + ObjStr->GetString().Data() + "#";
            if (mi.first.find(modifiedBranchName) != std::string::npos || mi.first.find("#all#") != std::string::npos) {
                if ((static_cast<FairOnlineSink*>(FairRootManager::Instance()->GetSink()))
                        ->IsPersistentBranchAny(ObjStr->GetString())) {
                    LOG(debug) << "Branch \"" << ObjStr->GetString() << "\" is persistent ANY";
                    if (ObjStr->GetString().CompareTo("MCTrack") == 0) {
                        TClonesArray** mcTrackArray =
                            (static_cast<FairOnlineSink*>(FairRootManager::Instance()->GetSink()))
                                ->GetPersistentBranchAny<TClonesArray**>(ObjStr->GetString());
                        if (mcTrackArray) {
                            (*mcTrackArray)->SetName("MCTrack");
                            LOG(debug) << "[" << FairRootManager::Instance()->GetInstanceId() << "] mcTrack "
                                       << mcTrackArray << " /// *mcTrackArray " << *mcTrackArray
                                       << " /// *mcTrackArray->GetName() " << (*mcTrackArray)->GetName();
                            TObject* objClone = (*mcTrackArray)->Clone();
                            LOG(debug) << "FairMQRunDevice::SendBranches() the track array has "
                                       << ((TClonesArray*)(objClone))->GetEntries() << " entries.";
                            auto mess(NewMessage());
                            RootSerializer().Serialize(*mess, objClone);
                            parts.AddPart(std::move(mess));
                            LOG(debug) << "channel >" << mi.first.data() << "< --> >" << ObjStr->GetString().Data()
                                       << "<";
                        }
                    } else {
                        LOG(warning) << "FairMQRunDevice::SendBranches() hasn't got knowledge how to send any branch \""
                                     << ObjStr->GetString().Data() << "\"";
                        continue;
                    }
                } else {
                    TObject* object = FairRootManager::Instance()->GetObject(ObjStr->GetString());
                    if (object) {
                        TObject* objClone = object->Clone();
                        auto mess(NewMessage());
                        RootSerializer().Serialize(*mess, objClone);
                        parts.AddPart(std::move(mess));
                        LOG(debug) << "channel >" << mi.first.data() << "< --> >" << ObjStr->GetString().Data() << "<";
                    } else {
                        LOG(fatal) << "Object " << ObjStr->GetString() << " NOT FOUND!!!";
                    }
                }
            }
        }
        if (parts.Size() > 0) {
            std::unique_lock<std::mutex> lock(mtx);
            Send(parts, mi.first.data());
        }
    }
}
