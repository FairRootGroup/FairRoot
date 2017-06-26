/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairProgOptions.cxx
 * Author: winckler
 * 
 * Created on March 11, 2015, 5:38 PM
 */

#include "FairProgOptions.h"

using namespace std;

/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor
FairProgOptions::FairProgOptions() :
                        fVarMap(),
                        fGenericDesc("Generic options description"),
                        fConfigDesc("Configuration options description"),
                        fEnvironmentDesc("Environment variables"),
                        fHiddenDesc("Hidden options description"),
                        fCmdLineOptions("Command line options"),
                        fConfigFileOptions("Configuration file options"),
                        fSeverityMap(),
                        fVisibleOptions("Visible options"),
                        fConfigMutex(),
                        fVerbosityLevel("INFO"),
                        fUseConfigFile(false),
                        fConfigFile()
{

    LOG(NOLOG) << "";// temporary hack to prevent throwing exception when accessing empty sinklist --> fixed me
    fGenericDesc.add_options()
        ("help,h", "produce help")
        ("version,v", "print version")
        ("verbosity", po::value<std::string>(&fVerbosityLevel)->default_value("DEBUG"), "Verbosity level : TRACE, DEBUG, RESULTS, INFO, WARN, ERROR, STATE, NOLOG")
        ("log-color", po::value<bool>()->default_value(true), "logger color: true or false")
        ("print-options", po::value<bool>()->implicit_value(true), "print options in machine-readable format (<option>:<computed-value>:<type>:<description>)");

    fSeverityMap["TRACE"]   = FairMQ::severity_level::TRACE;
    fSeverityMap["DEBUG"]   = FairMQ::severity_level::DEBUG;
    fSeverityMap["RESULTS"] = FairMQ::severity_level::RESULTS;
    fSeverityMap["INFO"]    = FairMQ::severity_level::INFO;
    fSeverityMap["WARN"]    = FairMQ::severity_level::WARN;
    fSeverityMap["ERROR"]   = FairMQ::severity_level::ERROR;
    fSeverityMap["STATE"]   = FairMQ::severity_level::STATE;
    fSeverityMap["NOLOG"]   = FairMQ::severity_level::NOLOG;
}

/// Destructor
FairProgOptions::~FairProgOptions()
{
}

/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/// Add option descriptions
int FairProgOptions::AddToCmdLineOptions(const po::options_description& optDesc, bool visible)
{
    fCmdLineOptions.add(optDesc);
    if (visible)
    {
        fVisibleOptions.add(optDesc);
    }
    return 0;
}

int FairProgOptions::AddToCfgFileOptions(const po::options_description& optDesc, bool visible)
{
    //if UseConfigFile() not yet called, then enable it with required file name to be provided by command line
    if (!fUseConfigFile)
    {
        UseConfigFile();
    }

    fConfigFileOptions.add(optDesc);
    if (visible)
    {
        fVisibleOptions.add(optDesc);
    }
    return 0;
}
//*
po::options_description& FairProgOptions::GetCmdLineOptions()
{
    return fCmdLineOptions;
}

po::options_description& FairProgOptions::GetCfgFileOptions()
{
    return fConfigFileOptions;
}

po::options_description& FairProgOptions::GetEnvironmentOptions()
{
    return fEnvironmentDesc;
}

int FairProgOptions::AddToEnvironmentOptions(const po::options_description& optDesc)
{
    fEnvironmentDesc.add(optDesc);
    return 0;
}

void FairProgOptions::UseConfigFile(const string& filename)
{
        fUseConfigFile = true;
        if (filename.empty())
        {
            fConfigDesc.add_options()
                ("config-file", po::value<boost::filesystem::path>(&fConfigFile)->required(), "Path to configuration file (required argument)");
            AddToCmdLineOptions(fConfigDesc);
        }
        else
        {
            fConfigFile = filename;
        }
}

