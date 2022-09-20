/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <TFile.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <TTree.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

void run_sim(Int_t nEvents = 10, TString mcEngine = "TGeant3", Int_t fileId = 0, Bool_t isMT = kFALSE)
{
    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/MQ/pixelDetector";

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    TString partName[] = {"pions", "eplus", "proton"};
    Int_t partPdgC[] = {211, 11, 2212};
    Int_t chosenPart = 0;

    TString outDir = "./";

    // Output file name
    TString outFile;
    if (fileId == 0) {
        outFile = Form("%s/pixel_%s.mc.root", outDir.Data(), mcEngine.Data());
    } else {
        outFile = Form("%s/pixel_%s.mc.f%d.root", outDir.Data(), mcEngine.Data(), fileId);
    }

    // Parameter file name
    TString parFile = Form("%s/pixel_%s.params.root", outDir.Data(), mcEngine.Data());

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
    auto run = std::make_unique<FairRunSim>();
    run->SetName(mcEngine);   // Transport engine
    run->SetSimulationConfig(std::make_unique<FairVMCConfig>());
    run->SetIsMT(isMT);   // Multi-threading mode (Geant4 only)
    run->SetSink(std::make_unique<FairRootFileSink>(outFile));
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    // ------------------------------------------------------------------------

    // -----   Create media   -------------------------------------------------
    run->SetMaterials("media.geo");   // Materials
    // ------------------------------------------------------------------------

    // -----   Create geometry   ----------------------------------------------

    FairModule* cave = new FairCave("CAVE");
    cave->SetGeometryFileName("cave_vacuum.geo");
    run->AddModule(cave);

    Pixel* det = new Pixel("PixelDetector", kTRUE);
    det->SetGeometryFileName("pixel.geo");
    //  det->SetMisalignDetector(kTRUE);
    run->AddModule(det);
    // ------------------------------------------------------------------------

    // -----   Create PrimaryGenerator   --------------------------------------
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
    FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 5);
    boxGen->SetPRange(1, 2);
    boxGen->SetThetaRange(0, 40);
    boxGen->SetPhiRange(0, 360);
    //  boxGen->SetDebug(kTRUE);

    primGen->AddGenerator(boxGen);

    run->SetGenerator(primGen);
    // ------------------------------------------------------------------------

    run->SetStoreTraj(kFALSE);

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
    run->CreateGeometryFile("geofile_full.root");
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

    std::unique_ptr<TFile> outputFile{TFile::Open(outFile)};
    assert(outputFile);
    std::unique_ptr<TTree> outputTree{outputFile->Get<TTree>("cbmsim")};
    assert(outputTree);
    outputTree->Draw("PixelPoint.fTime", "", "goff");
    std::unique_ptr<TH1F> htemp{outputFile->Get<TH1F>("htemp")};
    assert(htemp);
    int outputTreeEntries = outputTree->GetEntries();
    int outputPoints = (int)(htemp->GetEntries());
    double outputTime = htemp->GetMean();
    htemp.reset();
    outputTree.reset();
    outputFile.reset();

    cout << endl;
    cout << "<DartMeasurement name=\"TreeEntries\" type=\"numeric/int\">";
    cout << outputTreeEntries;
    cout << "</DartMeasurement>" << endl;
    cout << "<DartMeasurement name=\"NumberOfPoints\" type=\"numeric/int\">";
    cout << outputPoints;
    cout << "</DartMeasurement>" << endl;
    cout << "<DartMeasurement name=\"PointTimeMean\" type=\"numeric/double\">";
    cout << outputTime;
    cout << "</DartMeasurement>" << endl;
    cout << endl;

    if (outputTreeEntries < nEvents) {
        cout << "Not enough events (" << outputTreeEntries << ") in the output tree." << endl;
        return;
    }
    if (outputPoints < 7. * nEvents) {
        cout << "Not enough points (" << outputPoints << ") in the output tree." << endl;
        return;
    }

    cout << "Macro finished successfully." << endl;

    // ------------------------------------------------------------------------
}
