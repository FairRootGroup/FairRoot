#ifndef EX2SINK_H
#define EX2SINK_H

#include "BoostSerializer.h"
#include "MyHit.h"
#include "SerializerExample2.h"

#include <FairMQDevice.h>
#include <TFile.h>
#include <TTree.h>

class Ex2Sink : public FairMQDevice
{
  public:
    Ex2Sink()
        : FairMQDevice()
        , fInput(nullptr)
        , fFileName()
        , fOutFile(nullptr)
        , fTree(nullptr)
        , fNumMsgs(0)
    {}

    Ex2Sink(const Ex2Sink&);
    Ex2Sink& operator=(const Ex2Sink&);

    virtual ~Ex2Sink()
    {
        if (fTree) {
            fTree->Write("", TObject::kOverwrite);

            delete fTree;
        }

        if (fOutFile) {
            if (fOutFile->IsOpen()) {
                fOutFile->Close();
            }
            delete fOutFile;
        }
    }

  protected:
    virtual void Init()
    {
        fNumMsgs = fConfig->GetValue<int>("num-msgs");
        fFileName = fConfig->GetValue<std::string>("output-file");
        fOutFile = TFile::Open(fFileName.c_str(), "RECREATE");
        fInput = new TClonesArray("MyHit");
        fTree = new TTree("SerializationEx2", "output");
        fTree->Branch("MyHit", "TClonesArray", &fInput);
    }

    virtual void Run()
    {
        int receivedMsgs = 0;
        while (!NewStatePending()) {
            FairMQParts parts;
            if (Receive(parts, "data2") > 0) {
                Ex2Header header;
                BoostSerializer<Ex2Header>().Deserialize(*(parts.At(0)), header);
                BoostSerializer<MyHit>().Deserialize(*(parts.At(1)), fInput);

                receivedMsgs++;
                fTree->SetBranchAddress("MyHit", &fInput);
                fTree->Fill();

                if (fNumMsgs != 0) {
                    if (receivedMsgs == fNumMsgs) {
                        break;
                    }
                }
            }
        }
        LOG(info) << "Received " << receivedMsgs << " messages!";
    }

  private:
    TClonesArray* fInput;
    std::string fFileName;
    TFile* fOutFile;
    TTree* fTree;
    int fNumMsgs;
};

#endif
