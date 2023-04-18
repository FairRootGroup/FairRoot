/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <TStopwatch.h>
#include <TString.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

void run_digi(TString mcEngine = "TGeant4")
{
    FairLogger* logger = FairLogger::GetLogger();
    // logger->SetLogFileName("MyLog.log");
    // logger->SetLogToScreen(kTRUE);
    //  logger->SetLogToFile(kTRUE);
    logger->SetLogVerbosityLevel("LOW");
    //  logger->SetLogFileLevel("DEBUG4");
    //  logger->SetLogScreenLevel("DEBUG");

    // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
    Int_t iVerbose = 0;   // just forget about it, for the moment

    // Input file (MC events)
    TString inFile = "data/testrun_";
    inFile = inFile + mcEngine + ".root";

    // Parameter file
    TString parFile = "data/testparams_";
    parFile = parFile + mcEngine + ".root";

    // Output file
    TString outFile = "data/testdigi_";
    outFile = outFile + mcEngine + ".root";

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna run{};
    FairFileSource* fFileSource = new FairFileSource(inFile);
    run.SetSource(fFileSource);
    run.SetSink(std::make_unique<FairRootFileSink>(outFile));
    run.SetUseFairLinks(kTRUE);
    FairLinkManager::Instance()->AddIncludeType(0);
    //  FairLinkManager::Instance()->AddIncludeType(1);
    run.SetGenerateRunInfo(kTRUE);   // Create FairRunInfo file

    FairRuntimeDb* rtdb = run.GetRuntimeDb();
    FairParRootFileIo* parInput1 = new FairParRootFileIo();
    parInput1->open(parFile.Data());
    rtdb->setFirstInput(parInput1);

    // -----   TorinoDetector hit  producers   ---------------------------------
    FairTestDetectorDigiTask* digiTask = new FairTestDetectorDigiTask();
    run.AddTask(digiTask);

    run.Init();

    timer.Start();
    run.Run();

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
