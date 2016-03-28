#ifndef EX2PROCESSOR_H
#define EX2PROCESSOR_H

//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "FairMQParts.h"
#include "SerializerExample2.h"
#include "TMath.h"



class Ex2Processor : public FairMQDevice 
{
public:
	Ex2Processor() : FairMQDevice(), 
	    			 fInput(nullptr),
	    			 fOutput(nullptr)
    {}
	virtual ~Ex2Processor(){}

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
            //
            if (Receive(parts,"data-in") > 0)
            {
                Ex2Header* header=nullptr;
                Deserialize<SerializerEx2>(parts.At_ref(0),header);
                Deserialize<SerializerEx2>(parts.At_ref(1),fInput);
                
                receivedMsgs++;

                Exec(fInput,fOutput);
                FairMQParts partsToSend;
                partsToSend.AddPart(parts.At(0));

                partsToSend.AddPart(NewMessage());
                Serialize<SerializerEx2Boost>(partsToSend.At_ref(0),*header);
                Serialize<SerializerEx2Boost>(partsToSend.At_ref(1),fOutput);
                Send(partsToSend, "data-out");
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
