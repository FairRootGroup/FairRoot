void run_reco()
{
   // ----  Load libraries   -------------------------------------------------
   gROOT->LoadMacro("$VMCWORKDIR/example/gconfig/basiclibs.C");
   basiclibs();
   gSystem->Load("libFairTools");
   gSystem->Load("libFairDB");
   gSystem->Load("libGeoBase");
   gSystem->Load("libParBase");
   gSystem->Load("libBase");
   gSystem->Load("libMCStack");
   gSystem->Load("libGen");
   gSystem->Load("libPassive");
   gSystem->Load("libTutorial4.so");

  FairLogger *logger = FairLogger::GetLogger();
  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
//  logger->SetLogToFile(kTRUE);
  logger->SetLogVerbosityLevel("HIGH");
//  logger->SetLogFileLevel("DEBUG4");
  logger->SetLogScreenLevel("DEBUG");
  
  // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0; // just forget about it, for the moment
  
  // Input file (MC events)
  TString inFile = "data/testrun.root";
  
  // Parameter file
  TString parFile = "data/testparams.root"; 

  // Output file
  TString outFile = "data/testreco.root";
  

  TList *parFileList = new TList();

  TString workDir = gSystem->Getenv("VMCWORKDIR");
  paramDir = workDir + "/example/Tutorial4/macros/";

  TObjString tutDetDigiFile = paramDir + "TutorialDet.missallign.par";
  parFileList->Add(&tutDetDigiFile);

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile(inFile);
  fRun->SetOutputFile(outFile);
  
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  FairParAsciiFileIo* parIo2 = new FairParAsciiFileIo();
  parIo2->open(parFileList, "in");
  parInput1->open(parFile.Data());
  parIo2->open(parFileList, "in");
  rtdb->setFirstInput(parInput1);
  rtdb->setSecondInput(parIo2);
  rtdb->setOutput(parInput1);
  rtdb->saveOutput();
   
  // -----   TorinoDetector hit  producers   ---------------------------------
  FairTutorialDetHitProducerIdealMissallign* hitProducer = new FairTutorialDetHitProducerIdealMissallign();
  fRun->AddTask(hitProducer);
  

  fRun->Init();

  timer.Start();
  fRun->Run();

  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished successfully." << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------
  cout << " Test passed" << endl;
  cout << " All ok " << endl;

  exit(0);
}
