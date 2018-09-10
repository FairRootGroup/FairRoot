#ifndef EX2PROCESSOR_H
#define EX2PROCESSOR_H

// std
#include <iostream>
#include <memory>

// FairRoot
#include "FairMQDevice.h"
#include "FairMQParts.h"
#include "SerializerExample2.h"
#include "RootSerializer.h"
#include "BoostSerializer.h"

#include "TMath.h"

#include "MyDigi.h"
#include "MyHit.h"

class Ex2Processor : public FairMQDevice
{
  public:
    Ex2Processor()
        : fInput(nullptr)
        , fOutput(nullptr)
        , fNumMsgs(0)
    {}

    Ex2Processor(const Ex2Processor&);
    Ex2Processor& operator=(const Ex2Processor&);

    virtual ~Ex2Processor() {}

  protected:
    virtual void Init()
    {
        fNumMsgs = fConfig->GetValue<int>("num-msgs");
        fOutput = new TClonesArray("MyHit");
    }

    virtual void Run()
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (CheckCurrentState(RUNNING))
        {
            FairMQParts partsIn;

            if (Receive(partsIn, "data1") > 0)
            {
                Ex2Header* header = nullptr;
                Deserialize<SerializerEx2>(*(partsIn.At(0)), header);
                Deserialize<RootSerializer>(*(partsIn.At(1)), fInput);

                receivedMsgs++;

                Exec(fInput, fOutput);

                FairMQParts partsOut;
                partsOut.AddPart(std::move(partsIn.At(0)));
                partsOut.AddPart(NewMessage());

                Serialize<BoostSerializer<Ex2Header>>(*(partsOut.At(0)), *header);
                Serialize<BoostSerializer<MyHit>>(*(partsOut.At(1)), fOutput);
                Send(partsOut, "data2");
                sentMsgs++;

                if (fNumMsgs != 0)
                {
                    if (receivedMsgs == fNumMsgs)
                    {
                        break;
                    }
                }
            }
        }
        LOG(info) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

    // do some random dummy task
    void Exec(TClonesArray* digis, TClonesArray* hits)
    {
        hits->Delete();
        for (int idigi(0); idigi<digis->GetEntriesFast(); idigi++)
        {
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
    int fNumMsgs;
};

#endif
