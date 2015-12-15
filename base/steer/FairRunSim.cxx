/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//_____________________________________________________________________________
// -----                   FairRunSim source file                      -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
//_____________________________________________________________________________
#include "FairRunSim.h"

#include "FairBaseParSet.h"             // for FairBaseParSet
#include "FairGeoParSet.h"              // for FairGeoParSet
#include "FairField.h"                  // for FairField
#include "FairFileHeader.h"             // for FairFileHeader
#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairMCEventHeader.h"          // for FairMCEventHeader
#include "FairMesh.h"                   // for FairMesh
#include "FairModule.h"                 // for FairModule
#include "FairParSet.h"                 // for FairParSet
#include "FairPrimaryGenerator.h"       // for FairPrimaryGenerator
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunIdGenerator.h"         // for FairRunIdGenerator
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTask.h"                   // for FairTask
#include "FairTrajFilter.h"             // for FairTrajFilter

#include "Riosfwd.h"                    // for ostream
#include "TCollection.h"                // for TIter
#include "TGeoManager.h"                // for gGeoManager
#include "TList.h"                      // for TList
#include "TObjString.h"                 // for TObjString
#include "TObject.h"                    // for TObject
#include "TROOT.h"                      // for TROOT, gROOT
#include "TSystem.h"                    // for TSystem, gSystem

#include <stdlib.h>                     // for getenv, NULL
#include <string.h>                     // for strcmp, strncmp
#include <iostream>                     // for cout, endl, ostream

using std::cout;
using std::endl;

ClassImp(FairRunSim)
//_____________________________________________________________________________
FairRunSim::FairRunSim(Bool_t isMaster)
  :FairRun(isMaster),
   count(0),
   fApp(NULL),
   fBeamMom(0),
   fUseBeamMom(kFALSE),
   fGen(NULL),
   fMCEvHead(NULL),
   fField(NULL),
   fMapName(""),
   fIons(new TObjArray()),
   fParticles( new TObjArray()),
   ListOfModules(new TObjArray()),
   MatFname(""),
   fStoreTraj( kFALSE),
   fLoaderName( new TString("TGeo")),
   fPythiaDecayer(kFALSE),
   fPythiaDecayerConfig(""),
   fUserDecay(kFALSE),
   fUserDecayConfig(""),
   fRadLength(kFALSE),
   fRadMap(kFALSE),
   fRadGrid(kFALSE),
   fMeshList( new TObjArray() ),
   fUserConfig(""),
   fUserCuts("SetCuts.C")

