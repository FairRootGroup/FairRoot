
//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "SerializerExample2.h"
#include "TMath.h"

#include "MyDigi.h"
#include "MyHit.h"

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"
#include "FairMQParts.h"



class Ex2ProcessorTest : public FairMQDevice 
{
  public:
    Ex2ProcessorTest() :
        FairMQDevice(),
        fInput(nullptr),
        fOutput(nullptr)
    {}

    Ex2ProcessorTest(const Ex2ProcessorTest&);
    Ex2ProcessorTest& operator=(const Ex2ProcessorTest&);

    virtual ~Ex2ProcessorTest() {}

  protected:
    virtual void Init()
    {
        fOutput = new TClonesArray("MyHit");
    }

    virtual void Run()
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;

        while (CheckCurrentState(RUNNING))
        {
            FairMQParts parts;

            if (Receive(parts, "data-in") > 0)
            {
                Ex2Header* header=nullptr;
                Deserialize<SerializerEx2>(parts.AtRef(0), header);
                Deserialize<SerializerEx2>(parts.AtRef(1), fInput);

                receivedMsgs++;

                Exec(fInput, fOutput);
                FairMQParts partsToSend;
                partsToSend.AddPart(parts.At(0));

                partsToSend.AddPart(NewMessage());
                Serialize<SerializerEx2Boost>(partsToSend.AtRef(0), *header);
                Serialize<SerializerEx2Boost>(partsToSend.AtRef(1), fOutput);
                Send(partsToSend, "data-out");
                sentMsgs++;
            }
            if(receivedMsgs==100 && sentMsgs==100)
                break;
        }
        LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

    // do some random dummy task
    void Exec(TClonesArray* digis, TClonesArray* hits)
    {
        hits->Delete();
        for(int idigi(0); idigi<digis->GetEntriesFast(); idigi++)
        {
            TVector3 pos;
            TVector3 dpos;
            // Double_t timestamp = 0;
            // Double_t timestampErr = 0;
            Int_t fDetID = 0;
            Int_t fMCIndex = 0;
            MyDigi* digi = static_cast<MyDigi*>(digis->At(idigi));
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



int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        // parse command line
        config.ParseAll(argc, argv);

        Ex2ProcessorTest processor;
        runStateMachine(processor, config);

    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}




