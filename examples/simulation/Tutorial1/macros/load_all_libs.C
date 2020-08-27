void load_all_libs()
{
    gSystem->Load("libAlignment");
    gSystem->Load("libBase");
    gSystem->Load("libBaseMQ");
    gSystem->Load("libEventDisplay");
    gSystem->Load("libExHistogramServer");
    gSystem->Load("libExLmd");
    gSystem->Load("libExParameters");
    gSystem->Load("libExSerialization");
    gSystem->Load("libFairDataMatch");
    gSystem->Load("libFairFastSim");
    gSystem->Load("libFairMCStepLogger");
    gSystem->Load("libFairRutherford");
    gSystem->Load("libFairTestDetector");
    gSystem->Load("libFairTools");
    gSystem->Load("libGConfig");
    gSystem->Load("libGeane");
    gSystem->Load("libGen");
    gSystem->Load("libGeoBase");
    gSystem->Load("libMCConfigurator");
    gSystem->Load("libMCStack");
    gSystem->Load("libMbsAPI");
    gSystem->Load("libMbsTutorial");
    gSystem->Load("libParBase");
    gSystem->Load("libParMQ");
    gSystem->Load("libPassive");
    gSystem->Load("libPixel");
    gSystem->Load("libPixelAlt");
    gSystem->Load("libPropagatorExample");
    gSystem->Load("libSimMQ");
    gSystem->Load("libTrkBase");
    gSystem->Load("libTutorial1");
    gSystem->Load("libTutorial2");
    gSystem->Load("libTutorial4");

    cout << endl << endl;
    cout << "Macro finished succesfully." << endl;
}
