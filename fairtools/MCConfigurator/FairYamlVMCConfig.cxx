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

#include "FairLogger.h"
#include "FairRunSim.h"
#include "FairFastSimRunConfiguration.h"

#include "TGeant3.h"
#include "TGeant3TGeo.h"
#include "TGeant4.h"

#include "TROOT.h"
#include "TString.h"

//_____________________________________________________________________________
FairYamlVMCConfig::FairYamlVMCConfig()
    : FairGenericVMCConfig()
{
}
//_____________________________________________________________________________
FairYamlVMCConfig::~FairYamlVMCConfig()
{
}

//_____________________________________________________________________________
void FairYamlVMCConfig::Setup(const char* mcEngine)
{
    if ( ! ( (strcmp(mcEngine,"TGeant4")==0) || (strcmp(mcEngine,"TGeant3")==0) ) ) {
        LOG(fatal) << "FairYamlVMCConfig::Setup() Engine \"" << mcEngine << "\" unknown!";
    }

    TString yamlFileName = ObtainYamlFileName(mcEngine);
    fYamlConfig = YAML::LoadFile(yamlFileName.Data());

    if(strcmp(mcEngine,"TGeant4") == 0 ) {
        SetupGeant4();
    } else if(strcmp(mcEngine,"TGeant3") == 0 ) {
        SetupGeant3();
    }
    SetupStack();
    SetCuts();

    StoreYamlInfo();
}

//_____________________________________________________________________________
void FairYamlVMCConfig::SetupGeant3() {
    LOG(info) << "FairYamlVMCConfig::SetupGeant3() called";
    FairRunSim *fRun = FairRunSim::Instance();
    TString* gModel = fRun->GetGeoModel();
    TGeant3* geant3 = NULL;
    if ( strncmp(gModel->Data(),"TGeo",4) == 0 ) {
        geant3
            = new  TGeant3TGeo("C++ Interface to Geant3");
    }else{
        geant3
            = new  TGeant3("C++ Interface to Geant3");
    }

    if (fYamlConfig["G3_TRIG"])
        geant3->SetTRIG(fYamlConfig["G3_TRIG"].as<int>());
    if (fYamlConfig["G3_SWIT"]) {
        std::vector<int> intVect = fYamlConfig["G3_SWIT"].as<std::vector<int>>();
        if ( intVect.size() != 2 )
            LOG(fatal) << "FairSetupGeant3: expecting 2 integers to setup G3_SWIT";
        geant3->SetSWIT(intVect[0], intVect[1]);
    }
    if (fYamlConfig["G3_DEBU"]) {
        std::vector<int> intVect = fYamlConfig["G3_DEBU"].as<std::vector<int>>();
        if ( intVect.size() != 3 )
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

//_____________________________________________________________________________
void FairYamlVMCConfig::SetupGeant4() {
    LOG(info) << "FairYamlVMCConfig::SetupGeant4() called";

    if (!fYamlConfig["Geant4_UserGeometry"]) {
        LOG(fatal) << "User geometry not provided";
    }
    if (!fYamlConfig["Geant4_PhysicsList"]) {
        LOG(fatal) << "Physics list not provided";
    }
    if (!fYamlConfig["Geant4_SpecialProcess"]) {
        LOG(fatal) << "Special processy not provided";
    }
    bool specialStacking = false;
    if (fYamlConfig["Geant4_SpecialStacking"]) {
        //        LOG(info) << "Special stacking used";
        specialStacking = fYamlConfig["Geant4_SpecialStacking"].as<bool>();
    }
    bool mtMode = FairRunSim::Instance()->IsMT();
    
    FairFastSimRunConfiguration* runConfiguration
        = new FairFastSimRunConfiguration(fYamlConfig["Geant4_UserGeometry"]  .as<std::string>(),
                                          fYamlConfig["Geant4_PhysicsList"]   .as<std::string>(),
                                          fYamlConfig["Geant4_SpecialProcess"].as<std::string>(),
                                          specialStacking,
                                          mtMode);

    TGeant4* geant4 = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration);

    LOG(info) << geant4->GetName() << " MonteCarlo engine created!.";
}

//_____________________________________________________________________________
void FairYamlVMCConfig::SetCuts() {
    LOG(info) << "FairYamlVMCConfig::SetCuts() called";
    if ( fYamlConfig["MonteCarlo_Process"] ) {
        YAML::Node mcProcess = fYamlConfig["MonteCarlo_Process"];
        TVirtualMC *MC =TVirtualMC::GetMC();
        for (auto it = mcProcess.begin(); it != mcProcess.end(); ++it) {
            //            LOG(info) << "proc: " << it->first << " --> " << it->second;
            MC->SetProcess(it->first.as<std::string>().c_str(),it->second.as<int>());
        }
    }

    if ( fYamlConfig["MonteCarlo_Cut"] ) {
        YAML::Node mcProcess = fYamlConfig["MonteCarlo_Cut"];
        TVirtualMC *MC =TVirtualMC::GetMC();
        for (auto it = mcProcess.begin(); it != mcProcess.end(); ++it) {
            //            LOG(info) << "cut: " << it->first << " --> " << it->second;
            MC->SetCut(it->first.as<std::string>().c_str(),it->second.as<double>());
        }
    }
}

//_____________________________________________________________________________
TString FairYamlVMCConfig::ObtainYamlFileName(const char* mcEngine) {

    TString lUserConfig = FairRunSim::Instance()->GetUserConfig();

    TString work = getenv("VMCWORKDIR");
    TString work_config=work+"/gconfig/";
    work_config.ReplaceAll("//","/");

    TString config_dir= getenv("CONFIG_DIR");
    config_dir.ReplaceAll("//","/");

    Bool_t AbsPath=kFALSE;

    TString configFileWithPath;

    TString configFile;
    if(lUserConfig.IsNull()) {
        if(strcmp(mcEngine,"TGeant4") == 0 ) {
            configFile = "g4Config.yaml";
        }
        if(strcmp(mcEngine,"TGeant3") == 0 ) {
            configFile = "g3Config.yaml";
        }
        lUserConfig = configFile;
    } else {
        if (lUserConfig.Contains("/")) { AbsPath=kTRUE; }
        configFile = lUserConfig;
        LOG(info) << "---------------User config is used: "
                  << configFile.Data();
    }
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(),configFile)) != TString("")) {
        LOG(info) << "---------------CONFIG_DIR is used: "
                  << config_dir.Data() << " to get \"" << configFile.Data() << "\"";
        configFileWithPath=configFile;
    } else {
        if(AbsPath) { configFileWithPath = lUserConfig; }
        else { configFileWithPath =work_config+lUserConfig; }
    }
    return configFileWithPath;
}

//_____________________________________________________________________________
void FairYamlVMCConfig::StoreYamlInfo() {
    std::ostringstream nodestring;
    nodestring << "TGeant3\n";
    nodestring << fYamlConfig;
    nodestring << "\n";
    TObjString* configObject = new TObjString(nodestring.str().c_str());
    FairRunSim::Instance()->GetSink()->WriteObject(configObject,"SimulationSetup", TObject::kSingleKey);

    LOG(info) << "FairYamlVMCConfig::StoreYamlInfo() done.";
}

ClassImp(FairYamlVMCConfig)
