/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <fairlogger/Logger.h>                              // for LOG
#include <stdlib.h>                                         // for exit, EXI...
#include <exception>                                        // for exception
#include <iosfwd>                                           // for string
#include <string>                                           // for basic_string

#include "FairMQSampler.h"                                  // for FairMQSam...
#include "FairTestDetectorDigiLoader.h"                     // for FairTestD...
#include "runFairMQDevice.h"                                // for FairMQDev...
#include "BoostSerializer.h"                                // for has_Boost...
#include "FairTestDetectorDigi.h"                           // for FairTestD...

class TMessage;
namespace TestDetectorFlat {
struct DigiPayload;
}  // namespace TestDetectorFlat
namespace TestDetectorPayload {
class Digi;
}  // namespace TestDetectorPayload
namespace TestDetectorProto {
class DigiPayload;
}  // namespace TestDetectorProto
struct MsgPack;

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

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") {
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>>;
    } else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorDigi,
                                                              void(boost::archive::binary_oarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Output Payload requested, but the output type does not support it. "
                          "Check the TOut parameter. Aborting.";
            return nullptr;
        }
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::binary_oarchive>>;
    } else if (dataFormat == "tmessage") {
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>>;
    }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") {
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>>;
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return new FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>>;
    }
#endif
    else {
        LOG(error)
            << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        exit(EXIT_FAILURE);
    }
}
