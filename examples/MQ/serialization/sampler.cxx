/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// this example
#include "ExHeader.h"
#include "MyDigi.h"
#include "MyHit.h"   // temporary for the data check (see below)

// FairRoot
#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "FairRunFairMQDevice.h"
#include "RootSerializer.h"

// ROOT
#include <Rtypes.h>
#include <TFile.h>
#include <TMath.h>   // temporary for the data check (see below)
#include <TTree.h>

// std
#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace bpo = boost::program_options;

struct Sampler : fair::mq::Device
{
    Sampler() = default;

    void Init() override
    {
        fFileName = fConfig->GetValue<std::string>("input-file");
        fInputFile.reset(TFile::Open(fFileName.c_str(), "READ"));
        if (fInputFile) {
            fTree.reset(fInputFile->Get<TTree>("cbmsim"));
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

            // temporarily apply data processing steps to check that they work before & after serialization
            volatile TClonesArray hits = FindHits(*fInput);

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
    // temporary method to check data before transfer
    TClonesArray FindHits(const TClonesArray& digis)
    {
        TClonesArray hits("MyHit");
        const TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
        const Int_t fDetID = 0;
        const Int_t fMCIndex = 0;

        for (int i = 0; i < digis.GetEntriesFast(); i++) {
            auto digi = static_cast<MyDigi const*>(digis.At(i));
            const TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
            auto hit = new ((hits)[i]) MyHit(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }

        return hits;
    }

    TClonesArray* fInput{nullptr};
    std::string fFileName;
    std::unique_ptr<TFile> fInputFile;
    std::unique_ptr<TTree> fTree;
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
