/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_digi( TString mcEngine="TGeant3" )
{
  FairLogger *logger = FairLogger::GetLogger();
 // logger->SetLogFileName("MyLog.log");
 // logger->SetLogToScreen(kTRUE);
//  logger->SetLogToFile(kTRUE);
  logger->SetLogVerbosityLevel("LOW");
//  logger->SetLogFileLevel("DEBUG4");
//  logger->SetLogScreenLevel("DEBUG");
  
  // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0; // just forget about it, for the moment
  
  // Input file (MC events)
  TString inFile = "data/testrun_";
  inFile = inFile + mcEngine + ".root";
  
  // Parameter file
  TString parFile = "data/testparams_"; 
  parFile = parFile + mcEngine + ".root";

  // Output file
  TString outFile = "data/testdigi_";
  outFile = outFile + mcEngine + ".root";
  
  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile(inFile);
  fRun->SetOutputFile(outFile);
  
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(parFile.Data());
  rtdb->setFirstInput(parInput1);
  
  // -----   TorinoDetector hit  producers   ---------------------------------
  FairTestDetectorDigiTask* digiTask = new FairTestDetectorDigiTask();
  fRun->AddTask(digiTask);
  

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
