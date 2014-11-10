/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/* 
 * File:   runGenericFileSink.cxx
 * Author: winckler
 *
 * Created on November 12, 2014, 6:39 PM
 */

#include <iostream>
#include <csignal>

#include "boost/program_options.hpp"

#include "FairMQLogger.h"
#include "FairMQFileSink.h"

#ifdef NANOMSG
#include "nanomsg/FairMQTransportFactoryNN.h"
#else
#include "zeromq/FairMQTransportFactoryZMQ.h"
#endif


// payload/data class
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"

// Device, take input and output policy as template argument
#include "GenericFileSink.h"

// input policy of GenericFileSink
#include "FairTestDetectorHitSerializer.h"
#include "BoostSerializer.h"
#include "NoInputMethod.h"

// output policy of GenericFileSink
#include "RootOutFileManager.h"
#include "BinaryOutFileManager.h"

// storage policy of BinaryOutFileManager
#include "TriviallyCopyableDataSaver.h"
#include "BoostDataSaver.h"

// contain  an helper to handle the 
// genericsink with the different policy APIs in one main
#include "FairMQTemplate.h"



using namespace FairMQTemplate;
using namespace std;

// payload definition
typedef FairTestDetectorHit                                 THit;            // non POD/complex data
typedef TestDetectorPayload::Hit                            THitPod; // POD/trivial data

/// ////////////////////////////////////////////////////////////////////////
/// boost i/o archives
typedef boost::archive::binary_iarchive                     TBoostArchiveIn;
typedef boost::archive::binary_oarchive                     TBoostArchiveOut;

/// ////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////
/// -------------- INPUT POLICY (for GenericFileSink) --------------
/// The input policies deserialize the data contained in FairMQMessage* msg 
/// and send the data to the Output Policy. 
// ----------------------------------------------------------------
// I) Input Policy 1 (generic for boost (de)serializable data)
//    BoostSerializer<Tdata,BoostArchive,Tcontainer=vector<Tdata> >  
//    --> has two specializations corresponding to two API :
//      i)  Tcontainer=vector<Tdata>   --> vector<Tdata>& message(FairMQMessage* msg)
//      ii) Tcontainer=TClonesArray*   --> TClonesArray*  message(FairMQMessage* msg)
typedef BoostSerializer<THit,TBoostArchiveIn>               TInputMethod1a; // boost non pod, return vector (default)
typedef BoostSerializer<THitPod,TBoostArchiveIn>            TInputMethod1b; // boost pod, return vector (default)
typedef BoostSerializer<THit,TBoostArchiveIn,TClonesArray*> TInputMethod1c; // boost non pod, return TClonesArray*

// generic typedef w.r.t. payload types
template <typename TPayload>
    using BoostInPolicy_vec= BoostSerializer<TPayload,TBoostArchiveIn>;

template <typename TPayload>
    using BoostInPolicy_TCA= BoostSerializer<TPayload,TBoostArchiveIn,TClonesArray*>;

// ----------------------------------------------------------------
// II) Input Policy 2 (user code, specific to TestDetectorPayload::Hit )
//     --> Only 1 message member function : TClonesArray* message(FairMQMessage* msg)
typedef FairTestDetectorHitSerializer                       TInputMethod2;  // hand pod  TClonesArray* message(FairMQMessage* msg)
// ----------------------------------------------------------------
// III) Input Policy 3 (do nothing, just forward FairMQMessage* msg to the Output Policy)
typedef NoInputMethod                                       TInputMethod3;  // no input method
// ----------------------------------------------------------------

/// ////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////
/// -------------- STORAGE POLICY (for binary output policy) -------------- 
/// The storage policies are the required policies by BinaryOutFileManager. 
/// They serialize the data e.g. by boost or Hand method and store them in binary file.
//                 --> to plug in BinaryOutFileManager<TData,TStoragePolicy>
//                 --> not required in RootOutFileManager<TData>
// ----------------------------------------------------------------
// I) Storage Policy 1 (Generic for pod or Trivially copyable data)
// TriviallyCopyableDataSaver<Tdata> 
typedef TriviallyCopyableDataSaver<THitPod>                 HandPODStorage;
// ----------------------------------------------------------------
// II) Storage Policy 2 (Generic for boost serializable data)
// BoostDataSaver<Tdata> 
typedef BoostDataSaver<THitPod>                             BoostPODStorage;
typedef BoostDataSaver<THit>                                BoostNonPODStorage;

