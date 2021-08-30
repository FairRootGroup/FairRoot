/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairYamlVMCConfigurce file                      -----
// -----            Created 2019.02.19  by R. Karabowicz               -----
// -------------------------------------------------------------------------
#include "FairYamlVMCConfig.h"

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
#include <memory>         // for unique_ptr
#include <ostream>        // for operator<<, ostringstream
#include <string>         // for string, basic_string, cha...
#include <vector>         // for vector

FairYamlVMCConfig::FairYamlVMCConfig()
    : FairGenericVMCConfig()
    , fMCEngine("")
{
}

void FairYamlVMCConfig::Setup(const char* mcEngine)
{
    fMCEngine = mcEngine;
    if (!((strcmp(mcEngine, "TGeant4") == 0) || (strcmp(mcEngine, "TGeant3") == 0))) {
        LOG(fatal) << "FairYamlVMCConfig::Setup() Engine \"" << mcEngine << "\" unknown!";
    }

    std::string yamlFileName = ObtainYamlFileName(mcEngine);
    fYamlConfig = YAML::LoadFile(yamlFileName);

    if (strcmp(mcEngine, "TGeant4") == 0) {
        SetupGeant4();
    } else if (strcmp(mcEngine, "TGeant3") == 0) {
        SetupGeant3();
    }
    SetupStack();
    SetCuts();

    StoreYamlInfo();
}

void FairYamlVMCConfig::SetupPostInit(const char* mcEngine)
{
    if ( !fPostInitFlag ) {
        LOG(info) << "FairYamlVMCConfig::SetupPostInit() OFF." << fPostInitName;
        return;
    }

    if (!((strcmp(mcEngine, "TGeant4") == 0))) {
        LOG(fatal) << "FairYamlVMCConfig::SetupPostInit() only valid for TGeant4.";
    }
    LOG(info) << "Loading Geant4 PostInit Config." << endl;

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
        if (fPostInitName.find("/")!=std::string::npos) {
            AbsPath = kTRUE;
        }
        g4Macro = fPostInitName;
        LOG(info) << "---------------User config is used: " << g4Macro.Data();
    }
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), g4Macro)) != TString("")) {
        LOG(info) << "---User path for Configuration (" << fPostInitName << ") is used: " << config_dir.Data();
        ConfigMacro = g4Macro;
    } else {
        if (AbsPath) {
            ConfigMacro = fPostInitName;
        } else {
            ConfigMacro = work_config + fPostInitName;
        }
    }

    fYamlConfigPostInit = YAML::LoadFile(ConfigMacro.Data());

    if (fYamlConfigPostInit["Geant4_PostInit_Commands"]) {
        std::vector<std::string> g4commands = fYamlConfigPostInit["Geant4_PostInit_Commands"].as<std::vector<std::string>>();
        for ( const auto& value: g4commands ) {
            LOG(info) << " execute command \"" << value << "\"";
            TGeant4* geant4 = dynamic_cast<TGeant4*>(TVirtualMC::GetMC());
            geant4->ProcessGeantCommand(value.data());
        }
    }

    LOG(info) << "got info from " << fPostInitName;
}

void FairYamlVMCConfig::SetupGeant3()
{
    LOG(info) << "FairYamlVMCConfig::SetupGeant3() called";
    FairRunSim* fRun = FairRunSim::Instance();
    TString* gModel = fRun->GetGeoModel();
    TGeant3* geant3 = nullptr;
    if (strncmp(gModel->Data(), "TGeo", 4) == 0) {
        geant3 = new TGeant3TGeo("C++ Interface to Geant3");
    } else {
        geant3 = new TGeant3("C++ Interface to Geant3");
    }

    if (fYamlConfig["G3_TRIG"])
        geant3->SetTRIG(fYamlConfig["G3_TRIG"].as<int>());
    if (fYamlConfig["G3_SWIT"]) {
        std::vector<int> intVect = fYamlConfig["G3_SWIT"].as<std::vector<int>>();
        if (intVect.size() != 2)
            LOG(fatal) << "FairSetupGeant3: expecting 2 integers to setup G3_SWIT";
        geant3->SetSWIT(intVect[0], intVect[1]);
    }
    if (fYamlConfig["G3_DEBU"]) {
        std::vector<int> intVect = fYamlConfig["G3_DEBU"].as<std::vector<int>>();
        if (intVect.size() != 3)
            LOG(fatal) << "FairSetupGeant3: expecting 3 integers to setup G3_DEBU";
        geant3->SetDEBU(intVect[0], intVect[1], intVect[2]);
    }
    if (fYamlConfig["G3_RAYL"])
        geant3->SetRAYL(fYamlConfig["G3_RAYL"].as<int>());
    if (fYamlConfig["G3_STRA"])
        geant3->SetSTRA(fYamlConfig["G3_STRA"].as<int>());
    if (fYamlConfig["G3_AUTO"])
        geant3->SetAUTO(fYamlConfig["G3_AUTO"].as<int>());
    if (fYamlConfig["G3_ABAN"])
        geant3->SetABAN(fYamlConfig["G3_ABAN"].as<int>());
    if (fYamlConfig["G3_OPTI"])
        geant3->SetOPTI(fYamlConfig["G3_OPTI"].as<int>());
    if (fYamlConfig["G3_ERAN"])
        geant3->SetERAN(fYamlConfig["G3_ERAN"].as<double>());
    if (fYamlConfig["G3_CKOV"])
        geant3->SetCKOV(fYamlConfig["G3_CKOV"].as<int>());
}

