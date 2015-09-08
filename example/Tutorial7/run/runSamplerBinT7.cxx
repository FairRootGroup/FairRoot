/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerBin.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 10:48 PM
 */

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "GenericSampler.h"

// FairRoot - Base/MQ
// sampler policies
#include "SimpleTreeReader.h"

// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"
#include "MyDigiSerializer.h"
#include "MyDigi.h"

// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyDigiSerializer_t              SerializerPolicy;
// Remark : here, serialization by hand --> not a cross-platform
typedef SimpleTreeReader<TClonesArray>  TCASamplerPolicy;

// root sampler policy
typedef GenericSampler<TCASamplerPolicy,SerializerPolicy > TSampler;

void myFuncHello(){ LOG(INFO) << "Hello "; }
void myFuncWorld(){ LOG(INFO) << "World "; }

int main(int argc, char** argv)
{
    try
    {
        TSampler sampler;
        FairMQProgOptions config;
        InitSamplerSetting(sampler, config, argc, argv);

        sampler.RegisterTask([](TSampler* s, SamplerTasksMap& task_list) 
        {
            //task_list[2]=std::bind( &TSampler::template MultiPartTask<5>, s);
            task_list[0] = std::bind(myFuncHello);
            task_list[1] = std::bind(myFuncWorld);
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
