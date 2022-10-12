/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
int runMM(Int_t nEvents = 1000, TString mcEngine = "TGeant4", Bool_t isMT = false)
{
    UInt_t randomSeed = 123456;
    gRandom->SetSeed(randomSeed);

    TString dir = getenv("VMCWORKDIR");

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    TString outDir = "./";

    // Output file name
    TString outFile = Form("%s/prop.mc.root", outDir.Data());

    // Parameter file name
    TString parFile = Form("%s/prop.par.root", outDir.Data());

    TString geoFile = "geofile_" + mcEngine + "_full.root";

    // In general, the following parts need not be touched
    // ========================================================================

    // ----    Debug option   -------------------------------------------------
    gDebug = 0;
    // ------------------------------------------------------------------------

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;
    timer.Start();
    // ------------------------------------------------------------------------

    // -----   Create simulation run   ----------------------------------------
    FairRunSim* run = new FairRunSim();
    run->SetName(mcEngine);   // Transport engine
    run->SetSimulationConfig(make_unique<FairVMCConfig>());
    run->SetIsMT(isMT);                            // Multi-threading mode (Geant4 only)
    run->SetSink(new FairRootFileSink(outFile));   // Output file
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    // ------------------------------------------------------------------------

    // -----   Create media   -------------------------------------------------
    run->SetMaterials("media.geo");   // Materials
    // ------------------------------------------------------------------------

    // -----   Create geometry   ----------------------------------------------

    FairModule* cave = new FairCave("CAVE");
    cave->SetGeometryFileName("cave_vacuum.geo");
    run->AddModule(cave);

    FairTutPropDet* det = new FairTutPropDet("TutPropDetector", kTRUE);
    det->SetGeometryFileName("tutProp.geo");
    run->AddModule(det);

    FairTutPropDet* det2 = new FairTutPropDet("TutPropDetector", kTRUE);
    det2->SetGeometryFileName("tutProp2.geo");
    det2->SetPointsArrayName("FairTutPropPoint2");
    run->AddModule(det2);
    // ------------------------------------------------------------------------

    // -----   Create PrimaryGenerator   --------------------------------------
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
    FairBoxGenerator* pionBoxGen = new FairBoxGenerator(211, 2);

    pionBoxGen->SetThetaRange(0, 30);
    pionBoxGen->SetPRange(1., 3.);

    pionBoxGen->SetPhiRange(0., 360.);   // 10.,10. when looking for PCA
    pionBoxGen->SetDebug(kTRUE);

    primGen->AddGenerator(pionBoxGen);

    FairBoxGenerator* muonBoxGen = new FairBoxGenerator(13, 2);

    muonBoxGen->SetThetaRange(0, 30);
    muonBoxGen->SetPRange(1., 3.);
    muonBoxGen->SetPhiRange(0., 360.);   // 10.,10. when looking for PCA
    muonBoxGen->SetDebug(kTRUE);

    primGen->AddGenerator(muonBoxGen);

    FairConstField* fMagField = new FairConstField();
    fMagField->SetField(0., 0., 20.);                             // values are in kG
    fMagField->SetFieldRegion(-150, 150, -150, 150, -250, 250);   // values are in cm (xmin,xmax,ymin,ymax,zmin,zmax)
    run->SetField(fMagField);

    run->SetGenerator(primGen);
    // ------------------------------------------------------------------------

    // -----   Initialize simulation run   ------------------------------------
    run->Init();
    // ------------------------------------------------------------------------

    // -----   Runtime database   ---------------------------------------------

    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
    parOut->open(parFile.Data());
    rtdb->setOutput(parOut);
    rtdb->saveOutput();
    rtdb->print();
    // ------------------------------------------------------------------------

    // -----   Start run   ----------------------------------------------------
    run->Run(nEvents);
    run->CreateGeometryFile(geoFile);
    // ------------------------------------------------------------------------

    // -----   Finish   -------------------------------------------------------

    cout << endl << endl;

    // Extract the maximal used memory an add is as Dart measurement
    // This line is filtered by CTest and the value send to CDash
    FairSystemInfo sysInfo;
    Float_t maxMemory = sysInfo.GetMaxMemory();
    cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
    cout << maxMemory;
    cout << "</DartMeasurement>" << endl;

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();

    Float_t cpuUsage = ctime / rtime;
    cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
    cout << cpuUsage;
    cout << "</DartMeasurement>" << endl;

    cout << endl << endl;
    cout << "Output file is " << outFile << endl;
    cout << "Parameter file is " << parFile << endl;
    cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;
    cout << "Macro finished successfully." << endl;

    // ------------------------------------------------------------------------
    return 0;
}
