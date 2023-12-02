/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// -----                   FairRunSim source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----

#include "FairRunSim.h"

#include "FairBaseParSet.h"         // for FairBaseParSet
#include "FairField.h"              // for FairField
#include "FairFileHeader.h"         // for FairFileHeader
#include "FairGenericVMCConfig.h"   // for FairGenericVMCConfig
#include "FairGeoInterface.h"       // for FairGeoInterface
#include "FairGeoLoader.h"          // for FairGeoLoader
#include "FairGeoParSet.h"          // for FairGeoParSet
#include "FairLogger.h"             // for FairLogger, MESSAGE_ORIGIN
#include "FairMCEventHeader.h"      // for FairMCEventHeader
#include "FairMesh.h"               // for FairMesh
#include "FairModule.h"             // for FairModule
#include "FairParSet.h"             // for FairParSet
#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator
#include "FairRootManager.h"        // for FairRootManager
#include "FairRunIdGenerator.h"     // for FairRunIdGenerator
#include "FairRuntimeDb.h"          // for FairRuntimeDb
#include "FairTask.h"               // for FairTask

#include <TCollection.h>   // for TIter
#include <TGeoManager.h>   // for gGeoManager
#include <TList.h>         // for TList
#include <TObjString.h>    // for TObjString
#include <TObject.h>       // for TObject
#include <TROOT.h>         //
#include <TRandom.h>       // for gRandom
#include <TSystem.h>       // for TSystem, gSystem
#include <cassert>         //
#include <iostream>        // for cout, endl, ostream
#include <stdlib.h>        // for getenv, nullptr
#include <string.h>        // for strcmp, strncmp
#include <tuple>           // for std::ignore

using std::cout;
using std::endl;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
FairRunSim::FairRunSim(Bool_t isMaster)
    : FairRun(isMaster)
    , fMCEvHead(nullptr)
    , fField(nullptr)
    , fIons(new TObjArray())
    , fParticles(new TObjArray())
    , ListOfModules(new TObjArray())
    , MatFname("")
    , fPythiaDecayer(kFALSE)
    , fPythiaDecayerConfig("")
    , fUserDecay(kFALSE)
    , fUserDecayConfig("")
    , fRadLength(kFALSE)
    , fRadMap(kFALSE)
    , fRadGrid(kFALSE)
    , fMeshList(new TObjArray())
    , fUserConfig("")
    , fUserCuts("SetCuts.C")
    , fImportTGeoToVMC(kTRUE)
{
    if (fginstance) {
        Fatal("FairRun", "Singleton instance already exists.");
        return;
    }
    fginstance = this;
    fRunId = 0;
    fAna = kFALSE;
    fIons->SetName("fIons");
    fParticles->SetName("fParticles");
    ListOfModules->SetName("ListOfModules");
}
#pragma GCC diagnostic pop

FairRunSim::~FairRunSim()
{
    LOG(debug) << "Enter Destructor of FairRunSim ";

    // delete fApp;

    /** List of Modules is filled via AddModule from the macro, but it
   is the responsibility of FairRunSim to call the destructors of
   the modules-
  */
    LOG(debug) << "Start deleting all registered modules";
    ListOfModules->Delete();
    delete ListOfModules;
    LOG(debug) << "Finish deleting all registered modules";

    fIons->Delete();
    delete fIons;
    fParticles->Delete();
    delete fParticles;

    delete fApp;
    // delete fField;
    // Not owner of the field
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    delete fGen;
#pragma GCC diagnostic pop
    delete fMCEvHead;
    if (fginstance == this) {
        // Do not point to a destructed object!
        fginstance = nullptr;
    }

    /// \bug Leaks GeoLoader and related resources, prevents memory issues (probably a double free)
    ///      See: https://github.com/FairRootGroup/FairRoot/issues/1514
    std::ignore = fGeoLoader.release();
}

FairRunSim* FairRunSim::Instance()
{
    return fginstance;
}

void FairRunSim::AddModule(FairModule* Mod)
{
    assert(Mod);
    Mod->SetRunSim(this);
    ListOfModules->Add(Mod);
    Mod->SetModId(count++);
}

void FairRunSim::AddMesh(FairMesh* Mesh)
{
    Mesh->print();
    Mesh->calculate();
    fMeshList->Add(Mesh);
}

