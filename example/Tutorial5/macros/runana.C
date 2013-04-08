{

  // ----  Load libraries   -------------------------------------------------
  // ----  Load libraries   -------------------------------------------------
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
  basiclibs();

  gSystem->Load("libGenVector");

  gSystem->Load("libGeoBase");
  gSystem->Load("libFairDB");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libMCStack");
  gSystem->Load("libField");
  gSystem->Load("libGen");

  //----  Load R3B specific libraries ---------------------------------------
  gSystem->Load("libR3Bbase");
  gSystem->Load("libR3BGen");
  gSystem->Load("libR3BPassive");
  gSystem->Load("libR3BData");
  gSystem->Load("libR3BCal");
  gSystem->Load("libR3BCalo");
  gSystem->Load("libR3BDch");
  gSystem->Load("libR3BGfi");
  gSystem->Load("libR3BLand");
  gSystem->Load("libR3BmTof");
  gSystem->Load("libR3BTof");
  gSystem->Load("libR3BTra");
  gSystem->Load("libR3BSTaRTra");
  gSystem->Load("libELILuMon");

  gSystem->Load("libTutorial5");

  // -----   Reconstruction run   -------------------------------------------
  FairRunAna* fRun= new FairRunAna();
  fRun->SetInputFile("dummysim.root");
  fRun->SetOutputFile("dummyana.root");

  // -----  Parameter database   --------------------------------------------
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open("par.root","READ");//RECREATE etc. like in TFile from root
  rtdb->setFirstInput(parInput1);

  /*
  FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
  parInput2->open("ascii-example.par","in");
  rtdb->setSecondInput(parInput2);
  */

  // Set the SQL IO as second input
  FairParTSQLIo* inp = new FairParTSQLIo();
  inp->open();
  rtdb->setSecondInput(inp);

  // -----   Tasks to run   -------------------------------------------------
  fRun->AddTask(new FairDbTutAccessRtdbTask());

  // -----   Intialise and run   --------------------------------------------
  fRun->Init();

  /*
  Bool_t kParameterMerged=kTRUE;
  FairParRootFileIo* parOutput = new FairParRootFileIo(kParameterMerged);
  parOutput->open("par_merged.root","RECREATE");//RECREATE etc. like in TFile from root
  rtdb->setOutput(parOutput);
  rtdb->saveOutput();
  */
  rtdb->print();

  fRun->Run();

}
