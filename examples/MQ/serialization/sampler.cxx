/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// this example
#include "ExHeader.h"
#include "MyDigi.h"

// FairRoot
#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "FairRunFairMQDevice.h"
#include "RootSerializer.h"

// ROOT
#include <Rtypes.h>
#include <TFile.h>
#include <TTree.h>

// std
#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace bpo = boost::program_options;

struct Sampler : fair::mq::Device
{
    Sampler()
        : fInput(nullptr)
        , fTree(nullptr)
    {}

    void Init() override
    {
        fFileName = fConfig->GetValue<std::string>("input-file");
        fInputFile.reset(TFile::Open(fFileName.c_str(), "READ"));
        if (fInputFile) {
            fTree = fInputFile->Get<TTree>("cbmsim");
            if (fTree) {
                fTree->SetBranchAddress("MyDigi", &fInput);
            } else {
                LOG(error) << "Could not find tree 'MyDigi'";
            }
        } else {
            LOG(error) << "Could not open file " << fFileName << " in SimpleTreeReader::InitSource()";
        }
    }

    void Run() override
    {
        uint64_t sentMsgs = 0;
        const Long64_t numEvents = fTree->GetEntries();
        LOG(info) << "Number of events to process: " << numEvents;

        for (Long64_t idx = 0; idx < numEvents; idx++) {
            fTree->GetEntry(idx);

            ExHeader header;
            header.eventNumber = idx;

            auto msgHeader(NewMessage());
            BoostSerializer<ExHeader>().Serialize(*msgHeader, header);

            auto msg(NewMessage());
            RootSerializer().Serialize(*msg, fInput);

            fair::mq::Parts parts;
            parts.AddPart(std::move(msgHeader));
            parts.AddPart(std::move(msg));

            if (Send(parts, "data1") > 0) {
                sentMsgs++;
            }

            if (NewStatePending()) {
                break;
            }
        }

        LOG(info) << "Sent " << sentMsgs << " messages!";

        // stay in the Running state until a transition to Ready is requested
        while (!NewStatePending()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    std::unique_ptr<TFile> fInputFile;
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("input-file", bpo::value<std::string>(), "Path to the input file");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& /*config*/)
{
    return std::make_unique<Sampler>();
}
