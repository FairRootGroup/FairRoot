
/// std
#include <csignal>

/// FairRoot - FairMQ - base/MQ
#include "FairMQLogger.h"
#include "FairMQDDSTools.h"
#include "FairMQProgOptions.h"

#include "dds_intercom.h" // DDS

// 9-PixelDetector example
#include "FairMQEx9FileSink.h"

using namespace dds::intercom_api;

// ////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  FairMQEx9FileSink fileSink;
  fileSink.CatchSignals();

  FairMQProgOptions config;

  try
    {

      std::string interfaceName; // name of the network interface to use for communication.
      std::string filename;
      std::vector<std::string> classname;
      std::vector<std::string> branchname;
      
      namespace po = boost::program_options;
      po::options_description fileSink_options("FileSink options");
      fileSink_options.add_options()
	("file-name",   po::value<std::string>             (&filename)  , "Path to the output file")
	("class-name",  po::value<std::vector<std::string>>(&classname) , "class name")
	("branch-name", po::value<std::vector<std::string>>(&branchname), "branch name");
      config.AddToCmdLineOptions(fileSink_options);
      config.ParseAll(argc, argv);

      fileSink.SetProperty(FairMQEx9FileSink::OutputFileName,filename);

      if ( classname.size() != branchname.size() ) {
	LOG(ERROR) << "The classname size (" << classname.size() << ") and branchname size (" << branchname.size() << ") MISMATCH!!!";
      }
      
      fileSink.AddOutputBranch("FairEventHeader","EventHeader.");
      for ( unsigned int ielem = 0 ; ielem < classname.size() ; ielem++ ) {
	fileSink.AddOutputBranch(classname.at(ielem),branchname.at(ielem));
      }
      
      fileSink.SetInputChannelName ("data2");

      fileSink.SetConfig(config);
      
      fileSink.ChangeState("INIT_DEVICE");
      HandleConfigViaDDS(fileSink);
      fileSink.WaitForEndOfState("INIT_DEVICE");
      
      fileSink.ChangeState("INIT_TASK");
      fileSink.WaitForEndOfState("INIT_TASK");
      
      fileSink.ChangeState("RUN");

      runDDSStateHandler(fileSink);

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
