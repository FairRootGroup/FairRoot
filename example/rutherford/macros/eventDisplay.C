/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
eventDisplay()
{
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile("data/test.mc.root");
  
  fRun->SetOutputFile("data/test.root");

  // -----  Parameter database   --------------------------------------------
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();

  FairParRootFileIo* parIo1 = new FairParRootFileIo();
  parIo1->open("data/params.root");
  rtdb->setFirstInput(parIo1);
  // ------------------------------------------------------------------------

  FairEventManager   *fMan      = new FairEventManager   ();
  FairMCTracks       *Track     = new FairMCTracks       ("Monte-Carlo Tracks");
  FairMCPointDraw    *RutherfordPoints = new FairMCPointDraw    ("FairRutherfordPoint",kBlue , kFullSquare);
                                                     
  fMan->AddTask(Track);
  fMan->AddTask(RutherfordPoints);
    
  fMan->Init();                    
}
