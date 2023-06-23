 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include "FairBaseParSet.h"
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
#include <iostream>
#include <memory>
#endif

using std::cout;
using std::endl;

void read_digis()
{

    TStopwatch timer;
    timer.Start();

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
    fRun->SetSink(new FairRootFileSink(outFile));

    // Init Simulation Parameters from Root File
    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
    FairParRootFileIo* io1 = new FairParRootFileIo();
    io1->open(parFile.Data(), "UPDATE");

    // Fallback solution if paramters are not found in database (ROOT file)
    FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
    TString tutDetDigiFile = gSystem->Getenv("VMCWORKDIR");
    tutDetDigiFile += "/simulation/Tutorial2/parameters/tutdet.digi.par";
    parInput2->open(tutDetDigiFile.Data(), "in");

    // The parameter container is initialized from first input since it
    // is available from the ROOT parameter file. The second input is the
    // fallback when a parameter container is not found in the first
    // input. If you want to overwrite a paramter container already
    // existing in the "database" (ROOT file) you have to change the
    // order of the inputs. In this case the ASCII file has to be the
    // first input.
    rtdb->setFirstInput(io1);
    rtdb->setSecondInput(parInput2);

    // It is needed to request the parameter container before the run is
    // initialized. Otherwise the runtime database does not know that the
    // parameter container is needed and creates one with the default
    // constructor of the parameter container which is an empty one.
    // Normally the request is done in the function SetParContainers of the task.
    // You can check what happens if no parameter conatiner is requested
    // by disabling the next line.
    rtdb->getContainer("FairTutorialDet2DigiPar");
    rtdb->print();

    fRun->Init();

    rtdb->getContainer("FairTutorialDet2DigiPar")->print();

    // First short version to print the parameters
    // If you want to confirm that the parameters are really there you can
    // print them by disabling the following line
    // static_cast<FairTutorialDet2DigiPar*>(rtdb->getContainer("FairTutorialDet2DigiPar"))->printparams();

    rtdb->saveOutput();

    // -- Print out the random seed from the simulation ----------------------
    FairBaseParSet* BasePar = (FairBaseParSet*)rtdb->getContainer("FairBaseParSet");
    cout << "RndSeed used in simulation was  " << BasePar->GetRndSeed() << endl;

    // -----------------------------------------------------------------------

    // Second version to print the parameters
    // which also shows how to change and save them again

    FairTutorialDet2DigiPar* DigiPar = (FairTutorialDet2DigiPar*)rtdb->getContainer("FairTutorialDet2DigiPar");

    DigiPar->setChanged();
    DigiPar->setInputVersion(fRun->GetRunId(), 1);
    // If you want to confirm that the parameters are really there you can
    // print them by disabling the following line
    DigiPar->printParams();

    rtdb->print();
    rtdb->saveOutput();

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
}
