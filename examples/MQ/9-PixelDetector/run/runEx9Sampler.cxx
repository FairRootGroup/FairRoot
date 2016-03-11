
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"


// 9-PixelDetector example
#include "FairMQEx9Sampler.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        std::string filename;
        std::string branchname;
	int64_t     maxindex;

        namespace po = boost::program_options;
        po::options_description sampler_options("Sampler options");
        sampler_options.add_options()
	  ("file-name",   po::value<std::string>(&filename)                     , "Path to the input file")
	  ("max-index",   po::value<int64_t>    (&maxindex)  ->default_value(-1), "number of events to read")
	  ("branch-name", po::value<std::string>(&branchname)                   , "branch name");
	
	
        FairMQProgOptions config;
        config.AddToCmdLineOptions(sampler_options);

        if (config.ParseAll(argc, argv))
            return 1;

        FairMQEx9Sampler sampler;
        sampler.SetProperty(FairMQEx9Sampler::InputFileName,filename);

	sampler.SetMaxIndex(maxindex);

	sampler.AddInputBranchName(branchname);

	sampler.AddInputBranchName("EventHeader.");

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
