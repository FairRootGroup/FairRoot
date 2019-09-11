/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
int runMC(Int_t nEvents = 1000, TString mcEngine = "TGeant3", Bool_t isMT=true)
{

  TString dir = getenv("VMCWORKDIR");
  TString tutdir = dir + "/simulation/geane";

  TString tut_geomdir = dir + "/common/geometry";
  gSystem->Setenv("GEOMPATH",tut_geomdir.Data());

  TString tut_configdir = dir + "/common/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());

  TString partName[] = {"pions","eplus","proton"};
  Int_t   partPdgC[] = {    211,     11,    2212};
  Int_t chosenPart  = 0;

  Double_t momentum = 2.;

  Double_t theta    = 10.;

  TString outDir = "./";

  // Output file name
  TString outFile = Form("%s/geane.mc.root",
                         outDir.Data());

  // Parameter file name
  TString parFile = Form("%s/geane.par.root",
			 outDir.Data());

  TString geoFile = "geofile_" + mcEngine + "_full.root";

  // In general, the following parts need not be touched
  // ========================================================================

  // ----    Debug option   -------------------------------------------------
  gDebug = 0;
  // ------------------------------------------------------------------------

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------

  // -----   Create simulation run   ----------------------------------------
  FairRunSim* run = new FairRunSim();
  run->SetName(mcEngine);              // Transport engine
  //  run->SetSimulationConfig(new FairVMCConfig());
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

  FairTutGeaneDet*  det = new FairTutGeaneDet("TutGeaneDetector", kTRUE);
  det->SetGeometryFileName("pixel.geo");
//  det->SetMisalignDetector(kTRUE);
  run->AddModule(det);
  // ------------------------------------------------------------------------

  // -----   Create PrimaryGenerator   --------------------------------------
  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 1);

  boxGen->SetThetaRange (   theta,   theta+0.01);
  boxGen->SetPRange     (momentum,momentum+0.01);
  boxGen->SetPhiRange   (0.,360.);
  boxGen->SetDebug(kTRUE);

  primGen->AddGenerator(boxGen);

  FairConstField *fMagField=new FairConstField();
  fMagField->SetField(0.,0.,20.); // values are in kG
  fMagField->SetFieldRegion(-150, 150, -150, 150, -250, 250);// values are in cm (xmin,xmax,ymin,ymax,zmin,zmax)
  run->SetField(fMagField);

  run->SetGenerator(primGen);
  // ------------------------------------------------------------------------

  // -----   Initialize simulation run   ------------------------------------
  UInt_t randomSeed = 123456;
  TRandom3 random(randomSeed);
  gRandom = &random;

  run->Init();
  // ------------------------------------------------------------------------

  // -----   Runtime database   ---------------------------------------------

  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
  parOut->open(parFile.Data());
  rtdb->setOutput(parOut);
  rtdb->saveOutput();
  rtdb->print();
  // ------------------------------------------------------------------------

  // -----   Start run   ----------------------------------------------------
  run->Run(nEvents);
  run->CreateGeometryFile(geoFile);
  // ------------------------------------------------------------------------

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
  return 0;
}