TObjArray* FairRunSim::GetUserDefIons()
{
    /** return the array of user defined ions*/
    return fIons;
}

TObjArray* FairRunSim::GetUserDefParticles()
{
    /** return the array of user defined particles*/
    return fParticles;
}

void FairRunSim::Init()
{
    /**Initialize the simulation session*/
    fRootManager->InitSink();

    CheckFlukaExec();

    //  fOutFile=fRootManager->OpenOutFile(fOutname);
    LOG(info) << "==============  FairRunSim: Initialising simulation run ==============";

    fGeoLoader = std::make_unique<FairGeoLoader>(fLoaderName.Data(), "Geo Loader");
    FairGeoInterface* geointerFace = fGeoLoader->getGeoInterface();
    geointerFace->SetNoOfSets(ListOfModules->GetEntries());
    geointerFace->setMediaFile(MatFname.Data());
    geointerFace->readMedia();

    //  gSystem->cd(flout.Data());

    fApp = new FairMCApplication("Fair", "The Fair VMC App", ListOfModules, MatFname);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    fApp->SetGenerator(fGen);
#pragma GCC diagnostic pop

    // Add a Generated run ID to the FairRunTimeDb
    if (fRunId == 0) {
        FairRunIdGenerator genid;
        // FairRuntimeDb *rtdb= GetRuntimeDb();
        fRunId = genid.generateId();
    }
    fRtdb->addRun(fRunId);

    fFileHeader->SetRunId(fRunId);
    /** Add Tasks to simulation if any*/
    fApp->AddTask(fTask);
    /** This call will create the container if it does not exist*/
    auto par = dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
    if (par) {
        par->SetDetList(GetListOfModules());
        par->SetGen(GetPrimaryGenerator());
        par->SetBeamMom(fBeamMom);
    }

    /** This call will create the container if it does not exist*/
    auto geopar = dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
    if (geopar) {
        geopar->SetGeometry(gGeoManager);
    }

    // Set global Parameter Info

    if (fPythiaDecayer) {
        fApp->SetPythiaDecayer(fPythiaDecayer);
        if (fPythiaDecayerConfig) {
            fApp->SetPythiaDecayerConfig(fPythiaDecayerConfig);
        }
    }
    if (fUserDecay) {
        fApp->SetUserDecay(fUserDecay);
        if (fUserDecayConfig) {
            fApp->SetUserDecayConfig(fUserDecayConfig);
        }
    }
    // on/off visualisation
    if (fStoreTraj) {
        LOG(info) << "Create visualisation manager ";
    }
    if (fRadLength) {
        fApp->SetRadiationLengthReg(fRadLength);
    }
    if (fRadMap) {
        fApp->SetRadiationMapReg(fRadMap);
    }
    if (fRadGrid) {
        fApp->AddMeshList(fMeshList);
    }

    if (fField) {
        fField->Init();
    }
    fApp->SetField(fField);
    SetFieldContainer();

    TList* containerList = fRtdb->getListOfContainers();
    TIter next(containerList);
    FairParSet* cont;
    TObjArray* ContList = new TObjArray();
    while ((cont = dynamic_cast<FairParSet*>(next()))) {
        ContList->Add(new TObjString(cont->GetName()));
    }
    if (par) {
        par->SetContListStr(ContList);
        par->SetRndSeed(gRandom->TRandom::GetSeed());
        par->setChanged();
        par->setInputVersion(fRunId, 1);
    }
    if (geopar) {
        geopar->setChanged();
        geopar->setInputVersion(fRunId, 1);
    }

    /**Set the configuration for MC engine*/
    SetMCConfig();
    fRootManager->WriteFileHeader(fFileHeader);
}

void FairRunSim::SetFieldContainer()
{
    if (fField) {
        fField->FillParContainer();
    }
}

