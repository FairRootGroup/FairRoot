void create_digis(){

    TStopwatch timer;
    timer.Start();

    gROOT->LoadMacro("$VMCWORKDIR/example/gconfig/basiclibs.C");
    basiclibs();


    // Load this example libraries
    gSystem->Load("libGeoBase");
    gSystem->Load("libParBase");
    gSystem->Load("libBase");
    gSystem->Load("libMCStack");
    gSystem->Load("libPassive");
    gSystem->Load("libGen");
    gSystem->Load("libTutorial2");

    TString dir = getenv("VMCWORKDIR");
    TString tutdir = dir + "/example/Tutorial2";

    TString inFile = tutdir + "/macros/tutorial2_pions.mc_p2.000_t0_n10.root";
    TString paramFile = tutdir + "/macros/tutorial2_pions.params_p2.000_t0_n10.root";
    TString outFile = "./digis.mc.root";

    cout << "******************************" << endl;
    cout << "InFile: " << inFile << endl;
    cout << "ParamFile: " << paramFile << endl;
    cout << "OutFile: " << outFile << endl;
    cout << "******************************" << endl;

    CbmRunAna *fRun= new CbmRunAna();
    fRun->SetInputFile(inFile);
    fRun->SetOutputFile(outFile);


    // Init Simulation Parameters from Root File
    CbmRuntimeDb* rtdb=fRun->GetRuntimeDb();
    CbmParRootFileIo* io1=new CbmParRootFileIo();
    io1->open(paramFile.Data(),"UPDATE");
 
    CbmParAsciiFileIo* parInput2 = new CbmParAsciiFileIo();
    TString tutDetDigiFile = gSystem->Getenv("VMCWORKDIR");
    tutDetDigiFile += "/example/Tutorial2/macros/tutdet.digi.par";
    parInput2->open(tutDetDigiFile.Data(),"in");

    rtdb->setFirstInput(io1);
    rtdb->setSecondInput(parInput2);

    rtdb->print();

    //**  TUt Det Digi Producer **//

    CbmTutorialDetDigitizer *digi = new CbmTutorialDetDigitizer("tutdet","tut det task");

    // add the task
    fRun->AddTask( digi );
    


    fRun->LoadGeometry();
    fRun->Init();

    rtdb->getContainer("CbmTutorialDetDigiPar")->print();

    CbmTutorialDetDigiPar* DigiPar = (CbmTutorialDetDigiPar*) 
                                      rtdb->getContainer("CbmTutorialDetDigiPar");

    DigiPar->setChanged();
    DigiPar->setInputVersion(fRun->GetRunId(),1);
//    DigiPar->printparams();
    rtdb->setOutput(io1);
    rtdb->saveOutput();
    rtdb->print();

    fRun->Run();


    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);
}
