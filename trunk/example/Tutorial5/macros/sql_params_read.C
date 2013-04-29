Int_t  sql_params_read()
{
  // Create a Runtime Database singleton.
  FairRuntimeDb* db = FairRuntimeDb::instance();

  // Set the SQL IO as first input
  FairParTSQLIo* inp = new FairParTSQLIo();
  inp->open();
  db->setFirstInput(inp);

  // Create the container via the factory if not already created
  FairDbTutPar* p1 = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
  FairDbTutPar* p2 = (FairDbTutPar*)(db->getContainer("TUTParAlternative"));


  // Create a dummy runID using date in UTC from which
  // corresponding  parameters will be initialised

  ValTimeStamp tStamp(2013,04,08,08,17,00);
  UInt_t runId = tStamp.GetSec();
  cout << "-I- looking for parameters at runID# " << runId << endl;
  cout << "-I- corresponding  time in runID (UTC) " << tStamp.AsString("c") << endl;

  // Use the generated RunID to initialised the parameter
  // using the SQL-based IO input
  db->initContainers(runId);


  // Get the container after initialisation
  // from the RuntimeDB
  FairDbTutPar* pp1 = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
  FairDbTutPar* pp2 = (FairDbTutPar*)(db->getContainer("TUTParAlternative"));

  pp1->Print();
  pp2->Print();

  cout << endl;
  cout << "\n  -I- SQLDB: RuntimeDB::init from SQL Database done.... \n" << endl;
  cout << endl;


  return 0;
}
