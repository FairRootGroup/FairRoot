
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "runSimpleMQStateMachine.h"
#include "PixelFindHits.h"
#include "PixelFindTracks.h"
#include "PixelFitTracks.h"

// 9-PixelDetector example
#include "FairMQEx9TaskProcessor.h"

using HitFinder   = FairMQEx9TaskProcessor<PixelFindHits>;
using TrackFinder = FairMQEx9TaskProcessor<PixelFindTracks>;
using TrackFitter = FairMQEx9TaskProcessor<PixelFitTracks>;

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    try
    {
        std::string taskname;
	std::string keepdata;
	std::string inChannel;
	std::string outChannel;
	std::string parChannel;

        namespace po = boost::program_options;
        po::options_description processor_options("Processor options");
        processor_options.add_options()
	  ("task-name",   po::value<std::string>(&taskname)->required()                  ,  "Name of task to run")
	  ("keep-data",   po::value<std::string>(&keepdata)                              ,  "Name of data to keep in stream")
	  ("in-channel",  po::value<std::string>(&inChannel)->default_value("data-in")   , "input channel name")
	  ("out-channel", po::value<std::string>(&outChannel)->default_value("data-out") , "output channel name")
	  ("par-channel", po::value<std::string>(&parChannel)->default_value("param")    , "param channel name");
	
        FairMQProgOptions config;
        config.AddToCmdLineOptions(processor_options);
	
        config.ParseAll(argc, argv);
	
	if      ( strcmp(taskname.c_str(),"PixelFindHits") == 0 ) {
	  HitFinder processor;
	  processor.SetDataToKeep(keepdata);
	  processor.SetInputChannelName (inChannel);
	  processor.SetOutputChannelName(outChannel);
	  processor.SetParamChannelName (parChannel);
	  runStateMachine(processor, config);
	}
	else if ( strcmp(taskname.c_str(),"PixelFindTracks") == 0 ) {
	  TrackFinder processor;
	  processor.SetDataToKeep(keepdata);
	  processor.SetInputChannelName (inChannel);
	  processor.SetOutputChannelName(outChannel);
	  processor.SetParamChannelName (parChannel);
	  runStateMachine(processor, config);
	}
	else if ( strcmp(taskname.c_str(),"PixelFitTracks") == 0 ) {
	  TrackFitter processor;
	  processor.SetDataToKeep(keepdata);
	  processor.SetInputChannelName (inChannel);
	  processor.SetOutputChannelName(outChannel);
	  processor.SetParamChannelName (parChannel);
	  runStateMachine(processor, config);
	}
	else {
	  LOG(INFO) << "TASK \"" << taskname << "\" UNKNOWN!!!";
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