{
  if (fginstance) {
    Fatal("FairRun", "Singleton instance already exists.");
    return;
  }
  fOutname="";
  fginstance=this;
  fRunId=0;
  fAna=kFALSE;
}
//_____________________________________________________________________________
FairRunSim::~FairRunSim()
{
  LOG(DEBUG) << "Enter Destructor of FairRunSim " << FairLogger::endl;
  /** List of Modules is filled via AddModule from the macro, but it
   is the responsibility of FairRunSim to call the destructors of
   the modules-
  */
  LOG(DEBUG) << "Start deleting all registered modules" 
	     << FairLogger::endl;
  ListOfModules->Delete();
  delete ListOfModules;
  LOG(DEBUG) << "Finish deleting all registered modules"
	     << FairLogger::endl;

  fIons->Delete();
  delete fIons;
  fParticles->Delete();
  delete fParticles;

  delete fApp;
  delete fField;
  delete fGen;
  delete fMCEvHead;
}
//_____________________________________________________________________________
FairRunSim* FairRunSim::Instance()
{
  return fginstance;
}
//_____________________________________________________________________________
void FairRunSim::AddModule (FairModule* Mod)
{
  ListOfModules->Add(Mod);
  Mod->SetModId(count++);
}
//_____________________________________________________________________________
void FairRunSim::AddMesh (FairMesh* Mesh)
{
  Mesh->print();
  Mesh->calculate();
  fMeshList->Add(Mesh);
}
//_____________________________________________________________________________
TObjArray* FairRunSim::GetUserDefIons()
{
  /** return the array of user defined ions*/
  return fIons;
}
//_____________________________________________________________________________
TObjArray* FairRunSim::GetUserDefParticles()
{
  /** return the array of user defined particles*/
  return fParticles;
}
//_____________________________________________________________________________
void FairRunSim::Init()
{
  /**Initialize the simulation session*/

  CheckFlukaExec();

//  fOutFile=fRootManager->OpenOutFile(fOutname);
  LOG(INFO) << "==============  FairRunSim: Initialising simulation run ==============" << FairLogger::endl;

  FairGeoLoader* loader=new FairGeoLoader(fLoaderName->Data(), "Geo Loader");
  FairGeoInterface* GeoInterFace=loader->getGeoInterface();
  GeoInterFace->SetNoOfSets(ListOfModules->GetEntries());
  GeoInterFace->setMediaFile(MatFname.Data());
  GeoInterFace->readMedia();

  //  gSystem->cd(flout.Data());

  fApp= new FairMCApplication("Fair","The Fair VMC App",ListOfModules, MatFname);
  fApp->SetGenerator(fGen);

  // Add a Generated run ID to the FairRunTimeDb
  FairRunIdGenerator genid;
  // FairRuntimeDb *rtdb= GetRuntimeDb();
  fRunId = genid.generateId();
  fRtdb->addRun(fRunId);

  fFileHeader->SetRunId(fRunId);
  /** Add Tasks to simulation if any*/
  fApp->AddTask(fTask);

  FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
  if (par) {
    par->SetDetList(GetListOfModules());
    par->SetGen(GetPrimaryGenerator());
    par->SetBeamMom(fBeamMom);
  }

  FairGeoParSet* geopar=dynamic_cast<FairGeoParSet*>(fRtdb->getContainer("FairGeoParSet"));
  if (geopar) {
    geopar->SetGeometry(gGeoManager);
  }

  // Set global Parameter Info

  if(fPythiaDecayer) {
    fApp->SetPythiaDecayer(fPythiaDecayer);
    if (fPythiaDecayerConfig) {
      fApp->SetPythiaDecayerConfig(fPythiaDecayerConfig);
    }
  }
  if(fUserDecay) {
    fApp->SetUserDecay(fUserDecay);
    if (fUserDecayConfig) {
      fApp->SetUserDecayConfig(fUserDecayConfig);
    }
  }
  // on/off visualisation
  if( fStoreTraj ) {
    LOG(INFO) << "Create visualisation manager " << FairLogger::endl;
    new FairTrajFilter();
  }
  if(fRadLength) {
    fApp->SetRadiationLengthReg(fRadLength);
  }
  if(fRadMap) {
    fApp->SetRadiationMapReg(fRadMap);
  }
  if(fRadGrid) {
    fApp->AddMeshList(fMeshList);
  }

  if(fField) { fField->Init(); }
  fApp->SetField(fField);
  SetFieldContainer();

  TList* containerList=fRtdb->getListOfContainers();
  TIter next(containerList);
  FairParSet* cont;
  TObjArray* ContList= new TObjArray();
  while ((cont=dynamic_cast<FairParSet*>(next()))) {
    ContList->Add(new TObjString(cont->GetName()));
  }

  par->SetContListStr(ContList);
  par->setChanged();
  par->setInputVersion(fRunId,1);

  geopar->setChanged();
  geopar->setInputVersion(fRunId,1);



  /**Set the configuration for MC engine*/
  SetMCConfig();
  fRootManager->WriteFileHeader(fFileHeader);

}
//_____________________________________________________________________________
void FairRunSim::SetFieldContainer()
{
  if (fField) {
    fField->FillParContainer();
  }
}
//_____________________________________________________________________________
void FairRunSim::CheckFlukaExec()
{
  /** Private method for setting FLUKA simulation*/
  TString work = getenv("VMCWORKDIR");
  TString work_config=work+"/gconfig/";
  work_config.ReplaceAll("//","/");

  TString config_dir= getenv("CONFIG_DIR");
  config_dir.ReplaceAll("//","/");
  if (!config_dir.EndsWith("/")) { config_dir+="/"; }

  TString flout;
  if(strcmp(GetName(),"TFluka") == 0 ) {
    TString flexec="run_fluka.sh";
    if (TString(gSystem->FindFile(config_dir.Data(),flexec)) != TString("")) {
      LOG(INFO) << "---User path for Configuration is used: " 
		<< config_dir.Data() << FairLogger::endl;
    } else {
      flexec=work_config+"run_fluka.sh";
    }
    gSystem->Exec(flexec.Data());
    // More generic for different macro
    // dir layout <D.B>
    TString macrodir = getenv("PWD");
    cout << macrodir << endl;
    flout = macrodir + "/fluka_out" ;
    flout.ReplaceAll("//","/");
    gSystem->cd(flout.Data());
  }
}
//_____________________________________________________________________________
void FairRunSim::SetMCConfig()
{
  /** Private method for setting simulation and/or Geane configuration and cuts*/

  TString work = getenv("VMCWORKDIR");
  TString work_config=work+"/gconfig/";
  work_config.ReplaceAll("//","/");

  TString Lib_config= getenv("GEANT4VMC_MACRO_DIR");
  Lib_config.ReplaceAll("//","/");
  if (!Lib_config.EndsWith("/")) { Lib_config+="/"; }

  TString config_dir= getenv("CONFIG_DIR");
  config_dir.ReplaceAll("//","/");

  Bool_t AbsPath=kFALSE;

  TString LibMacro;
  TString LibFunction;
  TString ConfigMacro;
  TString cuts=fUserCuts;
  //----------------------------------------------Geant4 Config-----------------------------------------
  if(strcmp(GetName(),"TGeant4") == 0 ) {
    TString g4LibMacro="g4libs.C";
    TString g4Macro;
    if(fUserConfig.IsNull()) {
      g4Macro="g4Config.C";
      fUserConfig = g4Macro;
    } else {
      if (fUserConfig.Contains("/")) { AbsPath=kTRUE; }
      g4Macro = fUserConfig;
      LOG(INFO) << "---------------User config is used: " 
		<< g4Macro.Data() << FairLogger::endl;
    }
    if (TString(gSystem->FindFile(config_dir.Data(),g4LibMacro)) != TString("")) { //be carfull after this call the string g4LibMacro is empty if not found!!!!
      LOG(INFO) << "---User path for Configuration (g4libs.C) is used: " 
		<< config_dir.Data() << FairLogger::endl;
    } else {
      g4LibMacro=Lib_config+"g4libs.C";
    }
    LibMacro=g4LibMacro;
    LibFunction="g4libs()";
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(),g4Macro)) != TString("")) {
      LOG(INFO) << "---User path for Configuration (g4Config.C) is used: " 
		<< config_dir.Data() << FairLogger::endl;
      ConfigMacro=g4Macro;
    } else {
      if(AbsPath) { ConfigMacro = fUserConfig; }
      else { ConfigMacro =work_config+fUserConfig; }
    }
    //----------------------------------------------Geant3 Config-----------------------------------------
  } else if(strcmp(GetName(),"TGeant3") == 0 ) {
    TString g3LibMacro="g3libs.C";
    TString g3Macro="g3Config.C";
    if(fUserConfig.IsNull()) {
      g3Macro="g3Config.C";
      fUserConfig = g3Macro;
      LOG(INFO) << "-------------- Standard Config is called ------------------------------------" << FairLogger::endl;
    } else {
      if (fUserConfig.Contains("/")) { AbsPath=kTRUE; }
      g3Macro = fUserConfig;
      LOG(INFO) << "---------------User config is used: " 
		<< g3Macro.Data() << FairLogger::endl;
    }
    if (TString(gSystem->FindFile(config_dir.Data(),g3LibMacro)) != TString("")) {
      LOG(INFO) << "---User path for Configuration (g3libs.C) is used: " 
		<< config_dir.Data() << FairLogger::endl;
    } else {
      g3LibMacro=work_config+"g3libs.C";
    }
    LibMacro=g3LibMacro;
    LibFunction="g3libs()";
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(),g3Macro)) != TString("")) {
      LOG(INFO) << "---User path for Configuration (g3Config.C) is used: "
		<< config_dir.Data() << FairLogger::endl;
      ConfigMacro=g3Macro;
    } else {
      if(AbsPath) { ConfigMacro = fUserConfig; }
      else { ConfigMacro =work_config+fUserConfig; }
    }
    //----------------------------------------------Fluka Config-----------------------------------------
  } else if(strcmp(GetName(),"TFluka") == 0 ) {
    TString flLibMacro="fllibs.C";
    TString flMacro="flConfig.C";
    if(fUserConfig.IsNull()) {
      flMacro="flConfig.C";
      fUserConfig=flMacro;
    } else {
      if (fUserConfig.Contains("/")) { AbsPath=kTRUE; }
      flMacro = fUserConfig;
      LOG(INFO) << "---------------User config is used: " 
		<< flMacro.Data() << FairLogger::endl;
    }
    if (TString(gSystem->FindFile(config_dir.Data(), flLibMacro)) != TString("")) {
      LOG(INFO) << "---User path for Configuration (fllibs.C) is used: "
		<< config_dir.Data() << FairLogger::endl;
    } else {
      flLibMacro=work_config+"fllibs.C";
    }
    LibMacro=flLibMacro;
    LibFunction="fllibs()";
    if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(),flMacro)) != TString("")) {
      LOG(INFO) << "---User path for Configuration (flConfig.C) is used: " 
		<< config_dir.Data() << FairLogger::endl;
      ConfigMacro=flMacro;
    } else {
      if(AbsPath) { ConfigMacro = fUserConfig; }
      else { ConfigMacro =work_config+fUserConfig; }
    }
  }
  //----------------------------------------------SetCuts------------------------------------------------
  if (TString(gSystem->FindFile(config_dir.Data(),cuts)) != TString("")) {
    LOG(INFO) << "---User path for Cuts and Processes (SetCuts.C) is used: "
	      << config_dir.Data() << FairLogger::endl;
  } else {
    cuts =work_config+ fUserCuts;
  }
  //--------------------------------------Now load the Config and Cuts------------------------------------
  gROOT->LoadMacro(LibMacro.Data());
  gROOT->ProcessLine(LibFunction.Data());

  gROOT->LoadMacro(ConfigMacro.Data());
  gROOT->ProcessLine("Config()");

  gROOT->LoadMacro(cuts);
  gROOT->ProcessLine("SetCuts()");

  fApp->InitMC(ConfigMacro.Data(), cuts.Data());
}

