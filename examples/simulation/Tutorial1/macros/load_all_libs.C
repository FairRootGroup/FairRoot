void load_all_libs()
{
  gSystem->Load("libBaseMQ");
  gSystem->Load("libBase");
  gSystem->Load("libEventDisplay");
  gSystem->Load("libFairDataMatch");
  gSystem->Load("libFairMQExample1");
  gSystem->Load("libFairMQExample2");
  gSystem->Load("libFairMQExample4");
  gSystem->Load("libFairMQExample5");
  gSystem->Load("libFairMQExample6");
  gSystem->Load("libFairMQExample7");
  gSystem->Load("libFairMQExample8");
  gSystem->Load("libFairMQExampleShm");
  gSystem->Load("libfairmq_logger");
  gSystem->Load("libFairMQ");
  gSystem->Load("libFairMQTest");
  gSystem->Load("libFairRutherford");
  gSystem->Load("libFairTestDetector");
  gSystem->Load("libFairTools");
  gSystem->Load("libGeane");
  gSystem->Load("libGenericMQTuto");
  gSystem->Load("libGen");
  gSystem->Load("libGeoBase");
  gSystem->Load("libLmdMQSampler");
  gSystem->Load("libMbsAPI");
  gSystem->Load("libMbsTutorial");
  gSystem->Load("libMCStack");
  gSystem->Load("libParBase");
  gSystem->Load("libParMQ");
  gSystem->Load("libPassive");
  gSystem->Load("libPixel");
  gSystem->Load("libTrkBase");
  gSystem->Load("libTutorial1");
  gSystem->Load("libTutorial2");
  gSystem->Load("libTutorial4");

  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
}
