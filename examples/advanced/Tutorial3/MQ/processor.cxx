/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "ProcessorTask.h"
#include "MQRecoTask.h"
#include "MQRecoTaskBin.h"
#include "MQRecoTaskBoost.h"
#include "MQRecoTaskFlatBuffers.h"
#include "MQRecoTaskProtobuf.h"
#include "MQRecoTaskTMessage.h"

#include "FairRunFairMQDevice.h"
#include "FairMQ.h"   // for fair::mq::Device, fair::mq::MessagePtr

#include <fairlogger/Logger.h>

namespace bpo = boost::program_options;

template<typename Task>
class Processor : public fair::mq::Device
{
  public:
    Processor()
        : fProcessorTask(new Task)
        , fInChannelName("data1")
        , fOutChannelName("data2")
        , fReceivedMsgs(0)
        , fSentMsgs(0)
    {}

    /// Copy Constructor
    Processor(const Processor&) = delete;
    Processor operator=(const Processor&) = delete;

    virtual ~Processor() {}

  protected:
    virtual void InitTask()
    {
        std::string inChannelName = fConfig->GetValue<std::string>("in-channel");
        std::string outChannelName = fConfig->GetValue<std::string>("out-channel");
        // check if the returned value actually exists, for the compatibility with old devices.
        if (inChannelName != "") {
            fInChannelName = inChannelName;
        }
        if (outChannelName != "") {
            fOutChannelName = outChannelName;
        }

        fProcessorTask->InitTask();
        OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
            ++fReceivedMsgs;
            fProcessorTask->SetPayload(msg);
            fProcessorTask->Exec("0");
            fProcessorTask->GetPayload(msg);

            Send(msg, fOutChannelName);
            ++fSentMsgs;

            return true;
        });
    }

    virtual void PostRun() { LOG(info) << "Received " << fReceivedMsgs << " and sent " << fSentMsgs << " messages!"; }

  private:
    std::unique_ptr<ProcessorTask> fProcessorTask;
    std::string fInChannelName;
    std::string fOutChannelName;
    int fReceivedMsgs;
    int fSentMsgs;
};

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data1"),  "Name of the input channel")
        ("out-channel", bpo::value<std::string>()->default_value("data2"),  "Name of the output channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|flatbuffers|protobuf|tmessage)");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    LOG(info) << "Starting Processor with " << dataFormat << " data serialization";

    if (dataFormat == "binary") {
        return std::make_unique<Processor<MQRecoTask<TestDetectorBin>>>();
    } else if (dataFormat == "boost") {
        return std::make_unique<Processor<MQRecoTask<TestDetectorBoost>>>();
    } else if (dataFormat == "tmessage") {
        return std::make_unique<Processor<MQRecoTask<TestDetectorTMessage>>>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return std::make_unique<Processor<MQRecoTask<TestDetectorFlatBuffers>>>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return std::make_unique<Processor<MQRecoTask<TestDetectorProtobuf>>>();
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
