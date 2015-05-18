/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
eventDisplay(TString mcEngine="TGeant3")
{
  //-----User Settings:-----------------------------------------------
  TString  InputFile     ="data/testrun_" + mcEngine + ".root";
  TString  ParFile       ="data/testparams_" + mcEngine + ".root";
  TString  OutFile	 ="data/tst.root";
  //------------------------------------------------------------------

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

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairMemory mem;
  Float_t maxMemory=mem.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

}
