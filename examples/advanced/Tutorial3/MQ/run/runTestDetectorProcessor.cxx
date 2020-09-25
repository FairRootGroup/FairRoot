/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "BoostSerializer.h"              // for has_Boost...
#include "FairMQProcessor.h"              // for FairMQPro...
#include "FairTestDetectorDigi.h"         // for FairTestD...
#include "FairTestDetectorHit.h"          // for FairTestD...
#include "FairTestDetectorMQRecoTask.h"   // for FairTestD...
#include "runFairMQDevice.h"              // for FairMQDev...

#include <fairlogger/Logger.h>   // for LOG
#include <functional>            // for __base
#include <iosfwd>                // for string
#include <string>                // for basic_string

class TMessage;
namespace TestDetectorFlat {
struct DigiPayload;
struct HitPayload;
}   // namespace TestDetectorFlat
namespace TestDetectorPayload {
class Digi;
class Hit;
}   // namespace TestDetectorPayload
namespace TestDetectorProto {
class DigiPayload;
class HitPayload;
}   // namespace TestDetectorProto
struct MsgPack;

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

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") {
        return new FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                              FairTestDetectorHit,
                                                              TestDetectorPayload::Digi,
                                                              TestDetectorPayload::Hit>>;
    } else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorDigi,
                                                              void(boost::archive::binary_iarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Input Payload requested, but the input type does not support it. "
                          "Check the TIn parameter. Aborting.";
            return nullptr;
        }
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorHit,
                                                              void(boost::archive::binary_oarchive&,
                                                                   const unsigned int)>::value
            == 0) {
            LOG(error) << "Boost serialization for Output Payload requested, but the output type does not support it. "
                          "Check the TOut parameter. Aborting.";
            return nullptr;
        }
        return new FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                              FairTestDetectorHit,
                                                              boost::archive::binary_iarchive,
                                                              boost::archive::binary_oarchive>>;
    } else if (dataFormat == "tmessage") {
        return new FairMQProcessor<
            FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage, TMessage>>;
    }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") {
        return new FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                              FairTestDetectorHit,
                                                              TestDetectorFlat::DigiPayload,
                                                              TestDetectorFlat::HitPayload>>;
    }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") {
        return new FairMQProcessor<
            FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPack, MsgPack>>;
    }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") {
        return new FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi,
                                                              FairTestDetectorHit,
                                                              TestDetectorProto::DigiPayload,
                                                              TestDetectorProto::HitPayload>>;
    }
#endif
    else {
        LOG(error)
            << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        return nullptr;
    }
}
