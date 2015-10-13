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

// FairRoot - FairMQ
#include "GenericSampler.h"

// FairRoot - Base/MQ
// sampler & serialization policies
#include "SimpleTreeReader.h"
#include "BoostSerializer.h"

// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "MyDigi.h"

// ////////////////////////////////////////////////////////////////////////
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
        TSampler sampler;
        FairMQProgOptions config;
        InitSamplerSetting(sampler, config, argc, argv);

        if( config.GetValue<bool>("register-task-sampler") )
        {
            AddTask(sampler, config, std::bind(&manager,std::placeholders::_1,std::placeholders::_2) );
        }
        
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
