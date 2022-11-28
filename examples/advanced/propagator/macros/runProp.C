/********************************************************************************
 * Copyright (C) 2019-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <TStopwatch.h>
#include <TString.h>
#include <TSystem.h>
#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;

int runProp(std::string propName = "rk")
{
    if (propName != "geane" && propName != "rk") {
        cout << "Choose either \"geane\" or \"rk\"." << endl;
        return 1;
    }

    TString dir = getenv("VMCWORKDIR");

    TString tut_geomdir = dir + "/common/geometry";
    gSystem->Setenv("GEOMPATH", tut_geomdir.Data());

    TString tut_configdir = dir + "/common/gconfig";
    gSystem->Setenv("CONFIG_DIR", tut_configdir.Data());

    // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
    Int_t iVerbose = 0;   // just forget about it, for the moment

    // Input file (MC events)
    TString inFile = "prop.mc.root";

    // Parameter file
    TString parFile = "prop.par.root";

    // Output file
    TString outFile = Form("prop.%s.cal.root", propName.c_str());

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna* fRun = new FairRunAna();
    fRun->SetSource(new FairFileSource(inFile));
    fRun->SetSink(std::make_unique<FairRootFileSink>(outFile));

    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
    FairParRootFileIo* parInput1 = new FairParRootFileIo();
    parInput1->open(parFile.Data());

    rtdb->setFirstInput(parInput1);

    FairConstField* fMagField = new FairConstField();
    fMagField->SetField(0., 0., 20.);                             // values are in kG
    fMagField->SetFieldRegion(-150, 150, -150, 150, -250, 250);   // values are in cm (xmin,xmax,ymin,ymax,zmin,zmax)
    fRun->SetField(fMagField);

    // -----   Set propagator and run   ---------------------------------------
    if (propName == "geane") {
        FairGeane* Geane = new FairGeane();
        fRun->AddTask(Geane);
    }

    FairTutPropTr* propTask = new FairTutPropTr();
    if (propName == "rk") {
        FairRKPropagator* propagator = new FairRKPropagator(fMagField);
        propTask->SetPropagator(propagator);
    }
    fRun->AddTask(propTask);

    fRun->Init();

    if (propName == "geane") {
        FairGeanePro* GeaneProp = new FairGeanePro();
        propTask->SetPropagator(GeaneProp);
    }

    timer.Start();
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
    return 0;
}
