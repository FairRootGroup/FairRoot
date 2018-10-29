/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "FairTestDetectorFileSink.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("in-channel", bpo::value<std::string>()->default_value("data2"), "Name of the input channel")
        ("ack-channel", bpo::value<std::string>()->default_value("ack"), "Name of the acknowledgement channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|flatbuffers|msgpack|protobuf|tmessage)");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") { return new FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>; }
    else if (dataFormat == "boost") {
        if (fair::base::serialization::has_BoostSerialization<FairTestDetectorHit, void(boost::archive::binary_iarchive&, const unsigned int)>::value == 0) {
            LOG(error) << "Boost serialization for Input Payload requested, but the input type does not support it. Check the TIn parameter. Aborting.";
            return nullptr;
        }
        return new FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::binary_iarchive>;
    }
    else if (dataFormat == "tmessage") { return new FairTestDetectorFileSink<FairTestDetectorHit, TMessage>; }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") { return new FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>; }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") { return new FairTestDetectorFileSink<FairTestDetectorHit, MsgPack>; }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") { return new FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>; }
#endif
    else
    {
        LOG(error) << "No valid data format provided. (--data-format binary|boost|flatbuffers|msgpack|protobuf|tmessage). ";
        return nullptr;
    }
}
