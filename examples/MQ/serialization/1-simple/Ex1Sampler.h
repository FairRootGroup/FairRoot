#ifndef EX1SAMPLER_H
#define EX1SAMPLER_H

#include "MyDigi.h"
#include "RootSerializer.h"

#include <FairMQDevice.h>
#include <Rtypes.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

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
        if (fInputFile) {
            fInputFile->Close();
            delete fInputFile;
        }
    }

  protected:
    virtual void Init()
    {
        fFileName = fConfig->GetValue<std::string>("input-file");
        fInputFile = TFile::Open(fFileName.c_str(), "READ");
        if (fInputFile) {
            fTree = static_cast<TTree*>(fInputFile->Get("cbmsim"));
            if (fTree) {
                fTree->SetBranchAddress("MyDigi", &fInput);
            } else {
                LOG(error) << "Could not find tree 'MyDigi'";
            }
        } else {
            LOG(error) << "Could not open file " << fFileName << " in SimpleTreeReader::InitSource()";
        }
    }

    virtual void Run()
    {
        uint64_t sentMsgs = 0;
        const uint64_t numEvents = fTree->GetEntries();
        LOG(info) << "Number of events to process: " << numEvents;

        for (uint64_t i = 0; i < numEvents; i++) {
            FairMQMessagePtr msg(NewMessage());
            fTree->GetEntry(i);
            RootSerializer().Serialize(*msg, fInput);
            Send(msg, "data1");
            sentMsgs++;
            if (NewStatePending()) {
                break;
            }
        }

        LOG(info) << "Sent " << sentMsgs << " messages!";
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};

#endif   // EX1SAMPLER_H
