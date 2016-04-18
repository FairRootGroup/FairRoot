
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"


// 9-PixelDetector example
#include "FairMQEx9Sampler.h"

#include "PixelDigiSource.h"
#include "PixelDigiBinSource.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        std::vector<std::string> filename;
	std::vector<std::string> branchname;
	int64_t     maxindex;
	std::string samplerType;

        namespace po = boost::program_options;
        po::options_description sampler_options("Sampler options");
        sampler_options.add_options()
	  ("file-name",    po::value<std::vector<std::string>>(&filename)                                    , "Path to the input file")
	  ("max-index",    po::value<int64_t>                 (&maxindex)   ->default_value(-1)              , "number of events to read")
	  ("branch-name",  po::value<std::vector<std::string>>(&branchname) ->required()                     , "branch name")
	  ("sampler-type", po::value<std::string>             (&samplerType)->default_value("FairFileSource"), "FairSource type");

	FairMQProgOptions config;
	config.AddToCmdLineOptions(sampler_options);
	
	if (config.ParseAll(argc, argv))           
	  return 1;
	
	LOG(INFO) << "Using source \"" << samplerType << "\"";

	if ( strcmp(samplerType.c_str(),"FairFileSource") == 0 ) {
	  FairMQEx9Sampler sampler;
	  
	  for ( unsigned int ielem = 0 ; ielem < filename.size() ; ielem++ ) {
 	    sampler.AddInputFileName(filename.at(ielem));	  
	  }
	  
	  sampler.SetMaxIndex(maxindex);

	  for ( unsigned int ielem = 0 ; ielem < branchname.size() ; ielem++ ) {
 	    sampler.AddInputBranchName(branchname.at(ielem));	  
	  }

	  sampler.AddInputBranchName("EventHeader.");
	  runStateMachine(sampler, config);
	}
	else if ( strcmp(samplerType.c_str(),"PixelDigiSource") == 0 ) {
	  FairMQEx9Sampler sampler;
	  
	  if ( filename.size() >= 1 ) {
	    PixelDigiSource* digiSource = new PixelDigiSource(filename.at(0));
	    sampler.SetSource(digiSource);
	  }
	  
	  sampler.SetMaxIndex(maxindex);

	  // for now only supporting reading PixelDigis
	  sampler.AddInputBranchName(branchname.at(0));
	  sampler.AddInputBranchName("EventHeader.");
	  runStateMachine(sampler, config);
	}
	else if ( strcmp(samplerType.c_str(),"PixelDigiBinSource") == 0 ) {
	  FairMQEx9Sampler sampler;
	  
	  if ( filename.size() >= 1 ) {
	    PixelDigiBinSource* digiSource = new PixelDigiBinSource(filename.at(0));
	    sampler.SetSource(digiSource);
	  }
	  
	  sampler.SetMaxIndex(maxindex);

	  // for now only supporting reading PixelDigis
	  sampler.AddInputBranchName(branchname.at(0));
	  sampler.AddInputBranchName("EventHeader.");
	  runStateMachine(sampler, config);
	}
	else {
	  LOG(ERROR) << "Sampler \"" << samplerType 
		     << "\" unknown! Set it to \"FairFileSource\" or \"PixelDigiSource\" or \"PixelDigiBinSource\"";
	  return 1;
	}
	

    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
