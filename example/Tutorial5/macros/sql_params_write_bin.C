/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
Int_t  sql_params_write_bin()
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
  gSystem->Load("libTutorial5");

  // Generate a unique RunID
  FairRunIdGenerator runID;
  UInt_t runId =  runID.generateId();

  FairRuntimeDb* db = FairRuntimeDb::instance();
  cout << "-I- FairRuntimeDb created ----> " << db << endl;

  // Create in memory the relevant container
  FairDbTutParBin* p1 = (FairDbTutParBin*)(db->getContainer("TUTParBin"));

  // Set the Ascii IO as first input
  FairParAsciiFileIo* inp1 = new FairParAsciiFileIo();

  //TString work = getenv("VMCWORKDIR");
  TString filename = "ascii-example_bin.par";
  inp1->open(filename.Data(),"in");
  db->setFirstInput(inp1);

  // Set the SQL based IO as second input
  FairParTSQLIo* inp2 = new FairParTSQLIo();
  inp2->open();
  db->setSecondInput(inp2);


  // <INIT> containers from Ascii input
  // with assigned  RunId
  db->initContainers(runId);

  // Additionnally  prime some dummy values to the data members that are not
  // initialized using the ascii input file .
 
  p1->FillDummy();

  cout << endl;
  cout << "\n  -I- FAIRDB: RuntimeDB::init from Ascii File done using RunID# " <<  runId << endl;
  cout << endl;

  // <WRITE> back containers to the user-defined
  // Database using the Sql based IO of the
  // second input.

  db->setOutput(inp2);
  db->writeContainers();

  cout << endl;
  cout << "-I-  FAIRDB: RuntimeDB Parameters succesfully written to DB with RunID# " << runId << endl;
  cout << endl;

  if (db) delete db;
  return 0;
}
