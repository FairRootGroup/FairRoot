/*********************************************************************************
 *  Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                               *
 *              This software is distributed under the terms of the              *
 *              GNU Lesser General Public Licence (LGPL) version 3,              *
 *                  copied verbatim in the file "LICENSE"                        *
 *********************************************************************************/
#include "FairSimConfig.h"

#include "FairLogger.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <vector>

using namespace std;

static auto makeDescription()
{
    po::options_description description{"Options"};
    // clang-format off
    description.add_options()
        ("help",                                        "Print this message")
        ("nevents",        po::value<int>(),            "Number of events to simulate")
        ("engine",         po::value<vector<string>>(), "Monte Carlo engine")
        ("multi-threaded",                              "Geant4 multi threaded")
        ("output-file",    po::value<vector<string>>(), "Output file")
        ("parameter-file", po::value<vector<string>>(), "Parameter file")
        ("random-seed",    po::value<int>(),            "Seed for the random number generator");
    // clang-format on
    return description;
}

int FairSimConfig::ParseCommandLine(int argc, char* argv[])
{
    po::variables_map map;
    auto description = makeDescription();
    try {
        po::store(po::parse_command_line(argc, argv, description), map);

        po::notify(map);
    } catch (po::error& e) {
        LOG(error) << e.what();
        fHelp = true;
        return 0;
    }

    if (map.count("help")) {
        fHelp = true;
        return 0;
    }
    if (map.count("nevents")) {
        fnEvents = map["nevents"].as<int>();
    }
    if (map.count("engine")) {
        fEngine = map["engine"].as<vector<string>>().at(0);
        if (!GetEngine().EqualTo("TGeant3") && !GetEngine().EqualTo("TGeant4")) {
            LOG(error) << "Option engine can be either TGeant3 or TGeant4";
            return 1;
        }
    }
    if (map.count("output-file")) {
        fOutputFile = map["output-file"].as<vector<string>>().at(0);
    }
    if (map.count("parameter-file")) {
        fParameterFile = map["parameter-file"].as<vector<string>>().at(0);
    }
    if (map.count("random-seed")) {
        fRandomSeed = map["random-seed"].as<int>();
    }
    if (map.count("multi-threaded")) {
        LOG(info) << "YUPYUPYUP";
        fMultiThreaded = true;
    }
    return 0;
}

void FairSimConfig::PrintHelpMessage()
{
    auto description = makeDescription();
    std::cout << description << std::endl;
}
