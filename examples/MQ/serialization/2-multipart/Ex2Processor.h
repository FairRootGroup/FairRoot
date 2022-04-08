/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef EX2PROCESSOR_H
#define EX2PROCESSOR_H

#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "MyDigi.h"
#include "MyHit.h"
#include "RootSerializer.h"
#include "SerializerExample2.h"

#include <TMath.h>

class Ex2Processor : public fair::mq::Device
{
  public:
    Ex2Processor()
        : fInput(nullptr)
        , fOutput(nullptr)
    {}

    void Init() override { fOutput = new TClonesArray("MyHit"); }

    void Run() override
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (!NewStatePending()) {
            fair::mq::Parts partsIn;

            if (Receive(partsIn, "data1") > 0) {
                Ex2Header* header = nullptr;
                SerializerEx2().Deserialize(*(partsIn.At(0)), header);
                RootSerializer().Deserialize(*(partsIn.At(1)), fInput);

                receivedMsgs++;

                Exec(fInput, fOutput);

                fair::mq::Parts partsOut;
                partsOut.AddPart(std::move(partsIn.At(0)));
                partsOut.AddPart(NewMessage());

                BoostSerializer<Ex2Header>().Serialize(*(partsOut.At(0)), *header);
                BoostSerializer<MyHit>().Serialize(*(partsOut.At(1)), fOutput);
                if (Send(partsOut, "data2") >= 0) {
                    sentMsgs++;
                }
            }
        }
        LOG(info) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

    // do some random dummy task
    void Exec(TClonesArray* digis, TClonesArray* hits)
    {
        hits->Delete();
        for (int idigi(0); idigi < digis->GetEntriesFast(); idigi++) {
            TVector3 pos;
            TVector3 dpos;
            // Double_t timestamp = 0;
            // Double_t timestampErr = 0;
            Int_t fDetID = 0;
            Int_t fMCIndex = 0;
            MyDigi* digi = (MyDigi*)digis->At(idigi);
            pos.SetXYZ(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
            dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
            MyHit* hit = new ((*hits)[idigi]) MyHit(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }
    }

  private:
    TClonesArray* fInput;
    TClonesArray* fOutput;
};

#endif
