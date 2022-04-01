/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
void eventDisplay(TString mcEngine = "TGeant4")
{

    TString inFile = "data/test_" + mcEngine + ".mc.root";
    TString parFile = "data/params_" + mcEngine + ".root";
    TString outFile = "data/test_" + mcEngine + ".root";

    // -----   Reconstruction run   -------------------------------------------
    FairRunAna *fRun = new FairRunAna();
    FairFileSource *fFileSource = new FairFileSource(inFile);
    fRun->SetSource(fFileSource);

    fRun->SetSink(new FairRootFileSink(outFile));

    // -----  Parameter database   --------------------------------------------
    FairRuntimeDb *rtdb = fRun->GetRuntimeDb();

    FairParRootFileIo *parIo1 = new FairParRootFileIo();
    parIo1->open(parFile);
    rtdb->setFirstInput(parIo1);
    // ------------------------------------------------------------------------

    FairEventManager *fMan = new FairEventManager();
    FairMCTracksDraw *Track = new FairMCTracksDraw();
    FairMCPointDraw *RutherfordPoints = new FairMCPointDraw("FairRutherfordPoint", kBlue, kFullSquare);

    fMan->AddTask(Track);
    fMan->AddTask(RutherfordPoints);

    fMan->Init();
}
