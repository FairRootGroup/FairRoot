/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
Int_t  sql_params_write()
{
  // Generate a unique RunID
  FairRunIdGenerator runID;
  UInt_t runId =  runID.generateId();

  // Create the Runtime Database ( parameter manager class )
  FairRuntimeDb* db = FairRuntimeDb::instance();

  // Create in memory the relevant container
  FairDbTutPar* p1 = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
  FairDbTutPar* p2 = (FairDbTutPar*)(db->getContainer("TUTParAlternative"));

  // Set the Ascii IO as first input
  FairParAsciiFileIo* inp1 = new FairParAsciiFileIo();

  //TString work = getenv("VMCWORKDIR");
  TString filename ="ascii-example.par";
  inp1->open(filename.Data(),"in");
  db->setFirstInput(inp1);

  // Set the SQL based IO as second input
  FairParTSQLIo* inp2 = new FairParTSQLIo();

  //
  // FairParTSQLIo global settings section
  // 
  // 
  // Verbosity level 
  //               Level       Active Streams
  //
  //                 0         Warning+Errors(logged), 
  //                 1         Info (logged), 
  //                 2         Debug+Info (logged)
  //                 3         Debug+Info (logged+standard output) 
  inp2->SetVerbosity(1);

  // Set Global SeqNo ( Replication Global Index Base )
  //inp2->SetGlobalSeqNoIn();

  // Shutdown Mode ( True, False )
  inp2->SetShutdown(kTRUE);

  // <Comment: D.Bertini@gsi.de Date: 28.10.2013>
  // Following features are "advanced features" and
  // the user should know what he/she is doing !
  // (Otherwise see the FairDb documentation ) 

  // Rollback Activation
  //inp2->SetRollback("2013-10-25","CAL*");
  // Selective Rollback Using  
  //                          0 (Transaction Time)
  //                          1 (Incremental Time) 
  // inp2->SetRollbackMode(1,"CAL*");

  // Holding Connections
  ///inp2->SetHoldConnection();

  // Query Ordering
  ///inp2->SetQueryOrdering();

  // Caching Activation
  ///inp2->SetCache("test.fairdb_cache");

  inp2->open();
  db->setSecondInput(inp2);


// <INIT> containers from Ascii input
// with assigned  RunId
  db->initContainers(runId);

  cout << endl;
  cout << "\n  -I- Initialisation from Ascii File done using RunID# " <<  runId << endl;
  cout << endl;

  p1->Print();
  p2->Print();


  // <WRITE> back containers to the user-defined
  // Database using the Sql based IO of the
  // second input.

  db->setOutput(inp2);
  db->writeContainers();



  cout << endl;
  cout << "-I-  Parameters succesfully written to DB with RunID# " << runId << endl;
  cout << endl;

  if (db) delete db;
  return 0;
}
