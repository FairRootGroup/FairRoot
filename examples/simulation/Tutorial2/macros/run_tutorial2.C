/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include "FairBoxGenerator.h"
#include "FairCave.h"
#include "FairDetector.h"
#include "FairModule.h"
#include "FairParRootFileIo.h"
#include "FairPrimaryGenerator.h"
#include "FairRootFileSink.h"
#include "FairRunSim.h"
#include "FairRuntimeDb.h"
#include "FairSystemInfo.h"
#include "FairTutorialDet2.h"

#include <RtypesCore.h>
#include <TRandom.h>
#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <memory>
#endif

void run_tutorial2(Int_t nEvents = 10, TString mcEngine = "TGeant4", Bool_t isMT = true, UInt_t initial_seed = 98989)
{
    TString dir = getenv("VMCWORKDIR");

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    TString partName[] = {"pions", "eplus", "proton"};
    Int_t partPdgC[] = {211, 11, 2212};
    Int_t chosenPart = 0;

    Double_t momentum = 2.;

    Double_t theta = 0.;

    TString outDir = "./";

    // Output file name
    TString outFile = Form("%s/tutorial2_%s.mc_p%1.3f_t%1.0f_n%d.root",
                           outDir.Data(),
                           partName[chosenPart].Data(),
                           momentum,
                           theta,
                           nEvents);

    // Parameter file name
    TString parFile = Form("%s/tutorial2_%s.params_p%1.3f_t%1.0f_n%d.root",
                           outDir.Data(),
                           partName[chosenPart].Data(),
                           momentum,
                           theta,
                           nEvents);

    // Set the random seed
    gRandom->SetSeed(initial_seed);

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
    run->SetIsMT(isMT);       // Multi-threading mode (Geant4 only)
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

    FairDetector* tutdet = new FairTutorialDet2("TUTDET", kTRUE);
    tutdet->SetGeometryFileName("double_sector.geo");
    run->AddModule(tutdet);
    // ------------------------------------------------------------------------

    // -----   Create PrimaryGenerator   --------------------------------------
    FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
    FairBoxGenerator* boxGen = new FairBoxGenerator(partPdgC[chosenPart], 1);

    boxGen->SetThetaRange(theta, theta + 0.01);
    boxGen->SetPRange(momentum, momentum + 0.01);
    boxGen->SetPhiRange(0., 360.);

    primGen->AddGenerator(boxGen);

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
    // ------------------------------------------------------------------------

    // -----   Finish   -------------------------------------------------------

    std::cout << std::endl << std::endl;

    // Extract the maximal used memory an add is as Dart measurement
    // This line is filtered by CTest and the value send to CDash
    FairSystemInfo sysInfo;
    Float_t maxMemory = sysInfo.GetMaxMemory();
    std::cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
    std::cout << maxMemory;
    std::cout << "</DartMeasurement>" << std::endl;

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();

    Float_t cpuUsage = ctime / rtime;
    std::cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
    std::cout << cpuUsage;
    std::cout << "</DartMeasurement>" << std::endl;

    std::cout << std::endl << std::endl;
    std::cout << "Output file is " << outFile << std::endl;
    std::cout << "Parameter file is " << parFile << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;

    // ------------------------------------------------------------------------
}
