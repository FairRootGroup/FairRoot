/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "DigiLoader.h"
#include "DigiLoaderBin.h"
#include "DigiLoaderBoost.h"
#include "DigiLoaderFlatBuffers.h"
#include "DigiLoaderProtobuf.h"
#include "DigiLoaderTMessage.h"
#include "SamplerTask.h"

#include "FairFileSource.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::MessagePtr
#include "FairParRootFileIo.h"
#include "FairRootFileSink.h"
#include "FairRunAna.h"
#include "FairRunFairMQDevice.h"
#include "FairRuntimeDb.h"

#include <fairlogger/Logger.h>

#include <chrono>
#include <iomanip>
#include <stdexcept>
#include <thread>

namespace bpo = boost::program_options;

/**
 * Reads simulated digis from a root file and samples the digi as a time-series UDP stream.
 * Must be initialized with the filename to the root file and the name of the sub-detector
 * branch, whose digis should be streamed.
 *
 * The purpose of this class is to provide a data source of digis very similar to the
 * future detector output at the point where the detector is connected to the online
 * computing farm. For the development of online analysis algorithms, it is very important
 * to simulate the future detector output as realistic as possible to evaluate the
 * feasibility and quality of the various possible online analysis features.
 */

template<typename Task>
class Sampler : public fair::mq::Device
{
  public:
    Sampler()
        : fFairRunAna(nullptr)
        , fSamplerTask(nullptr)
        , fStart()
        , fEnd()
        , fInputFile()
        , fParFile()
        , fBranch()
        , fOutChannelName("data1")
        , fAckChannelName("ack")
        , fNumEvents(0)
        , fChainInput(0)
        , fSentMsgs(0)
        , fAckListener()
    {}

    Sampler(const Sampler&) = delete;
    Sampler operator=(const Sampler&) = delete;

    virtual ~Sampler() {}

  protected:
    virtual void InitTask()
    {
        LOG(info) << "Initializing Task...";

        fFairRunAna = new FairRunAna();
        fSamplerTask = new Task();

        fInputFile = fConfig->GetValue<std::string>("input-file");
        fParFile = fConfig->GetValue<std::string>("parameter-file");
        fBranch = fConfig->GetValue<std::string>("branch");
        fChainInput = fConfig->GetValue<int>("chain-input");

        std::string outChannelName = fConfig->GetValue<std::string>("out-channel");
        std::string ackChannelName = fConfig->GetValue<std::string>("ack-channel");
        // check if the returned value actually exists, for the compatibility with old devices.
        if (outChannelName != "") {
            fOutChannelName = outChannelName;
        }
        if (ackChannelName != "") {
            fAckChannelName = ackChannelName;
        }

        fSamplerTask->SetBranch(fBranch);
        fSamplerTask->SetTransport(fTransportFactory);

        FairFileSource* source = new FairFileSource(TString(fInputFile));
        // Adds the same file to the input. The output will still be a single file.
        for (int i = 0; i < fChainInput; ++i) {
            source->AddFile(fInputFile);
        }

        fFairRunAna->SetSource(source);

        TString output = fInputFile;
        output.Append(".out.root");
        fFairRunAna->SetSink(std::make_unique<FairRootFileSink>(output.Data()));

        fFairRunAna->AddTask(fSamplerTask);

        if (fParFile != "") {
            FairRuntimeDb* rtdb = fFairRunAna->GetRuntimeDb();
            FairParRootFileIo* parInput = new FairParRootFileIo();
            parInput->open(TString(fParFile).Data());
            rtdb->setFirstInput(parInput);
            rtdb->print();
        } else {
            LOG(warn) << "Parameter file not provided. Starting without RuntimeDB.";
        }

        fFairRunAna->Init();
        // fFairRunAna->Run(0, 0);
        fNumEvents = int((FairRootManager::Instance()->GetInChain())->GetEntries());

        LOG(info) << "Task initialized.";
        LOG(info) << "Number of events to process: " << fNumEvents;
    }

