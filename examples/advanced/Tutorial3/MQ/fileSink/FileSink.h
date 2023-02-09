/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_FILESINK_H_
#define FAIR_TESTDETECTOR_FILESINK_H_

#include "FairMQ.h"   // for fair::mq::Device
#include "FairTestDetectorHit.h"
#include "Payload.h"

#include <Rtypes.h>
#include <TClonesArray.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>
#include <array>
#include <fairlogger/Logger.h>
#include <iostream>
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
        , fReceivedMsgs(0)
        , fInChannelName("data2")
        , fAckChannelName("ack")
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

    virtual void InitOutputFile(const std::string& defaultId = "100")
    {
        std::string filename("filesink_" + defaultId + ".root");
        fOutFile = std::unique_ptr<TFile>(TFile::Open(filename.c_str(), "recreate"));
        fTree.Branch("Output", "TClonesArray", fOutput, 64000, 99);
    }

  protected:
    void Init() override
    {
        fInChannelName = fConfig->GetValue<std::string>("in-channel");
        fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

        InitOutputFile(fConfig->GetValue<std::string>("data-format"));
    }

    void PostRun() override { LOG(info) << "Received " << fReceivedMsgs << " messages!"; }

    void InitTask() override;

  private:
    TClonesArray* fOutput;
    std::unique_ptr<TFile> fOutFile;
    TTree fTree;
    int fReceivedMsgs;
    std::string fInChannelName;
    std::string fAckChannelName;
};

#endif /* FAIR_TESTDETECTOR_FILESINK_H_ */