void FairRunSim::CheckFlukaExec()
{
    /** Private method for setting FLUKA simulation*/
    TString work = getenv("VMCWORKDIR");
    TString work_config = work + "/gconfig/";
    work_config.ReplaceAll("//", "/");

    TString config_dir = getenv("CONFIG_DIR");
    config_dir.ReplaceAll("//", "/");
    if (!config_dir.EndsWith("/")) {
        config_dir += "/";
    }

    TString flout;
    if (strcmp(GetName(), "TFluka") == 0) {
        TString flexec = "run_fluka.sh";
        if (TString(gSystem->FindFile(config_dir.Data(), flexec)) != TString("")) {
            LOG(info) << "---User path for Configuration is used: " << config_dir.Data();
        } else {
            flexec = work_config + "run_fluka.sh";
        }
        gSystem->Exec(flexec.Data());
        // More generic for different macro
        // dir layout <D.B>
        TString macrodir = getenv("PWD");
        // cout << macrodir << endl;
        flout = macrodir + "/fluka_out";
        flout.ReplaceAll("//", "/");
        gSystem->cd(flout.Data());
    }
}

void FairRunSim::SetMCConfig()
{
    // Either setup the simulation with the provided user hook
    if (fUseSimSetupFunction) {
        fSimSetup();
    } else {
        if (!fSimulationConfig) {
            fSimulationConfig = std::make_unique<FairGenericVMCConfig>();
        }
        fSimulationConfig->Setup(GetName());
    }

    fApp->InitMC("foo", "bar");

    if (fUseSimSetupPostInitFunction) {
        fSimSetupPostInit();
    } else {
        if (fSimulationConfig) {
            fSimulationConfig->SetupPostInit(GetName());
        }
    }
}

void FairRunSim::Run(Int_t NEvents, Int_t)
{
    fApp->RunMC(NEvents);
    fWasMT = fApp->GetIsMT();
}

void FairRunSim::SetField(FairField* field)
{
    fField = field;
}

void FairRunSim::SetGenerator(FairPrimaryGenerator* Gen)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    fGen = Gen;
#pragma GCC diagnostic pop
}

void FairRunSim::SetMaterials(const char* MatFileName)
{
    TString Mat = "";
    TString work = getenv("GEOMPATH");
    work.ReplaceAll("//", "/");
    if (work.IsNull()) {
        work = getenv("VMCWORKDIR");
        Mat = work + "/geometry/";
        Mat.ReplaceAll("//", "/");
    } else {
        Mat = work;
        if (!Mat.EndsWith("/")) {
            Mat += "/";
        }
    }
    MatFname = Mat + MatFileName;
    LOG(info) << "Media file used: " << MatFname.Data();
}

void FairRunSim::SetGeoModel(const char* name)
{
    if (fName == "TGeant3") {
        fLoaderName = name;
        LOG(info) << "FairRun::SetGeoModel(): G3 native geometry model used ";
    } else {
        LOG(info) << "FairRun::SetGeoModel(): Geant3 MC engine only !";
        LOG(info) << "FairRun::SetGeoModel(): Method skipped ... ";
    }
}

void FairRunSim::SetPythiaDecayer(const TString& Config)
{
    /**switch On external decayer (Pythia). Config macro will be used */
    fPythiaDecayerConfig = Config;
    fPythiaDecayer = kTRUE;
}

void FairRunSim::SetUserDecay(const TString& Config)
{
    /**switch On user defined decay, Config  macro will be called  */
    fUserDecayConfig = Config;
    fUserDecay = kTRUE;
}

FairMCEventHeader* FairRunSim::GetMCEventHeader()
{
    if (nullptr == fMCEvHead) {
        fMCEvHead = new FairMCEventHeader();
    }
    return fMCEvHead;
}

FairGeoLoader& FairRunSim::GetGeometryLoader()
{
    assert(fGeoLoader);
    return *fGeoLoader;
}

void FairRunSim::ls(Option_t* option) const
{
    FairRun::ls(option);
    TROOT::IncreaseDirLevel();
    if (fGeoLoader) {
        fGeoLoader->ls(option);
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    if (fGen) {
        fGen->ls(option);
    }
#pragma GCC diagnostic pop
    if (fField) {
        fField->ls(option);
    }
    // if (fSimulationConfig) {
    //     fSimulationConfig->ls(option);
    // }
    ListOfModules->ls();
    fParticles->ls();
    fIons->ls();
    if (fMCEvHead) {
        fMCEvHead->ls(option);
    }
    if (fApp) {
        fApp->ls(option);
    }
    TROOT::DecreaseDirLevel();
}

TMCThreadLocal FairRunSim* FairRunSim::fginstance = nullptr;
