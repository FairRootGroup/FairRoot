/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runFileSinkRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 7:51 PM
 */

/// std
#include <iostream>
#include <csignal>

/// boost
#include "boost/program_options.hpp"

/// ZMQ/nmsg (in FairSoft)
#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif

/// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "GenericFileSink.h"

/// FairRoot - base/MQ
#include "RootSerializer.h"
#include "RootOutFileManager.h"

/// FairRoot - Tutorial7
#include "MyHit.h"

// alternative to RootOutFileManager : BinaryOutFileManager
// storage policy of BinaryOutFileManager :
//#include "TriviallyCopyableDataSaver.h"
//#include "BoostDataSaver.h"


using namespace std;
/// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyHit                                        THit;
typedef RootDeSerializer                             TInputPolicy; 
typedef RootOutFileManager<THit>                     TOutputPolicy; 
typedef GenericFileSink<TInputPolicy,TOutputPolicy>  TSink;    

TSink filesink;

static void s_signal_handler(int signal)
{
    cout << endl << "Caught signal " << signal << endl;

    filesink.ChangeState(TSink::STOP);
    filesink.ChangeState(TSink::END);

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
        id(), ioThreads(0),
        inputSocketType(), inputBufSize(0), inputMethod(), inputAddress(),
        filename(), treename(), branchname(), classname(), fileoption(), useTClonesArray(true) {}
    
    string id;
    int ioThreads;
    string inputSocketType;
    int inputBufSize;
    string inputMethod;
    string inputAddress;
    string filename;
    string treename;
    string branchname;
    string classname;
    string fileoption;
    bool useTClonesArray;
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
        ("input-address", bpo::value<string>()->required(), "Input address, e.g.: \"tcp://*:5555\"")
        ("input-file", bpo::value<string>()->required(), "Prefix of the output file")
        ("tree", bpo::value<string>()->required(), "Name of the tree (for root file output)")
        ("branch", bpo::value<string>()->required(), "Name of the branch (for root file output)")
        ("class-name", bpo::value<string>()->required(), "Name of the payload class")
        ("file-option", bpo::value<string>()->default_value("RECREATE"), "Root file option : UPDATE, RECREATE etc.")
        ("use-TClonesArray", bpo::value<bool>()->default_value(true), "Method used to store data in root file")
        ("help", "Print help messages");

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(_argc, _argv, desc), vm);

    if ( vm.count("help") )
    {
        MQLOG(INFO) << "FairMQ File Sink" << endl << desc;
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
    
    if ( vm.count("input-file") )
        _options->filename = vm["input-file"].as<string>();
    
    if ( vm.count("tree") )
        _options->treename = vm["tree"].as<string>();
    
    if ( vm.count("branch") )
        _options->branchname = vm["branch"].as<string>();
    
    if ( vm.count("class-name") )
        _options->classname = vm["class-name"].as<string>();
    
    if ( vm.count("file-option") )
        _options->fileoption = vm["file-option"].as<string>();
    
    if ( vm.count("use-TClonesArray") )
        _options->useTClonesArray = vm["use-TClonesArray"].as<bool>();
    
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
        MQLOG(ERROR) << e.what();
        return 1;
    }

    MQLOG(INFO) << "PID: " << getpid();

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    filesink.SetTransport(transportFactory);

    filesink.SetProperty(TSink::Id, options.id);
    filesink.SetProperty(TSink::NumIoThreads, options.ioThreads);

    filesink.SetProperty(TSink::NumInputs, 1);
    filesink.SetProperty(TSink::NumOutputs, 0);
    
    filesink.InitInputPolicyContainer( options.classname.c_str() );
    filesink.SetFileProperties(options.filename,options.treename,options.branchname,options.classname,
                                                options.fileoption,options.useTClonesArray);

    filesink.ChangeState(TSink::INIT);
    filesink.SetProperty(TSink::InputSocketType, options.inputSocketType);
    filesink.SetProperty(TSink::InputRcvBufSize, options.inputBufSize);
    filesink.SetProperty(TSink::InputMethod, options.inputMethod);
    filesink.SetProperty(TSink::InputAddress, options.inputAddress);

    filesink.ChangeState(TSink::SETOUTPUT);
    filesink.ChangeState(TSink::SETINPUT);
    filesink.ChangeState(TSink::BIND);
    filesink.ChangeState(TSink::CONNECT);
    filesink.ChangeState(TSink::RUN);

    // wait until the running thread has finished processing.
    boost::unique_lock<boost::mutex> lock(filesink.fRunningMutex);
    while (!filesink.fRunningFinished)
    {
        filesink.fRunningCondition.wait(lock);
    }

    filesink.ChangeState(TSink::STOP);
    filesink.ChangeState(TSink::END);

    return 0;
}


