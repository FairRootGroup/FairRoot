/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_FILESINK_H
#define FAIR_TESTDETECTOR_FILESINK_H

// this example
#include "FairTestDetectorHit.h"
#include "Payload.h"

// FairRoot
#include "FairMQ.h"   // for fair::mq::Device

// ROOT
#include <Rtypes.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>

// logger
#include <fairlogger/Logger.h>

// std
#include <memory>
#include <string>

template<typename T>
class FileSink : public fair::mq::Device
{
  public:
    FileSink()
        : fOutput(new TClonesArray("FairTestDetectorHit"))
        , fOutFile(nullptr)
        , fTree("MQOut", "Test output")
        , fInChannelName("data2")
    {
        gSystem->ResetSignal(kSigInterrupt);
        gSystem->ResetSignal(kSigTermination);
    }

    FileSink(const FileSink&) = delete;
    FileSink operator=(const FileSink&) = delete;

    ~FileSink() override
    {
        fTree.Write();
        if (fOutput) {
            delete fOutput;
        }
    }

    void Init() override
    {
        fInChannelName = fConfig->GetValue<std::string>("in-channel");
        fMaxMsgs = fConfig->GetValue<uint64_t>("max-msgs");

        std::string format = fConfig->GetValue<std::string>("data-format");
        std::string filename("filesink_" + format + ".root");
        fOutFile = std::unique_ptr<TFile>(TFile::Open(filename.c_str(), "recreate"));
        fTree.Branch("Output", "TClonesArray", fOutput, 64000, 99);
    }

    void PostRun() override { LOG(info) << "Received " << fReceivedMsgs << " messages!"; }

    void InitTask() override;

  private:
    TClonesArray* fOutput;
    std::unique_ptr<TFile> fOutFile;
    TTree fTree;
    uint64_t fReceivedMsgs = 0;
    uint64_t fMaxMsgs = 0;
    std::string fInChannelName;
};

#endif /* FAIR_TESTDETECTOR_FILESINK_H */