//_____________________________________________________________________________
void FairRunSim::Run(Int_t NEvents, Int_t)
{
  fApp->RunMC(NEvents);
}
//_____________________________________________________________________________
void FairRunSim::SetField(FairField* field)
{
  fField=field;
}
//_____________________________________________________________________________
void FairRunSim::SetGenerator(FairPrimaryGenerator* Gen)
{
  fGen=Gen;
}
//_____________________________________________________________________________
void FairRunSim::SetMaterials(const char* MatFileName)
{
  TString Mat="";
  TString work = getenv("GEOMPATH");
  work.ReplaceAll("//","/");
  if (work.IsNull()) {
    work = getenv("VMCWORKDIR");
    Mat=work+"/geometry/";
    Mat.ReplaceAll("//","/");
  } else {
    Mat=work;
    if (!Mat.EndsWith("/")) { Mat+="/"; }
  }
  MatFname=Mat+MatFileName;
  LOG(INFO) << "Media file used: " << MatFname.Data() << FairLogger::endl;
}
//_____________________________________________________________________________
void FairRunSim::SetGeoModel( char* name )
{
  if ( strncmp(fName,"TGeant3",7) == 0 ) {
    if (fLoaderName) { delete fLoaderName; }
    fLoaderName = new TString(name);
    LOG(INFO) << "FairRun::SetGeoModel(): G3 native geometry model used "
	      << FairLogger::endl;
  } else {
    LOG(INFO) << "FairRun::SetGeoModel(): Geant3 MC engine only !"
	      << FairLogger::endl;
    LOG(INFO) << "FairRun::SetGeoModel(): Method skipped ... "
	      << FairLogger::endl;
  }
}
//_____________________________________________________________________________
void  FairRunSim::SetPythiaDecayer(const TString& Config )
{
  /**switch On external decayer (Pythia). Config macro will be used */
  fPythiaDecayerConfig = Config;
  fPythiaDecayer =kTRUE;

}
//_____________________________________________________________________________

void  FairRunSim::SetUserDecay(const TString& Config)
{
  /**switch On user defined decay, Config  macro will be called  */
  fUserDecayConfig = Config;
  fUserDecay = kTRUE;
}
//_____________________________________________________________________________
FairMCEventHeader*  FairRunSim::GetMCEventHeader()
{
  if ( NULL == fMCEvHead ) { fMCEvHead = new FairMCEventHeader(); }
  return fMCEvHead;
}
//_____________________________________________________________________________

TMCThreadLocal FairRunSim* FairRunSim::fginstance= 0;



