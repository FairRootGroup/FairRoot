/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "BaseMQFileSink.h"
#include "runSimpleMQStateMachine.h"

#include "RootSerializer.h"
#include "RootOutFileManager.h"

#include "FairMBSRawItem.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        std::string filename;
        std::string treename;
        std::string branchname;
        std::string hitname;
        std::string fileoption;

        po::options_description sink_options("File Sink options");
        sink_options.add_options()
            ("output-file-name",   po::value<std::string>(&filename),                                    "Path to the input file")
            ("output-file-tree",   po::value<std::string>(&treename)->default_value("mbstree"),          "Name of the output tree")
            ("output-file-branch", po::value<std::string>(&branchname)->default_value("FairMBSRawItem"), "Name of the output Branch")
            ("output-file-option", po::value<std::string>(&fileoption)->default_value("RECREATE"),       "Root file option : UPDATE, RECREATE etc.")
            ("hit-classname",      po::value<std::string>(&hitname)->default_value("FairMBSRawItem"),    "Hit class name for initializing TClonesArray");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(sink_options);
        config.ParseAll(argc, argv, true);

        BaseMQFileSink<RootDefaultInputPolicy, RootOutFileManager<FairMBSRawItem>> sink;
        // call function member from storage policy
        sink.SetFileProperties(filename, treename, branchname, hitname, fileoption, true);
        // call function member from deserialization policy
        sink.InitInputData(hitname.c_str());

        runStateMachine(sink, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: "  << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
