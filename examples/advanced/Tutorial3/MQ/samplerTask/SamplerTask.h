/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_SAMPLERTASK_H
#define FAIR_TESTDETECTOR_SAMPLERTASK_H

// FairRoot
#include "FairEventHeader.h"
#include "FairMQ.h"   // for fair::mq::Message, fair::mq::TransportFactory
#include "FairRootManager.h"
#include "FairTask.h"

// ROOT
#include <TClonesArray.h>

// std
#include <memory>
#include <string>

class SamplerTask : public FairTask
{
  public:
    SamplerTask()
        : FairTask("Abstract base task used for loading a branch from a root file into memory")
    {}

    SamplerTask(const Text_t* name, int iVerbose = 1)
        : FairTask(name, iVerbose)
    {}

    SamplerTask(const SamplerTask&) = delete;
    SamplerTask operator=(const SamplerTask&) = delete;

    InitStatus Init() override
    {
        FairRootManager* ioman = FairRootManager::Instance();
        fEvtHeader = static_cast<FairEventHeader*>(ioman->GetObject("EventHeader."));
        fInput = static_cast<TClonesArray*>(ioman->GetObject(fBranch.c_str()));
        return kSUCCESS;
    }

    void SetEventIndex(Long64_t eventIndex) { fEventIndex = eventIndex; }
    void SetBranch(const std::string& branch) { fBranch = branch; }

    void GetPayload(std::unique_ptr<fair::mq::Message>& msg) { msg = std::move(fPayload); }
    void SetTransport(std::shared_ptr<fair::mq::TransportFactory> factory) { fTransportFactory = factory; }

  protected:
    std::string fBranch;
    TClonesArray* fInput = nullptr;   // non-owning ptr, populated from FairRootManager during Init
    fair::mq::MessagePtr fPayload;
    Long64_t fEventIndex = 0;
    FairEventHeader* fEvtHeader = nullptr;   // non-owning ptr, populated from FairRootManager during Init
    std::shared_ptr<fair::mq::TransportFactory> fTransportFactory;
};

#endif /* FAIR_TESTDETECTOR_SAMPLERTASK_H */
