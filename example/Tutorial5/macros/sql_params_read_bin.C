/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
Int_t  sql_params_read_bin()
{
  // ----  Load libraries   -------------------------------------------------
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
  basiclibs();
  gSystem->Load("libGenVector");
  gSystem->Load("libGeoBase");
  gSystem->Load("libFairDB");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libMCStack");
  gSystem->Load("libField");
  gSystem->Load("libTutorial5");


  // Create a Runtime Database singleton.
  FairRuntimeDb* db = FairRuntimeDb::instance();

  // Set the SQL IO as first input
  FairParTSQLIo* inp = new FairParTSQLIo();
  // Verbosity level
  inp->SetVerbosity(1);

  inp->open();
  db->setFirstInput(inp);

  // Create the container via the factory if not already created
  FairDbTutParBin* p1 = (FairDbTutParBin*)(db->getContainer("TUTParBin"));

  p1->Print();

  // Create a dummy runID using date in UTC from which
  // corresponding  parameters will be initialised

  ValTimeStamp tStamp(2014,02,03,10,07,48);
  UInt_t runId = tStamp.GetSec();
  cout << "-I- looking for parameters at runID# " << runId << endl;
  cout << "-I- corresponding  time in runID (UTC) " << tStamp.AsString("c") << endl;

  // Use the generated RunID to initialised the parameter
  // using the SQL-based IO input
  db->initContainers(runId);


 

  cout << endl;
  cout << "-I- Initialisation from SQL Database:" << endl;
  cout << endl;

 // Get the container after initialisation
  // from the RuntimeDB
  FairDbTutParBin* pp1 = (FairDbTutParBin*)(db->getContainer("TUTParBin"));
  pp1->Print();

  cout << endl;


  if (db) delete db;
  return 0;
}
