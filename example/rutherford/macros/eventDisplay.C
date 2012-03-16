eventDisplay()
{
  // Load basic libraries 
  TString dir = gSystem->Getenv("VMCWORKDIR");
  TString tut_configdir = dir + "/example/gconfig";
  gSystem->Setenv("CONFIG_DIR",tut_configdir.Data());
  gROOT->LoadMacro("$CONFIG_DIR/basiclibs.C");
  basiclibs();
  
  gSystem->Load("libFairTools");
  gSystem->Load("libFairDB");
  gSystem->Load("libGeoBase");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libGen");
  gSystem->Load("libPassive");
  gSystem->Load("libFairRutherford");
  gSystem->Load("libEve");
  gSystem->Load("libEventDisplay");


                                     
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile("data/test.mc.root");
  
  fRun->SetOutputFile("data/test.root");

  // -----  Parameter database   --------------------------------------------
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  FairParRootFileIo* parIo1 = new FairParRootFileIo();
  parIo1->open("data/params.root");
  rtdb->setFirstInput(parIo1);
  // ------------------------------------------------------------------------

  FairEventManager   *fMan      = new FairEventManager   ();
  FairMCTracks       *Track     = new FairMCTracks       ("Monte-Carlo Tracks");
  FairMCPointDraw    *RutherfordPoints = new FairMCPointDraw    ("FairRutherfordPoint",kBlue , kFullSquare);
                                                     
  fMan->AddTask(Track);
  fMan->AddTask(RutherfordPoints);
    
  fMan->Init();                    

  // Automatic visible depth is disabled
  //  gGeoManager->SetVisLevel(3);
}
