/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "FairMQProcessor.h"
#include "FairTestDetectorMQRecoTask.h"

namespace bpo = boost::program_options;

using TProcessorBin         = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorPayload::Digi,       TestDetectorPayload::Hit>>;
using TProcessorBoostBin    = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, boost::archive::binary_iarchive, boost::archive::binary_oarchive>>;
using TProcessorBoostText   = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, boost::archive::text_iarchive,   boost::archive::text_oarchive>>;
using TProcessorTMessage    = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TMessage,                        TMessage>>;
#ifdef PROTOBUF
using TProcessorProtobuf    = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorProto::DigiPayload,  TestDetectorProto::HitPayload>>;
#endif
#ifdef FLATBUFFERS
using TProcessorFlatBuffers = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorFlat::DigiPayload,   TestDetectorFlat::HitPayload>>;
#endif
#ifdef MSGPACK
using TProcessorMsgPack     = FairMQProcessor<FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, MsgPack,                         MsgPack>>;
#endif

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("in-channel", bpo::value<std::string>()->default_value("data1"), "Name of the input channel")
        ("out-channel", bpo::value<std::string>()->default_value("data2"), "Name of the output channel")
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") { return new TProcessorBin; }
    else if (dataFormat == "boost") { return new TProcessorBoostBin; }
    else if (dataFormat == "boost-text") { return new TProcessorBoostText; }
    else if (dataFormat == "tmessage") { return new TProcessorTMessage; }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") { return new TProcessorFlatBuffers; }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") { return new TProcessorMsgPack; }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") { return new TProcessorProtobuf; }
#endif
    else
    {
        LOG(error) << "No valid data format provided. (--data-format binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage). ";
        exit(EXIT_FAILURE);
    }
}