/// ////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////
/// -------------- OUTPUT POLICY (for GenericFileSink) -------------- 
typedef RootOutFileManager<THit>                            TOutputMethod1a; // root non pod
typedef RootOutFileManager<THitPod>                         TOutputMethod1b; // root pod
typedef BinaryOutFileManager<THit,BoostNonPODStorage>       TOutputMethod2a; // boost non pod
typedef BinaryOutFileManager<THitPod,BoostPODStorage>       TOutputMethod2b; // boost pod
typedef BinaryOutFileManager<THitPod,HandPODStorage>        TOutputMethod3; // hand pod

template <typename TPayload>
    using BinaryBoostOutPolicy= BinaryOutFileManager<TPayload,BoostDataSaver<TPayload> >;

template <typename TPayload>
    using BinaryHandOutPolicy= BinaryOutFileManager<TPayload,TriviallyCopyableDataSaver<TPayload> >;

/// ////////////////////////////////////////////////////////////////////////
/// Typedef of different valid filesink types (possible combination):
// for root output file policy
typedef GenericFileSink<TInputMethod1a,TOutputMethod1a>     TSink_1a_1a;    // rootfile/non pod/Boost deserialize/vect API
typedef GenericFileSink<TInputMethod1b,TOutputMethod1b>     TSink_1b_1b;    // rootfile/pod/Boost deserialize/vect API
typedef GenericFileSink<TInputMethod1c,TOutputMethod1a>     TSink_1c_1a;    // rootfile/non pod/Boost deserialize/TClonesArray* API
typedef GenericFileSink<TInputMethod2,TOutputMethod1b>      TSink_2_1b;     // rootfile/pod/hand deserialize/TClonesArray* API
typedef GenericFileSink<TInputMethod3,TOutputMethod1b>      TSink_3_1b;     // rootfile/pod/hand deserialize/FairMQMessage* API

// for binary policy (boost output file policy)
typedef GenericFileSink<TInputMethod1a,TOutputMethod2a>     TSink_1a_2a;    // boostfile/non pod/Boost deserialize/vect API
typedef GenericFileSink<TInputMethod1b,TOutputMethod2b>     TSink_1b_2b;    // boostfile/pod/Boost deserialize/vect API
//typedef GenericFileSink<TInputMethod1c,TOutputMethod2b>   TSink_1c_2a;    // not valid because no TClonesArray* API in BinaryOutFileManager
//typedef GenericFileSink<TInputMethod2,TOutputMethod2b>    TSink_2_2b;     // not valid because no TClonesArray* API in BinaryOutFileManager
typedef GenericFileSink<TInputMethod3,TOutputMethod2b>      TSink_3_2b;     // boostfile/pod/hand deserialize/FairMQMessage* API

// for binary policy (hand output file policy)
//typedef GenericFileSink<TInputMethod1a,TOutputMethod3>     TSink_1a_3;    // not valid because non pod data
typedef GenericFileSink<TInputMethod1b,TOutputMethod3>     TSink_1b_3;    // Handfile/pod/Boost deserialize/vect API
//typedef GenericFileSink<TInputMethod1c,TOutputMethod3>   TSink_1c_2a;    // not valid because no TClonesArray* API in BinaryOutFileManager
//typedef GenericFileSink<TInputMethod2,TOutputMethod3>    TSink_2_2b;     // not valid because no TClonesArray* API in BinaryOutFileManager
typedef GenericFileSink<TInputMethod3,TOutputMethod3>      TSink_3_3;     // Handfile/pod/hand deserialize/FairMQMessage* API


