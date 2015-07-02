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
#include <csignal>

/// FairRoot - FairMQ
#include "GenericFileSink.h"

/// FairRoot - base/MQ
#include "RootSerializer.h"
#include "RootOutFileManager.h"

/// FairRoot - Tutorial7
#include "tuto7FileSinkFunctions.h"
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
    LOG(INFO) << "Caught signal " << signal;

    filesink.ChangeState(TSink::END);

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
        if(runFileSink(filesink,argc,argv))
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
