/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef EX1PROCESSOR_H
#define EX1PROCESSOR_H

#include "FairMQ.h"   // for fair::mq::Device
#include "MyDigi.h"
#include "MyHit.h"
#include "RootSerializer.h"

#include <TClonesArray.h>
#include <TMath.h>
#include <memory>

class Ex1Processor : public fair::mq::Device
{
  public:
    Ex1Processor() = default;
    ~Ex1Processor() override = default;

    void Run() override
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (!NewStatePending()) {
            // Receive
            auto msgIn(NewMessageFor("data1", 0));
            if (Receive(msgIn, "data1") > 0) {
                receivedMsgs++;

                // Deserialize
                auto digis = RootSerializer().DeserializeTo<TClonesArray>(*msgIn);
                if (!digis) {
                    LOG(warn) << "Deserialization FAILED, skipping";
                    continue;
                }

                // Compute
                TClonesArray hits = FindHits(*digis);

                // Serialize
                auto msgOut(NewMessageFor("data2", 0));
                RootSerializer().Serialize(*msgOut, &hits);

                // Send
                if (Send(msgOut, "data2") >= 0) {
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

#endif   // EX1PROCESSOR_H
