
#include "CbmRunSim.h"
#include "CbmRootManager.h"
#include "CbmTrajFilter.h"
#include "CbmBaseParSet.h"
#include "CbmRunIdGenerator.h"
#include "CbmModule.h"
#include "CbmField.h"
#include "CbmRuntimeDb.h"
#include "CbmGeoLoader.h"
#include "CbmGeoInterface.h"
#include "TROOT.h"
#include "TSystem.h"
#include <iostream>

using std::cout;
using std::endl;

ClassImp(CbmRunSim)

CbmRunSim::CbmRunSim()
  :CbmRun(),
   count(0),
   fApp(0),                                   
   fGen(0),
   fField(0),
   fMapName(""),
   fIons(new TObjArray()),
   fParticles( new TObjArray()),
   ListOfModules(new TObjArray()),
   MatFname(""),
   fStoreTraj( kFALSE),
   fLoaderName( new TString("TGeo")),
   fPythiaDecayer(kFALSE),
   fUserDecay(kFALSE),
   fRadLength(kFALSE)

{
  if (fginstance) {
      Fatal("CbmRun", "Singleton instance already exists.");
      return;
  } 
 

  Outfname="";
  fginstance=this;
  fRunId=0;
  fAna=kFALSE;
 
}

CbmRunSim::~CbmRunSim()
{
   delete ListOfModules;
   delete fApp;
   delete fIons;
   delete fParticles;    

}
CbmRunSim * CbmRunSim::Instance(){

        return fginstance;
}
void CbmRunSim::AddModule (CbmModule *Mod)
{
  ListOfModules->Add(Mod);
  Mod->SetModId(count++);
}

TObjArray *CbmRunSim::GetUserDefIons()
{
  /** return the array of user defined ions*/
  return fIons;
}

TObjArray *CbmRunSim::GetUserDefParticles()                              
{
  /** return the array of user defined particles*/
  return fParticles;
}

void CbmRunSim::Init()
{
    /**Initialize the simulation session*/
    TString work = getenv("VMCWORKDIR");
    TString flout;
    if(strcmp(GetName(),"TFluka") == 0 ){
       TString flexec=work +"/gconfig/run_fluka.sh";
       gSystem->Exec(flexec.Data());
       flout = work + "/macro/run/fluka_out" ;
       gSystem->cd(flout.Data());
     }
    
    fOutFile=fRootManager->OpenOutFile(Outfname);
    cout << endl;
    cout << "==============  CbmRunSim: Initialising simulation run  "
       << "==============" << endl;
     
    CbmGeoLoader *loader=new CbmGeoLoader(fLoaderName->Data(), "Geo Loader");
    CbmGeoInterface *GeoInterFace=loader->getGeoInterface();
    GeoInterFace->SetNoOfSets(ListOfModules->GetEntries());
    GeoInterFace->setMediaFile(MatFname.Data());
    GeoInterFace->readMedia();
    
    gSystem->cd(flout.Data());

       fApp= new CbmMCApplication("Cbm","The Cbm VMC App",ListOfModules, MatFname);
       fApp->SetGenerator(fGen);
    
    // Add a Generated run ID to the CbmRunTimeDb
    CbmRunIdGenerator genid;
   // CbmRuntimeDb *rtdb= GetRuntimeDb();
    fRunId = genid.generateId();
    fRtdb->addRun(fRunId);

    // Set global Parameter Info
    CbmBaseParSet* par=(CbmBaseParSet*)(fRtdb->getContainer("CbmBaseParSet"));
    par->SetDetList(GetListOfModules());
    par->SetGen(GetPrimaryGenerator());
    par->setChanged();
    par->setInputVersion(GetRunId(),1);
 
    if(fPythiaDecayer){
       fApp->SetPythiaDecayer(fPythiaDecayer);
    }
    if(fUserDecay){
       fApp->SetUserDecay(fUserDecay);
    }
    // on/off visualisation
    if( fStoreTraj ) {
        cout << "CbmRunSim::Init() create visualisation manager "<<endl; 
	new CbmTrajFilter();  
    }
    if(fRadLength){
        fApp->SetRadiationLengthReg(fRadLength);
    }
 
 
    fApp->AddTask(fTask);
    
    if(fField)fField->Init();
    fApp->SetField(fField);

    
    if (strcmp(GetName(),"TGeant4") == 0 ) {
      TString g4LibMacro = work + "/gconfig/g4libs.C";
      gROOT->LoadMacro(g4LibMacro.Data());
      gROOT->ProcessLine("g4libs()");
      TString g4Macro = work + "/gconfig/g4Config.C";
      fApp->InitMC(g4Macro.Data());
    }else if(strcmp(GetName(),"TGeant3") == 0 ){
      TString g3LibMacro = work + "/gconfig/g3libs.C";
      gROOT->LoadMacro(g3LibMacro.Data());
      gROOT->ProcessLine("g3libs()");
      TString g3Macro = work+"/gconfig/g3Config.C";
      fApp->InitMC(g3Macro.Data());
    }else if(strcmp(GetName(),"TFluka") == 0 ){
      TString flLibMacro = work + "/gconfig/fllibs.C";
      gROOT->LoadMacro(flLibMacro.Data());
      gROOT->ProcessLine("fllibs()");
      TString flMacro = work+"/gconfig/flConfig.C";
      gSystem->cd(flout.Data());
      fApp->InitMC(flMacro.Data()); 
    }else{
      TString geaneLibMacro = work + "/gconfig/g3libs.C";
      gROOT->LoadMacro(geaneLibMacro.Data());
      gROOT->ProcessLine("g3libs()");
      TString geaneMacro = work+"/gconfig/Geane.C";
      fApp->InitMC(geaneMacro.Data());
    }
    
         
  
}
void CbmRunSim::Run(Int_t NStart, Int_t NStop)
{
  fApp->RunMC(NStart);
}
void CbmRunSim::SetField(CbmField *field)
{
  fField=field;
}
void CbmRunSim::SetGenerator(CbmPrimaryGenerator *Gen)
{
  fGen=Gen;
}

void CbmRunSim::SetMaterials(const char * MatFileName)
{
  TString work = getenv("VMCWORKDIR"); 
  TString Mat=work+"/geometry/";
  MatFname=Mat+MatFileName;
  cout << "-I- CbmRun::SetMaterials() Media file used: "<< MatFname << endl;
}

void CbmRunSim::SetGeoModel( char * name ) 
{
    if ( strncmp(fName,"TGeant3",7) == 0 ){
      if (fLoaderName) delete fLoaderName;
      fLoaderName = new TString(name);
      cout << " -I-  CbmRun::SetGeoModel(): G3 native geometry model used " << endl;
    }else {
      cout << " -E-  CbmRun::SetGeoModel(): Geant3 MC engine only !" << endl;
      cout << " -E-  CbmRun::SetGeoModel(): Method skipped ... " << endl;
    }
}

CbmRunSim *CbmRunSim::fginstance= 0;
