
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "GenericProcessor.h"
#include "runSimpleMQStateMachine.h"
#include "BoostSerializer.h"
#include "RootSerializer.h"


// 9-PixelDetector example
#include "FairMQEx9TaskProcessor.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        int runid;
        std::string diginame;
        namespace po = boost::program_options;
        po::options_description processor_options("Processor options");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(processor_options);

        if (config.ParseAll(argc, argv))
            return 1;

        FairMQEx9TaskProcessor processor;
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
