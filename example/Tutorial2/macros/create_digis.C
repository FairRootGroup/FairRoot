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
    gSystem->Load("libOra");
    

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

    FairRunAna *fRun= new FairRunAna();
    fRun->SetInputFile(inFile);
    fRun->SetOutputFile(outFile);


    // Init Simulation Parameters from Root File
    FairRuntimeDb* rtdb=fRun->GetRuntimeDb();
    FairParRootFileIo* io1=new FairParRootFileIo();
    io1->open(paramFile.Data(),"UPDATE");
 
    FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
    TString tutDetDigiFile = gSystem->Getenv("VMCWORKDIR");
    tutDetDigiFile += "/example/Tutorial2/macros/tutdet.digi.par";
    parInput2->open(tutDetDigiFile.Data(),"in");

    FairParOraIo *OraIo= new FairParOraIo();
    OraIo->open("alturany");
    
    rtdb->setOutput(OraIo);
    
    rtdb->setFirstInput(io1);
    rtdb->setSecondInput(parInput2);

    rtdb->print();

    //**  TUt Det Digi Producer **//

    FairTutorialDetDigitizer *digi = new FairTutorialDetDigitizer("tutdet","tut det task");

    // add the task
    fRun->AddTask( digi );
    


    fRun->LoadGeometry();
    fRun->Init();
   
    
     
    FairTutorialDetDigiPar* DigiPar = (FairTutorialDetDigiPar*) 
                                      rtdb->findContainer("FairTutorialDetDigiPar");
    DigiPar->setAuthor("alturany");
    DigiPar->setDescription("Test digi parameters");
    DigiPar->setChanged();
    DigiPar->setInputVersion(fRun->GetRunId(),1);
    
    fRun->Run();
    FairTutorialDetGeoPar* GeoPar = (FairTutorialDetGeoPar*) 
                                      rtdb->findContainer("FairTutorialDetGeoPar");
    
    GeoPar->setAuthor("alturany");
    GeoPar->setDescription("Test Geo parameters");
    GeoPar->setChanged();
    GeoPar->setInputVersion(fRun->GetRunId(),1);
				      
    
    rtdb->setContainersStatic();
    
    rtdb->initContainers(8000); 
    
    DigiPar->setChanged();
    DigiPar->print();
    DigiPar->write(OraIo);
    
    GeoPar->setChanged();
    GeoPar->print();
    GeoPar->write(OraIo);
    
    
    rtdb->print();


   


    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);
}
