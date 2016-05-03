
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "FairMQDDSTools.h"
#include "FairMQProgOptions.h"

#include "dds_intercom.h" // DDS

// 9-PixelDetector example
#include "FairMQEx9TaskProcessor.h"

#include "PixelFindHits.h"
#include "PixelFindTracks.h"
#include "PixelFitTracks.h"

using HitFinder   = FairMQEx9TaskProcessor<PixelFindHits>;

using namespace dds::intercom_api;

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  
  HitFinder processor;
  processor.CatchSignals();

  FairMQProgOptions config;
  
  try 
    {
      std::string interfaceName; // name of the network interface to use for communication.
      std::string taskname;
      std::string keepdata;
      
      namespace po = boost::program_options;
      po::options_description processor_options("Processor options");
      processor_options.add_options()
	("task-name",   po::value<std::string>(&taskname)->required(),  "Name of task to run")
	("keep-data",   po::value<std::string>(&keepdata)            ,  "Name of data to keep in stream");
      
      config.AddToCmdLineOptions(processor_options);
      
      if (config.ParseAll(argc, argv)) 
	{
	  return 1;
	}
      
      processor.SetDataToKeep(keepdata);

      processor.SetInputChannelName ("data1");
      processor.SetOutputChannelName("data2");
      processor.SetParamChannelName ("param");

      processor.SetConfig(config);
      
      processor.ChangeState("INIT_DEVICE");
      HandleConfigViaDDS(processor);
      processor.WaitForEndOfState("INIT_DEVICE");
      
      processor.ChangeState("INIT_TASK");
      processor.WaitForEndOfState("INIT_TASK");

      processor.ChangeState("RUN");
      
      runDDSStateHandler(processor);
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
