/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void run_reco(TString mcEngine = "TGeant3", Bool_t AlignDone = true)
{
    // ----  Load libraries   -------------------------------------------------
    FairLogger* logger = FairLogger::GetLogger();
    //  logger->SetLogFileName("MyLog.log");
    logger->SetLogToScreen(kTRUE);
    //  logger->SetLogToFile(kTRUE);
    //  logger->SetLogVerbosityLevel("HIGH");
    //  logger->SetLogFileLevel("DEBUG4");
    logger->SetLogScreenLevel("INFO");

    // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
    Int_t iVerbose = 0;   // just forget about it, for the moment

    TString Align = "";
    if (AlignDone) {
        Align = "align_";
    }
    TString InDir = "./data/";
    // Input file (MC Events)
    TString inFile = "testrun_";
    inFile = InDir + inFile + Align + mcEngine + ".root";

    // Output file name
    TString outFile = "testreco_";
    outFile = InDir + outFile + Align + mcEngine + ".root";

    // Parameter file
    TString parFile = "testparams_";
    parFile = InDir + parFile + Align + mcEngine + ".root";

    // Millepede file name
    TString milleFile = "testmille_";
    milleFile = InDir + milleFile + Align + mcEngine;

    TList* parFileList = new TList();

    TString workDir = FairConfig::Instance().GetVMCWorkDir();
    TString paramDir = workDir + "/simulation/Tutorial4/parameters/";
    TString paramFile = paramDir + "example.par";

    TObjString tutDetDigiFile;
    tutDetDigiFile.SetString(paramFile);
    parFileList->Add(&tutDetDigiFile);

    // -----   Timer   --------------------------------------------------------
    TStopwatch timer;

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna* fRun = new FairRunAna();
    FairFileSource* fFileSource = new FairFileSource(inFile);
    fRun->SetSource(fFileSource);
    fRun->SetSink(new FairRootFileSink(outFile));

    FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
    FairParRootFileIo* parInput1 = new FairParRootFileIo();
    FairParAsciiFileIo* parIo2 = new FairParAsciiFileIo();
    parIo2->open(parFileList, "in");
    parInput1->open(parFile.Data());
    parIo2->open(parFileList, "in");
    rtdb->setFirstInput(parInput1);
    rtdb->setSecondInput(parIo2);
    rtdb->setOutput(parInput1);
    rtdb->saveOutput();

    // -----   TorinoDetector hit  producers   ---------------------------------
    FairTutorialDet4HitProducerIdealMisalign* hitProducer = new FairTutorialDet4HitProducerIdealMisalign();
    hitProducer->DoMisalignment(kFALSE);
    fRun->AddTask(hitProducer);

    FairTutorialDet4StraightLineFitter* fitter = new FairTutorialDet4StraightLineFitter();
    fitter->SetVersion(2);
    fRun->AddTask(fitter);

    FairTutorialDet4MilleWriter* writer = new FairTutorialDet4MilleWriter();
    //  writer->SetWriteAscii(kTRUE);
    writer->SetVersion(2);
    writer->SetFileName(milleFile);
    fRun->AddTask(writer);

    fRun->Init();

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
}
