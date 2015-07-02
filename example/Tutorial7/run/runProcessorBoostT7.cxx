/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   runProcessorBoost.cxx
 * Author: winckler
 *
 * Created on December 2, 2014, 11:14 PM
 */

/// std
#include <csignal>

/// FairRoot - FairMQ
#include "GenericProcessor.h"

/// FairRoot - base/MQ
#include "BoostSerializer.h"

/// FairRoot - Tutorial7 
#include "tuto7ProcessorFunctions.h"
#include "DigiToHitTask.h"
#include "MyDigi.h"
#include "MyHit.h"

using namespace std;
/// ////////////////////////////////////////////////////////////////////////
// payload and policy type definitions
typedef MyDigi              TDigi; 
typedef MyHit               THit;

// build policy classes
typedef BoostDeSerializer<TDigi>    TInputPolicy;   // deserialize digi
typedef BoostSerializer<THit>       TOutputPolicy;  // serialize Hit
typedef DigiToHitTask<TDigi,THit>   TTaskPolicy;    // process deserialized digi and fill Hit

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

int main(int argc, char** argv)
{
    try
    {
        s_catch_signals();
        if(runProcessor<TProcessor,BoostProcessorPolicyFlag>(processor,argc,argv))
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

