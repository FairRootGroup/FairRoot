/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   runMBSUnpacker.cxx
 * Author: winckler
 *
 * Created on January 15, 2015, 1:57 PM
 */

#include "FairMQLogger.h"
#include "FairMQProgOptions.h"
#include "runSimpleMQStateMachine.h"

#include "FairMQUnpacker.h"
#include "FairMBSUnpacker.h"
#include "FairMBSRawItem.h"

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        short type;
        short subType;
        short procId;
        short subCrate;
        short control;
        std::string chanName;

        po::options_description unpacker_options("Unpacker options");
        unpacker_options.add_options()
            ("lmd-type",      po::value<short>(&type),           "sub-event type")
            ("lmd-sub-type",  po::value<short>(&subType),        "sub-event subType")
            ("lmd-proc-id",   po::value<short>(&procId),         "sub-event procId")
            ("lmd-sub-crate", po::value<short>(&subCrate),       "sub-event subCrate")
            ("lmd-control",   po::value<short>(&control),        "sub-event control")
            ("lmd-chan-name", po::value<std::string>(&chanName), "MQ-channel name for this sub-event");

        FairMQProgOptions config;
        config.AddToCmdLineOptions(unpacker_options);
        config.ParseAll(argc, argv);

        FairMQUnpacker<FairMBSUnpacker> unpacker;
        // combination of sub-event header value = one special channel
        // this channel MUST be defined in the json file for the MQ configuration
        unpacker.AddSubEvtKey(type, subType, procId, subCrate, control, chanName);

        runStateMachine(unpacker, config);
    }
    catch (std::exception& e)
    {
        LOG(ERROR)  << "Unhandled Exception reached the top of main: "  << e.what() << ", application will now exit";
        return 1;
    }

    return 0;
}

