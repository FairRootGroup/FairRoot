
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"


// 9-PixelDetector example
#include "FairMQEx9Merger.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        std::string filename;
	std::vector<std::string> classname;
	std::vector<std::string> branchname;

        namespace po = boost::program_options;
        po::options_description merger_options("Merger options");
        merger_options.add_options()
	  ("file-name",   po::value<std::string>             (&filename)  , "Path to the output file")
	  ("class-name",  po::value<std::vector<std::string>>(&classname) , "class name")
	  ("branch-name", po::value<std::vector<std::string>>(&branchname), "branch name");
	

        FairMQProgOptions config;
        config.AddToCmdLineOptions(merger_options);

        if (config.ParseAll(argc, argv))
            return 1;

        FairMQEx9Merger merger;
	
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
