{
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna* fRun= new FairRunAna();
  fRun->SetInputFile("dummysim.root");
  fRun->SetOutputFile("dummyana.root");

  // -----  Parameter database   --------------------------------------------
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open("par.root","READ");//RECREATE etc. like in TFile from root
  rtdb->setFirstInput(parInput1);

  /*
  FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
  parInput2->open("ascii-example.par","in");
  rtdb->setSecondInput(parInput2);
  */

  // Set the SQL IO as second input
  FairParTSQLIo* inp = new FairParTSQLIo();
  inp->open();
  rtdb->setSecondInput(inp);

  // -----   Tasks to run   -------------------------------------------------
  fRun->AddTask(new FairDbTutAccessRtdbTask());

  // -----   Intialise and run   --------------------------------------------
  fRun->Init();

  /*
  Bool_t kParameterMerged=kTRUE;
  FairParRootFileIo* parOutput = new FairParRootFileIo(kParameterMerged);
  parOutput->open("par_merged.root","RECREATE");//RECREATE etc. like in TFile from root
  rtdb->setOutput(parOutput);
  rtdb->saveOutput();
  */
  rtdb->print();

  fRun->Run();

}
