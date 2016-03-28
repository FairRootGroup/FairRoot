
#ifndef EX2SAMPLER_H
#define EX2SAMPLER_H

//std
#include <iostream>
#include <memory>

//boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/timer/timer.hpp>
#include <boost/core/null_deleter.hpp>

//FairRoot
#include "FairMQDevice.h"
#include "FairMQMessageZMQ.h"
#include "SerializerExample2.h"

// root

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
//typedef boost::null_deleter empty_deleter_t;

struct D { // deleter
    D() {};
    D(const D&) { std::cout << "D copy ctor\n"; }
    D(D&) { std::cout << "D non-const copy ctor\n";}
    D(D&&) { std::cout << "D move ctor \n"; }
    void operator()(FairMQMessageZMQ* p) const {}
    void operator()(FairMQMessage& p) const {}
        
    };
typedef D empty_deleter_t;
class Ex2Sampler : public FairMQDevice
{
public:
	Ex2Sampler() : 	FairMQDevice(), 
    						fInput(nullptr),
    						fTree(nullptr),
    						fFileName(),
    						fInputFile(nullptr)
    {}
	virtual ~Ex2Sampler()
	{
		if (fInputFile)
        {
            fInputFile->Close();
            delete fInputFile;
        }
	}
	void SetFileName(const std::string& name){fFileName=name;}

protected:
    
    virtual void Init()
    {
        fInputFile = TFile::Open(fFileName.c_str(), "READ");
        if (fInputFile)
        {
            fTree = static_cast<TTree*>(fInputFile->Get("cbmsim"));
            if (fTree)
                fTree->SetBranchAddress("MyDigi", &fInput);
            else
				LOG(ERROR) << "Could not find tree 'MyDigi'";
        }
        else
            LOG(ERROR) << "Could not open file " << fFileName << " in SimpleTreeReader::InitSource()";
    }
	virtual void Run()
    {
    	int64_t sentMsgs(0);
    	const int64_t numEvents=fTree->GetEntries();
        LOG(INFO) << "Number of events to process: " << numEvents;
        boost::timer::auto_cpu_timer timer;
        for (int64_t idx(0); idx < numEvents; idx++)
        {
            //std::unique_ptr<FairMQMessage> msg(NewMessage());
            fTree->GetEntry(idx);
            Ex2Header* header = new Ex2Header();
            header->EventNumber=idx;
            std::unique_ptr<FairMQMessage> msgHeader(NewMessage(header, sizeof(Ex2Header)));
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            
            Serialize<SerializerEx2>(*msg,fInput);
            FairMQParts parts;
            parts.AddPart(msgHeader);
            parts.AddPart(msg);
            Send(parts,"data-out");
            sentMsgs++;

            if (!CheckCurrentState(RUNNING))
                break;
        }
        boost::timer::cpu_times const elapsed_time(timer.elapsed());
        LOG(INFO) << "Sent everything in:\n" << boost::timer::format(elapsed_time, 2);
        LOG(INFO) << "Sent " << sentMsgs << " messages!";
    }

private:
	/* data */
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};


#endif