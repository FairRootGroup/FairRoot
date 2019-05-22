/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
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
#include "FairGenericVMCConfig.h"       // for FairGenericVMCConfig
#include "FairTask.h"                   // for FairTask
#include "FairTrajFilter.h"             // for FairTrajFilter

#include <iosfwd>                       // for ostream
#include "TCollection.h"                // for TIter
#include "TGeoManager.h"                // for gGeoManager
#include "TList.h"                      // for TList
#include "TObjString.h"                 // for TObjString
#include "TObject.h"                    // for TObject
#include "TROOT.h"                      // for TROOT, gROOT
#include "TSystem.h"                    // for TSystem, gSystem
#include "TRandom.h"                    // for gRandom
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
   fSimulationConfig(NULL),
   fUserConfig(""),
   fUserCuts("SetCuts.C"),
   fIsMT(kFALSE),
   fImportTGeoToVMC(kTRUE)

{
  if (fginstance) {
    Fatal("FairRun", "Singleton instance already exists.");
    return;
  }
  fginstance=this;
  fRunId=0;
  fAna=kFALSE;
}
//_____________________________________________________________________________
FairRunSim::~FairRunSim()
{

  LOG(debug) << "Enter Destructor of FairRunSim ";

  // delete fApp;

  /** List of Modules is filled via AddModule from the macro, but it
   is the responsibility of FairRunSim to call the destructors of
   the modules-
  */
  LOG(debug) << "Start deleting all registered modules" ;
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
  fRootManager->InitSink();
  
  CheckFlukaExec();

//  fOutFile=fRootManager->OpenOutFile(fOutname);
  LOG(info) << "==============  FairRunSim: Initialising simulation run ==============";

  FairGeoLoader* loader=new FairGeoLoader(fLoaderName->Data(), "Geo Loader");
  FairGeoInterface* GeoInterFace=loader->getGeoInterface();
  GeoInterFace->SetNoOfSets(ListOfModules->GetEntries());
  GeoInterFace->setMediaFile(MatFname.Data());
  GeoInterFace->readMedia();

  //  gSystem->cd(flout.Data());

  fApp= new FairMCApplication("Fair","The Fair VMC App",ListOfModules, MatFname);
  fApp->SetGenerator(fGen);

  // Add a Generated run ID to the FairRunTimeDb
  if ( fRunId == 0 ) {
      FairRunIdGenerator genid;
      // FairRuntimeDb *rtdb= GetRuntimeDb();
      fRunId = genid.generateId();
  }
  fRtdb->addRun(fRunId);

  fFileHeader->SetRunId(fRunId);
  /** Add Tasks to simulation if any*/
  fApp->AddTask(fTask);
  /** This call will create the container if it does not exist*/
  FairBaseParSet* par=dynamic_cast<FairBaseParSet*>(fRtdb->getContainer("FairBaseParSet"));
  if (par) {
    par->SetDetList(GetListOfModules());
    par->SetGen(GetPrimaryGenerator());
    par->SetBeamMom(fBeamMom);
  }

  /** This call will create the container if it does not exist*/
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
    LOG(info) << "Create visualisation manager ";
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
  if(par){
     par->SetContListStr(ContList);
     par->SetRndSeed(gRandom->GetSeed());
     par->setChanged();
     par->setInputVersion(fRunId,1);
  }
  if(geopar){
     geopar->setChanged();
     geopar->setInputVersion(fRunId,1);
  }

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
      LOG(info) << "---User path for Configuration is used: " 
		<< config_dir.Data();
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
  // Either setup the simulation with the provided user hook
  if (fUseSimSetupFunction) {
    fSimSetup();
  }
  else {
      if ( fSimulationConfig == NULL ) // RKRKRK COMMENT
          fSimulationConfig = new FairGenericVMCConfig();
      fSimulationConfig->Setup(GetName());
  }

  fApp->InitMC("foo", "bar");
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
  LOG(info) << "Media file used: " << MatFname.Data();
}
//_____________________________________________________________________________
void FairRunSim::SetGeoModel( char* name )
{
  if ( strncmp(fName,"TGeant3",7) == 0 ) {
    delete fLoaderName;
    fLoaderName = new TString(name);
    LOG(info) << "FairRun::SetGeoModel(): G3 native geometry model used ";
  } else {
    LOG(info) << "FairRun::SetGeoModel(): Geant3 MC engine only !";
    LOG(info) << "FairRun::SetGeoModel(): Method skipped ... ";
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



