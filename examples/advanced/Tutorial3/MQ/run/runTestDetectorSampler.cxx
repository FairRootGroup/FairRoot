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
#include "FairTestDetectorDigiLoader.h"

using namespace std;

using TPayloadOut = TestDetectorPayload::Digi; // binary payload
using TBoostBinPayloadOut = boost::archive::binary_oarchive; // boost binary format
using TBoostTextPayloadOut = boost::archive::text_oarchive;  // boost text format
using TProtoDigiPayload = TestDetectorProto::DigiPayload; // protobuf payload

using TSamplerBin = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TPayloadOut>>;
using TSamplerBoostBin = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TBoostBinPayloadOut>>;
using TSamplerBoostText = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TBoostTextPayloadOut>>;
using TSamplerProtobuf = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TProtoDigiPayload>>;
using TSamplerTMessage = FairMQSampler<FairTestDetectorDigiLoader<FairTestDetectorDigi, TMessage>>;

typedef struct DeviceOptions
{
    DeviceOptions() :
        id(), ioThreads(0), transport(), dataFormat(), inputFile(), parameterFile(), branch(), eventRate(0), chainInput(0),
        outputSocketType(), outputBufSize(0), outputMethod(), outputAddress(),
        ackSocketType(), ackBufSize(0), ackMethod(), ackAddress() {}

    string id;
    int ioThreads;
    string transport;
    string dataFormat;
    string inputFile;
    string parameterFile;
    string branch;
    int eventRate;
    int chainInput;
    string outputSocketType;
    int outputBufSize;
    string outputMethod;
    string outputAddress;
    string ackSocketType;
    int ackBufSize;
    string ackMethod;
    string ackAddress;
} DeviceOptions_t;

inline bool parse_cmd_line(int _argc, char* _argv[], DeviceOptions* _options)
{
    if (_options == NULL)
        throw runtime_error("Internal error: options' container is empty.");

    namespace bpo = boost::program_options;
    bpo::options_description desc("Options");
    desc.add_options()
        ("id", bpo::value<string>()->required(), "Device ID")
        ("io-threads", bpo::value<int>()->default_value(1), "Number of I/O threads")
        ("transport", bpo::value<string>()->default_value("zeromq"), "Transport (zeromq/nanomsg)")
        ("data-format", bpo::value<string>()->default_value("binary"), "Data format (binary/boost/boost-text/protobuf/tmessage)")
        ("input-file", bpo::value<string>()->required(), "Path to the input file")
        ("parameter-file", bpo::value<string>()->required(), "path to the parameter file")
        ("branch", bpo::value<string>()->default_value("FairTestDetectorDigi"), "Name of the Branch")
        ("event-rate", bpo::value<int>()->default_value(0), "Event rate limit in maximum number of events per second")
        ("chain-input", bpo::value<int>()->default_value(0), "Chain input file more than once (default)")
        ("output-socket-type", bpo::value<string>()->required(), "Output socket type: pub/push")
        ("output-buff-size", bpo::value<int>()->required(), "Output buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("output-method", bpo::value<string>()->required(), "Output method: bind/connect")
        ("output-address", bpo::value<string>()->required(), "Output address, e.g.: \"tcp://*:5555\"")
        ("ack-socket-type", bpo::value<string>()->default_value("pull"), "ack socket type: pub/push")
        ("ack-buff-size", bpo::value<int>()->default_value(1000), "ack buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("ack-method", bpo::value<string>()->default_value("bind"), "ack method: bind/connect")
        ("ack-address", bpo::value<string>()->required(), "ack address, e.g.: \"tcp://*:5555\"")
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
    if (vm.count("transport"))          { _options->transport        = vm["transport"].as<string>(); }
    if (vm.count("data-format"))        { _options->dataFormat       = vm["data-format"].as<string>(); }
    if (vm.count("input-file"))         { _options->inputFile        = vm["input-file"].as<string>(); }
    if (vm.count("parameter-file"))     { _options->parameterFile    = vm["parameter-file"].as<string>(); }
    if (vm.count("branch"))             { _options->branch           = vm["branch"].as<string>(); }
    if (vm.count("event-rate"))         { _options->eventRate        = vm["event-rate"].as<int>(); }
    if (vm.count("chain-input"))        { _options->chainInput       = vm["chain-input"].as<int>(); }
    if (vm.count("output-socket-type")) { _options->outputSocketType = vm["output-socket-type"].as<string>(); }
    if (vm.count("output-buff-size"))   { _options->outputBufSize    = vm["output-buff-size"].as<int>(); }
    if (vm.count("output-method"))      { _options->outputMethod     = vm["output-method"].as<string>(); }
    if (vm.count("output-address"))     { _options->outputAddress    = vm["output-address"].as<string>(); }
    if (vm.count("ack-socket-type"))    { _options->ackSocketType    = vm["ack-socket-type"].as<string>(); }
    if (vm.count("ack-buff-size"))      { _options->ackBufSize       = vm["ack-buff-size"].as<int>(); }
    if (vm.count("ack-method"))         { _options->ackMethod        = vm["ack-method"].as<string>(); }
    if (vm.count("ack-address"))        { _options->ackAddress       = vm["ack-address"].as<string>(); }

    return true;
}

template<typename T>
void runSampler(const DeviceOptions_t& options)
{
    T sampler;
    sampler.CatchSignals();

    sampler.SetTransport(options.transport);

    FairMQChannel outputChannel(options.outputSocketType, options.outputMethod, options.outputAddress);
    outputChannel.UpdateSndBufSize(options.outputBufSize);
    outputChannel.UpdateRcvBufSize(options.outputBufSize);
    outputChannel.UpdateRateLogging(1);

    sampler.fChannels["data-out"].push_back(outputChannel);

    FairMQChannel ackChannel(options.ackSocketType, options.ackMethod, options.ackAddress);
    ackChannel.UpdateSndBufSize(options.ackBufSize);
    ackChannel.UpdateRcvBufSize(options.ackBufSize);
    ackChannel.UpdateRateLogging(0);

    sampler.fChannels["ack-in"].push_back(ackChannel);

    sampler.SetProperty(T::Id, options.id);
    sampler.SetProperty(T::InputFile, options.inputFile);
    sampler.SetProperty(T::ParFile, options.parameterFile);
    sampler.SetProperty(T::Branch, options.branch);
    sampler.SetProperty(T::EventRate, options.eventRate);
    sampler.SetProperty(T::ChainInput, options.chainInput);
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
    else if (options.dataFormat == "boost") { runSampler<TSamplerBoostBin>(options); }
    else if (options.dataFormat == "boost-text") { runSampler<TSamplerBoostText>(options); }
    else if (options.dataFormat == "protobuf") { runSampler<TSamplerProtobuf>(options); }
    else if (options.dataFormat == "tmessage") { runSampler<TSamplerTMessage>(options); }
    else
    {
        LOG(ERROR) << "No valid data format provided. (--data-format binary|boost|boost-text|protobuf|tmessage). ";
        return 1;
    }

    return 0;
}
