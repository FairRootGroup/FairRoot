/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// this example
#include "FileSink.h"
#include "FileSinkBin.h"
#include "FileSinkBoost.h"
#include "FileSinkFlatBuffers.h"
#include "FileSinkProtobuf.h"
#include "FileSinkTMessage.h"

// FairRoot
#include "FairRunFairMQDevice.h"

// std
#include <iomanip>   // std::quoted

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data2"),  "Name of the input channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|flatbuffers|protobuf|tmessage)")
        ("max-msgs",    bpo::value<uint64_t>()->default_value(0),           "Stop after <n> msgs (0 - no limit).");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    LOG(info) << "Starting Sink with " << dataFormat << " data serialization";

    if (dataFormat == "binary") {
        return std::make_unique<FileSink<TestDetectorBin>>();
    } else if (dataFormat == "boost") {
        return std::make_unique<FileSink<TestDetectorBoost>>();
    } else if (dataFormat == "tmessage") {
        return std::make_unique<FileSink<TestDetectorTMessage>>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return std::make_unique<FileSink<TestDetectorFlatBuffers>>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return std::make_unique<FileSink<TestDetectorProtobuf>>();
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
