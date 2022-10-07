/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairXmlVMCConfigurce file                       -----
// -----            Created 2019.02.19  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#include "FairXmlVMCConfig.h"

#include "FairFastSimRunConfiguration.h"
#include "FairLogger.h"
#include "FairRunSim.h"
#include "FairSink.h"   // for FairSink

#include <Rtypes.h>
#include <TGeant3.h>
#include <TGeant3TGeo.h>
#include <TGeant4.h>
#include <TObjString.h>   // for TObjString
#include <TObject.h>      // for TObject, TObject::kSingleKey
#include <TString.h>
#include <TSystem.h>      // for TSystem, gSystem
#include <TVirtualMC.h>   // for TVirtualMC
#include <cstdlib>        // for getenv
#include <cstring>        // for strcmp, strncmp
#include <ostream>        // for operator<<, ostringstream
#include <string>         // for string, basic_string, cha...
#include <vector>         // for vector

FairXmlVMCConfig::FairXmlVMCConfig()
    : FairGenericVMCConfig()
    , fMCEngine("")
    , fXmlEngine(new TXMLEngine())
{
    UsePostInitConfig(false);
}

void FairXmlVMCConfig::Setup(const char* mcEngine)
{
    fMCEngine = mcEngine;
    if (!((strcmp(mcEngine, "TGeant4") == 0) || (strcmp(mcEngine, "TGeant3") == 0))) {
        LOG(fatal) << "FairXmlVMCConfig::Setup() Engine \"" << mcEngine << "\" unknown!";
    }

    string xmlFileName = ObtainXmlFileName(mcEngine);

    // Parse xml file
    // Only file with restricted xml syntax are supported
    XMLDocPointer_t xmldoc = fXmlEngine->ParseFile(xmlFileName.data());
    if (!xmldoc)
        return;

    // take access to main node
    fXmlConfig = fXmlEngine->DocGetRootElement(xmldoc);

    if (strcmp(mcEngine, "TGeant4") == 0) {
        SetupGeant4();
    } else if (strcmp(mcEngine, "TGeant3") == 0) {
        SetupGeant3();
    }
    SetupStack();
    SetCuts();

    StoreXmlInfo();
}

void FairXmlVMCConfig::SetupPostInit(const char* mcEngine)
{
    if (!fPostInitFlag) {
        LOG(info) << "FairXmlVMCConfig::SetupPostInit() OFF.";
        return;
    }

    if (!((strcmp(mcEngine, "TGeant4") == 0))) {
        LOG(fatal) << "FairXmlVMCConfig::SetupPostInit() only valid for TGeant4.";
    }
    LOG(info) << "Loading Geant4 PostInit Config.";

    TString work = getenv("VMCWORKDIR");
    TString work_config = work + "/gconfig/";
    work_config.ReplaceAll("//", "/");

    TString config_dir = getenv("CONFIG_DIR");
    config_dir.ReplaceAll("//", "/");

    Bool_t AbsPath = kFALSE;

    TString ConfigMacro;
    TString g4Macro;
    if (fPostInitName.empty()) {
        g4Macro = "g4ConfigPostInit.C";
        fPostInitName = g4Macro;
    } else {
        if (fPostInitName.find("/") != std::string::npos) {
            AbsPath = kTRUE;
        }
        g4Macro = fPostInitName;
        LOG(debug) << "---------------User config is used: " << g4Macro.Data();
    }
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), g4Macro)) != TString("")) {
        LOG(debug) << "---User path for Configuration (" << fPostInitName << ") is used: " << config_dir.Data();
        ConfigMacro = g4Macro;
    } else {
        if (AbsPath) {
            ConfigMacro = fPostInitName;
        } else {
            ConfigMacro = work_config + fPostInitName;
        }
    }

    XMLDocPointer_t xmldoc = fXmlEngine->ParseFile(ConfigMacro.Data());
    if (!xmldoc)
        return;

    // take access to main node
    fXmlConfigPostInit = fXmlEngine->DocGetRootElement(xmldoc);

    XMLNodePointer_t xmlNode = 0;

    if ((xmlNode = GetPointer("SIM:G4_PostInit:Commands", fXmlConfigPostInit))) {
        std::vector<string> strVect = ConvertToVector<string>(xmlNode);
        LOG(debug) << "FairXmlVMCConfig: SIM:G4_PostInit:Commands got " << strVect.size() << " values:";
        TGeant4* geant4 = dynamic_cast<TGeant4*>(TVirtualMC::GetMC());
        for (auto val : strVect) {
            LOG(debug) << "   -> \"" << val << "\"";
            geant4->ProcessGeantCommand(val.data());
        }
    }
}

