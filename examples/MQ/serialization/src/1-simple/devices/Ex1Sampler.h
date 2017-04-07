#ifndef GENEXPART1SAMPLER_H
#define GENEXPART1SAMPLER_H

// std
#include <iostream>
#include <memory>
#include <chrono>

// FairRoot
#include "FairMQDevice.h"
#include "SerializerExample.h"

// root
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"

#include "MyDigi.h"

class Ex1Sampler : public FairMQDevice
{
  public:
    Ex1Sampler() :
        fInput(nullptr),
        fTree(nullptr),
        fFileName(),
        fInputFile(nullptr)
    {}

    Ex1Sampler(const Ex1Sampler&);
    Ex1Sampler& operator=(const Ex1Sampler&);

    virtual ~Ex1Sampler()
    {
        if (fInputFile)
        {
            fInputFile->Close();
            delete fInputFile;
        }
    }

  protected:
    virtual void Init()
    {
        fFileName = fConfig->GetValue<std::string>("input-file");
        fInputFile = TFile::Open(fFileName.c_str(), "READ");
        if (fInputFile)
        {
            fTree = static_cast<TTree*>(fInputFile->Get("cbmsim"));
            if (fTree)
            {
                fTree->SetBranchAddress("MyDigi", &fInput);
            }
            else
            {
                LOG(ERROR) << "Could not find tree 'MyDigi'";
            }
        }
        else
        {
            LOG(ERROR) << "Could not open file " << fFileName << " in SimpleTreeReader::InitSource()";
        }
    }

    virtual void Run()
    {
        int64_t sentMsgs(0);
        const int64_t numEvents = fTree->GetEntries();
        LOG(INFO) << "Number of events to process: " << numEvents;
        auto tStart = std::chrono::high_resolution_clock::now();
        for (int64_t idx = 0; idx < numEvents; idx++)
        {
            std::unique_ptr<FairMQMessage> msg(NewMessage());
            fTree->GetEntry(idx);
            Serialize<MySerializer>(*msg, fInput);
            Send(msg, "data-out");
            sentMsgs++;//LOG(INFO)<<"SAMPLER";
            if (!CheckCurrentState(RUNNING))
            {
                break;
            }
        }
        auto tEnd = std::chrono::high_resolution_clock::now();
        LOG(INFO) << "Sent everything in: " << std::chrono::duration<double, std::milli>(tEnd - tStart).count() << " ms";
        LOG(INFO) << "Sent " << sentMsgs << " messages!";
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};

#endif
