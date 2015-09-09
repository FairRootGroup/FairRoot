/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runFileSink.cxx
 *
 * @since 2013-01-21
 * @author A. Rybalchenko
 */

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQFileSink.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

// data format for the task
#include "FairTestDetectorHit.h"

// binary data format
#include "FairTestDetectorPayload.h"

// boost data format
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// Google Protocol Buffers data format
#include "FairTestDetectorPayload.pb.h"

// TMessage data format
#include "TMessage.h"

using namespace std;

typedef TestDetectorPayload::Hit TPayloadIn; // binary payload
typedef boost::archive::binary_iarchive TBoostBinPayload; // boost binary format
typedef boost::archive::text_iarchive TBoostTextPayload;  // boost text format
typedef TestDetectorProto::HitPayload TProtoPayload; // protobuf payload

typedef FairMQFileSink<FairTestDetectorHit, TPayloadIn> TSinkBin;
typedef FairMQFileSink<FairTestDetectorHit, TBoostBinPayload> TSinkBoost;
typedef FairMQFileSink<FairTestDetectorHit, TProtoPayload> TSinkProtobuf;
typedef FairMQFileSink<FairTestDetectorHit, TMessage> TSinkTMessage;

typedef struct DeviceOptions
{
    DeviceOptions() :
        id(), ioThreads(0), dataFormat(),
        inputSocketType(), inputBufSize(0), inputMethod(), inputAddress() {}

    string id;
    int ioThreads;
    string dataFormat;
    string inputSocketType;
    int inputBufSize;
    string inputMethod;
    string inputAddress;
} DeviceOptions_t;

inline bool parse_cmd_line(int _argc, char* _argv[], DeviceOptions* _options)
{
    if (_options == NULL)
        throw std::runtime_error("Internal error: options' container is empty.");

    namespace bpo = boost::program_options;
    bpo::options_description desc("Options");
    desc.add_options()
        ("id", bpo::value<string>()->required(), "Device ID")
        ("io-threads", bpo::value<int>()->default_value(1), "Number of I/O threads")
        ("data-format", bpo::value<string>()->default_value("binary"), "Data format (binary/boost/protobuf/tmessage)")
        ("input-socket-type", bpo::value<string>()->required(), "Input socket type: sub/pull")
        ("input-buff-size", bpo::value<int>()->required(), "Input buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("input-method", bpo::value<string>()->required(), "Input method: bind/connect")
        ("input-address", bpo::value<string>()->required(), "Input address, e.g.: \"tcp://*:5555\"")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if (vm.count("help"))
    {
        LOG(INFO) << "FairMQ File Sink" << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if (vm.count("id"))                { _options->id              = vm["id"].as<string>(); }
    if (vm.count("io-threads"))        { _options->ioThreads       = vm["io-threads"].as<int>(); }
    if (vm.count("data-format"))       { _options->dataFormat      = vm["data-format"].as<string>(); }
    if (vm.count("input-socket-type")) { _options->inputSocketType = vm["input-socket-type"].as<string>(); }
    if (vm.count("input-buff-size"))   { _options->inputBufSize    = vm["input-buff-size"].as<int>(); }
    if (vm.count("input-method"))      { _options->inputMethod     = vm["input-method"].as<string>(); }
    if (vm.count("input-address"))     { _options->inputAddress    = vm["input-address"].as<string>(); }

    return true;
}

template<typename T>
void runFileSink(const DeviceOptions_t& options)
{
    T filesink;
    filesink.CatchSignals();

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    filesink.SetTransport(transportFactory);

    FairMQChannel channel(options.inputSocketType, options.inputMethod, options.inputAddress);
    channel.UpdateSndBufSize(options.inputBufSize);
    channel.UpdateRcvBufSize(options.inputBufSize);
    channel.UpdateRateLogging(1);

    filesink.fChannels["data-in"].push_back(channel);

    filesink.SetProperty(T::Id, options.id);
    filesink.SetProperty(T::NumIoThreads, options.ioThreads);

    filesink.ChangeState("INIT_DEVICE");
    filesink.WaitForEndOfState("INIT_DEVICE");

    filesink.ChangeState("INIT_TASK");
    filesink.WaitForEndOfState("INIT_TASK");

    filesink.InitOutputFile(options.id);

    filesink.ChangeState("RUN");
    filesink.InteractiveStateLoop();
}

int main(int argc, char** argv)
{
    DeviceOptions_t options;
    try
    {
        if (!parse_cmd_line(argc, argv, &options))
            return 0;
    }
    catch (exception& e)
    {
        LOG(ERROR) << e.what();
        return 1;
    }

    LOG(INFO) << "PID: " << getpid();

    if (options.dataFormat == "binary") { runFileSink<TSinkBin>(options); }
    else if (options.dataFormat == "boost") { runFileSink<TSinkBoost>(options); }
    else if (options.dataFormat == "protobuf") { runFileSink<TSinkProtobuf>(options); }
    else if (options.dataFormat == "tmessage") { runFileSink<TSinkTMessage>(options); }
    else
    {
        LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|protobuf|tmessage). ";
        return 1;
    }

    return 0;
}
