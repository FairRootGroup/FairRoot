// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#include "FairGeaneNew.h"
#include "GeaneMCApplication.h"
#include "FairMCApplication.h"

#include "TGeant3TGeo.h"
#include "TGeoManager.h"
#include "TString.h"
#include "TVirtualMC.h"
#include "TROOT.h"
#include "TSystem.h"
#include<iostream>

// -----   Default constructor   -------------------------------------------
FairGeaneNew::FairGeaneNew() {  	
}
// -----   Standard constructor   ------------------------------------------
FairGeaneNew::FairGeaneNew(const char* name){
  TGeoManager* geom = new TGeoManager("Geometry", "Geane geometry");
  TGeoManager::Import(name);
  //FairMCApplication * app = new FairMCApplication(kTRUE);
  GeaneMCApplication * app = new GeaneMCApplication();
  //  new GeaneMCApplication();
  gSystem->Load("libgeant321.so");
  //  new  TGeant3TGeo("C++ Interface to Geant3");



  gSystem->Load("libgeant321.so");

  TString work = getenv("VMCWORKDIR");
  TString work_config=work+"/gconfig/";
  TString ConfigMacro=work_config+"Geane.C";
  TString CutsMacro=work_config+"SetCuts.C";
  
  gROOT->LoadMacro(ConfigMacro.Data());
  gROOT->ProcessLine("Config()");
  gROOT->LoadMacro(CutsMacro);
  gROOT->ProcessLine("SetCuts()");

  app->InitMC();

}
// -----   Destructor   ----------------------------------------------------
FairGeaneNew::~FairGeaneNew() {
  
}


ClassImp(FairGeaneNew)
