/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTestDetectorFileSink.h
 *
 * @since 2013-06-05
 * @author A. Rybalchenko
 */

#ifndef FAIRTESTDETECTORFILESINK_H_
#define FAIRTESTDETECTORFILESINK_H_

#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"

#include <FairMQDevice.h>
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

template<typename TIn, typename TPayloadIn>
class FairTestDetectorFileSink : public FairMQDevice
{
  public:
    FairTestDetectorFileSink()
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

    FairTestDetectorFileSink(const FairTestDetectorFileSink&) = delete;
    FairTestDetectorFileSink operator=(const FairTestDetectorFileSink&) = delete;

    virtual ~FairTestDetectorFileSink()
    {
        fTree.Write();
        fOutFile->Close();
    }

    virtual void InitOutputFile(const std::string& defaultId = "100")
    {
        std::string filename("filesink_" + defaultId + ".root");
        fOutFile = std::unique_ptr<TFile>(TFile::Open(filename.c_str(), "recreate"));
        fTree.Branch("Output", "TClonesArray", fOutput.get(), 64000, 99);
    }

  protected:
    virtual void Init()
    {
        fInChannelName = fConfig->GetValue<std::string>("in-channel");
        fAckChannelName = fConfig->GetValue<std::string>("ack-channel");

        InitOutputFile(fConfig->GetValue<std::string>("data-format"));
    }

    virtual void PostRun() { LOG(info) << "Received " << fReceivedMsgs << " messages!"; }

    virtual void InitTask();

  private:
    std::unique_ptr<TClonesArray> fOutput;
    std::unique_ptr<TFile> fOutFile;
    TTree fTree;
    int fReceivedMsgs;
    std::string fInChannelName;
    std::string fAckChannelName;
};

// Template implementation of Run() in FairTestDetectorFileSink.tpl :
#include "FairTestDetectorFileSinkBin.tpl"
#include "FairTestDetectorFileSinkBoost.tpl"
#include "FairTestDetectorFileSinkFlatBuffers.tpl"
#include "FairTestDetectorFileSinkMsgpack.tpl"
#include "FairTestDetectorFileSinkProtobuf.tpl"
#include "FairTestDetectorFileSinkTMessage.tpl"

#endif /* FAIRTESTDETECTORFILESINK_H_ */
