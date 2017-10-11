#ifndef EX1SAMPLER_H
#define EX1SAMPLER_H

#include "FairMQDevice.h"
#include "SerializerExample.h"

#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"

#include "MyDigi.h"

class Ex1Sampler : public FairMQDevice
{
  public:
    Ex1Sampler()
        : fInput(nullptr)
        , fTree(nullptr)
        , fFileName()
        , fInputFile(nullptr)
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
        uint64_t sentMsgs = 0;
        const uint64_t numEvents = fTree->GetEntries();
        LOG(INFO) << "Number of events to process: " << numEvents;

        for (uint64_t i = 0; i < numEvents; i++)
        {
            FairMQMessagePtr msg(NewMessage());
            fTree->GetEntry(i);
            Serialize<MySerializer>(*msg, fInput);
            Send(msg, "data-out");
            sentMsgs++;
            if (!CheckCurrentState(RUNNING))
            {
                break;
            }
        }

        LOG(INFO) << "Sent " << sentMsgs << " messages!";
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};

#endif // EX1SAMPLER_H
