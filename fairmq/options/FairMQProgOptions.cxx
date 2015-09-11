/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairMQProgOptions.cxx
 * Author: winckler
 * 
 * Created on March 11, 2015, 10:20 PM
 */

#include "FairMQProgOptions.h"
#include <algorithm>

using namespace std;

FairMQProgOptions::FairMQProgOptions()
    : FairProgOptions()
    , fMQParserOptions("MQ-Device parser options")
    , fMQOptionsInCmd("MQ-Device options")
    , fMQOptionsInCfg("MQ-Device options")
    , fMQtree()
    , fFairMQMap()
{
}

FairMQProgOptions::~FairMQProgOptions()
{
}

int FairMQProgOptions::ParseAll(const int argc, char** argv, bool allowUnregistered)
{
    // init description
    InitOptionDescription();
    // parse command line options
    if (ParseCmdLine(argc, argv, fCmdLineOptions, fVarMap, allowUnregistered))
    {
        return 1;
    }

    // if txt/INI configuration file enabled then parse it as well
    if (fUseConfigFile)
    {
        // check if file exist
        if (fs::exists(fConfigFile))
        {
            if (ParseCfgFile(fConfigFile.string(), fConfigFileOptions, fVarMap, allowUnregistered))
            {
                return 1;
            }
        }
        else
        {
            LOG(ERROR) << "config file '" << fConfigFile << "' not found";
            return 1;
        }
    }

    // set log level before printing (default is 0 = DEBUG level)
    std::string verbose=GetValue<std::string>("verbose");
    //SET_LOG_LEVEL(DEBUG);
    if (fSeverityMap.count(verbose))
    {
        set_global_log_level(log_op::operation::GREATER_EQ_THAN,fSeverityMap.at(verbose));
    }
    else
    {
        LOG(ERROR)<<" verbosity level '"<<verbose<<"' unknown, it will be set to INFO";
        set_global_log_level(log_op::operation::GREATER_EQ_THAN,fSeverityMap.at("RESULTS"));
    }

    PrintOptions();

    // check if one of required MQ config option is there  
    auto parserOption_shptr = fMQParserOptions.options();
    bool optionExists = false;
    vector<string> MQParserKeys;
    for (const auto& p : parserOption_shptr)
    {
        MQParserKeys.push_back(p->canonical_display_name());
        if (fVarMap.count(p->canonical_display_name()))
        {
            optionExists = true;
            break;
        }
    }

    if (!optionExists)
    {
        LOG(ERROR) << "Required option to configure the MQ device is not there.";
        LOG(ERROR) << "Please provide the value of one of the following key:";
        for (const auto& p : MQParserKeys)
        {
            LOG(ERROR) << p;
        }
        return 1;
    }

    return 0;
}

int FairMQProgOptions::NotifySwitchOption()
{
    if (fVarMap.count("help"))
    {
        LOG(INFO) << "***** FAIRMQ Program Options ***** \n" << fVisibleOptions;
        return 1;
    }

    if (fVarMap.count("version")) 
    {
        LOG(INFO) << "Beta version 0.1\n";
        return 1;
    }

    return 0;
}

void FairMQProgOptions::InitOptionDescription()
{
    // Id required in command line if config txt file not enabled
    if (fUseConfigFile)
    {
        fMQOptionsInCmd.add_options()
            ("id",             po::value<string>(),                       "Device ID (required argument).")
            ("io-threads",     po::value<int>()->default_value(1),        "Number of I/O threads.");

        fMQOptionsInCfg.add_options()
            ("id",             po::value<string>()->required(),           "Device ID (required argument).")
            ("io-threads",     po::value<int>()->default_value(1),        "Number of I/O threads.");
    }
    else
    {
        fMQOptionsInCmd.add_options()
            ("id",             po::value<string>()->required(),           "Device ID (required argument)")
            ("io-threads",     po::value<int>()->default_value(1),        "Number of I/O threads");
    }

    fMQParserOptions.add_options()
        ("config-xml-string",  po::value<vector<string>>()->multitoken(), "XML input as command line string.")
        ("config-xml-file",    po::value<string>(),                       "XML input as file.")
        ("config-json-string", po::value<vector<string>>()->multitoken(), "JSON input as command line string.")
        ("config-json-file",   po::value<string>(),                       "JSON input as file.");

    AddToCmdLineOptions(fGenericDesc);
    AddToCmdLineOptions(fMQOptionsInCmd);
    AddToCmdLineOptions(fMQParserOptions);

    if (fUseConfigFile)
    {
        AddToCfgFileOptions(fMQOptionsInCfg,false);
        AddToCfgFileOptions(fMQParserOptions,false);
    }
}
