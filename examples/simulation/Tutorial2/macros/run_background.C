#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <memory>

void run_background(Int_t nEvents = 130)
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
    TString outFile = Form("%s/tutorial2_%s.mc_p%1.3f_t%1.0f_n%d.bg.root",
                           outDir.Data(),
                           partName[chosenPart].Data(),
                           momentum,
                           theta,
                           nEvents);

    // Parameter file name
    TString parFile = Form("%s/tutorial2_%s.params_p%1.3f_t%1.0f_n%d.bg.root",
                           outDir.Data(),
                           partName[chosenPart].Data(),
                           momentum,
                           theta,
                           nEvents);

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
    run->SetName("TGeant4");                       // Transport engine
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
