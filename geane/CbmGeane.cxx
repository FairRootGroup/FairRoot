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

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
CbmGeane::CbmGeane() {  	
  cout << "This ctr should not be called by user !!"<< endl; 
}
// -----   Standard constructor   ------------------------------------------
CbmGeane::CbmGeane(const char* name)
  : TObject(){

  TGeoManager* geom = new TGeoManager("Geometry", "Geane geometry");
  TGeoManager *geom2= TGeoManager::Import(name);
  
  fApp= new CbmMCApplication(kTRUE);
  TString work = getenv("VMCWORKDIR"); 
  TString g3LibMacro = work + "/gconfig/g3libs.C";
  gROOT->LoadMacro(g3LibMacro.Data());
  gROOT->ProcessLine("g3libs()");
  TString g3Macro = work+"/gconfig/Geane.C";
  fApp->InitMC(g3Macro.Data());
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
