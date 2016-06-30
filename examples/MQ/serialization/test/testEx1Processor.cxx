
//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "SerializerExample.h"
#include "TMath.h"

#include "MyDigi.h"
#include "MyHit.h"

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"



class Ex1ProcessorTest : public FairMQDevice 
{
  public:
    Ex1ProcessorTest() :
        FairMQDevice(),
        fInput(nullptr),
        fOutput(nullptr)
    {}

    virtual ~Ex1ProcessorTest() {}

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
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            if (Receive(msg,"data-in") > 0)
            {
                Deserialize<MyDeserializer>(*msg,fInput);
                receivedMsgs++;
                Exec(fInput,fOutput);
                Serialize<MySerializer>(*msg,fOutput);
                Send(msg, "data-out");
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
        for(unsigned int idigi(0); idigi<digis->GetEntriesFast(); idigi++)
        {
            TVector3 pos;
            TVector3 dpos;
            Double_t timestamp = 0;
            Double_t timestampErr = 0;
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

        Ex1ProcessorTest processor;
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




