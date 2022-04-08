/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQSampler.h"
#include "FairRunFairMQDevice.h"
#include "FairTestDetectorDigiLoader.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("data-format",    bpo::value<std::string>()->default_value("binary"),               "Data format (binary|boost|flatbuffers|msgpack|protobuf|tmessage)")
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
        using Sampler = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>>;
        return std::make_unique<Sampler>();
    } else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorDigi,
                                                              void(boost::archive::binary_oarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Output Payload requested, but the output type does not support it. "
                          "Check the TOut parameter. Aborting.";
            return {nullptr};
        }
        using Sampler =
            FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::binary_oarchive>>;
        return std::make_unique<Sampler>();
    } else if (dataFormat == "tmessage") {
        using Sampler = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;
        return std::make_unique<Sampler>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        using Sampler = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>>;
        return std::make_unique<Sampler>();
    }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") {
        using Sampler = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>>;
        return std::make_unique<Sampler>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        using Sampler = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>>;
        return std::make_unique<Sampler>();
    }
#endif
    else {
        LOG(error)
            << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        exit(EXIT_FAILURE);
    }
}
