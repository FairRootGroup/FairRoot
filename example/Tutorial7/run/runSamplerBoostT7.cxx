/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   runSamplerBoostT7.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 10:45 PM
 */

/// std
#include <csignal>

/// FairRoot - FairMQ
#include "GenericSampler.h"

/// FairRoot - Base/MQ
// sampler & serialization policies
#include "SimpleTreeReader.h"
#include "BoostSerializer.h"

/// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "MyDigi.h"

using namespace std;
/// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyDigi                                         TDigi;
// sampler and serialization policy
typedef SimpleTreeReader<TClonesArray>                 TSamplerPolicy;
typedef BoostSerializer<TDigi>                         TSerializePolicy;
// remark : by default BoostSerializer has boost-binary archive format, which is not cross-platform
// for cross-platform use xml or text format e.g. as follow:
// BoostSerializer<TDigi,std::vector<TDigi>,boost::archive::text_iarchive,boost::archive::text_oarchive>

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

void manager(TSampler* policy, SamplerTasksMap& task_list)
{
    task_list[0]=std::bind(myFuncHello);
    task_list[1]=std::bind(myFuncWorld);
}


int main(int argc, char** argv)
{
    try
    {
        s_catch_signals();
        FairMQProgOptions config;
        InitSamplerSetting(sampler, config, argc, argv);
        
        AddTask(sampler, config, std::bind(&manager,std::placeholders::_1,std::placeholders::_2) );
        
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
