/* 
 * File:   runProcessorBin.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

// std
#include <iostream>
#include <csignal>

// boost
#include "boost/program_options.hpp"

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
#include "MyDigiSerializer.h"
#include "MyHitSerializer.h"

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
// policy classes
typedef Tuto3DigiDeSerializer_t             TInputPolicy;
typedef Tuto3HitSerializer_t              TOutputPolicy;
typedef DigiToHitTask_TCA<TDigi,THit>     TTaskPolicy; // process deserialized digi and fill Hit

typedef GenericProcessor<TInputPolicy,TOutputPolicy,TTaskPolicy> TProcessor;

TProcessor processor;

static void s_signal_handler(int signal)
{
    cout << endl << "Caught signal " << signal << endl;

    processor.ChangeState(TProcessor::STOP);
    processor.ChangeState(TProcessor::END);

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
        ("digi-classname", bpo::value<string>()->default_value("MyDigi"), "Digi class name for initializing TClonesArray")
        ("hit-classname", bpo::value<string>()->default_value("MyHit"), "Hit class name for initializing TClonesArray")
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

    processor.SetTransport(transportFactory);

    processor.SetProperty(TProcessor::Id, options.id);
    processor.SetProperty(TProcessor::NumIoThreads, options.ioThreads);
    processor.SetProperty(TProcessor::NumInputs, 1);
    processor.SetProperty(TProcessor::NumOutputs, 1);

    processor.InitInputContainer(options.digiclassname);
    processor.InitTask(options.hitclassname);
    
    processor.ChangeState(TProcessor::INIT);

    processor.SetProperty(TProcessor::InputSocketType, options.inputSocketType);
    processor.SetProperty(TProcessor::InputSndBufSize, options.inputBufSize);
    processor.SetProperty(TProcessor::InputMethod, options.inputMethod);
    processor.SetProperty(TProcessor::InputAddress, options.inputAddress);

    processor.SetProperty(TProcessor::OutputSocketType, options.outputSocketType);
    processor.SetProperty(TProcessor::OutputSndBufSize, options.outputBufSize);
    processor.SetProperty(TProcessor::OutputMethod, options.outputMethod);
    processor.SetProperty(TProcessor::OutputAddress, options.outputAddress);

    processor.ChangeState(TProcessor::SETOUTPUT);
    processor.ChangeState(TProcessor::SETINPUT);
    processor.ChangeState(TProcessor::BIND);
    processor.ChangeState(TProcessor::CONNECT);
    processor.ChangeState(TProcessor::RUN);

    // wait until the running thread has finished processing.
    boost::unique_lock<boost::mutex> lock(processor.fRunningMutex);
    while (!processor.fRunningFinished)
    {
        processor.fRunningCondition.wait(lock);
    }

    processor.ChangeState(TProcessor::STOP);
    processor.ChangeState(TProcessor::END);

    return 0;
}
