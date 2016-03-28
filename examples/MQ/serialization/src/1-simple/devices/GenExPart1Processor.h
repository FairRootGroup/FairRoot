#ifndef GENEXPART1PROCESSOR_H
#define GENEXPART1PROCESSOR_H

//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "SerializerExample.h"
#include "TMath.h"



class GenExPart1Processor : public FairMQDevice 
{
public:
	GenExPart1Processor() : FairMQDevice(), 
	    					fInput(nullptr),
	    					fOutput(nullptr)
    {}
	virtual ~GenExPart1Processor(){}

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
        }
        LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }



    // do some random dummy task
    void Exec(TClonesArray* digis, TClonesArray* hits)
	{
		hits->Delete();
	    for(unsigned int idigi(0);idigi<digis->GetEntriesFast();idigi++)
	    {
	        TVector3 pos;
	        TVector3 dpos;
	        Double_t timestamp=0;
	        Double_t timestampErr=0;
	        Int_t fDetID=0;
    		Int_t fMCIndex=0;
	        MyDigi* digi = (MyDigi*)digis->At(idigi);
	        pos.SetXYZ(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
	        dpos.SetXYZ(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));
	        MyHit* hit = new ((*hits)[idigi]) MyHit(fDetID, fMCIndex, pos, dpos);
	        hit->SetTimeStamp(digi->GetTimeStamp());
	        hit->SetTimeStampError(digi->GetTimeStampError());
	    }
	}

private:
	/* data */
    TClonesArray* fInput;
    TClonesArray* fOutput;
};


#endif
