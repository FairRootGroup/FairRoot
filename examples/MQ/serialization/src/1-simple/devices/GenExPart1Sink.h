



#ifndef GENEXPART1SINK_H
#define GENEXPART1SINK_H

//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "SerializerExample.h"

//root
#include "TFile.h"
#include "TTree.h"



class GenExPart1Sink : public FairMQDevice 
{
public:
	GenExPart1Sink() : 	FairMQDevice(), 
						fInput(nullptr),
						fFileName(),
						fOutFile(nullptr),
						fTree(nullptr)
    {}
	virtual ~GenExPart1Sink()
	{
	    fTree->Write("", TObject::kOverwrite);

	    if (fTree)
	        delete fTree;

	    if (fOutFile)
	    {
	        if (fOutFile->IsOpen())
	            fOutFile->Close();
	        delete fOutFile;
	    }
	}
	void SetFileName(const std::string& filename){fFileName=filename;}

protected:
    virtual void Init()
    {
	    fOutFile = TFile::Open(fFileName.c_str(),"RECREATE");
	    fInput = new TClonesArray("MyHit");
	    fTree = new TTree("GenExPart1", "Test output");
	    fTree->Branch("MyHit","TClonesArray", &fInput);	       
    }

    virtual void Run()
    {
        int receivedMsgs = 0;
        int sentMsgs = 0;
        while (CheckCurrentState(RUNNING))
        {
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            if (Receive(msg, "data-in") > 0)
            {
                Deserialize<MyDeserializer>(msg,fInput);
                receivedMsgs++;
                fTree->SetBranchAddress("MyHit", &fInput);
                fTree->Fill();
            }
        }
        LOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
    }

private:
	/* data */
    TClonesArray* fInput;
    std::string fFileName;
    TFile* fOutFile;
    TTree* fTree;
};


#endif
