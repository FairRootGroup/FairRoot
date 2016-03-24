



#ifndef EX2SINK_H
#define EX2SINK_H

//std
#include <iostream>
#include <memory>

//FairRoot
#include "FairMQDevice.h"
#include "SerializerExample2.h"

#include <boost/core/null_deleter.hpp>

//root
#include "TFile.h"
#include "TTree.h"




class Ex2Sink : public FairMQDevice 
{
public:
	Ex2Sink() : FairMQDevice(), 
				fInput(nullptr),
				fFileName(),
				fOutFile(nullptr),
				fTree(nullptr)
    {}
	virtual ~Ex2Sink()
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
            FairMQParts parts;
            if (Receive(parts,"data-in") > 0)
            {
                Ex2Header header;
                Deserialize<SerializerEx2Boost>(parts.At_ptr(0),header);
                Deserialize<SerializerEx2Boost>(parts.At_ptr(1),fInput);
                LOG(INFO)<<"Event number"<< header.EventNumber;
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
