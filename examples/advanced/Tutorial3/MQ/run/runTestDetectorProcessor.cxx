/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQProcessor.h"
#include "FairRunFairMQDevice.h"
#include "FairTestDetectorMQRecoTask.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    // clang-format off
    options.add_options()
        ("in-channel",  bpo::value<std::string>()->default_value("data1"),  "Name of the input channel")
        ("out-channel", bpo::value<std::string>()->default_value("data2"),  "Name of the output channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|flatbuffers|msgpack|protobuf|tmessage)");
    // clang-format on
}

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") {
        using Processor = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                                     FairTestDetectorHit,
                                                                     TestDetectorPayload::Digi,
                                                                     TestDetectorPayload::Hit>>;
        return std::unique_ptr<Processor>(new Processor());
    } else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorDigi,
                                                              void(boost::archive::binary_iarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Input Payload requested, but the input type does not support it. "
                          "Check the TIn parameter. Aborting.";
            return {nullptr};
        }
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorHit,
                                                              void(boost::archive::binary_oarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Output Payload requested, but the output type does not support it. "
                          "Check the TOut parameter. Aborting.";
            return {nullptr};
        }
        using Processor = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                                     FairTestDetectorHit,
                                                                     boost::archive::binary_iarchive,
                                                                     boost::archive::binary_oarchive>>;
        return std::unique_ptr<Processor>(new Processor());
    } else if (dataFormat == "tmessage") {
        using Processor =
            FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage, TMessage>>;
        return std::unique_ptr<Processor>(new Processor());
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        using Processor = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                                     FairTestDetectorHit,
                                                                     TestDetectorFlat::DigiPayload,
                                                                     TestDetectorFlat::HitPayload>>;
        return std::unique_ptr<Processor>(new Processor());
    }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") {
        using Processor =
            FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPack, MsgPack>>;
        return std::unique_ptr<Processor>(new Processor());
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        using Processor = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                                     FairTestDetectorHit,
                                                                     TestDetectorProto::DigiPayload,
                                                                     TestDetectorProto::HitPayload>>;
        return std::unique_ptr<Processor>(new Processor());
    }
#endif
    else {
        LOG(error)
            << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        return {nullptr};
    }
}
