/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#include "FairGeane.h"

#include "FairField.h"              // for FairField
#include "FairGeaneApplication.h"   // for FairGeaneApplication
#include "FairRunAna.h"             // for FairRunAna

#include <TGeoManager.h>   // for TGeoManager
#include <TROOT.h>         // for TROOT, gROOT
#include <TString.h>       // for TString, operator!=, etc
#include <TSystem.h>       // for TSystem, gSystem
#include <cstdlib>         // for getenv
#include <iostream>        // for operator<<, basic_ostream, etc

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
// FairGeane::FairGeane() {
//  cout << "This ctr should not be called by user !!"<< endl;
//}
// -----   Standard constructor   ------------------------------------------
FairGeane::FairGeane(const char* name, TString UserConfig, TString UserCuts)
    : FairTask("Geane Application")
    , fApp(new FairGeaneApplication(kTRUE))
    , fName(name)
    , fUserConfig(UserConfig)
    , fUserCuts(UserCuts)
{
    // Create a new Geometry
    new TGeoManager("Geometry", "Geane geometry");
    // now import the geometry from file to the empty TGeo
    TGeoManager::Import(name);
}

FairGeane::FairGeane(TString UserConfig, TString UserCuts)
    : FairTask("Geane Application")
    , fApp(new FairGeaneApplication(kFALSE))
    , fName("")
    , fUserConfig(UserConfig)
    , fUserCuts(UserCuts)
{}

void FairGeane::SetParTask()
{
    cout << "------------------------FairGeane::SetParTask()------------------------------" << endl;
}

InitStatus FairGeane::Init()
{
    cout << "------------------------FairGeane::Init ()------------------------------" << endl;

    TString LibMacro;
    TString LibFunction;
    TString ConfigMacro;
    TString cuts = fUserCuts;
    if (cuts == TString("")) {
        cuts = "SetCuts.C";
    }

    TString work = getenv("VMCWORKDIR");
    TString work_config = work + "/gconfig/";
    work_config.ReplaceAll("//", "/");
    TString config_dir = getenv("CONFIG_DIR");
    config_dir.ReplaceAll("//", "/");

    Bool_t AbsPath = kFALSE;
    if (!config_dir.EndsWith("/")) {
        config_dir += "/";
    }

    TString geaneLibMacro = "g3libs.C";
    TString geaneMacro;
    if (fUserConfig.IsNull()) {
        geaneMacro = "Geane.C";
        fUserConfig = geaneMacro;
    } else {
        if (fUserConfig.Contains("/")) {
            AbsPath = kTRUE;
        }
        geaneMacro = fUserConfig;
        cout << "---------------User config is used :  " << geaneMacro.Data() << "-----------------" << endl;
    }
    if (TString(gSystem->FindFile(config_dir.Data(), geaneLibMacro)) != TString("")) {
        cout << "---User path for Configuration (g3libs.C) is used : " << config_dir.Data() << endl;
    } else {
        geaneLibMacro = work_config + "g3libs.C";
    }
    LibMacro = geaneLibMacro;
    LibFunction = "g3libs()";

    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), geaneMacro)) != TString("")) {
        cout << "---User path for Configuration (Geane.C) is used : " << config_dir.Data() << endl;
        ConfigMacro = geaneMacro;
    } else {
        if (AbsPath) {
            ConfigMacro = fUserConfig;
        } else {
            ConfigMacro = work_config + fUserConfig;
        }
    }

    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(), cuts)) != TString("")) {
        cout << "---User path for Cuts and Processes  (SetCuts.C) is used : " << config_dir.Data() << endl;
    } else {
        cuts = work_config + "SetCuts.C";
    }

    gROOT->LoadMacro(LibMacro.Data());
    gROOT->ProcessLine(LibFunction.Data());

    gROOT->LoadMacro(ConfigMacro.Data());
    gROOT->ProcessLine("Config()");

    // gROOT->LoadMacro(cuts);
    // gROOT->ProcessLine("SetCuts()");

    FairField* field = FairRunAna::Instance()->GetField();
    field->Print("");
    fApp->SetField(field);

    fApp->InitMC(ConfigMacro.Data(), "");

    cout << "I- FairGeane::FairGeane:  Geane is Initialized " << endl;
    return kSUCCESS;
}

FairGeane::~FairGeane() {}

void FairGeane::SetField(FairField* /*field*/)
{
    cout << "\033[5m\033[31m -W- FairGeane::SetField  This method is not used anymore, use FairRunAna::SetField "
            "instead \033[0m "
         << endl;
}
