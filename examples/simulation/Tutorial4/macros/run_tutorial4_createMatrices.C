/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_tutorial4_createMatrices(Int_t nEvents = 10, TString mcEngine="TGeant3",  Bool_t isMT=false)
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

  TString geoFile ="data/geoFile_" + mcEngine + "_full.root";
  TString geoFileMisaligned ="data/geoFile_" + mcEngine + "_full_misaligned.root";

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

  //sadly, the align parameters are only available AFTER we called fRun->Init()

  // We fill a std::map<std::string, TGeoHMatrix> map with all misalignment matrices
  // how you get those in your geometry is up to you

  auto matrices = tutdet->getMisalignmentMatrices();

  ofstream myfile;
  myfile.open ("misalignmentMatrices.txt");

  double *rot;
  double *trans;

  // this can probably be done more elegantly
  for(auto &mat : matrices){
    myfile << mat.first << "\n";
    rot = mat.second.GetRotationMatrix();
    trans = mat.second.GetTranslation();
    for(int i=0; i<9; i++)  myfile << rot[i] << "\n";
    for(int i=0; i<3; i++)  myfile << trans[i] << "\n";
  }
  myfile.close();

  LOG(info) << "AlignHandler: all matrices added!";

  LOG(info) << "SUCCESS! All matrices created and saved!";

  return;
}