    virtual void PreRun()
    {
        fStart = std::chrono::high_resolution_clock::now();
        fAckListener = std::thread(&Sampler::ListenForAcks, this);
    }

    virtual bool ConditionalRun()
    {
        fair::mq::MessagePtr msg;

        fSamplerTask->SetEventIndex(fSentMsgs);
        fFairRunAna->RunMQ(fSentMsgs);
        fSamplerTask->GetPayload(msg);

        if (Send(msg, fOutChannelName) >= 0) {
            ++fSentMsgs;
            if (fSentMsgs == fNumEvents) {
                return false;
            }
        }

        return true;
    }

    virtual void PostRun()
    {
        try {
            fAckListener.join();
        } catch (std::exception& e) {
            LOG(error) << "Exception when ending AckListener thread: " << e.what();
            exit(EXIT_FAILURE);
        }
    }

    virtual void ResetTask()
    {
        if (fFairRunAna) {
            fFairRunAna->TerminateRun();
        }
        delete fSamplerTask;
    }

    void ListenForAcks()
    {
        uint64_t numAcks = 0;
        for (Long64_t eventNr = 0; eventNr < fNumEvents; ++eventNr) {
            auto ack(NewMessage());
            if (Receive(ack, fAckChannelName) >= 0) {
                ++numAcks;
            }

            if (NewStatePending()) {
                break;
            }
        }

        fEnd = std::chrono::high_resolution_clock::now();
        LOG(info) << "Acknowledged " << numAcks
                  << " messages in: " << std::chrono::duration<double, std::milli>(fEnd - fStart).count() << "ms.";
    }

  private:
    FairRunAna* fFairRunAna;
    SamplerTask* fSamplerTask;
    std::chrono::high_resolution_clock::time_point fStart;
    std::chrono::high_resolution_clock::time_point fEnd;
    std::string fInputFile;   // Filename of a root file containing the simulated digis.
    std::string fParFile;
    std::string fBranch;   // The name of the sub-detector branch to stream the digis from.
    std::string fOutChannelName;
    std::string fAckChannelName;
    int fNumEvents;
    int fChainInput;
    int fSentMsgs;
    std::thread fAckListener;
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("data-format",    bpo::value<std::string>()->default_value("binary"),               "Data format (binary|boost|flatbuffers|protobuf|tmessage)")
        ("input-file",     bpo::value<std::string>()->required(),                            "Path to the input file")
        ("parameter-file", bpo::value<std::string>()->default_value(""),                     "Path to the parameter file")
        ("branch",         bpo::value<std::string>()->default_value("FairTestDetectorDigi"), "Name of the Branch")
        ("out-channel",    bpo::value<std::string>()->default_value("data1"),                "Name of the output channel")
        ("ack-channel",    bpo::value<std::string>()->default_value("ack"),                  "Name of the acknowledgement channel")
        ("chain-input",    bpo::value<int>()->default_value(0),                              "Chain input file more than once (default)");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") {
        return std::make_unique<Sampler<DigiLoader<TestDetectorBin>>>();
    } else if (dataFormat == "boost") {
        return std::make_unique<Sampler<DigiLoader<TestDetectorBoost>>>();
    } else if (dataFormat == "tmessage") {
        return std::make_unique<Sampler<DigiLoader<TestDetectorTMessage>>>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return std::make_unique<Sampler<DigiLoader<TestDetectorFlatBuffers>>>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return std::make_unique<Sampler<DigiLoader<TestDetectorProtobuf>>>();
    }
#endif
    else {
        std::stringstream ss;
        ss << "Invalid valid data format provided (--data-format): " << std::quoted(dataFormat)
           << ", available are: binary, boost, tmessage"
#ifdef FLATBUFFERS
           << ", flatbuffers"
#endif
#ifdef PROTOBUF
           << ", protobuf"
#endif
           ;
        throw std::runtime_error(ss.str());
    }
}
