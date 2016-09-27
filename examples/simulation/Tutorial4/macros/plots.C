/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
plots(Int_t nEvents = 1000, Int_t iout=1, TString mcEngine="TGeant3")
{

  // Input data definitions
  //-----User Settings:-----------------------------------------------
  TString  MCFile     ="testrun_" + mcEngine + ".root";
  TString  ParFile       ="testparams_" + mcEngine + ".root";
  TString  RecoFile       ="testreco_"+ mcEngine + ".root";;
  

  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();

  fRun->SetInputFile(MCFile.Data());
  fRun->AddFriend(RecoFile.Data());

  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo* parInput1 = new FairParRootFileIo();
  parInput1->open(ParFile.Data());
  rtdb->setFirstInput(parInput1);

  TFile *f1 = TFile::Open(MCFile);
  TFile *f2 = TFile::Open(RecoFile);

  TTree *t1 = f1->Get("cbmsim");
  TTree *t2 = f2->Get("cbmsim");
	
  FairMCEventHeader *MCEventHeader  = new FairMCEventHeader();
  TClonesArray *MCTracks   = new TClonesArray("FairMCTrack");
  TClonesArray *TutorialDetPoints  = new TClonesArray("FairTutorialDet4Point");
  TClonesArray *TutorialDetHits    = new TClonesArray("FairTutorialDet4Hit");

  t1->SetBranchAddress("MCEventHeader.",&MCEventHeader);
  t1->SetBranchAddress("MCTrack",       &MCTracks);
  t1->SetBranchAddress("TutorialDetPoint",      &TutorialDetPoints);
  t2->SetBranchAddress("TutorialDetHit",        &TutorialDetHits);

  FairMCTrack     *MCTrack;
  FairTutorialDet4Point    *Point;
  FairTutorialDet4Hit      *Hit;

  //histograms 
  fRun->SetOutputFile("test.ana.root");
  TFile *fHist = fRun->GetOutputFile();

  Float_t xrange=80.;
  Float_t yrange=80.;

  TH2F* dxx    = new TH2F("dxx","Hit; x; Delta x;",100,-xrange,xrange,50.,-10.,10.);
  TH2F* dyy    = new TH2F("dyy","Hit; y; Delta y;",100,-yrange,yrange,50.,-10.,10.);
  TH1F* pullx    = new TH1F("pullx","Hit; pullx;",100.,-5.,5.);
  TH1F* pully    = new TH1F("pully","Hit; pully;",100.,-5.,5.);
  TH1F* pullz    = new TH1F("pullz","Hit; pullz;",50.,-10.,10.);
  TH1F* pointx    = new TH1F("pointx","Hit; posx;",200.,-80.,80.);
  TH1F* pointy    = new TH1F("pointy","Hit; posy;",200.,-80.,80.);
 
  Int_t nMCTracks, nPoints, nHits;
  Float_t x_point, y_point, z_point, tof_point, SMtype_point, mod_point, cel_point, gap_point;  
  Float_t x_poi, y_poi, z_poi; 
  Float_t SMtype_poi, mod_poi, cel_poi, gap_poi;
  Float_t p_MC, px_MC, py_MC, pz_MC;
  Float_t x_hit, y_hit, z_hit, dy_hit;

  Int_t nevent = t1->GetEntries();	

  if (nevent > nEvents) nevent=nEvents;

  cout << "total number of events to process: " << nevent 
       <<endl;

// Event loop
	
for (Int_t iev=0; iev< nevent; iev++) {
  // get entry	
  t1->GetEntry(iev);
  t2->GetEntry(iev);
		
  nMCTracks = MCTracks->GetEntriesFast();
  nPoints = TutorialDetPoints->GetEntriesFast();
  nHits = TutorialDetHits->GetEntriesFast();
    		
  cout << " Event"  << iev << ":";
  cout << nMCTracks << " MC tracks ";
  cout << nPoints << "  points ";
  cout << nHits << " Hits "<<endl;
    
  // Hit loop					
  for (Int_t j =0; j<nHits; j++) {
    Hit   = (FairTutorialDet4Hit*) TutorialDetHits->At(j);
    Int_t l = Hit->GetRefIndex();
    Point = (FairTutorialDet4Point*) TutorialDetPoints->At(l);

    // Point info
    x_poi	= Point -> GetX();
    y_poi	= Point -> GetY();
    z_poi	= Point -> GetZ();

    // Hit	info		
    x_hit	= Hit->GetX();
    y_hit	= Hit->GetY();
    z_hit	= Hit->GetZ();
    dy_hit	= Hit->GetDy();
//    Int_t flg_hit = Hit->GetFlag();

    Float_t delta_x	= x_poi - x_hit;
    Float_t delta_y	= y_poi - y_hit;
    Float_t delta_z	= z_poi - z_hit;
			
    dxx ->Fill(x_poi,delta_x);
    dyy ->Fill(y_poi,delta_y);
    pullx ->Fill(delta_x);
    pully ->Fill(delta_y);
    pullz ->Fill(delta_z);
    pointx ->Fill(x_hit);
    pointy ->Fill(y_hit);
		
  } //  Hit loop end

} // event loop end 


// save histos to file
// TFile *fHist = TFile::Open("data/auaumbias.hst.root","RECREATE");
 cout << "Processing done, outflag =" <<iout << endl;
 if (iout==1){
   fHist->Write();
   if(0){ // explicit writing 
     TIter next(gDirectory->GetList());
     TH1 *h;
     TObject* obj;
     while(obj= (TObject*)next()){
       if(obj->InheritsFrom(TH1::Class())){
         h = (TH1*)obj;
         cout << "Write histo " << h->GetTitle() << endl;
         h->Write();
       }
     }
   }
   fHist->ls();
   fHist->Close();
  }

  // -----   Finish   -------------------------------------------------------

  cout << endl << endl;

  // Extract the maximal used memory an add is as Dart measurement
  // This line is filtered by CTest and the value send to CDash
  FairSystemInfo sysInfo;
  Float_t maxMemory=sysInfo.GetMaxMemory();
  cout << "<DartMeasurement name=\"MaxMemory\" type=\"numeric/double\">";
  cout << maxMemory;
  cout << "</DartMeasurement>" << endl;

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();

  Float_t cpuUsage=ctime/rtime;
  cout << "<DartMeasurement name=\"CpuLoad\" type=\"numeric/double\">";
  cout << cpuUsage;
  cout << "</DartMeasurement>" << endl;

  cout << endl << endl;
  cout << "Output file is "    << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime
       << "s" << endl << endl;
  cout << "Macro finished successfully." << endl;

  // ------------------------------------------------------------------------
}
