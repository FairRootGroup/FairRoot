/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
// Example includes
#include "PixelDigiBinSource.h"
#include "PixelEventHeader.h"
#include "PixelFindHits.h"

// FairRoot includes
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRootFileSink.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairSystemInfo.h"
#endif

#include <TStopwatch.h>
#include <TString.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

void run_dBinSource(TString mcEngine = "TGeant3")
{
    // Parameter file
    TString parFile = "pixel_";
    parFile = parFile + mcEngine + ".params.root";

    // Digitization parameter file
    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/MQ/pixelDetector";
    TString digParFile = tutdir + "/param/pixel_digi.par";

    // Output file
    TString outFile = "pixel_";
    outFile = outFile + mcEngine + ".viaBinSource.hits.root";

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna run{};
    run.SetEventHeader(std::make_unique<PixelEventHeader>());
    run.SetSink(std::make_unique<FairRootFileSink>(outFile));

    PixelDigiBinSource* digiSource = new PixelDigiBinSource("Pixel Digi Source");
    digiSource->SetInputFileName("digisBin.dat");

    run.SetSource(digiSource);

    FairRuntimeDb* rtdb = run.GetRuntimeDb();
    FairParRootFileIo* parInput1 = new FairParRootFileIo();
    parInput1->open(parFile.Data());

    FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo();
    parIo1->open(digParFile.Data(), "in");

    rtdb->setFirstInput(parInput1);
    rtdb->setSecondInput(parIo1);

    // -----   TorinoDetector hit  producers   ---------------------------------
    //  PixelDigiReadFromFile* digiRead = new PixelDigiReadFromFile();
    //  run->AddTask(digiRead);

    auto hitFinderTask = std::make_unique<PixelFindHits>();
    run.AddTask(std::move(hitFinderTask));

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
