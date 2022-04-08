/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef EX2SINK_H
#define EX2SINK_H

#include "BoostSerializer.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::Parts
#include "MyHit.h"
#include "SerializerExample2.h"

#include <TFile.h>
#include <TTree.h>

class Ex2Sink : public fair::mq::Device
{
  public:
    Ex2Sink()
        : fInput(nullptr)
        , fOutFile(nullptr)
        , fTree("SerializationEx1", "Test output")
        , fNumMsgs(0)
    {}

    void Init() override
    {
        fNumMsgs = fConfig->GetValue<int>("num-msgs");
        fFileName = fConfig->GetValue<std::string>("output-file");
        fOutFile = TFile::Open(fFileName.c_str(), "RECREATE");
        fInput = new TClonesArray("MyHit");
        fTree.Branch("MyHit", "TClonesArray", &fInput);
    }

    void Run() override
    {
        int receivedMsgs = 0;
        while (!NewStatePending()) {
            fair::mq::Parts parts;
            if (Receive(parts, "data2") > 0) {
                Ex2Header header;
                BoostSerializer<Ex2Header>().Deserialize(*(parts.At(0)), header);
                BoostSerializer<MyHit>().Deserialize(*(parts.At(1)), fInput);

                receivedMsgs++;
                fTree.SetBranchAddress("MyHit", &fInput);
                fTree.Fill();

                if (fNumMsgs != 0) {
                    if (receivedMsgs == fNumMsgs) {
                        break;
                    }
                }
            }
        }

        LOG(info) << "Received " << receivedMsgs << " messages!";
    }

    void Reset() override
    {
        fTree.Write("", TObject::kOverwrite);

        if (fOutFile) {
            if (fOutFile->IsOpen()) {
                fOutFile->Close();
            }
            delete fOutFile;
        }

        if (fInput) {
            delete fInput;
        }
    }

  private:
    TClonesArray* fInput;
    std::string fFileName;
    TFile* fOutFile;
    TTree fTree;
    int fNumMsgs;
};

#endif   // EX2SINK_H
