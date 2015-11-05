/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runSamplerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"

// FairRoot - Base/MQ
#include "FairMQLmdSampler.h"


// ////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    try
    {
        namespace po = boost::program_options;
        FairMQProgOptions config;
        
        // sampler-specific commandline configuration
        std::string filename;
        po::options_description sampler_options("Sampler options");
        sampler_options.add_options()
            ("input-file-name", po::value<std::string>(&filename), "Path to the input file")
        ;

        short type;
        short subType;
        short procId;
        short subCrate;
        short control;
        std::string chanName;
        // INI-FILE CONFIGURATION (in FairRoot/example/MQ/LmdSampler/options/LmdHeaderConfig.INI)
        po::options_description lmd_header_def("Lmd-header definition");
        lmd_header_def.add_options()
            ("LmdHeader.Tutorial8.chanName",    po::value<std::string>(&chanName),  "MQ-channel name for this sub-event")
            ("LmdHeader.Tutorial8.type",        po::value<short>(&type),            "sub-event type")
            ("LmdHeader.Tutorial8.subType",     po::value<short>(&subType),         "sub-event subType")
            ("LmdHeader.Tutorial8.procId",      po::value<short>(&procId),          "sub-event procId")
            ("LmdHeader.Tutorial8.subCrate",    po::value<short>(&subCrate),        "sub-event subCrate")
            ("LmdHeader.Tutorial8.control",     po::value<short>(&control),         "sub-event control")
        ;

        config.AddToCmdLineOptions(sampler_options);
        config.AddToCfgFileOptions(lmd_header_def);

        // parse command line and INI file arguments
        if (config.ParseAll(argc, argv))
        {
            return 1;
        }

        FairMQLmdSampler sampler;
        sampler.AddFile(filename);
        // combination of sub-event header value = one special channel
        // this channel MUST be defined in the json file for the MQ configuration
        sampler.AddSubEvtKey(type, subType, procId, subCrate, control, chanName);
        runStateMachine(sampler, config);



    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}
