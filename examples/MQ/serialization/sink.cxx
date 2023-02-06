/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// this example
#include "ExHeader.h"
#include "MyHit.h"

// FairRoot
#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "FairRunFairMQDevice.h"

// ROOT
#include <TFile.h>
#include <TTree.h>

// std
#include <memory>
#include <string>

namespace bpo = boost::program_options;

struct Sink : fair::mq::Device
{
    Sink()
        : fInput(nullptr)
        , fTree("SerializationEx", "Test output")
    {}

    void Init() override
    {
        fNumMsgs = fConfig->GetValue<int>("num-msgs");
        fFileName = fConfig->GetValue<std::string>("output-file");
        fOutputFile.reset(TFile::Open(fFileName.c_str(), "RECREATE"));
        fInput = new TClonesArray("MyHit");
        fTree.Branch("MyHit", "TClonesArray", &fInput);
    }

    void Run() override
    {
        int receivedMsgs = 0;
        while (!NewStatePending()) {
            fair::mq::Parts parts;
            if (Receive(parts, "data2") > 0) {
                if (parts.Size() != 2) {
                    LOG(error) << "parts does not have 2 messages; skipping";
                    continue;
                }
                ExHeader header;
                BoostSerializer<ExHeader>().Deserialize(parts[0], header);
                BoostSerializer<MyHit>().Deserialize(parts[1], fInput);

                receivedMsgs++;
                fTree.SetBranchAddress("MyHit", &fInput);
                fTree.Fill();

                if (fNumMsgs != 0) {
                    if (receivedMsgs == fNumMsgs) {
                        break;
                    }
                }
            }
        }

        LOG(info) << "Received " << receivedMsgs << " messages!";
    }

    void Reset() override
    {
        fTree.Write("", TObject::kOverwrite);

        if (fInput) {
            delete fInput;
        }
    }

  private:
    TClonesArray* fInput;
    std::string fFileName;
    std::unique_ptr<TFile> fOutputFile;
    TTree fTree;
    int fNumMsgs = 0;
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("output-file", bpo::value<std::string>(),           "Path to the output file")
        ("num-msgs",    bpo::value<int>()->default_value(0), "Stop after <n> msgs (0 - no limit).");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& /*config*/)
{
    return std::make_unique<Sink>();
}
