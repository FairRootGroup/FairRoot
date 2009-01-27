/// Configuration macro for Geant3 VirtualMC 

void Config()
{

    new  TFluka("C++ Interface to Fluka", 1/*verbositylevel*/);

    cout << "GConfig: Fluka has been created." << endl;
  
    CbmStack *st = new CbmStack();
    st->SetMinPoints(0);
    gMC->SetStack( st ) ;
    gMC->SetProcess("CKOV",1);

   // set the common cuts 
    TString configm(gSystem->Getenv("VMCWORKDIR"));
    TString cuts = configm + "/gconfig/SetCuts.C";
    cout << "Physics cuts with script \n "<<  cuts.Data() << endl;
    Int_t cut=gROOT->LoadMacro(cuts.Data());
    if(cut==0)gInterpreter->ProcessLine("SetCuts()"); 
}


