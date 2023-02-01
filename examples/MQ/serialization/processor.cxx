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
#include "MyHit.h"

// FairRoot
#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "FairRunFairMQDevice.h"
#include "RootSerializer.h"

// ROOT
#include <TMath.h>

// std
#include <memory>

namespace bpo = boost::program_options;

struct Processor : fair::mq::Device
{
    void Run() override
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (!NewStatePending()) {
            fair::mq::Parts partsIn;

            if (Receive(partsIn, "data1") > 0) {
                ExHeader header;
                BoostSerializer<ExHeader>().Deserialize(*(partsIn.At(0)), header);
                auto digis = RootSerializer().DeserializeTo<TClonesArray>(*(partsIn.At(1)));
                if (!digis) {
                    LOG(warn) << "Deserialization FAILED, skipping";
                    continue;
                }

                receivedMsgs++;

                TClonesArray hits = FindHits(*digis);

                fair::mq::Parts partsOut;
                partsOut.AddPart(std::move(partsIn.At(0)));
                partsOut.AddPart(NewMessage());

                BoostSerializer<MyHit>().Serialize(*(partsOut.At(1)), &hits);
                if (Send(partsOut, "data2") >= 0) {
                    sentMsgs++;
                }
            }
        }
        LOG(info) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

  private:
    // do some random dummy task
    TClonesArray FindHits(const TClonesArray& digis)
    {
        TClonesArray hits("MyHit");
        const TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
        const Int_t fDetID = 0;
        const Int_t fMCIndex = 0;

        for (int i = 0; i < digis.GetEntriesFast(); i++) {
            // Double_t timestamp = 0;
            // Double_t timestampErr = 0;
            auto digi = static_cast<MyDigi const*>(digis.At(i));
            const TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
            auto hit = new ((hits)[i]) MyHit(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }

        return hits;
    }
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("num-msgs", bpo::value<int>()->default_value(0), "Stop after <n> msgs (0 - no limit).");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& /*config*/)
{
    return std::make_unique<Processor>();
}
