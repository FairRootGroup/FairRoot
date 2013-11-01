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

  TString work = getenv("VMCWORKDIR");
  TString filename = work + "/Tutorial5/macros/ascii-example.par";
  inp1->open(filename.Data(),"in");
  db->setFirstInput(inp1);

  // Set the SQL based IO as second input
  FairParTSQLIo* inp2 = new FairParTSQLIo();
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

  cout << "-I- Delete FairRuntimeDb " << endl; 
  if (db) delete db;
  return 0;
}
