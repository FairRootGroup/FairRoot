/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void eventDisplay(TString mcEngine = "TGeant3")
{
    //-----User Settings:-----------------------------------------------
    TString InputFile = "testrun_" + mcEngine + ".root";
    TString ParFile = "testparams_" + mcEngine + ".root";
    TString OutFile = "tst.root";
    //------------------------------------------------------------------

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
    FairTutorialDet4PointDraw *TutorialDetectorPoints =
        new FairTutorialDet4PointDraw("TutorialDetPoint", kRed, kFullSquare);

    fMan->AddTask(Track);
    fMan->AddTask(TutorialDetectorPoints);

    fMan->Init();
}
