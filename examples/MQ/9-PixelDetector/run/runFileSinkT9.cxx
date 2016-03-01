
// FairRoot - FairMQ
#include "GenericFileSink.h"
#include "runSimpleMQStateMachine.h"

// FairRoot - base/MQ
#include "RootOutFileManager.h"
#include "RootSerializer.h"

// temp to compile
#include "PixelHit.h"

typedef GenericFileSink<RootDeSerializer, RootOutFileManager<PixelHit>>                         TSinkRoot;

int main(int argc, char** argv)
{
    try
    {
        

        std::string filename;
        std::string treename;
        std::string branchname;
        std::string fileoption;
        std::string hitname;

        namespace po = boost::program_options;

        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            ("output-name",         po::value<std::string>(&filename),                                 "Path to the input file")
            ("output-tree",         po::value<std::string>(&treename)->default_value("cbmsim"),        "Name of the output tree")
            ("output-branch",       po::value<std::string>(&branchname)->default_value("PixelHit"),       "Name of the output Branch")
            ("output-file-option",       po::value<std::string>(&fileoption)->default_value("RECREATE"),    "Root file option : UPDATE, RECREATE etc.")
            ("hit-name",            po::value<std::string>(&hitname)->default_value("PixelHit"),          "Hit class name for initializing TClonesArray")
        ;

        FairMQProgOptions config;

        config.AddToCmdLineOptions(sink_options);

        if (config.ParseAll(argc, argv))
        {
            return 1;
        }

        TSinkRoot sink;
        // call function member from storage policy
        sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
        // call function member from deserialization policy
        sink.InitInputContainer(hitname);
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
