/* 
 * File:   runProcessorBoost.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

#include <iostream>
#include <csignal>

#include "boost/program_options.hpp"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

// FairRoot
#include "FairMQLogger.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

// FairRoot - Tutorial7 
// Processor device
#include "GenericProcessor.h"

// Serialization policy
#include "BoostSerializer.h"

// Task policy
#include "DigiToHitTask.h"

// payload/data class
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorHit.h"

using namespace std;
/// ////////////////////////////////////////////////////////////////////////
// payload definition
typedef FairTestDetectorDigi              TDigi; 
typedef FairTestDetectorHit               THit;

// build policy classes
typedef BoostDeSerializer<TDigi>          TInputPolicy;   // deserialize digi
typedef BoostSerializer<THit>             TOutputPolicy;  // serialize Hit
typedef DigiToHitTask<TDigi,THit>         TTaskPolicy;    // process deserialized digi and fill Hit

typedef GenericProcessor<TInputPolicy,TOutputPolicy,TTaskPolicy> TProcessor;

TProcessor processor;

static void s_signal_handler(int signal)
{
    LOG(INFO) << "Caught signal " << signal;

    processor.ChangeState(TProcessor::END);

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
    string id;
    int ioThreads;
    string inputSocketType;
    int inputBufSize;
    string inputMethod;
    string inputAddress;
    string outputSocketType;
    int outputBufSize;
    string outputMethod;
    string outputAddress;
    string digiclassname;
    string hitclassname;
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
        ("input-socket-type", bpo::value<string>()->required(), "Input socket type: sub/pull")
        ("input-buff-size", bpo::value<int>()->required(), "Input buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("input-method", bpo::value<string>()->required(), "Input method: bind/connect")
        ("input-address", bpo::value<string>()->required(), "Input address, e.g.: \"tcp://localhost:5555\"")
        ("output-socket-type", bpo::value<string>()->required(), "Output socket type: pub/push")
        ("output-buff-size", bpo::value<int>()->required(), "Output buffer size in number of messages (ZeroMQ)/bytes(nanomsg)")
        ("output-method", bpo::value<string>()->required(), "Output method: bind/connect")
        ("output-address", bpo::value<string>()->required(), "Output address, e.g.: \"tcp://localhost:5555\"")
        ("digi-classname", bpo::value<string>()->default_value("FairTestDetectorDigi"), "Digi class name for initializing TClonesArray")
        ("hit-classname", bpo::value<string>()->default_value("FairTestDetectorHit"), "Hit class name for initializing TClonesArray")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if ( vm.count("help") )
    {
        LOG(INFO) << "FairMQ Test Detector Processor" << endl << desc;
        return false;
    }

    bpo::notify(vm);

    if ( vm.count("id") )
        _options->id = vm["id"].as<string>();

    if ( vm.count("io-threads") )
        _options->ioThreads = vm["io-threads"].as<int>();

    if ( vm.count("input-socket-type") )
        _options->inputSocketType = vm["input-socket-type"].as<string>();

    if ( vm.count("input-buff-size") )
        _options->inputBufSize = vm["input-buff-size"].as<int>();

    if ( vm.count("input-method") )
        _options->inputMethod = vm["input-method"].as<string>();

    if ( vm.count("input-address") )
        _options->inputAddress = vm["input-address"].as<string>();

    if ( vm.count("output-socket-type") )
        _options->outputSocketType = vm["output-socket-type"].as<string>();

    if ( vm.count("output-buff-size") )
        _options->outputBufSize = vm["output-buff-size"].as<int>();

    if ( vm.count("output-method") )
        _options->outputMethod = vm["output-method"].as<string>();

    if ( vm.count("output-address") )
        _options->outputAddress = vm["output-address"].as<string>();
    
    if ( vm.count("output-address") )
        _options->digiclassname = vm["digi-classname"].as<string>();
    
    if ( vm.count("output-address") )
        _options->hitclassname = vm["hit-classname"].as<string>();

    return true;
}

int main(int argc, char** argv)
{
    try
    {
        s_catch_signals();

        DeviceOptions_t options;
        try
        {
            if (!parse_cmd_line(argc, argv, &options))
                return 0;
        }
        catch (std::exception& err)
        {
            LOG(ERROR) << err.what();
            return 1;
        }

        LOG(INFO) << "PID: " << getpid();

    #ifdef NANOMSG
        FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
    #else
        FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
    #endif

        processor.SetTransport(transportFactory);

        FairMQChannel inputChannel(options.inputSocketType, options.inputMethod, options.inputAddress);
        inputChannel.fSndBufSize = options.inputBufSize;
        inputChannel.fRcvBufSize = options.inputBufSize;
        inputChannel.fRateLogging = 1;

        processor.fChannels["data-in"].push_back(inputChannel);

        FairMQChannel outputChannel(options.outputSocketType, options.outputMethod, options.outputAddress);
        outputChannel.fSndBufSize = options.outputBufSize;
        outputChannel.fRcvBufSize = options.outputBufSize;
        outputChannel.fRateLogging = 1;

        processor.fChannels["data-out"].push_back(outputChannel);

        processor.SetProperty(TProcessor::Id, options.id);
        processor.SetProperty(TProcessor::NumIoThreads, options.ioThreads);

        processor.ChangeState(TProcessor::INIT_DEVICE);
        processor.WaitForEndOfState(TProcessor::INIT_DEVICE);

        processor.ChangeState(TProcessor::INIT_TASK);
        processor.WaitForEndOfState(TProcessor::INIT_TASK);

        processor.ChangeState(TProcessor::RUN);
        processor.WaitForEndOfState(TProcessor::RUN);

        processor.ChangeState(TProcessor::STOP);

        processor.ChangeState(TProcessor::RESET_TASK);
        processor.WaitForEndOfState(TProcessor::RESET_TASK);

        processor.ChangeState(TProcessor::RESET_DEVICE);
        processor.WaitForEndOfState(TProcessor::RESET_DEVICE);

        processor.ChangeState(TProcessor::END);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    
    return 0;
}
