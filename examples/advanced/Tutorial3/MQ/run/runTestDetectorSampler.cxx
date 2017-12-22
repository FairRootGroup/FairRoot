/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "FairMQSampler.h"
#include "FairTestDetectorDigiLoader.h"

namespace bpo = boost::program_options;

using TSamplerBin         = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>>;
using TSamplerBoostBin    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::binary_oarchive>>;
using TSamplerBoostText   = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, boost::archive::text_oarchive>>;
using TSamplerTMessage    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;
#ifdef PROTOBUF
using TSamplerProtobuf    = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>>;
#endif
#ifdef FLATBUFFERS
using TSamplerFlatBuffers = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>>;
#endif
#ifdef MSGPACK
using TSamplerMsgPack     = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, MsgPack>>;
#endif

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("data-format", bpo::value<std::string>()->default_value("binary"), "Data format (binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage)")
        ("input-file", bpo::value<std::string>()->required(), "Path to the input file")
        ("parameter-file", bpo::value<std::string>()->default_value(""), "Path to the parameter file")
        ("branch", bpo::value<std::string>()->default_value("FairTestDetectorDigi"), "Name of the Branch")
        ("out-channel", bpo::value<std::string>()->default_value("data1"), "Name of the output channel")
        ("ack-channel", bpo::value<std::string>()->default_value("ack"), "Name of the acknowledgement channel")
        ("chain-input", bpo::value<int>()->default_value(0), "Chain input file more than once (default)");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& config)
{
    std::string dataFormat = config.GetValue<std::string>("data-format");

    if (dataFormat == "binary") { return new TSamplerBin; }
    else if (dataFormat == "boost") { return new TSamplerBoostBin; }
    else if (dataFormat == "boost-text") { return new TSamplerBoostText; }
    else if (dataFormat == "tmessage") { return new TSamplerTMessage; }
#ifdef FLATBUFFERS
    else if (dataFormat == "flatbuffers") { return new TSamplerFlatBuffers; }
#endif
#ifdef MSGPACK
    else if (dataFormat == "msgpack") { return new TSamplerMsgPack; }
#endif
#ifdef PROTOBUF
    else if (dataFormat == "protobuf") { return new TSamplerProtobuf; }
#endif
    else
    {
        LOG(error) << "No valid data format provided. (--data-format binary|boost|boost-text|flatbuffers|msgpack|protobuf|tmessage). ";
        exit(EXIT_FAILURE);
    }
}
