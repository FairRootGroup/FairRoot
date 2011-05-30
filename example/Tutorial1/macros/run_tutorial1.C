void run_tutorial1(Int_t nEvents = 10)
{
  
  TString dir = getenv("VMCWORKDIR");
  TString tutdir = dir + "/example/Tutorial1";

  TString tut_geomdir = dir + "/example/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());

  TString tut_geomdir = dir + "/example/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_geomdir.Data());

  TString partName[] = {"pions","eplus","proton"};
  Int_t   partPdgC[] = {    211,     11,    2212};
  Int_t chosenPart  = 0;
  
  Double_t momentum = 2.;

  Double_t theta    = 0.;

  TString outDir = "./";

  // Output file name
  TString outFile = Form("%s/tutorial1_%s.mc_p%1.3f_t%1.0f_n%d.root",
			 outDir.Data(),
			 partName[chosenPart].Data(),
			 momentum,
			 theta,
			 nEvents);
  
  // Parameter file name
  TString parFile = Form("%s/tutorial1_%s.params_p%1.3f_t%1.0f_n%d.root",
			 outDir.Data(),
			 partName[chosenPart].Data(),
			 momentum,
			 theta,
			 nEvents);
/*
  TString parFile = Form("%s/tutorial1_%s.params_p%1.3f_t%1.0f_n%d.txt",
			 outDir.Data(),
			 partName[chosenPart].Data(),
			 momentum,
			 theta,
			 nEvents);
*/  

  // In general, the following parts need not be touched
  // ========================================================================

  // ----    Debug option   -------------------------------------------------
  gDebug = 0;
  // ------------------------------------------------------------------------

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------

  // ----  Load libraries   -------------------------------------------------
  gROOT->LoadMacro("$VMCWORKDIR/example/gconfig/basiclibs.C");
  basiclibs();
  gSystem->Load("libFairTools");
  gSystem->Load("libGeoBase");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libMCStack");
  gSystem->Load("libGen");
  gSystem->Load("libPassive");
  gSystem->Load("libTutorial1");
  // ------------------------------------------------------------------------

   
 
  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();
  run->SetName("TGeant3");              // Transport engine
  run->SetOutputFile(outFile);          // Output file
  FairRuntimeDb* rtdb = run->GetRuntimeDb();
  // ------------------------------------------------------------------------
  
  // -----   Create media   -------------------------------------------------
  run->SetMaterials("media.geo");       // Materials
  // ------------------------------------------------------------------------
  
  // -----   Create geometry   ----------------------------------------------
//  TString cave_geo = dir + "/tutorials/geometry/cave_vacuum.geo";

  FairModule* cave= new FairCave("CAVE");
  cave->SetGeometryFileName("cave_vacuum.geo"); 
//  cave->SetGeometryFileName(cave_geo.Data()); 
  run->AddModule(cave);

  FairDetector* tutdet = new FairTutorialDet("TUTDET", kTRUE);
  tutdet->SetGeometryFileName("double_sector.geo"); 
  run->AddModule(tutdet);
  // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 1);

  boxGen->SetThetaRange (   theta,   theta+0.01);
  boxGen->SetPRange     (momentum,momentum+0.01);
  boxGen->SetPhiRange   (0.,360.);

  primGen->AddGenerator(boxGen);

  run->SetGenerator(primGen);
  // ------------------------------------------------------------------------

  // -----   Initialize simulation run   ------------------------------------
  run->Init();
  // ------------------------------------------------------------------------

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
//  FairParAsciiFileIo* parOut = new FairParAsciiFileIo();
  parOut->open(parFile.Data());
  rtdb->setOutput(parOut);
  rtdb->saveOutput();
  rtdb->print();
  // ------------------------------------------------------------------------
   
  // -----   Start run   ----------------------------------------------------
  run->Run(nEvents);
  // ------------------------------------------------------------------------
  
  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime 
       << "s" << endl << endl;
  // ------------------------------------------------------------------------
}


