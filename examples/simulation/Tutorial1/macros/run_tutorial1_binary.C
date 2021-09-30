/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include <iostream>
using namespace std;
#include "FairBoxGenerator.h"
#include "FairConfig.h"
#include "FairCave.h"
#include "FairParRootFileIo.h"
#include "FairPrimaryGenerator.h"
#include "FairRootFileSink.h"
#include "FairRunSim.h"
#include "FairSimConfig.h"
#include "FairSystemInfo.h"
#include "FairTutorialDet1.h"

#include <TRandom3.h>
#include <TStopwatch.h>
#endif

void run_tutorial1_main(const FairSimConfig& config);

// Default function, to be executed from cling
void run_tutorial1_binary()
{
    FairSimConfig config;

    run_tutorial1_main(config);
}

// This function should be called from main of the executable
void run_tutorial1_main(const FairSimConfig& config)
{
    TString dir = FairConfig::Instance().GetVMCWorkDir();
    TString tutdir = dir + "/simulation/Tutorial1";

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    TString partName[] = {"pions", "eplus", "proton"};
    Int_t partPdgC[] = {211, 11, 2212};
    Int_t chosenPart = 0;

    Double_t momentum = 2.;

    Double_t theta = 0.;

    // Output file name
    TString outFile = config.GetOutputFile();

    // Parameter file name
    TString parFile = config.GetParameterFile();

    TString geoFile = "geofile_" + config.GetEngine() + "_full.root";

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
    FairRunSim run;
    run.SetName(config.GetEngine());              // Transport engine
    run.SetIsMT(config.IsMultiThreaded());        // Multi-threading mode (Geant4 only)
    run.SetSink(new FairRootFileSink(outFile));   // Output file
    FairRuntimeDb* rtdb = run.GetRuntimeDb();
    // ------------------------------------------------------------------------

    // -----   Create media   -------------------------------------------------
    run.SetMaterials("media.geo");   // Materials
    // ------------------------------------------------------------------------

    // -----   Create geometry   ----------------------------------------------
    FairCave cave("CAVE");
    cave.SetGeometryFileName("cave_vacuum.geo");
    run.AddModule(&cave);

    FairTutorialDet1 tutdet("TUTDET", kTRUE);
    tutdet.SetGeometryFileName("double_sector.geo");
    run.AddModule(&tutdet);
    // ------------------------------------------------------------------------

    // -----   Create PrimaryGenerator   --------------------------------------
    FairPrimaryGenerator primGen;
    FairBoxGenerator boxGen(partPdgC[chosenPart], 1);

    boxGen.SetThetaRange(theta, theta + 0.01);
    boxGen.SetPRange(momentum, momentum + 0.01);
    boxGen.SetPhiRange(0., 360.);
    boxGen.SetDebug(kTRUE);

    primGen.AddGenerator(&boxGen);

    run.SetGenerator(&primGen);
    // ------------------------------------------------------------------------

    // -----   Initialize simulation run   ------------------------------------
    UInt_t randomSeed = config.GetRandomSeed();
    TRandom3 random(randomSeed);
    gRandom = &random;

    run.Init();
    // ------------------------------------------------------------------------

    // -----   Runtime database   ---------------------------------------------

    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo parOut(kParameterMerged);
    parOut.open(parFile.Data());
    rtdb->setOutput(&parOut);
    rtdb->saveOutput();
    rtdb->print();
    // ------------------------------------------------------------------------

    // -----   Start run   ----------------------------------------------------
    run.Run(config.GetNEvents());
    run.CreateGeometryFile(geoFile);
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
