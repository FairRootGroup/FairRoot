#ifndef EX1PROCESSOR_H
#define EX1PROCESSOR_H

#include "MyDigi.h"
#include "MyHit.h"
#include "RootSerializer.h"

#include <FairMQDevice.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <memory>

class Ex1Processor : public FairMQDevice
{
  public:
    Ex1Processor()
        : fNumMsgs(0)
    {}

    Ex1Processor(const Ex1Processor&);
    Ex1Processor& operator=(const Ex1Processor&);

    virtual ~Ex1Processor() {}

  protected:
    virtual void Init() { fNumMsgs = fConfig->GetValue<int>("num-msgs"); }

    virtual void Run()
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (!NewStatePending()) {
            /// RECEIVE ///
            FairMQMessagePtr msgIn(NewMessageFor("data1", 0));
            if (Receive(msgIn, "data1") > 0) {
                receivedMsgs++;

                /// DESERIALIZE ///
                std::unique_ptr<TClonesArray> digis(nullptr);
                RootSerializer().Deserialize(*msgIn, digis);

                /// COMPUTE ///
                TClonesArray hits = FindHits(*digis);

                /// SERIALIZE ///
                FairMQMessagePtr msgOut(NewMessageFor("data2", 0));
                RootSerializer().Serialize(*msgOut, &hits);

                /// SEND ///
                Send(msgOut, "data2");
                sentMsgs++;

                if (fNumMsgs != 0) {
                    if (receivedMsgs == fNumMsgs) {
                        break;
                    }
                }
            }
        }
        LOG(info) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

    // do some random dummy task
    TClonesArray FindHits(const TClonesArray& digis)
    {
        TClonesArray hits("MyHit");

        for (int i = 0; i < digis.GetEntriesFast(); i++) {
            TVector3 pos;
            TVector3 dpos;
            // Double_t timestamp = 0;
            // Double_t timestampErr = 0;
            Int_t fDetID = 0;
            Int_t fMCIndex = 0;
            MyDigi* digi = static_cast<MyDigi*>(digis.At(i));
            pos.SetXYZ(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
            dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
            MyHit* hit = new ((hits)[i]) MyHit(fDetID, fMCIndex, pos, dpos);
            hit->SetTimeStamp(digi->GetTimeStamp());
            hit->SetTimeStampError(digi->GetTimeStampError());
        }

        return hits;
    }

  private:
    int fNumMsgs;
};

#endif   // EX1PROCESSOR_H
