/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairSimConfig.h"

#include "FairLogger.h"

#include <iostream>
#include <vector>

using std::string;
using std::vector;

FairSimConfig::FairSimConfig()
    : fDescription("Options")
    , fHelp(false)
    , fnEvents(1)
    , fEngine("TGeant3")
    , fMultiThreaded(false)
    , fOutputFile("sim.root")
    , fParameterFile("par.root")
    , fRandomSeed(0)
{
    // clang-format off
    fDescription.add_options()
        ("help",                                        "Print this message")
        ("nevents",        po::value<int>(),            "Number of events to simulate")
        ("engine",         po::value<vector<string>>(), "Monte Carlo engine")
        ("multi-threaded",                              "Geant4 multi threaded")
        ("output-file",    po::value<vector<string>>(), "Output file")
        ("parameter-file", po::value<vector<string>>(), "Parameter file")
        ("random-seed",    po::value<int>(),            "Seed for the random number generator");
    // clang-format on
}

FairSimConfig::~FairSimConfig() {}

int FairSimConfig::ParseCommandLine(int argc, char* argv[])
{
    try {
        po::store(po::parse_command_line(argc, argv, fDescription), fMap);

        po::notify(fMap);
    } catch (po::error& e) {
        LOG(error) << e.what();
        fHelp = true;
        return 0;
    }

    if (fMap.count("help")) {
        fHelp = true;
        return 0;
    }
    if (fMap.count("nevents")) {
        fnEvents = fMap["nevents"].as<int>();
    }
    if (fMap.count("engine")) {
        fEngine = fMap["engine"].as<vector<string>>().at(0);
        if (!GetEngine().EqualTo("TGeant3") && !GetEngine().EqualTo("TGeant4")) {
            LOG(error) << "Option engine can be either TGeant3 or TGeant4";
            return 1;
        }
    }
    if (fMap.count("output-file")) {
        fOutputFile = fMap["output-file"].as<vector<string>>().at(0);
    }
    if (fMap.count("parameter-file")) {
        fParameterFile = fMap["parameter-file"].as<vector<string>>().at(0);
    }
    if (fMap.count("random-seed")) {
        fRandomSeed = fMap["random-seed"].as<int>();
    }
    if (fMap.count("multi-threaded")) {
        LOG(info) << "YUPYUPYUP";
        fMultiThreaded = true;
    }
    return 0;
}

void FairSimConfig::PrintHelpMessage()
{
    std::cout << fDescription << std::endl;
}
