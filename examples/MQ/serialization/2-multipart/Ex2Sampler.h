#ifndef EX2SAMPLER_H
#define EX2SAMPLER_H

#include "MyDigi.h"
#include "RootSerializer.h"
#include "SerializerExample2.h"

#include <FairMQDevice.h>
#include <Rtypes.h>
#include <TFile.h>
#include <TTree.h>
#include <chrono>

class Ex2Sampler : public FairMQDevice
{
  public:
    Ex2Sampler()
        : FairMQDevice()
        , fInput(nullptr)
        , fTree(nullptr)
        , fFileName()
        , fInputFile(nullptr)
    {}

    Ex2Sampler(const Ex2Sampler&);
    Ex2Sampler& operator=(const Ex2Sampler&);

    virtual ~Ex2Sampler()
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
        int64_t sentMsgs = 0;
        const int64_t numEvents = fTree->GetEntries();
        LOG(info) << "Number of events to process: " << numEvents;

        auto tStart = std::chrono::high_resolution_clock::now();

        for (int64_t idx = 0; idx < numEvents; idx++) {
            fTree->GetEntry(idx);
            Ex2Header* header = new Ex2Header();
            header->EventNumber = idx;

            FairMQMessagePtr msgHeader(NewMessage());
            SerializerEx2().Serialize(*msgHeader, header);

            FairMQMessagePtr msg(NewMessage());
            RootSerializer().Serialize(*msg, fInput);

            FairMQParts parts;
            parts.AddPart(std::move(msgHeader));
            parts.AddPart(std::move(msg));

            if (Send(parts, "data1") > 0) {
                sentMsgs++;
            }

            if (NewStatePending()) {
                break;
            }
        }

        auto tEnd = std::chrono::high_resolution_clock::now();
        LOG(info) << "Sent " << sentMsgs
                  << " messages in: " << std::chrono::duration<double, std::milli>(tEnd - tStart).count() << " ms";
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};

#endif
