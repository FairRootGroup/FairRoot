/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
eventDisplay()
{
  //-----User Settings:-----------------------------------------------
  TString  SimEngine     ="TGeant3"; 
  TString  InputFile     ="data/testrun.root";
  TString  ParFile       ="data/testparams.root";
  TString  OutFile	 ="data/tst.root";
  //------------------------------------------------------------------


  // Load basic libraries
/*
  gROOT->LoadMacro("$VMCWORKDIR/example/gconfig/basiclibs.C");
  basiclibs();
  gSystem->Load("libFairTools");
  gSystem->Load("libFairDB");
  gSystem->Load("libGeoBase");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libMCStack");
  gSystem->Load("libGen");
  gSystem->Load("libPassive");
  gSystem->Load("libFairTestDetector.so");
  gSystem->Load("libEve");
  gSystem->Load("libEventDisplay");
*/
                                     
  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile(InputFile.Data());
  fRun->SetOutputFile(OutFile.Data());

  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(ParFile.Data());
  rtdb->setFirstInput(parInput1);
   
  FairEventManager *fMan= new FairEventManager();
  
  //----------------------Traks and points -------------------------------------
  FairMCTracks    *Track     = new FairMCTracks("Monte-Carlo Tracks");
  FairMCPointDraw *TorinoDetectorPoints = new FairMCPointDraw("FairTestDetectorPoint", kRed, kFullSquare);
//  FairHitDraw     *ToyHits   = new FairHitDraw("ToyHit");
 
  fMan->AddTask(Track);
  fMan->AddTask(TorinoDetectorPoints);
//  fMan->AddTask(ToyHits);
  
  
  fMan->Init();                     

}