void FairYamlVMCConfig::SetupGeant4()
{
    LOG(info) << "FairYamlVMCConfig::SetupGeant4() called";

    if (!fYamlConfig["Geant4_UserGeometry"]) {
        LOG(fatal) << "User geometry not provided";
    }
    auto const g4UserGeometry(fYamlConfig["Geant4_UserGeometry"].as<std::string>());

    if (!fYamlConfig["Geant4_PhysicsList"]) {
        LOG(fatal) << "Physics list not provided";
    }
    auto const g4PhysicsList(fYamlConfig["Geant4_PhysicsList"].as<std::string>());

    if (!fYamlConfig["Geant4_SpecialProcess"]) {
        LOG(fatal) << "Special processy not provided";
    }
    auto const g4SpecialProcess(fYamlConfig["Geant4_SpecialProcess"].as<std::string>());

    bool specialStacking = false;
    if (fYamlConfig["Geant4_SpecialStacking"]) {
        //        LOG(info) << "Special stacking used";
        specialStacking = fYamlConfig["Geant4_SpecialStacking"].as<bool>();
    }
    bool mtMode = FairRunSim::Instance()->IsMT();

    if (fYamlConfig["Geant4_Multithreaded"]) {
        mtMode = fYamlConfig["Geant4_Multithreaded"].as<bool>();
        //        LOG(info) << "Setting Geant4 multithreaded to " << (mtMode?"true":"false");
    }

    auto const useFastSim(fYamlConfig["UseFastSim"] ? fYamlConfig["UseFastSim"].as<bool>() : fUseFastSimDefault);
    std::unique_ptr<TG4RunConfiguration> runConfiguration;
    if (useFastSim) {
        runConfiguration = std::make_unique<FairFastSimRunConfiguration>(
            g4UserGeometry, g4PhysicsList, g4SpecialProcess, specialStacking, mtMode);
    } else {
        runConfiguration = std::make_unique<TG4RunConfiguration>(
            g4UserGeometry, g4PhysicsList, g4SpecialProcess, specialStacking, mtMode);
    }

    // Instantiate a singleton like object, "leaking" it is the current API
    TGeant4* geant4 = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration.release());

    if (fYamlConfig["Geant4_MaxNStep"]) {
        LOG(info) << " execute SetMaxNStep (" << fYamlConfig["Geant4_MaxNStep"].as<int>() << ")";
        geant4->SetMaxNStep(fYamlConfig["Geant4_MaxNStep"].as<int>());
    }
    if (fYamlConfig["Geant4_Commands"]) {
        std::vector<std::string> g4commands = fYamlConfig["Geant4_Commands"].as<std::vector<std::string>>();
        for (const auto& value : g4commands) {
            LOG(info) << " execute command \"" << value << "\"";
            geant4->ProcessGeantCommand(value.data());
        }
    }

    LOG(info) << geant4->GetName() << " MonteCarlo engine created!.";
}

void FairYamlVMCConfig::SetCuts()
{
    LOG(info) << "FairYamlVMCConfig::SetCuts() called";
    if (fYamlConfig["MonteCarlo_Process"]) {
        YAML::Node mcProcess = fYamlConfig["MonteCarlo_Process"];
        TVirtualMC* MC = TVirtualMC::GetMC();
        for (auto it = mcProcess.begin(); it != mcProcess.end(); ++it) {
            //            LOG(info) << "proc: " << it->first << " --> " << it->second;
            MC->SetProcess(it->first.as<std::string>().c_str(), it->second.as<int>());
        }
    }

    if (fYamlConfig["MonteCarlo_Cut"]) {
        YAML::Node mcProcess = fYamlConfig["MonteCarlo_Cut"];
        TVirtualMC* MC = TVirtualMC::GetMC();
        for (auto it = mcProcess.begin(); it != mcProcess.end(); ++it) {
            //            LOG(info) << "cut: " << it->first << " --> " << it->second;
            MC->SetCut(it->first.as<std::string>().c_str(), it->second.as<double>());
        }
    }
}

std::string FairYamlVMCConfig::ObtainYamlFileName(const char* mcEngine)
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
            configFile = "g4Config.yaml";
        }
        if (strcmp(mcEngine, "TGeant3") == 0) {
            configFile = "g3Config.yaml";
        }
        lUserConfig = configFile;
    } else {
        if (lUserConfig.Contains("/")) {
            AbsPath = kTRUE;
        }
        configFile = lUserConfig;
        LOG(info) << "---------------User config is used: " << configFile.Data();
    }
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), configFile)) != TString("")) {
        LOG(info) << "---------------CONFIG_DIR is used: " << config_dir.Data() << " to get \"" << configFile.Data()
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

void FairYamlVMCConfig::StoreYamlInfo()
{
    std::ostringstream nodestring;
    nodestring << fMCEngine << "\n";
    nodestring << fYamlConfig;
    nodestring << "\n";
    TObjString* configObject = new TObjString(nodestring.str().c_str());
    FairRunSim::Instance()->GetSink()->WriteObject(configObject, "SimulationSetup", TObject::kSingleKey);

    LOG(info) << "FairYamlVMCConfig::StoreYamlInfo() done.";
}

ClassImp(FairYamlVMCConfig);
