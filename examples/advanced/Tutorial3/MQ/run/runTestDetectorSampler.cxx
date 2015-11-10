/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTestDetectorSamplerBin.cxx
 *
 * @since 2013-04-29
 * @author A. Rybalchenko, N. Winckler
 */

#include <iostream>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQSampler.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

#include "FairTestDetectorDigiLoader.h"

// data format for the task
#include "FairTestDetectorDigi.h"

// binary data format
#include "FairTestDetectorPayload.h"

// boost data format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

// Google Protocol Buffers data format
#include "FairTestDetectorPayload.pb.h"

// TMessage data format
#include "TMessage.h"

using namespace std;

using TPayloadOut = TestDetectorPayload::Digi; // binary payload
using TBoostBinPayloadOut = boost::archive::binary_oarchive; // boost binary format
using TBoostTextPayloadOut = boost::archive::text_oarchive;  // boost text format
using TProtoDigiPayload = TestDetectorProto::DigiPayload; // protobuf payload

using TSamplerBin = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TPayloadOut>>;
using TSamplerBoost = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TBoostBinPayloadOut>>;
using TSamplerProtobuf = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TProtoDigiPayload>>;
using TSamplerTMessage = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;

typedef struct DeviceOptions
{
    DeviceOptions() :
        id(), ioThreads(0), dataFormat(), inputFile(), parameterFile(), branch(), eventRate(0),
        outputSocketType(), outputBufSize(0), outputMethod(), outputAddress() {}

    string id;
    int ioThreads;
    string dataFormat;
    string inputFile;
    string parameterFile;
    string branch;
    int eventRate;
    string outputSocketType;
    int outputBufSize;
    string outputMethod;
    string outputAddress;
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
        ("input-file", bpo::value<string>()->required(), "Path to the input file")
        ("parameter-file", bpo::value<string>()->required(), "path to the parameter file")
        ("branch", bpo::value<string>()->default_value("FairTestDetectorDigi"), "Name of the Branch")
        ("event-rate", bpo::value<int>()->default_value(0), "Event rate limit in maximum number of events per second")
        ("output-socket-type", bpo::value<string>()->required(), "Output socket type: pub/push")
        ("output-buff-size", bpo::value<int>()->required(), "Output buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("output-method", bpo::value<string>()->required(), "Output method: bind/connect")
        ("output-address", bpo::value<string>()->required(), "Output address, e.g.: \"tcp://*:5555\"")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if (vm.count("help"))
    {
        LOG(INFO) << "FairMQ Test Detector Sampler" << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if (vm.count("id"))                 { _options->id               = vm["id"].as<string>(); }
    if (vm.count("io-threads"))         { _options->ioThreads        = vm["io-threads"].as<int>(); }
    if (vm.count("data-format"))        { _options->dataFormat       = vm["data-format"].as<string>(); }
    if (vm.count("input-file"))         { _options->inputFile        = vm["input-file"].as<string>(); }
    if (vm.count("parameter-file"))     { _options->parameterFile    = vm["parameter-file"].as<string>(); }
    if (vm.count("branch"))             { _options->branch           = vm["branch"].as<string>(); }
    if (vm.count("event-rate"))         { _options->eventRate        = vm["event-rate"].as<int>(); }
    if (vm.count("output-socket-type")) { _options->outputSocketType = vm["output-socket-type"].as<string>(); }
    if (vm.count("output-buff-size"))   { _options->outputBufSize    = vm["output-buff-size"].as<int>(); }
    if (vm.count("output-method"))      { _options->outputMethod     = vm["output-method"].as<string>(); }
    if (vm.count("output-address"))     { _options->outputAddress    = vm["output-address"].as<string>(); }

    return true;
}

template<typename T>
void runSampler(const DeviceOptions_t& options)
{
    T sampler;
    sampler.CatchSignals();

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    sampler.SetTransport(transportFactory);

    FairMQChannel channel(options.outputSocketType, options.outputMethod, options.outputAddress);
    channel.UpdateSndBufSize(options.outputBufSize);
    channel.UpdateRcvBufSize(options.outputBufSize);
    channel.UpdateRateLogging(1);

    sampler.fChannels["data-out"].push_back(channel);

    sampler.SetProperty(T::Id, options.id);
    sampler.SetProperty(T::InputFile, options.inputFile);
    sampler.SetProperty(T::ParFile, options.parameterFile);
    sampler.SetProperty(T::Branch, options.branch);
    sampler.SetProperty(T::EventRate, options.eventRate);
    sampler.SetProperty(T::NumIoThreads, options.ioThreads);

    sampler.ChangeState("INIT_DEVICE");
    sampler.WaitForEndOfState("INIT_DEVICE");

    sampler.ChangeState("INIT_TASK");
    sampler.WaitForEndOfState("INIT_TASK");

    sampler.ChangeState("RUN");
    sampler.InteractiveStateLoop();
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

    if (options.dataFormat == "binary") { runSampler<TSamplerBin>(options); }
    else if (options.dataFormat == "boost") { runSampler<TSamplerBoost>(options); }
    else if (options.dataFormat == "protobuf") { runSampler<TSamplerProtobuf>(options); }
    else if (options.dataFormat == "tmessage") { runSampler<TSamplerTMessage>(options); }
    else
    {
        LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|protobuf|tmessage). ";
        return 1;
    }

    return 0;
}
