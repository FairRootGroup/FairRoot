/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

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
#include <thread>

class Ex2Sampler : public FairMQDevice
{
  public:
    Ex2Sampler()
        : fInput(nullptr)
        , fTree(nullptr)
        , fInputFile(nullptr)
    {}

    void Init() override
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

    void Run() override
    {
        uint64_t sentMsgs = 0;
        const Long64_t numEvents = fTree->GetEntries();
        LOG(info) << "Number of events to process: " << numEvents;

        for (Long64_t idx = 0; idx < numEvents; idx++) {
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

        LOG(info) << "Sent " << sentMsgs << " messages!";

        // stay in the Running state until a transition to Ready is requested
        while (!NewStatePending()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Reset() override
    {
        if (fInputFile) {
            fInputFile->Close();
            delete fInputFile;
        }
    }

  private:
    TClonesArray* fInput;
    TTree* fTree;
    std::string fFileName;
    TFile* fInputFile;
};

#endif   // EX2SAMPLER_H
