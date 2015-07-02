/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */


/// std
#include <csignal>

/// FairRoot - FairMQ
//#include "FairMQLogger.h"
#include "GenericSampler.h"

/// FairRoot - Base/MQ
// sampler policies
#include "SimpleTreeReader.h"
#include "RootSerializer.h"

/// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"

/// ////////////////////////////////////////////////////////////////////////
// sampler and serialization policy
typedef SimpleTreeReader<TClonesArray>                 TSamplerPolicy;
typedef RootSerializer                                 TSerializePolicy;
// build sampler type
typedef GenericSampler<TSamplerPolicy,TSerializePolicy> TSampler;

TSampler sampler;

static void s_signal_handler(int signal)
{
    LOG(INFO) << "Caught signal " << signal;

    sampler.ChangeState(TSampler::END);

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

void myFuncHello(){LOG(INFO)<<"Hello ";}
void myFuncWorld(){LOG(INFO)<<"World ";}

int main(int argc, char** argv)
{
    try
    {
        s_catch_signals();
        FairMQProgOptions config;
        InitSamplerSetting(sampler, config, argc, argv);
        
        AddTask(sampler, config, [](TSampler* s, SamplerTasksMap& task_list) 
        {
            //task_list[2]=std::bind( &TSampler::template MultiPartTask<5>, s);
            task_list[0]=std::bind(myFuncHello);
            task_list[1]=std::bind(myFuncWorld);
        });
        
        runStateMachine(sampler, config);
        
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    return 0;
}
