{
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

  FairRunSim* fRun = new FairRunSim();
  fRun->SetName("TGeant3");                      // Transport engine
  fRun->SetOutputFile("dummysim.root");          // Output file
  fRun->SetMaterials("media_r3b.geo");

  FairModule* Cave= new R3BCave("CAVE");
  Cave->SetGeometryFileName("r3b_cave.geo");
  fRun->AddModule(Cave);

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  fRun->SetGenerator(primGen);

  FairRuntimeDb* rtdb=fRun->GetRuntimeDb();
  Bool_t kParameterMerged=kTRUE;
  FairParRootFileIo* output=new FairParRootFileIo(kParameterMerged);
  output->open("par.root","RECREATE");
  rtdb->setOutput(output);

  fRun->Init();
  fRun->Run(10);
  rtdb->saveOutput();

}

