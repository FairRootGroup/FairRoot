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

/// std
#include <csignal>

/// FairRoot - FairMQ
#include "GenericSampler.h"

/// FairRoot - Base/MQ
// sampler & serialization policies
#include "SimpleTreeReader.h"
#include "MyDigiSerializer.h"

/// FairRoot - Tutorial 7
#include "tuto7SamplerFunctions.h"

using namespace std;
/// ////////////////////////////////////////////////////////////////////////
// type definitions
typedef Tuto3DigiSerializer_t SerializerPolicy;
typedef SimpleTreeReader<TClonesArray> TCASamplerPolicy;

// root sampler policy
typedef GenericSampler<TCASamplerPolicy,SerializerPolicy > TSampler;

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

int main(int argc, char** argv)
{
    try
    {
        s_catch_signals();
        if(runSampler(sampler,argc,argv))
            return 1;
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    return 0;
}