// To test one genericfilesink type, choose one of the predefined types
// change the class name in the macro accordingly. 
// In this example : 
// non pod data --> classname=FairTestDetectorHit
// pod data     --> classname=TestDetectorPayload::Hit

// Rootfile output:
//typedef TSink_1a_1a TSink;
//typedef TSink_1b_1b TSink;
//typedef TSink_1c_1a TSink;
//typedef TSink_2_1b  TSink;
//typedef TSink_3_1b  TSink;

// Boostfile ouput
//typedef TSink_1a_2a TSink;
//typedef TSink_1b_2b TSink;
typedef TSink_3_2b  TSink;

// hand made binary output
//typedef TSink_1b_3  TSink;
//typedef TSink_3_3  TSink;

TSink filesink;

template <typename T , typename... Args>
void SetParam(T &FileSink, string& filename, Args&... args)
{
    if(is_same<T,TSink_1a_1a>::value) filename+="TSink_1a_1a.root";
    if(is_same<T,TSink_1b_1b>::value) filename+="TSink_1b_1b.root";
    if(is_same<T,TSink_1c_1a>::value) filename+="TSink_1c_1a.root";
    if(is_same<T,TSink_2_1b >::value) filename+="TSink_2_1b.root";
    if(is_same<T,TSink_3_1b >::value) filename+="TSink_3_1b.root";
    
    if(is_same<T,TSink_1a_2a>::value) filename+="TSink_1a_2a.boost.dat";
    if(is_same<T,TSink_1b_2b>::value) filename+="TSink_1b_2b.boost.dat";
    if(is_same<T,TSink_3_2b >::value) filename+="TSink_3_2b.boost.dat";
    
    if(is_same<T,TSink_1b_3 >::value) filename+="TSink_1b_3.hand.dat";
    if(is_same<T,TSink_3_2b >::value) filename+="TSink_3_2b.hand.dat";
    
    
    MQDeviceTool::SinkHelper handler(filename,args...);
    handler.SetProperties<T>(FileSink);
    
    /*
    constexpr int Narg = sizeof...(Args);
    if(Narg<1)
        std::cout<<"At lease one argument (filename) is required"<<std::endl;
    else
    {
        //MQDeviceTool::SinkHelper<Args...> handler(std::forward<Args>(args)...);
        MQDeviceTool::SinkHelper handler(args...);
        //handler.template SetProperties<T>(FileSink);
        handler.SetProperties<T>(FileSink);
    }
    
    */
    
}




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
        ("file-name", bpo::value<string>()->required(), "Prefix of the output file")
        ("tree-name", bpo::value<string>()->required(), "Name of the tree (for root file output)")
        ("branch-name", bpo::value<string>()->required(), "Name of the branch (for root file output)")
        ("class-name", bpo::value<string>()->required(), "Name of the payload class")
        ("file-option", bpo::value<string>()->required(), "Root file option : UPDATE, RECREATE etc.")
        ("use-TClonesArray", bpo::value<bool>()->required(), "Method used to store data in root file")
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
    
    if ( vm.count("file-name") )
        _options->filename = vm["file-name"].as<string>();
    
    if ( vm.count("tree-name") )
        _options->treename = vm["tree-name"].as<string>();
    
    if ( vm.count("branch-name") )
        _options->branchname = vm["branch-name"].as<string>();
    
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

    filesink.ChangeState(TSink::INIT);
    
    
    SetParam<TSink>(filesink,options.filename.append(options.id),  
                             options.classname,
                             options.treename,  options.branchname,
                             options.fileoption,options.useTClonesArray);
    
    //filesink.InitOutputFile(options.id);

    filesink.SetProperty(TSink::InputSocketType, options.inputSocketType);
    filesink.SetProperty(TSink::InputRcvBufSize, options.inputBufSize);
    filesink.SetProperty(TSink::InputMethod, options.inputMethod);
    filesink.SetProperty(TSink::InputAddress, options.inputAddress);

    filesink.ChangeState(TSink::SETOUTPUT);
    filesink.ChangeState(TSink::SETINPUT);
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
