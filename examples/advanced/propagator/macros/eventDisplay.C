
/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * eventDisplay.C
 *
 *  Created on: 27 sie 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

void eventDisplay()
{

    TString inFile = "prop.mc.root";
    TString parFile = "prop.par.root";
    TString outFile = "ed.root";
    // -----   Reconstruction run   -------------------------------------------
    FairRunAna *fRun = new FairRunAna();
    // prop.rk.cal.root
    FairFileSource *fFileSource = new FairFileSource(inFile);
    fFileSource->AddFriend("prop.tracks.root");
    fFileSource->AddFriend("prop.hits.root");
    fRun->SetSource(fFileSource);

    fRun->SetSink(new FairRootFileSink(outFile));

    // -----  Parameter database   --------------------------------------------
    FairRuntimeDb *rtdb = fRun->GetRuntimeDb();

    FairParRootFileIo *parIo1 = new FairParRootFileIo();
    parIo1->open(parFile);
    rtdb->setFirstInput(parIo1);
    // ------------------------------------------------------------------------

    FairConstField *fMagField = new FairConstField();
    fMagField->SetField(0., 0., 20.);                             // values are in kG
    fMagField->SetFieldRegion(-150, 150, -150, 150, -250, 250);   // values are in cm (xmin,xmax,ymin,ymax,zmin,zmax)
    fRun->SetField(fMagField);
    //-------------------

    FairEventManager *fMan = new FairEventManager();
    fMan->SetXMLConfig("conf.xml");
    // set view from the front
    fMan->SetRPhiPlane(0, 0, -5, 0, TGLViewer::kCameraOrthoXOY);

    FairMCTracksDraw *mcTracks = new FairMCTracksDraw();
    FairGeoTracksDraw *geoTracks = new FairGeoTracksDraw();
    FairRecoTracksDraw *recoTracks = new FairRecoTracksDraw();
    FairMCPointDraw *RutherfordPoints = new FairMCPointDraw("FairTutPropPoint", kBlue, kFullSquare);
    FairMCPointDraw *RutherfordPoints2 = new FairMCPointDraw("FairTutPropPoint2", kRed, kFullSquare);

    fMan->AddTask(mcTracks);
    fMan->AddTask(geoTracks);
    fMan->AddTask(recoTracks);

    fMan->AddTask(RutherfordPoints);
    fMan->AddTask(RutherfordPoints2);

    fMan->Init();
}