void FairXmlVMCConfig::SetupGeant3()
{
    LOG(debug) << "FairXmlVMCConfig::SetupGeant3() called";
    FairRunSim* fRun = FairRunSim::Instance();
    TString* gModel = fRun->GetGeoModel();
    TGeant3* geant3 = nullptr;
    if (strncmp(gModel->Data(), "TGeo", 4) == 0) {
        geant3 = new TGeant3TGeo("C++ Interface to Geant3");
    } else {
        geant3 = new TGeant3("C++ Interface to Geant3");
    }

    XMLNodePointer_t xmlNode = 0;

    if ((xmlNode = GetPointer("SIM:G3:TRIG", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:TRIG to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetTRIG(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:SWIT", fXmlConfig))) {
        std::vector<float> floatVect = ConvertToVector<float>(xmlNode);
        LOG(debug) << "Setting SIM:G3:SWIT to " << floatVect.size() << " values:";
        for (auto val : floatVect) {
            LOG(debug) << "   -> " << val;
        }
        if (floatVect.size() != 2)
            LOG(fatal) << "Setting: expecting 2 floats to setup G3_SWIT";
        geant3->SetSWIT(floatVect[0], floatVect[1]);
    }
    if ((xmlNode = GetPointer("SIM:G3:DEBU", fXmlConfig))) {
        std::vector<float> floatVect = ConvertToVector<float>(xmlNode);
        LOG(debug) << "Setting SIM:G3:DEBU to " << floatVect.size() << " values:";
        for (auto val : floatVect) {
            LOG(debug) << "   -> " << val;
        }
        if (floatVect.size() != 3)
            LOG(fatal) << "Setting: expecting 3 floats to setup G3_DEBU";
        geant3->SetDEBU(floatVect[0], floatVect[1], floatVect[2]);
    }
    if ((xmlNode = GetPointer("SIM:G3:RAYL", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:RAYL to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetRAYL(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:STRA", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:STRA to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetSTRA(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:AUTO", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:AUTO to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetAUTO(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:ABAN", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:ABAN to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetABAN(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:OPTI", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:OPTI to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetOPTI(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:ERAN", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:ERAN to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetERAN(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:CKOV", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G3:CKOV to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant3->SetCKOV(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G3:CUTS", fXmlConfig))) {
        std::vector<float> floatVect = ConvertToVector<float>(xmlNode);
        LOG(debug) << "Setting SIM:G3:CUTS to " << floatVect.size() << " values:";
        for (auto val : floatVect) {
            LOG(debug) << "   -> " << val;
        }
        if (floatVect.size() != 11 && floatVect.size() != 16)
            LOG(fatal) << "Setting: expecting 11 or 16 floats to setup G3_CUTS";
        geant3->SetCUTS(floatVect[0],
                        floatVect[1],
                        floatVect[2],
                        floatVect[3],
                        floatVect[4],
                        floatVect[5],
                        floatVect[6],
                        floatVect[7],
                        floatVect[8],
                        floatVect[9],
                        floatVect[10],
                        (floatVect.size() == 16) ? (&floatVect[11]) : 0);
    }
}

void FairXmlVMCConfig::SetupGeant4()
{
    LOG(debug) << "FairXmlVMCConfig::SetupGeant4() called";

    XMLNodePointer_t xmlNode = 0;

    string userGeometry = "";
    if ((xmlNode = GetPointer("SIM:G4:UserGeometry", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:UserGeometry to \"" << ConvertTo<string>(xmlNode) << "\"";
        userGeometry = ConvertTo<string>(xmlNode);
    }
    string physicsList = "";
    if ((xmlNode = GetPointer("SIM:G4:PhysicsList", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:PhysicsList to \"" << ConvertTo<string>(xmlNode) << "\"";
        physicsList = ConvertTo<string>(xmlNode);
    }
    string specialProcess = "";
    if ((xmlNode = GetPointer("SIM:G4:SpecialProcess", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:SpecialProcess to \"" << ConvertTo<string>(xmlNode) << "\"";
        specialProcess = ConvertTo<string>(xmlNode);
    }
    bool specialStacking = false;
    if ((xmlNode = GetPointer("SIM:G4:SpecialStacking", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:SpecialStacking to \"" << (ConvertTo<bool>(xmlNode) ? "true" : "false") << "\"";
        specialStacking = ConvertTo<bool>(xmlNode);
    }
    bool mtMode = FairRunSim::Instance()->IsMT();
    if ((xmlNode = GetPointer("SIM:G4:Multithreaded", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:Multithreaded to \"" << (ConvertTo<bool>(xmlNode) ? "true" : "false") << "\"";
        mtMode = ConvertTo<bool>(xmlNode);
    }

    FairFastSimRunConfiguration* runConfiguration =
        new FairFastSimRunConfiguration(userGeometry, physicsList, specialProcess, specialStacking, mtMode);

    TGeant4* geant4 = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);

    if ((xmlNode = GetPointer("SIM:G4:MaxNStep", fXmlConfig))) {
        LOG(debug) << "Setting SIM:G4:MaxNStep to \"" << ConvertTo<float>(xmlNode) << "\"";
        geant4->SetMaxNStep(ConvertTo<float>(xmlNode));
    }
    if ((xmlNode = GetPointer("SIM:G4:Commands", fXmlConfig))) {
        std::vector<string> strVect = ConvertToVector<string>(xmlNode);
        LOG(debug) << "Setting SIM:G4:Commands to " << strVect.size() << " values:";
        for (auto val : strVect) {
            LOG(debug) << "   -> \"" << val << "\"";
            geant4->ProcessGeantCommand(val.data());
        }
    }

    LOG(debug) << geant4->GetName() << " MonteCarlo engine created!.";
}

void FairXmlVMCConfig::SetCuts()
{
    LOG(debug) << "FairXmlVMCConfig::SetCuts() called";
    XMLNodePointer_t xmlNode = 0;

    if ((xmlNode = GetPointer("SIM:MonteCarlo:Process", fXmlConfig))) {
        TVirtualMC* MC = TVirtualMC::GetMC();
        XMLNodePointer_t child = fXmlEngine->GetChild(xmlNode);
        while (child != 0) {
            fXmlEngine->GetNodeName(child);
            MC->SetProcess(fXmlEngine->GetNodeName(child), ConvertTo<float>(child));
            LOG(debug) << "Setting Process \"" << fXmlEngine->GetNodeName(child) << "\" to " << ConvertTo<float>(child);
            child = fXmlEngine->GetNext(child);
        }
    }

    if ((xmlNode = GetPointer("SIM:MonteCarlo:Cut", fXmlConfig))) {
        TVirtualMC* MC = TVirtualMC::GetMC();
        XMLNodePointer_t child = fXmlEngine->GetChild(xmlNode);
        while (child != 0) {
            fXmlEngine->GetNodeName(child);
            MC->SetCut(fXmlEngine->GetNodeName(child), ConvertTo<float>(child));
            LOG(debug) << "Setting Cut \"" << fXmlEngine->GetNodeName(child) << "\" to " << ConvertTo<float>(child);
            child = fXmlEngine->GetNext(child);
        }
    }
}

string FairXmlVMCConfig::ObtainXmlFileName(const char* mcEngine)
{
    TString lUserConfig = FairRunSim::Instance()->GetUserConfig();

    TString work = getenv("VMCWORKDIR");
    TString work_config = work + "/gconfig/";
    work_config.ReplaceAll("//", "/");

    TString config_dir = getenv("CONFIG_DIR");
    config_dir.ReplaceAll("//", "/");

    Bool_t AbsPath = kFALSE;

    TString configFileWithPath;

    TString configFile;
    if (lUserConfig.IsNull()) {
        if (strcmp(mcEngine, "TGeant4") == 0) {
            configFile = "g4Config.xml";
        }
        if (strcmp(mcEngine, "TGeant3") == 0) {
            configFile = "g3Config.xml";
        }
        lUserConfig = configFile;
    } else {
        if (lUserConfig.Contains("/")) {
            AbsPath = kTRUE;
        }
        configFile = lUserConfig;
        LOG(debug) << "---------------User config is used: " << configFile.Data();
    }
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), configFile)) != TString("")) {
        LOG(debug) << "---------------CONFIG_DIR is used: " << config_dir.Data() << " to get \"" << configFile.Data()
                   << "\"";
        configFileWithPath = configFile;
    } else {
        if (AbsPath) {
            configFileWithPath = lUserConfig;
        } else {
            configFileWithPath = work_config + lUserConfig;
        }
    }
    return configFileWithPath.Data();
}

void FairXmlVMCConfig::StoreXmlInfo()
{
    std::ostringstream nodestring;
    nodestring << fMCEngine << "\n";
    nodestring << fXmlConfig;
    nodestring << "\n";
    TObjString* configObject = new TObjString(nodestring.str().c_str());
    FairRunSim::Instance()->GetSink()->WriteObject(configObject, "SimulationSetup", TObject::kSingleKey);

    LOG(debug) << "FairXmlVMCConfig::StoreXmlInfo() done.";
}

XMLNodePointer_t FairXmlVMCConfig::GetPointer(string path, XMLNodePointer_t node, int verbose)
{
    // this function display all accessible information about xml node and its children
    if (verbose)
        cout << "GetPointer with path \"" << path << "\"" << endl;
    path.replace(0, path.find(':') + 1, "");

    XMLNodePointer_t child = fXmlEngine->GetChild(node);
    while (child != 0) {
        if (verbose)
            cout << "got child with name " << fXmlEngine->GetNodeName(child) << " and the path is \"" << path << "\""
                 << endl;
        if (path.find(fXmlEngine->GetNodeName(child)) != 0) {
            child = fXmlEngine->GetNext(child);
            continue;
        }
        if (verbose)
            cout << "got the correct name!" << endl;
        if (path.find(':') == std::string::npos) {
            return child;
        }

        child = GetPointer(path, child, verbose);
        if (child) {
            return child;
        }
        child = fXmlEngine->GetNext(child);
    }
    return child;
}

template<>
string FairXmlVMCConfig::ConvertTo<string>(XMLNodePointer_t xmlPointer)
{
    return string(fXmlEngine->GetNodeContent(xmlPointer));
}

template<>
float FairXmlVMCConfig::ConvertTo<float>(XMLNodePointer_t xmlPointer)
{
    string str = fXmlEngine->GetNodeContent(xmlPointer);
    if (str.find_first_not_of("0123456789e.-") != std::string::npos) {
        LOG(fatal) << "Cannot convert string \"" << str << "\" to float";
    }
    return stof(str);
}

template<>
bool FairXmlVMCConfig::ConvertTo<bool>(XMLNodePointer_t xmlPointer)
{
    string str = fXmlEngine->GetNodeContent(xmlPointer);
    if (isdigit(str[0])) {
        if (str[0] == '0')
            return false;
        return true;
    }
    string s_l;
    for (auto elem : str)
        s_l += std::tolower(elem);
    if (s_l.find("true") != std::string::npos)
        return true;
    if (s_l.find("false") != std::string::npos)
        return false;
    LOG(fatal) << "Cannot convert string \"" << str << "\" to bool";
    return false;
}

ClassImp(FairXmlVMCConfig);
