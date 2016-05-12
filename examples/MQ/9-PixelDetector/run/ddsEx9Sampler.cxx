
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "FairMQDDSTools.h"
#include "FairMQProgOptions.h"

#include "dds_intercom.h" // DDS

// 9-PixelDetector example
#include "FairMQEx9Sampler.h"

using namespace dds::intercom_api;

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  
  FairMQEx9Sampler sampler;
  sampler.CatchSignals();
  
  FairMQProgOptions config;
  
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
      
      config.AddToCmdLineOptions(sampler_options);
      config.ParseAll(argc, argv);

      for ( unsigned int ielem = 0 ; ielem < filename.size() ; ielem++ ) {
	sampler.AddInputFileName(filename.at(ielem));	  
      }
      sampler.SetMaxIndex(maxindex);
      for ( unsigned int ielem = 0 ; ielem < branchname.size() ; ielem++ ) {
	sampler.AddInputBranchName(branchname.at(ielem));	  
      }
      sampler.AddInputBranchName("EventHeader.");

      sampler.SetOutputChannelName("data1");
      
      sampler.SetConfig(config);
      
      sampler.ChangeState("INIT_DEVICE");
      HandleConfigViaDDS(sampler);
      sampler.WaitForEndOfState("INIT_DEVICE");
      
      sampler.ChangeState("INIT_TASK");
      sampler.WaitForEndOfState("INIT_TASK");
      
      sampler.ChangeState("RUN");

      runDDSStateHandler(sampler);
    }
  catch (exception& e)
    {
      LOG(ERROR) << e.what();
      LOG(INFO) << "Command line options are the following: ";
      config.PrintHelp();
      return 1;
    }
  
  return 0;
}

