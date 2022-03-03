/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSamplerTask.cxx
 *
 * @since 2012-11-22
 * @author D. Klein, A. Rybalchenko
 */

#include "FairMQSamplerTask.h"

#include "FairRootManager.h"

FairMQSamplerTask::FairMQSamplerTask()
    : FairTask("Abstract base task used for loading a branch from a root file into memory")
    , fBranch()
    , fInput(nullptr)
    , fPayload()
    , fEventIndex(0)
    , fEvtHeader(nullptr)
    , fTransportFactory(nullptr)
{}

FairMQSamplerTask::FairMQSamplerTask(const Text_t* name, int iVerbose)
    : FairTask(name, iVerbose)
    , fBranch()
    , fInput(nullptr)
    , fPayload()
    , fEventIndex(0)
    , fEvtHeader(nullptr)
    , fTransportFactory(nullptr)
{}

FairMQSamplerTask::~FairMQSamplerTask() { delete fInput; }

InitStatus FairMQSamplerTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    fEvtHeader = static_cast<FairEventHeader*>(ioman->GetObject("EventHeader."));
    fInput = static_cast<TClonesArray*>(ioman->GetObject(fBranch.c_str()));

    return kSUCCESS;
}

void FairMQSamplerTask::Exec(Option_t* /*opt*/) {}

void FairMQSamplerTask::SetBranch(const std::string& branch) { fBranch = branch; }

void FairMQSamplerTask::SetEventIndex(Long64_t eventIndex) { fEventIndex = eventIndex; }

void FairMQSamplerTask::GetPayload(fair::mq::MessagePtr& msg) { msg = move(fPayload); }

void FairMQSamplerTask::SetTransport(std::shared_ptr<fair::mq::TransportFactory> factory)
{
    fTransportFactory = factory;
}
