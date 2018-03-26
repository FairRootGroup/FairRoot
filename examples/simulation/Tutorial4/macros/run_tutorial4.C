/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_tutorial4(Int_t nEvents = 10, TString mcEngine="TGeant3",  Bool_t isMT=false)
{
  
  TString dir = getenv("VMCWORKDIR");

  TString tut_configdir = dir + "/simulation/Tutorial4/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  TString tut_geomdir = dir + "/common/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());
  
  Double_t momentum = 2.;

  Double_t theta    = 2.;

  TString outDir = "./";

  // Output file name
  TString  outFile     ="testrun_";
  outFile = outFile + mcEngine + ".root";

  TString  parFile     ="testparams_";
  parFile = parFile + mcEngine + ".root";
  
  TList *parFileList = new TList();

  TString paramDir = dir + "/simulation/Tutorial4/parameters/";
  TString paramFile = paramDir + "example.par";

  TObjString* tutDetDigiFile = new TObjString(paramFile);
  parFileList->Add(tutDetDigiFile);


  // In general, the following parts need not be touched
  // ========================================================================

  // ----    Debug option   -------------------------------------------------
  gDebug = 0;
  // ------------------------------------------------------------------------

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------

  //Does not work with automatic loading pf libraries. The info is not in the rootmap file
//  gLogger->SetLogScreenLevel("INFO");   
 
  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();
  run->SetName(mcEngine);              // Transport engine
  run->SetIsMT(isMT);                  // Multi-threading mode (Geant4 only)
  run->SetOutputFile(outFile);          // Output file
  FairRuntimeDb* rtdb = run->GetRuntimeDb();
  // ------------------------------------------------------------------------
  
  // -----   Create media   -------------------------------------------------
  run->SetMaterials("media.geo");       // Materials
  // ------------------------------------------------------------------------
  
  // -----   Create geometry   ----------------------------------------------
  FairModule* cave= new FairCave("CAVE");
  cave->SetGeometryFileName("cave_vacuum.geo"); 
  run->AddModule(cave);

  FairTutorialDet4* tutdet = new FairTutorialDet4("TUTDET", kTRUE);
  tutdet->SetGeometryFileName("tutorial4.root"); 
  if ( ! isMT ) {
    // This mode does not yet work with MT
    tutdet->SetModifyGeometry(kTRUE);
  }
  run->AddModule(tutdet);
  // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  FairBoxGenerator* boxGen = new FairBoxGenerator(2212, 1);

  boxGen->SetThetaRange (   theta,   theta+0.1);
//  boxGen->SetThetaRange (  0.,  0.);
  boxGen->SetPRange     (momentum,momentum+0.01);
  boxGen->SetPhiRange   (0.,360.);
  boxGen->SetBoxXYZ (-20.,-20.,20.,20., 0.);
//  boxGen->SetBoxXYZ (0.,0.,0.,0., 0.);

//  boxGen->SetDebug(kTRUE);

  primGen->AddGenerator(boxGen);

  
  run->SetGenerator(primGen);
  // ------------------------------------------------------------------------

  // -----   Initialize simulation run   ------------------------------------
  run->SetStoreTraj(kTRUE);

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  FairParAsciiFileIo* parIn = new FairParAsciiFileIo();
  parOut->open(parFile.Data());
  parIn->open(parFileList, "in");
  rtdb->setFirstInput(parIn);
  rtdb->setOutput(parOut);
  // ------------------------------------------------------------------------

  run->Init();


 // -Trajectories Visualization (TGeoManager Only )
 // -----------------------------------------------

 // Set cuts for storing the trajectpries
  /* FairTrajFilter* trajFilter = FairTrajFilter::Instance();
     trajFilter->SetStepSizeCut(0.01); // 1 cm
     trajFilter->SetVertexCut(-2000., -2000., 4., 2000., 2000., 100.);
     trajFilter->SetMomentumCutP(10e-3); // p_lab > 10 MeV
     trajFilter->SetEnergyCut(0., 1.02); // 0 < Etot < 1.04 GeV
     trajFilter->SetStorePrimaries(kTRUE);
     trajFilter->SetStoreSecondaries(kTRUE);
   */

  // ------------------------------------------------------------------------

   
  // -----   Start run   ----------------------------------------------------
  run->CreateGeometryFile("data/geofile_full_misaligned.root");
  run->Run(nEvents);
  run->CreateGeometryFile("data/geofile_full.root");
  // ------------------------------------------------------------------------
  
  rtdb->saveOutput();
  rtdb->print();

  delete run;

  // -----   Finish   -------------------------------------------------------

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Float_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}


