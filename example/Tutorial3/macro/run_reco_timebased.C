void run_reco_timebased()
{
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
  TString inFile = "data/testdigitimebased.root";
  
  // Parameter file
  TString parFile = "data/testparams.root"; 

  // Output file
  TString outFile = "data/testrecotimebased.root";
  
  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile(inFile);
  fRun->SetOutputFile(outFile);
  fRun->RunWithTimeStamps();
  
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(parFile.Data());
  rtdb->setFirstInput(parInput1);
  
  // -----   TorinoDetector hit  producers   ---------------------------------
  FairTestDetectorTimeRecoTask* hitProducer = new FairTestDetectorTimeRecoTask();
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
