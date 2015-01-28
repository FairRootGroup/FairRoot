/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runTestDetectorSamplerRoot.cxx
 *
 * @since 2013-04-29
 * @author A. Rybalchenko, N. Winckler
 */

#include <iostream>
#include <csignal>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQSampler.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

#include "TestDetectorDigiLoader.h"

#include "TMessage.h"
#include "FairTestDetectorDigi.h"

using namespace std;

typedef TestDetectorDigiLoader<FairTestDetectorDigi, TMessage> TLoader;
typedef FairMQSampler<TLoader> TSampler;

TSampler sampler;

static void s_signal_handler(int signal)
{
    cout << endl << "Caught signal " << signal << endl;

    sampler.ChangeState(TSampler::STOP);
    sampler.ChangeState(TSampler::END);

    cout << "Shutdown complete. Bye!" << endl;
    exit(1);
}

static void s_catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

typedef struct DeviceOptions
{
    DeviceOptions() :
        id(), inputFile(), parameterFile(), branch(), eventRate(0), ioThreads(0),
        outputSocketType(), outputBufSize(0), outputMethod(), outputAddress() {}

    string id;
    string inputFile;
    string parameterFile;
    string branch;
    int eventRate;
    int ioThreads;
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
        ("input-file", bpo::value<string>()->required(), "Path to the input file")
        ("parameter-file", bpo::value<string>()->required(), "path to the parameter file")
        ("branch", bpo::value<string>()->default_value("FairTestDetectorDigi"), "Name of the Branch")
        ("event-rate", bpo::value<int>()->default_value(0), "Event rate limit in maximum number of events per second")
        ("io-threads", bpo::value<int>()->default_value(1), "Number of I/O threads")
        ("output-socket-type", bpo::value<string>()->required(), "Output socket type: pub/push")
        ("output-buff-size", bpo::value<int>()->required(), "Output buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("output-method", bpo::value<string>()->required(), "Output method: bind/connect")
        ("output-address", bpo::value<string>()->required(), "Output address, e.g.: \"tcp://*:5555\"")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if ( vm.count("help") )
    {
        LOG(INFO) << "FairMQ Test Detector Sampler" << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if ( vm.count("id") )
        _options->id = vm["id"].as<string>();

    if ( vm.count("input-file") )
        _options->inputFile = vm["input-file"].as<string>();

    if ( vm.count("parameter-file") )
        _options->parameterFile = vm["parameter-file"].as<string>();

    if ( vm.count("branch") )
        _options->branch = vm["branch"].as<string>();

    if ( vm.count("event-rate") )
        _options->eventRate = vm["event-rate"].as<int>();

    if ( vm.count("io-threads") )
        _options->ioThreads = vm["io-threads"].as<int>();

    if ( vm.count("output-socket-type") )
        _options->outputSocketType = vm["output-socket-type"].as<string>();

    if ( vm.count("output-buff-size") )
        _options->outputBufSize = vm["output-buff-size"].as<int>();

    if ( vm.count("output-method") )
        _options->outputMethod = vm["output-method"].as<string>();

    if ( vm.count("output-address") )
        _options->outputAddress = vm["output-address"].as<string>();

    return true;
}

int main(int argc, char** argv)
{
    s_catch_signals();

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
    LOG(INFO) << "CONFIG: " << "id: " << options.id << ", event rate: " << options.eventRate << ", I/O threads: " << options.ioThreads;
    LOG(INFO) << "FILES: " << "input file: " << options.inputFile << ", parameter file: " << options.parameterFile << ", branch: " << options.branch;
    LOG(INFO) << "OUTPUT: " << options.outputSocketType << " " << options.outputBufSize << " " << options.outputMethod << " " << options.outputAddress;

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    sampler.SetTransport(transportFactory);

    sampler.SetProperty(TSampler::Id, options.id);
    sampler.SetProperty(TSampler::InputFile, options.inputFile);
    sampler.SetProperty(TSampler::ParFile, options.parameterFile);
    sampler.SetProperty(TSampler::Branch, options.branch);
    sampler.SetProperty(TSampler::EventRate, options.eventRate);
    sampler.SetProperty(TSampler::NumIoThreads, options.ioThreads);

    sampler.SetProperty(TSampler::NumInputs, 0);
    sampler.SetProperty(TSampler::NumOutputs, 1);

    sampler.ChangeState(TSampler::INIT);

    sampler.SetProperty(TSampler::OutputSocketType, options.outputSocketType);
    sampler.SetProperty(TSampler::OutputSndBufSize, options.outputBufSize);
    sampler.SetProperty(TSampler::OutputMethod, options.outputMethod);
    sampler.SetProperty(TSampler::OutputAddress, options.outputAddress);

    sampler.ChangeState(TSampler::SETOUTPUT);
    sampler.ChangeState(TSampler::SETINPUT);
    sampler.ChangeState(TSampler::BIND);
    sampler.ChangeState(TSampler::CONNECT);

    try
    {
        sampler.ChangeState(TSampler::RUN);
    }
    catch (boost::archive::archive_exception& e)
    {
        LOG(ERROR) << e.what();
    }

    // wait until the running thread has finished processing.
    boost::unique_lock<boost::mutex> lock(sampler.fRunningMutex);
    while (!sampler.fRunningFinished)
    {
        sampler.fRunningCondition.wait(lock);
    }

    sampler.ChangeState(TSampler::STOP);
    sampler.ChangeState(TSampler::END);

    return 0;
}