/// //////////////////////////////////////////////////////////////////////////////////////////////////////
/// Parser

int FairProgOptions::ParseCmdLine(const int argc, const char** argv, const po::options_description& desc, po::variables_map& varmap, bool allowUnregistered)
{
    // get options from cmd line and store in variable map
    // here we use command_line_parser instead of parse_command_line, to allow unregistered and positional options
    if (allowUnregistered)
    {
        po::command_line_parser parser{argc, argv};
        parser.options(desc).allow_unregistered();
        po::parsed_options parsedOptions = parser.run();
        po::store(parsedOptions, varmap);
    }
    else
    {
        po::store(po::parse_command_line(argc, argv, desc), varmap);
    }

    // call the virtual NotifySwitchOption method to handle switch options like e.g. "--help" or "--version"
    // return 1 if switch options found in varmap
    if (NotifySwitchOption())
    {
        return 1;
    }

    po::notify(varmap);
    return 0;
}

int FairProgOptions::ParseCmdLine(const int argc, const char** argv, const po::options_description& desc, bool allowUnregistered)
{
    return ParseCmdLine(argc, argv, desc, fVarMap, allowUnregistered);
}

int FairProgOptions::ParseCfgFile(ifstream& ifs, const po::options_description& desc, po::variables_map& varmap, bool allowUnregistered)
{
    if (!ifs)
    {
        LOG(ERROR) << "can not open configuration file";
        return -1;
    }
    else
    {
        po::store(parse_config_file(ifs, desc, allowUnregistered), varmap);
        po::notify(varmap);
    }
    return 0;
}

int FairProgOptions::ParseCfgFile(const string& filename, const po::options_description& desc, po::variables_map& varmap, bool allowUnregistered)
{
    ifstream ifs(filename.c_str());
    if (!ifs)
    {
        LOG(ERROR) << "can not open configuration file: " << filename;
        return -1;
    }
    else
    {
        po::store(parse_config_file(ifs, desc, allowUnregistered), varmap);
        po::notify(varmap);
    }
    return 0;
}

int FairProgOptions::ParseCfgFile(const string& filename, const po::options_description& desc, bool allowUnregistered)
{
    return ParseCfgFile(filename,desc,fVarMap,allowUnregistered);
}

int FairProgOptions::ParseCfgFile(ifstream& ifs, const po::options_description& desc, bool allowUnregistered)
{
    return ParseCfgFile(ifs,desc,fVarMap,allowUnregistered);
}

int FairProgOptions::ParseEnvironment(const function<string(string)>& environmentMapper)
{
    po::store(po::parse_environment(fEnvironmentDesc, environmentMapper), fVarMap);
    po::notify(fVarMap);

    return 0;
}

int FairProgOptions::PrintHelp() const
{
    cout << fVisibleOptions << "\n";
    return 0;
}

int FairProgOptions::PrintOptionsRaw()
{
    MapVarValInfo_t mapInfo;

    for (const auto& m : fVarMap)
    {
        mapInfo[m.first] = GetVariableValueInfo(m.second);
    }

    for (const auto& p : mapInfo)
    {
        string keyStr;
        string valueStr;
        string typeInfoStr;
        string defaultStr;
        string emptyStr;
        keyStr = p.first;
        tie(valueStr, typeInfoStr, defaultStr, emptyStr) = p.second;
        auto option = fCmdLineOptions.find_nothrow(keyStr, false);
        cout << keyStr << ":" << valueStr << ":" << typeInfoStr << ":" << (option ? option->description() : "<not found>") << endl;
    }

    return 0;
}

