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
  inp->open();
  db->setFirstInput(inp);

  // Create the container via the factory if not already created
  FairDbTutParBin* p1 = (FairDbTutParBin*)(db->getContainer("TUTParBin"));

  p1->Print();

  // Create a dummy runID using date in UTC from which
  // corresponding  parameters will be initialised

  ValTimeStamp tStamp(2013,10,23,12,28,00);
  UInt_t runId = tStamp.GetSec();
  cout << "-I- looking for parameters at runID# " << runId << endl;
  cout << "-I- corresponding  time in runID (UTC) " << tStamp.AsString("c") << endl;

  // Use the generated RunID to initialised the parameter
  // using the SQL-based IO input
  db->initContainers(runId);


  // Get the container after initialisation
  // from the RuntimeDB
  FairDbTutParBin* pp1 = (FairDbTutParBin*)(db->getContainer("TUTParBin"));
  pp1->Print();

  cout << endl;
  cout << "\n  -I- SQLDB: RuntimeDB::init from SQL Database done.... \n" << endl;
  cout << endl;


  return 0;
}
