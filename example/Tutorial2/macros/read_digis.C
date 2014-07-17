/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void read_digis(){

    TStopwatch timer;
    timer.Start();

    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/Tutorial2";

    TString inFile = "./tutorial2_pions.mc_p2.000_t0_n10.root";
    TString paramFile = "./tutorial2_pions.params_p2.000_t0_n10.root";
    TString outFile = "./digis.mc.root";

    cout << "******************************" << endl;
    cout << "InFile: " << inFile << endl;
    cout << "ParamFile: " << paramFile << endl;
    cout << "OutFile: " << outFile << endl;
    cout << "******************************" << endl;

    FairRunAna *fRun= new FairRunAna();
    fRun->SetInputFile(inFile);
    fRun->SetOutputFile(outFile);


    // Init Simulation Parameters from Root File
    FairRuntimeDb* rtdb=fRun->GetRuntimeDb();
    FairParRootFileIo* io1=new FairParRootFileIo();
    io1->open(paramFile.Data(),"UPDATE");
 
    FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
    TString tutDetDigiFile = gSystem->Getenv("VMCWORKDIR");
    tutDetDigiFile += "/Tutorial2/parameters/tutdet.digi.par";
    parInput2->open(tutDetDigiFile.Data(),"in");

    rtdb->setFirstInput(io1);
    rtdb->setSecondInput(parInput2);

    rtdb->print();

    fRun->Init();

    rtdb->getContainer("FairTutorialDet2DigiPar")->print();
    rtdb->saveOutput();

    FairTutorialDet2DigiPar* DigiPar = (FairTutorialDet2DigiPar*) 
                                      rtdb->getContainer("FairTutorialDet2DigiPar");

    DigiPar->setChanged();
    DigiPar->setInputVersion(fRun->GetRunId(),1);
    DigiPar->printParams();
    rtdb->print();
    fRun->Run();

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);

    cout << "Macro finished succesfully." << endl;
}