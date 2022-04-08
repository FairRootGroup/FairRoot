/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef EX1SINK_H
#define EX1SINK_H

#include "FairMQ.h"   // for fair::mq::Device
#include "MyHit.h"
#include "RootSerializer.h"

#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

class Ex1Sink : public fair::mq::Device
{
  public:
    Ex1Sink()
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
            auto msg(NewMessage());
            if (Receive(msg, "data2") > 0) {
                RootSerializer().Deserialize(*msg, fInput);
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

#endif   // EX1SINK_H
