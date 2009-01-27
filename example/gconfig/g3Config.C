// $Id: g3Config.C,v 1.1.1.1 2005/06/23 07:14:09 dbertini Exp $
//
// Configuration macro for Geant3 VirtualMC 

void Config()
{
  FairRunSim *fRun = FairRunSim::Instance();
  TString* gModel = fRun->GetGeoModel();
  TGeant3* geant3 = NULL;
  if ( strncmp(gModel->Data(),"TGeo",4) == 0 ) {
     geant3
          = new  TGeant3TGeo("C++ Interface to Geant3");
      cout << "-I- G3Config: Geant3 with TGeo has been created."
           << endl;
  }else{
     geant3
          = new  TGeant3("C++ Interface to Geant3");
      cout << "-I- G3Config: Geant3 native has been created."
             << endl;
  }
  // create Fair Specific Stack
  FairStack *st = new FairStack();
  st->SetMinPoints(0);
  st->StoreSecondaries(kTRUE);
  geant3->SetStack( st ) ;

  // ******* GEANT3  specific configuration for simulated Runs  *******
    geant3->SetTRIG(1);         //Number of events to be processed
    geant3->SetSWIT(4, 100);
    geant3->SetDEBU(0, 0, 1);
  
    geant3->SetRAYL(1);
    geant3->SetSTRA(1);
    geant3->SetAUTO(0);         //Select automatic STMIN etc... calc. (AUTO 1) or manual (AUTO 0)
    geant3->SetABAN(0);         //Restore 3.16 behaviour for abandoned tracks
    geant3->SetOPTI(2);         //Select optimisation level for GEANT geometry searches (0,1,2)
    geant3->SetERAN(5.e-7);
    geant3->SetCKOV(1);     // cerenkov photons 
  // set common stuff 
    TString configm(gSystem->Getenv("VMCWORKDIR"));
    TString cuts = configm + "/gconfig/SetCuts.C";
    cout << "Physics cuts with script \n "<<  cuts.Data() << endl;
    Int_t cut=gROOT->LoadMacro(cuts.Data());
    if(cut==0)gInterpreter->ProcessLine("SetCuts()"); 

}


