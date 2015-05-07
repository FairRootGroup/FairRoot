/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_reco( TString mcEngine="TGeant3" )
{
   // ----  Load libraries   -------------------------------------------------
  FairLogger *logger = FairLogger::GetLogger();
//  logger->SetLogFileName("MyLog.log");
  logger->SetLogToScreen(kTRUE);
//  logger->SetLogToFile(kTRUE);
//  logger->SetLogVerbosityLevel("HIGH");
//  logger->SetLogFileLevel("DEBUG4");
  logger->SetLogScreenLevel("INFO");
  
  // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0; // just forget about it, for the moment
  
  // Input file (MC Events)
  TString  inFile     ="testrun_";
  inFile = inFile + mcEngine + ".root";

  // Output file name
  TString  outFile     ="testreco_";
  outFile = outFile + mcEngine + ".root";

  // Parameter file
  TString  parFile     ="testparams_";
  parFile = parFile + mcEngine + ".root";

  // Millepede file name
  TString  milleFile     ="testmille_";
  milleFile = milleFile + mcEngine;

  TList *parFileList = new TList();

  TString workDir = gSystem->Getenv("VMCWORKDIR");
  paramDir = workDir + "/Tutorial4/parameters/";
  TString paramFile = paramDir + "example.par";

  TObjString tutDetDigiFile;
  tutDetDigiFile.SetString(paramFile);                                         
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
  FairTutorialDet4HitProducerIdealMisalign* hitProducer = new FairTutorialDet4HitProducerIdealMisalign();
  hitProducer->DoMisalignment(kFALSE);
  fRun->AddTask(hitProducer);

  FairTutorialDet4StraightLineFitter* fitter = new FairTutorialDet4StraightLineFitter();
  fitter->SetVersion(2);
  fRun->AddTask(fitter);

  FairTutorialDet4MilleWriter* writer = new FairTutorialDet4MilleWriter();
//  writer->SetWriteAscii(kTRUE);
  writer->SetVersion(2);
  writer->SetFileName(milleFile);
  fRun->AddTask(writer);
  

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
