/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// this example
#include "FairMBSRawItem.h"   // data type

// FairRoot
#include "FairMQ.h"   // for fair::mq::Device
#include "FairRunFairMQDevice.h"
#include "RootSerializer.h"   // RootSerializer

// ROOT
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

// logger
#include <fairlogger/Logger.h>

// std
#include <memory>
#include <string>

namespace bpo = boost::program_options;

struct MBSSink : fair::mq::Device
{
    MBSSink()
        : fInput(nullptr)
        , fTree("mbstree", "Test output")
    {}

    void InitTask() override
    {
        fInputChanName = fConfig->GetValue<std::string>("in-chan-name");
        fFileName = fConfig->GetValue<std::string>("output-file-name");
        fOutputFile.reset(TFile::Open(fFileName.c_str(), "RECREATE"));
        fInput = new TClonesArray("FairMBSRawItem");
        fTree.Branch("FairMBSRawItem", "TClonesArray", &fInput);
    }

    void Run() override
    {
        int receivedMsg = 0;
        while (!NewStatePending()) {
            auto msg(NewMessage());
            if (Receive(msg, fInputChanName) > 0) {
                RootSerializer().Deserialize(*msg, fInput);
                fTree.SetBranchAddress("FairMBSRawItem", &fInput);
                fTree.Fill();
                ++receivedMsg;
            }
        }

        LOG(info) << "Received " << receivedMsg << " messages!";
    }

    void Reset() override
    {
        fTree.Write("", TObject::kOverwrite);
        if (fInput) {
            delete fInput;
        }
    }

  private:
    std::string fInputChanName;
    std::string fFileName;
    std::unique_ptr<TFile> fOutputFile;
    TClonesArray* fInput;
    TTree fTree;
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("output-file-name", bpo::value<std::string>(),                        "Path to the output file")
        ("in-chan-name",     bpo::value<std::string>()->default_value("data"), "Input channel name");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    return std::make_unique<MBSSink>();
}
