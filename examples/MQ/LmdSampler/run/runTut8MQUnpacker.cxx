/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runtut8UnpackerRoot.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

// FairRoot - FairMQ
#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"

// FairRoot - Base/MQ
#include "FairMQUnpacker.h"

// FairRoot - MQ/lmdSampler Tutorial 
#include "FairTut8Unpacker.h"

// FairRoot - Tutorial 8
#include "FairTut8RawItem.h"

// ////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    try
    {
        namespace po = boost::program_options;
        FairMQProgOptions config;

        short type;
        short subType;
        short procId;
        short subCrate;
        short control;
        std::string chanName;
        // INI-FILE CONFIGURATION
        po::options_description lmd_header_def("Lmd-header definition");
        lmd_header_def.add_options()
            ("LmdHeader.Tutorial8.chanName",    po::value<std::string>(&chanName),  "MQ-channel name for this sub-event")
            ("LmdHeader.Tutorial8.type",        po::value<short>(&type),            "sub-event type")
            ("LmdHeader.Tutorial8.subType",     po::value<short>(&subType),         "sub-event subType")
            ("LmdHeader.Tutorial8.procId",      po::value<short>(&procId),          "sub-event procId")
            ("LmdHeader.Tutorial8.subCrate",    po::value<short>(&subCrate),        "sub-event subCrate")
            ("LmdHeader.Tutorial8.control",     po::value<short>(&control),         "sub-event control")
        ;

        config.AddToCfgFileOptions(lmd_header_def);

        if (config.ParseAll(argc, argv, true))
        {
            return 1;
        }

        FairMQUnpacker<FairTut8Unpacker> unpacker;
        // combination of sub-event header value = one special channel
        // this channel MUST be defined in the json file for the MQ configuration
        unpacker.AddSubEvtKey(type, subType, procId, subCrate, control, chanName);
        runStateMachine(unpacker, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: " 
                    << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}