int FairProgOptions::PrintOptions()
{
    // //////////////////////////////////
    // Method to overload.
    // -> loop over variable map and print its content
    // -> In this example the following types are supported:
    // string, int, float, double, short, boost::filesystem::path
    // vector<string>, vector<int>, vector<float>, vector<double>, vector<short>

    MapVarValInfo_t mapinfo;

    // get string length for formatting and convert varmap values into string
    int maxLength1st = 0;
    int maxLength2nd = 0;
    int maxLengthTypeInfo = 0;
    int maxLengthDefault = 0;
    int maxLengthEmpty = 0;
    int totalLength = 0;
    for (const auto& m : fVarMap)
    {
        Max(maxLength1st, m.first.length());

        VarValInfo_t valinfo = GetVariableValueInfo(m.second);
        mapinfo[m.first] = valinfo;
        string valueStr;
        string typeInfoStr;
        string defaultStr;
        string emptyStr;
        tie(valueStr, typeInfoStr, defaultStr, emptyStr) = valinfo;

        Max(maxLength2nd, valueStr.length());
        Max(maxLengthTypeInfo, typeInfoStr.length());
        Max(maxLengthDefault, defaultStr.length());
        Max(maxLengthEmpty, emptyStr.length());
    }

    // TODO : limit the value length field in a better way
    if (maxLength2nd > 100)
    {
        maxLength2nd = 100;
    }
    totalLength = maxLength1st + maxLength2nd + maxLengthTypeInfo + maxLengthDefault + maxLengthEmpty;

    // maxLength2nd = 200;

    // formatting and printing

    LOG(DEBUG) << setfill ('*') << setw (totalLength + 3) << "*";// +3 because of string " = "
    string PrintOptionsTitle = "     Configuration     ";

    int leftSpaceLength = 0;
    int rightSpaceLength = 0;
    int leftTitleShiftLength = 0;
    int rightTitleShiftLength = 0;

    leftTitleShiftLength = PrintOptionsTitle.length() / 2;

    if ((PrintOptionsTitle.length()) % 2)
        rightTitleShiftLength = leftTitleShiftLength + 1;
    else
        rightTitleShiftLength = leftTitleShiftLength;

    leftSpaceLength = (totalLength + 3) / 2 - leftTitleShiftLength;
    if ((totalLength + 3) % 2)
    {
        rightSpaceLength = (totalLength + 3) / 2 - rightTitleShiftLength + 1;
    }
    else
    {
        rightSpaceLength = (totalLength + 3) / 2 - rightTitleShiftLength;
    }

    LOG(DEBUG) << setfill ('*') << setw(leftSpaceLength) << "*"
                << setw(PrintOptionsTitle.length()) << PrintOptionsTitle
                << setfill ('*') << setw(rightSpaceLength) << "*";

    LOG(DEBUG) << setfill ('*') << setw (totalLength+3) << "*";

    for (const auto& p : mapinfo)
    {
        string keyStr;
        string valueStr;
        string typeInfoStr;
        string defaultStr;
        string emptyStr;
        keyStr = p.first;
        tie(valueStr, typeInfoStr, defaultStr, emptyStr) = p.second;
        LOG(DEBUG) << std::setfill(' ')
                    << setw(maxLength1st) << left
                    << p.first << " = "
                    << setw(maxLength2nd)
                    << valueStr
                    << setw(maxLengthTypeInfo)
                    << typeInfoStr
                    << setw(maxLengthDefault)
                    << defaultStr
                    << setw(maxLengthEmpty)
                    << emptyStr;
    }
    LOG(DEBUG) << setfill ('*') << setw (totalLength + 3) << "*";// +3 for " = "

    return 0;
}

int FairProgOptions::NotifySwitchOption()
{
    // Method to overload.
    if (fVarMap.count("help"))
    {
        cout << "***** FAIR Program Options ***** \n" << fVisibleOptions;
        return 1;
    }

    if (fVarMap.count("version"))
    {
        cout << "alpha version 0.0\n";
        return 1;
    }

    return 0;
}

FairProgOptions::VarValInfo_t FairProgOptions::GetVariableValueInfo(const po::variable_value& varValue)
{
    return FairMQ::ConvertVariableValue<FairMQ::ToVarInfo>().Run(varValue);
}
