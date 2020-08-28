void eventDisplay()
{
    //-----User Settings:-----------------------------------------------
    TString InputFile = "tutorial1_TGeant3_pions.mc_p2.000_t0_n10.root";
    TString ParFile = "tutorial1_TGeant3_pions.params_p2.000_t0_n10.root";
    TString OutFile = "tst.root";

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna *fRun = new FairRunAna();
    FairFileSource *fFileSource = new FairFileSource(InputFile);
    fRun->SetSource(fFileSource);
    fRun->SetSink(new FairRootFileSink(OutFile.Data()));

    FairRuntimeDb *rtdb = fRun->GetRuntimeDb();
    FairParRootFileIo *parInput1 = new FairParRootFileIo();
    parInput1->open(ParFile.Data());
    rtdb->setFirstInput(parInput1);

    FairEventManager *fMan = new FairEventManager();

    //----------------------Traks and points -------------------------------------
    FairMCTracksDraw *Track = new FairMCTracksDraw();
    //  FairMCPointDraw *TorinoDetectorPoints = new FairMCPointDraw("FairTestDetectorPoint", kRed, kFullSquare);

    fMan->AddTask(Track);
    //  fMan->AddTask(TorinoDetectorPoints);

    fMan->Init();
}
