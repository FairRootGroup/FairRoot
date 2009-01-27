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
  geant3->SetStack( st ) ;

  // ******* GEANT3 configuration for simulated Runs  *******
    geant3->SetTRIG(1);         //Number of events to be processed
    geant3->SetSWIT(4, 100);
    geant3->SetDEBU(0, 0, 1);
    geant3->SetDCAY(1);
    geant3->SetPAIR(1);
    geant3->SetCOMP(1);
    geant3->SetPHOT(1);
    geant3->SetPFIS(0); //
    geant3->SetDRAY(1);
    geant3->SetANNI(1);
    geant3->SetBREM(1);
    geant3->SetMUNU(1);
    geant3->SetCKOV(1);
    geant3->SetHADR(3);         //Select pure GEANH (HADR 1) or GEANH/NUCRIN (HADR 3) //5==GCALOR
    geant3->SetLOSS(1);
    geant3->SetMULS(1);
    geant3->SetRAYL(1);
    geant3->SetSTRA(1);


    geant3->SetAUTO(0);         //Select automatic STMIN etc... calc. (AUTO 1) or manual (AUTO 0)
    geant3->SetABAN(0);         //Restore 3.16 behaviour for abandoned tracks
    geant3->SetOPTI(2);         //Select optimisation level for GEANT geometry searches (0,1,2)
    geant3->SetERAN(5.e-7);


    Float_t cut =  1. e-3;        // 1MeV cut by default
    Float_t tofmax = 1.e10;
    // Float_t cut2 =  1.e-10; // 1 keV?
    Float_t cut2 = cut;
    Float_t cut3 =50.e-6 ; // Threshold for delta electrons

    Float_t cut5[5] ={0,0,0,0,0};
    // set cuts here 
    //             GAM ELEC NHAD CHAD MUON EBREM MUHAB EDEL MUDEL MUPA TOFMAX
//    geant3->SetCUTS(cut2, cut2, cut2, cut2, cut, cut2, cut2, cut3, cut2, cut2,
//                    tofmax);
    geant3->SetCUTS(cut2, cut2, cut2, cut2, cut, cut2, cut2, cut2, cut2, cut2,
                    tofmax,cut5);

   
}


