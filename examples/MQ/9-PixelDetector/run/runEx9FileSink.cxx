
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"


// 9-PixelDetector example
#include "FairMQEx9FileSink.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        std::string filename;
	std::vector<std::string> classname;
	std::vector<std::string> branchname;

        namespace po = boost::program_options;
        po::options_description fileSink_options("FileSink options");
        fileSink_options.add_options()
	  ("file-name",   po::value<std::string>             (&filename)  , "Path to the output file")
	  ("class-name",  po::value<std::vector<std::string>>(&classname) , "class name")
	  ("branch-name", po::value<std::vector<std::string>>(&branchname), "branch name");
	

        FairMQProgOptions config;
        config.AddToCmdLineOptions(fileSink_options);

        if (config.ParseAll(argc, argv))
            return 1;

        FairMQEx9FileSink fileSink;
        fileSink.SetProperty(FairMQEx9FileSink::OutputFileName,filename);

	if ( classname.size() != branchname.size() ) {
	  LOG(ERROR) << "The classname size (" << classname.size() << ") and branchname size (" << branchname.size() << ") MISMATCH!!!";
	}

	fileSink.AddOutputBranch("FairEventHeader","EventHeader.");
	for ( unsigned int ielem = 0 ; ielem < classname.size() ; ielem++ ) {
	  fileSink.AddOutputBranch(classname.at(ielem),branchname.at(ielem));
	}
	
        runStateMachine(fileSink, config);


    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
