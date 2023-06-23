/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include "FairFileSource.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairRootFileSink.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairSystemInfo.h"
#include "FairTutorialDet2CustomTask.h"
#include "FairTutorialDet2DigiPar.h"
#include "FairTutorialDet2Digitizer.h"

#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <iostream>
#include <memory>
#endif

using std::cout;
using std::endl;

void create_digis()
{
    TStopwatch timer;
    timer.Start();

    gDebug = 0;

    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/simulation/Tutorial2";

    TString inFile = "./tutorial2_pions.mc_p2.000_t0_n10.root";
    TString parFile = "./tutorial2_pions.params_p2.000_t0_n10.root";
    TString outFile = "./digis.mc.root";

    cout << "******************************" << endl;
    cout << "InFile: " << inFile << endl;
    cout << "ParamFile: " << parFile << endl;
    cout << "OutFile: " << outFile << endl;
    cout << "******************************" << endl;

    FairRunAna* fRun = new FairRunAna();
    FairFileSource* fFileSource = new FairFileSource(inFile);
    fRun->SetSource(fFileSource);

    fRun->SetSink(std::make_unique<FairRootFileSink>(outFile));

    // Init Simulation Parameters from Root File
    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
    FairParRootFileIo* io1 = new FairParRootFileIo();
    io1->open(parFile.Data(), "UPDATE");

    FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
    TString tutDetDigiFile = gSystem->Getenv("VMCWORKDIR");
    tutDetDigiFile += "/simulation/Tutorial2/parameters/tutdet.digi.par";
    parInput2->open(tutDetDigiFile.Data(), "in");

    rtdb->setFirstInput(io1);
    rtdb->setSecondInput(parInput2);

    rtdb->print();

    //**  TUt Det Digi Producer **//

    FairTutorialDet2Digitizer* digi = new FairTutorialDet2Digitizer("tutdet", "tut det task");

    // add the task
    fRun->AddTask(digi);
    // add another task (to test reading data from in memory branches)
    fRun->AddTask(new FairTutorialDet2CustomTask());

    fRun->Init();

    rtdb->getContainer("FairTutorialDet2DigiPar")->print();

    FairTutorialDet2DigiPar* DigiPar = (FairTutorialDet2DigiPar*)rtdb->getContainer("FairTutorialDet2DigiPar");

    DigiPar->setChanged();
    DigiPar->setInputVersion(fRun->GetRunId(), 1);
    rtdb->setOutput(io1);
    rtdb->saveOutput();
    rtdb->print();

    fRun->Run();

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
