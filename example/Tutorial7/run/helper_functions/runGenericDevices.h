/* 
 * File:   runGenericDevices.h
 * Author: winckler
 *
 * Created on July 2, 2015, 2:07 PM
 */

#ifndef RUNGENERICDEVICES_H
#define RUNGENERICDEVICES_H

/// std
#include <iostream>
#include <type_traits>
#include <string>

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
#include "FairMQParser.h"
#include "FairMQProgOptions.h"

/// FairRoot - Tutorial7
#include "Tuto7Helper.h"



// template function that take any device, 
// and run a simple state machine configured from a JSON file
template<typename TMQDevice>
inline int runStateMachine(TMQDevice& device, FairMQProgOptions& config)
{
    device.CatchSignals();
    std::string jsonfile = config.GetValue<std::string>("config-json-file");
    std::string id = config.GetValue<std::string>("id");
    int ioThreads = config.GetValue<int>("io-threads");

    config.UserParser<FairMQParser::JSON>(jsonfile, id);

    device.fChannels = config.GetFairMQMap();

    device.SetProperty(TMQDevice::Id, id);
    device.SetProperty(TMQDevice::NumIoThreads, ioThreads);

    LOG(INFO) << "PID: " << getpid();

#ifdef NANOMSG
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryNN();
#else
    FairMQTransportFactory* transportFactory = new FairMQTransportFactoryZMQ();
#endif

    device.SetTransport(transportFactory);

    device.ChangeState(TMQDevice::INIT_DEVICE);
    device.WaitForEndOfState(TMQDevice::INIT_DEVICE);

    device.ChangeState(TMQDevice::INIT_TASK);
    device.WaitForEndOfState(TMQDevice::INIT_TASK);

    device.ChangeState(TMQDevice::RUN);
    device.InteractiveStateLoop();

    return 0;
}


// template function that take generic devices and an anonymous function as template parameters.
// The function allow to register tasks that will be executed in the run()
template<typename TGenDevice, typename TaskMan>
inline int AddTask(TGenDevice& generic_device, FairMQProgOptions& config, TaskMan man)
{
    bool taskman = config.GetValue<bool>("register-task");
    if (taskman)
    {
        generic_device.RegisterTask(man);
    }
    return 0;
}


#endif /* RUNGENERICDEVICES_H */

