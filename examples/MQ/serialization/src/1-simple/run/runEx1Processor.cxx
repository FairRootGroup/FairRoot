
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"

#include "runSimpleMQStateMachine.h"

#include "MyDigi.h"
#include "MyHit.h"

#include "Ex1Processor.h"


int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        // parse command line
        config.ParseAll(argc, argv);

        Ex1Processor processor;
        runStateMachine(processor, config);

    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}