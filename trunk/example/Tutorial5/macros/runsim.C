{

  TString dir = getenv("VMCWORKDIR");
  TString tutdir = dir + "/example/Tutorial5";

  TString tut_geomdir = dir + "/example/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());

  TString tut_configdir = dir + "/example/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  FairRunSim* fRun = new FairRunSim();
  fRun->SetName("TGeant3");                      // Transport engine
  fRun->SetOutputFile("dummysim.root");          // Output file
  fRun->SetMaterials("media.geo");

  FairModule* Cave= new FairCave("CAVE");
  Cave->SetGeometryFileName("cave.geo");
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

