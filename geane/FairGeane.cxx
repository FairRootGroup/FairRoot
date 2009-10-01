// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#include "FairGeane.h"

#include "FairMCApplication.h"
#include "FairField.h"
#include "FairRunAna.h"
#include "TGeoManager.h"
#include "TString.h"
#include "TGeoManager.h"
#include "TVirtualMC.h"
#include "TROOT.h"
#include "TSystem.h"

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
//FairGeane::FairGeane() {  	
//  cout << "This ctr should not be called by user !!"<< endl; 
//}
// -----   Standard constructor   ------------------------------------------
FairGeane::FairGeane(const char* name, TString UserConfig,   TString UserCuts )
:  FairTask("Geane Application"),
  fApp(new FairMCApplication(kTRUE)),
  fName(name),
  fUserConfig(UserConfig),  
  fUserCuts (UserCuts)
{
     //Create a new Geometry
     new TGeoManager("Geometry", "Geane geometry");
     // now import the geometry from file to the empty TGeo	  
     TGeoManager::Import(name);
  
  }


FairGeane::FairGeane(TString UserConfig,   TString UserCuts )
: FairTask("Geane Application"),
  fApp(new FairMCApplication(kTRUE)),
  fName(""),
  fUserConfig(UserConfig),  
  fUserCuts (UserCuts)
{

	
}

void  FairGeane::SetParTask()
{

	cout <<  "------------------------FairGeane::SetParTask()------------------------------" << endl;
}

InitStatus FairGeane::Init()
{

	cout <<  "------------------------FairGeane::Init ()------------------------------" << endl;
	
    TString LibMacro;
	TString LibFunction;
	TString ConfigMacro;
	TString cuts=fUserCuts;
	if(cuts== TString(""))cuts="SetCuts.C";
	
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
	
	if (!AbsPath &&TString(gSystem->FindFile(config_dir.Data(),cuts)) != TString("")){
		cout << "---User path for Cuts and Processes  (SetCuts.C) is used : " <<  config_dir.Data() << endl;
	}else{
		cuts =work_config+ "SetCuts.C";
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
	FairField *field=FairRunAna::Instance()->GetField();
	field->Print();
	fApp->SetField(field);
	
	fApp->InitMC(ConfigMacro.Data(), "");
	 
	cout <<"I- FairGeane::FairGeane:  Geane is Initialized " << endl; 
	
    
}




// -----   Destructor   ----------------------------------------------------




FairGeane::~FairGeane() {
  
}
void FairGeane::SetField(FairField *field)
{
   if(field && fApp) {
    //  cout << "-I- Geane:  Magnetic Field is Set and will be used" << endl;
    //   field->Print();
    //  fApp->SetField(field);
    }
}

ClassImp(FairGeane)
