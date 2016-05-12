/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "FairMQDDSTools.h"
#include "FairMQProgOptions.h"
#include "FairMQParser.h"

#include "dds_intercom.h" // DDS

#include "ParameterMQServer.h"
#include "TApplication.h"

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  ParameterMQServer server;
  server.CatchSignals();
  
  FairMQProgOptions config;
  
    try
    {
        std::string interfaceName; // name of the network interface to use for communication.
        string firstInputName;
        string firstInputType;
        string secondInputName;
        string secondInputType;
        string outputName;
        string outputType;
	string channelName;

        namespace po = boost::program_options;
        po::options_description serverOptions("Parameter MQ Server options");
        serverOptions.add_options()
	  ("first-input-name", po::value<string>(&firstInputName)->default_value("first_input.root"), "First input file name")
	  ("first-input-type", po::value<string>(&firstInputType)->default_value("ROOT"), "First input file type (ROOT/ASCII)")
	  ("second-input-name", po::value<string>(&secondInputName)->default_value(""), "Second input file name")
	  ("second-input-type", po::value<string>(&secondInputType)->default_value("ROOT"), "Second input file type (ROOT/ASCII)")
	  ("output-name", po::value<string>(&outputName)->default_value(""), "Output file name")
	  ("output-type", po::value<string>(&outputType)->default_value("ROOT"), "Output file type")
	  ("channel-name", po::value<string>(&channelName)->default_value("param"), "Parameter channel name");
	
        config.AddToCmdLineOptions(serverOptions);
	
	
      config.ParseAll(argc, argv);

      server.SetConfig(config);
      
      server.SetProperty(ParameterMQServer::FirstInputName, firstInputName);
      server.SetProperty(ParameterMQServer::FirstInputType, firstInputType);
      server.SetProperty(ParameterMQServer::SecondInputName, secondInputName);
      server.SetProperty(ParameterMQServer::SecondInputType, secondInputType);
      server.SetProperty(ParameterMQServer::OutputName, outputName);
      server.SetProperty(ParameterMQServer::OutputType, outputType);
      server.SetProperty(ParameterMQServer::ChannelName,channelName);

      server.ChangeState("INIT_DEVICE");
      HandleConfigViaDDS(server);
      server.WaitForEndOfState("INIT_DEVICE");
      
      server.ChangeState("INIT_TASK");
      server.WaitForEndOfState("INIT_TASK");
      
      server.ChangeState("RUN");

      runDDSStateHandler(server);
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
