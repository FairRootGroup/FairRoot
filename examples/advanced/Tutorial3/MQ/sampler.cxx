/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQSampler.h"
#include "FairRunFairMQDevice.h"
#include "DigiLoader.h"
#include "DigiLoaderBin.h"
#include "DigiLoaderBoost.h"
#include "DigiLoaderFlatBuffers.h"
#include "DigiLoaderProtobuf.h"
#include "DigiLoaderTMessage.h"

#include <iomanip>
#include <stdexcept>

namespace bpo = boost::program_options;

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
        return std::make_unique<FairMQSampler<DigiLoader<TestDetectorBin>>>();
    } else if (dataFormat == "boost") {
        return std::make_unique<FairMQSampler<DigiLoader<TestDetectorBoost>>>();
    } else if (dataFormat == "tmessage") {
        return std::make_unique<FairMQSampler<DigiLoader<TestDetectorTMessage>>>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return std::make_unique<FairMQSampler<DigiLoader<TestDetectorFlatBuffers>>>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return std::make_unique<FairMQSampler<DigiLoader<TestDetectorProtobuf>>>();
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
