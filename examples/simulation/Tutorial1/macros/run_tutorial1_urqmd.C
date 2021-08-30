/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <memory>

void run_tutorial1_urqmd(Int_t nEvents = 2, TString mcEngine = "TGeant3")
{
    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/simulation//Tutorial1";

    TString inFile = dir + "/common/input/urqmd.ftn14";

    TString Urqmd_Conversion_table = dir + "/common/input/urqmd_pdg.dat";

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    TString outDir = "./";

    // Output file name
    TString outFile = Form("%s/tutorial1_urqmd_%s.mc.root", outDir.Data(), mcEngine.Data());

    // Parameter file name
    TString parFile = Form("%s/tutorial1_urqmd_%s.params.root", outDir.Data(), mcEngine.Data());

    TString geoFile = outDir + "geofile_urqmd_" + mcEngine + "_full.root";

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
    run->SetName(mcEngine);                        // Transport engine
    run->SetSimulationConfig(new FairVMCConfig());
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

    FairDetector* tutdet = new FairTutorialDet1("TUTDET", kTRUE);
    tutdet->SetGeometryFileName("double_sector.geo");
    run->AddModule(tutdet);
    // ------------------------------------------------------------------------

    // -----   Create PrimaryGenerator   --------------------------------------
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

    FairUrqmdGenerator* urqmdGen = new FairUrqmdGenerator(inFile.Data(), Urqmd_Conversion_table.Data());
    primGen->AddGenerator(urqmdGen);

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
}
