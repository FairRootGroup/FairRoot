/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
Int_t  sql_params_read()
{
  // Create a Runtime Database singleton.
  FairRuntimeDb* db = FairRuntimeDb::instance();

  // Set the SQL IO as first input
  FairParTSQLIo* inp = new FairParTSQLIo();
  
 
  // Verbosity level
  inp->SetVerbosity(1);

  inp->open();
  db->setFirstInput(inp);

  // Create the container via the factory if not already created
  FairDbTutPar* p1 = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
  FairDbTutPar* p2 = (FairDbTutPar*)(db->getContainer("TUTParAlternative"));


  // Create a dummy runID using date in UTC from which
  // corresponding  parameters will be initialised

  ValTimeStamp tStamp(2014,02,03,10,18,04);
  UInt_t runId = tStamp.GetSec();
  cout << "-I- looking for parameters at runID# " << runId << endl;
  cout << "-I- corresponding  time in runID (UTC) " << tStamp.Format("iso") << endl;

  // Use the generated RunID to initialised the parameter
  // using the SQL-based IO input
  db->initContainers(runId);


  // Get the container after initialisation
  // from the RuntimeDB
  FairDbTutPar* pp1 = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
  FairDbTutPar* pp2 = (FairDbTutPar*)(db->getContainer("TUTParAlternative"));


  cout << endl;
  cout << "-I- Reading Parameter data from SQL Database: \n" << endl;
  cout << endl;

  pp1->Print();
  pp2->Print();

  cout << endl;
 


  if (db) delete db;
  return 0;
}
