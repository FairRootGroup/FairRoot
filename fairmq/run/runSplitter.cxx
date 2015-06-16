/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * runSplitter.cxx
 *
 * @since 2012-12-06
 * @author D. Klein, A. Rybalchenko
 */

#include <iostream>
#include <csignal>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQSplitter.h"

#ifdef NANOMSG
#include "FairMQTransportFactoryNN.h"
#else
#include "FairMQTransportFactoryZMQ.h"
#endif

using namespace std;

FairMQSplitter splitter;

static void s_signal_handler(int signal)
{
    LOG(INFO) << "Caught signal " << signal;

    splitter.ChangeState(FairMQSplitter::END);

    LOG(INFO) << "Shutdown complete.";
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
        id(), ioThreads(0), numOutputs(0),
        inputSocketType(), inputBufSize(0), inputMethod(), inputAddress(),
        outputSocketType(), outputBufSize(), outputMethod(), outputAddress()
        {}

    string id;
    int ioThreads;
    int numOutputs;
    string inputSocketType;
    int inputBufSize;
    string inputMethod;
    string inputAddress;
    vector<string> outputSocketType;
    vector<int> outputBufSize;
    vector<string> outputMethod;
    vector<string> outputAddress;
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
        ("num-outputs", bpo::value<int>()->required(), "Number of Splitter output sockets")
        ("input-socket-type", bpo::value<string>()->required(), "Input socket type: sub/pull")
        ("input-buff-size", bpo::value<int>(), "Input buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("input-method", bpo::value<string>()->required(), "Input method: bind/connect")
        ("input-address", bpo::value<string>()->required(), "Input address, e.g.: \"tcp://localhost:5555\"")
        ("output-socket-type", bpo::value< vector<string> >()->required(), "Output socket type: pub/push")
        ("output-buff-size", bpo::value< vector<int> >(), "Output buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("output-method", bpo::value< vector<string> >()->required(), "Output method: bind/connect")
        ("output-address", bpo::value< vector<string> >()->required(), "Output address, e.g.: \"tcp://localhost:5555\"")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if ( vm.count("help") )
    {
        LOG(INFO) << "FairMQ Splitter" << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if ( vm.count("id") )
        _options->id = vm["id"].as<string>();

    if ( vm.count("io-threads") )
        _options->ioThreads = vm["io-threads"].as<int>();

    if ( vm.count("num-outputs") )
        _options->numOutputs = vm["num-outputs"].as<int>();

    if ( vm.count("input-socket-type") )
        _options->inputSocketType = vm["input-socket-type"].as<string>();

    if ( vm.count("input-buff-size") )
        _options->inputBufSize = vm["input-buff-size"].as<int>();

    if ( vm.count("input-method") )
        _options->inputMethod = vm["input-method"].as<string>();

    if ( vm.count("input-address") )
        _options->inputAddress = vm["input-address"].as<string>();

    if ( vm.count("output-socket-type") )
        _options->outputSocketType = vm["output-socket-type"].as< vector<string> >();

    if ( vm.count("output-buff-size") )
        _options->outputBufSize = vm["output-buff-size"].as< vector<int> >();

    if ( vm.count("output-method") )
        _options->outputMethod = vm["output-method"].as< vector<string> >();

    if ( vm.count("output-address") )
        _options->outputAddress = vm["output-address"].as< vector<string> >();

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

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    splitter.SetTransport(transportFactory);

    FairMQChannel inputChannel(options.inputSocketType, options.inputMethod, options.inputAddress);
    inputChannel.fSndBufSize = options.inputBufSize;
    inputChannel.fRcvBufSize = options.inputBufSize;
    inputChannel.fRateLogging = 1;

    splitter.fChannels["data-in"].push_back(inputChannel);

    for (int i = 0; i < options.outputAddress.size(); ++i)
    {
        FairMQChannel outputChannel(options.outputSocketType.at(i), options.outputMethod.at(i), options.outputAddress.at(i));
        outputChannel.fSndBufSize = options.outputBufSize.at(i);
        outputChannel.fRcvBufSize = options.outputBufSize.at(i);
        outputChannel.fRateLogging = 1;

        splitter.fChannels["data-out"].push_back(outputChannel);
    }

    splitter.SetProperty(FairMQSplitter::Id, options.id);
    splitter.SetProperty(FairMQSplitter::NumIoThreads, options.ioThreads);

    splitter.ChangeState(FairMQSplitter::INIT_DEVICE);
    splitter.WaitForEndOfState(FairMQSplitter::INIT_DEVICE);

    splitter.ChangeState(FairMQSplitter::INIT_TASK);
    splitter.WaitForEndOfState(FairMQSplitter::INIT_TASK);

    splitter.ChangeState(FairMQSplitter::RUN);
    splitter.WaitForEndOfState(FairMQSplitter::RUN);

    splitter.ChangeState(FairMQSplitter::STOP);

    splitter.ChangeState(FairMQSplitter::RESET_TASK);
    splitter.WaitForEndOfState(FairMQSplitter::RESET_TASK);

    splitter.ChangeState(FairMQSplitter::RESET_DEVICE);
    splitter.WaitForEndOfState(FairMQSplitter::RESET_DEVICE);

    splitter.ChangeState(FairMQSplitter::END);

    return 0;
}
