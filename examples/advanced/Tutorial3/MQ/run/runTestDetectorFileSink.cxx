/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairRunFairMQDevice.h"
#include "FairTestDetectorFileSink.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data2"),  "Name of the input channel")
        ("ack-channel", bpo::value<std::string>()->default_value("ack"),    "Name of the acknowledgement channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|flatbuffers|msgpack|protobuf|tmessage)");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") {
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>;
        return std::make_unique<Sink>();
    } else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorHit,
                                                              void(boost::archive::binary_iarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Input Payload requested, but the input type does not support it. "
                          "Check the TIn parameter. Aborting.";
            return {nullptr};
        }
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::binary_iarchive>;
        return std::make_unique<Sink>();
    } else if (dataFormat == "tmessage") {
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, TMessage>;
        return std::make_unique<Sink>();
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>;
        return std::make_unique<Sink>();
    }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") {
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, MsgPack>;
        return std::make_unique<Sink>();
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        using Sink = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>;
        return std::make_unique<Sink>();
    }
#endif
    else {
        LOG(error)
            << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        return {nullptr};
    }
}
