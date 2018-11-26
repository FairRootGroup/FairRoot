/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_tutorial4_createGeometryFile(Int_t nEvents = 1, TString mcEngine="TGeant3",  Bool_t isMT=false)
{
  
  TString dir = getenv("VMCWORKDIR");

  TString tut_configdir = dir + "/simulation/Tutorial4/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  TString tut_geomdir = dir + "/common/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());
  
  Double_t momentum = 2.;

  Double_t theta    = 2.;

  TString outDir = "./data/";

  // Output file name
  TString  outFile     ="makeGeo_";
  outFile = outDir + outFile + mcEngine + ".root";

  TString geoFile ="makeGeoFile_";
  geoFile = outDir + geoFile + mcEngine + "_full.root";


  TString  parFile     ="makeGeoParams_";
  parFile = outDir + parFile + mcEngine + ".root";
  
  TList *parFileList = new TList();

/*
  TString paramDir = dir + "/simulation/Tutorial4/parameters/";
  TString paramFile = paramDir + "example.par";

  TObjString* tutDetDigiFile = new TObjString(paramFile);
  parFileList->Add(tutDetDigiFile);
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

  //Does not work with automatic loading pf libraries. The info is not in the rootmap file
//  gLogger->SetLogScreenLevel("INFO");   
 
  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();
  run->SetName(mcEngine);              // Transport engine
  run->SetIsMT(isMT);                  // Multi-threading mode (Geant4 only)
  run->SetSink(new FairRootFileSink(outFile));          // Output file
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
  
  // ------------------------------------------------------------------------

   
  // -----   Start run   ----------------------------------------------------
  run->Run(nEvents);
  run->CreateGeometryFile(geoFile);
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


