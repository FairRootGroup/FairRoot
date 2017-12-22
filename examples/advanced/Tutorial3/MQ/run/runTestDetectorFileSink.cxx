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

using TSinkBin         = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorPayload::Hit>;
using TSinkBoostBin    = FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::binary_iarchive>;
using TSinkBoostText   = FairTestDetectorFileSink<FairTestDetectorHit, boost::archive::text_iarchive>;
using TSinkTMessage    = FairTestDetectorFileSink<FairTestDetectorHit, TMessage>;
#ifdef PROTOBUF
using TSinkProtobuf    = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorProto::HitPayload>;
#endif
#ifdef FLATBUFFERS
using TSinkFlatBuffers = FairTestDetectorFileSink<FairTestDetectorHit, TestDetectorFlat::HitPayload>;
#endif
#ifdef MSGPACK
using TSinkMsgPack     = FairTestDetectorFileSink<FairTestDetectorHit, MsgPack>;
#endif

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("in-channel", bpo::value<std::string>()->default_value("data2"), "Name of the input channel")
        ("ack-channel", bpo::value<std::string>()->default_value("ack"), "Name of the acknowledgement channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") { return new TSinkBin; }
    else if (dataFormat == "boost") { return new TSinkBoostBin; }
    else if (dataFormat == "boost-text") { return new TSinkBoostText; }
    else if (dataFormat == "tmessage") { return new TSinkTMessage; }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") { return new TSinkFlatBuffers; }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") { return new TSinkMsgPack; }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") { return new TSinkProtobuf; }
#endif
    else
    {
        LOG(error) << "No valid data format provided. (--data-format binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage). ";
        exit(EXIT_FAILURE);
    }
}
