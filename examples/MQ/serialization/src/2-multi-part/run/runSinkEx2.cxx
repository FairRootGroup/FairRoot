
// FairRoot - FairMQ
#include "runSimpleMQStateMachine.h"

// FairRoot - Tutorial7
#include "FairMQProgOptions.h"
#include "MyHit.h"

#include "Ex2Sink.h"





int main(int argc, char** argv)
{
    try
    {
        FairMQProgOptions config;
        namespace po = boost::program_options;
        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            ("output-file", po::value<std::string>(), "Path to the input file");

        config.AddToCmdLineOptions(sink_options);

        if (config.ParseAll(argc, argv))
            return 1;

        std::string filename = config.GetValue<std::string>("output-file");

        Ex2Sink sink;
        sink.SetFileName(filename);
        runStateMachine(sink, config);

        
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
