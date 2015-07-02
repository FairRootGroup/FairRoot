/* 
 * File:   runMergerT7.cxx
 * Author: winckler
 *
 * Created on July 7, 2015, 4:28 PM
 */

/// std
#include <csignal>

/// FairRoot - FairMQ
#include "FairMQMerger.h"

/// FairRoot - Tutorial7
#include "runGenericDevices.h"

FairMQMerger merger;

static void s_signal_handler(int signal)
{
    LOG(INFO) << "Caught signal " << signal;

    merger.ChangeState(FairMQMerger::END);

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
        FairMQProgOptions config;
        config.UseConfigFile();
        if (config.ParseAll(argc, argv,true))
        {
            return 1;
        }

        runStateMachine(merger, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }
    
    return 0;
}
