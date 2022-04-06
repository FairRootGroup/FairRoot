/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQExParamsClient.cpp
 *
 * @since 2015-10-26
 * @author A. Rybalchenko
 */

#include "FairMQExParamsClient.h"

#include "FairMQExParamsParOne.h"
#include "RootSerializer.h"

#include <chrono>
#include <fairlogger/Logger.h>
#include <thread>   // this_thread::sleep_for

FairMQExParamsClient::FairMQExParamsClient()
    : fRunId(0)
    , fParameterName()
    , fMaxIterations(0)
    , fNumIterations(0)
{}

FairMQExParamsClient::~FairMQExParamsClient() {}

void FairMQExParamsClient::InitTask()
{
    fParameterName = fConfig->GetValue<std::string>("parameter-name");
    fMaxIterations = fConfig->GetValue<uint64_t>("max-iterations");
    fRunId = 2000;
}

bool FairMQExParamsClient::ConditionalRun()
{
    LOG(info) << "Requesting parameter \"" << fParameterName << "\" for Run ID " << fRunId << ".";

    // NewSimpleMessage creates a copy of the data and takes care of its destruction (after the transfer takes place).
    // Should only be used for small data because of the cost of an additional copy
    auto req(NewSimpleMessage(fParameterName + "," + std::to_string(fRunId)));
    auto rep(NewMessage());

    if (Send(req, "data") > 0) {
        if (Receive(rep, "data") >= 0) {
            if (rep->GetSize() != 0) {
                FairMQExParamsParOne* par = nullptr;
                RootSerializer().Deserialize(*rep, par);
                LOG(info) << "Received parameter from the server:";
                par->print();
                delete par;
            } else {
                LOG(error) << "Received empty reply. Parameter not available";
            }
        }
    }

    fRunId == 2099 ? fRunId = 2000 : fRunId++;

    if (fMaxIterations > 0 && ++fNumIterations >= fMaxIterations) {
        LOG(info) << "Configured maximum number of iterations reached. Leaving RUNNING state.";
        return false;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return true;
}
