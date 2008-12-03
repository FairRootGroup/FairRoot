// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#include "CbmGeane.h"

#include "CbmMCApplication.h"
#include "CbmField.h"

#include "TGeoManager.h"
#include "TString.h"
#include "TGeoManager.h"
#include "TVirtualMC.h"
#include "TROOT.h"
#include "TSystem.h"

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
CbmGeane::CbmGeane() {  	
  cout << "This ctr should not be called by user !!"<< endl; 
}
// -----   Standard constructor   ------------------------------------------
CbmGeane::CbmGeane(const char* name, TString fUserConfig,   TString fUserCuts )
  : TObject(){

  TGeoManager* geom = new TGeoManager("Geometry", "Geane geometry");
  TGeoManager *geom2= TGeoManager::Import(name);
  
  fApp= new CbmMCApplication(kTRUE);

	  TString LibMacro;
	  TString LibFunction;
	  TString ConfigMacro;
	  TString cuts=fUserCuts;
	  
	  
	  TString work = getenv("VMCWORKDIR");
	  TString work_config=work+"/gconfig/";
	  TString config_dir= getenv("CONFIG_DIR");
	  Bool_t AbsPath=kFALSE;
	  if (!config_dir.EndsWith("/")) config_dir+="/";
	  
	  
	  TString geaneLibMacro="g3libs.C";
	  TString geaneMacro;
	  if(fUserConfig.IsNull()){
		  geaneMacro="Geane.C";
		  fUserConfig = geaneMacro;
	  }else{
		  if (fUserConfig.Contains("/")) AbsPath=kTRUE;	
		  geaneMacro = fUserConfig;
		  cout << "---------------User config is used :  " << geaneMacro.Data() <<"-----------------"<< endl;
	  }
	  if (TString(gSystem->FindFile(config_dir.Data(),geaneLibMacro)) != TString("")){
          cout << "---User path for Configuration (g3libs.C) is used : " <<  config_dir.Data() << endl;
	  }else{
          geaneLibMacro=work_config+"g3libs.C";
	  }
	  LibMacro=geaneLibMacro;
	  LibFunction="g3libs()";			
	  
	  if (!AbsPath && TString(gSystem->FindFile(config_dir.Data(),geaneMacro)) != TString("")){
          cout << "---User path for Configuration (Geane.C) is used : " <<  config_dir.Data() << endl;
		  ConfigMacro =geaneMacro;
	  }else{
		  if(AbsPath)  ConfigMacro = fUserConfig;				
		  else ConfigMacro =work_config+fUserConfig;
	  }
	
	  gROOT->LoadMacro(LibMacro.Data());
	  gROOT->ProcessLine(LibFunction.Data());
	  
	  gROOT->LoadMacro(ConfigMacro.Data());
	  gROOT->ProcessLine("Config()");
	  
	  gROOT->LoadMacro(cuts);
	  gROOT->ProcessLine("SetCuts()");
	  
	  
	  
	  
  /*TString work = getenv("VMCWORKDIR"); 
  TString g3LibMacro = work + "/gconfig/g3libs.C";
  gROOT->LoadMacro(g3LibMacro.Data());
  gROOT->ProcessLine("g3libs()");
  TString g3Macro = work+"/gconfig/Geane.C";*/
	  
  fApp->InitMC(ConfigMacro.Data(), "");
  cout <<"I- CbmGeane::CbmGeane:  Geane is Initialized " << endl; 
}
// -----   Destructor   ----------------------------------------------------
CbmGeane::~CbmGeane() {
  
}
void CbmGeane::SetField(CbmField *field)
{
   if(field && fApp) {
      cout << "-I- Geane:  Magnetic Field is Set and will be used" << endl;
      field->Print();
      fApp->SetField(field);
    }
}

ClassImp(CbmGeane)
