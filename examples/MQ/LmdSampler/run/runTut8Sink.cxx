
// FairRoot - FairMQ
#include "GenericFileSink.h"
#include "runSimpleMQStateMachine.h"

// FairRoot - base/MQ
#include "RootSerializer.h"
#include "RootOutFileManager.h"

// FairRoot - Tutorial8
#include "FairTut8RawItem.h"


typedef GenericFileSink<RootDefaultInputPolicy, RootOutFileManager<FairTut8RawItem>>  TSink;


int main(int argc, char** argv)
{
    try
    {

        namespace po = boost::program_options;
        FairMQProgOptions config;

        std::string filename;
        std::string treename;
        std::string branchname;
        std::string hitname;
        std::string fileoption;

        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            // TODO : make the semantic required for at least one source (and not both cfg & cmd)
            //("input.file.name",         value<std::string>(&filename)->required(),                       "Path to the input file")
            ("output-file-name",         po::value<std::string>(&filename),                                     "Path to the input file")
            ("output-file-tree",         po::value<std::string>(&treename)->default_value("tut8tree"),          "Name of the output tree")
            ("output-file-branch",       po::value<std::string>(&branchname)->default_value("FairTut8RawItem"), "Name of the output Branch")
            ("output-file-option",       po::value<std::string>(&fileoption)->default_value("RECREATE"),        "Root file option : UPDATE, RECREATE etc.")
            ("hit-classname",            po::value<std::string>(&hitname)->default_value("FairTut8RawItem"),    "Hit class name for initializing TClonesArray")
        ;

        config.AddToCmdLineOptions(sink_options);

        if (config.ParseAll(argc, argv, true))
        {
            return 1;
        }

        TSink sink;
        // call function member from storage policy
        sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
        // call function member from deserialization policy
        sink.InitInputData(hitname.c_str());
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
