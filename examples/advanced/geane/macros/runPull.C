/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
int runPull(bool drawHist = false)
{
    gROOT->Reset();
    gStyle->SetOptFit(1);

    TFile *f=new TFile("geane.cal.root");
    TTree *simtree=(TTree*)f->Get("cbmsim") ;

    TClonesArray* fTrackParGeane = new TClonesArray("FairTrackParP");
    TClonesArray* fTrackParIni   = new TClonesArray("FairTrackParP");
    TClonesArray* fTrackParFinal = new TClonesArray("FairTrackParP");

    TH1F *hQP = new TH1F("hQP","charge over momentum",100,-10.,10.);
    TH1F *hX  = new TH1F("hX", "position X",100,-10,10);
    TH1F *hY  = new TH1F("hY", "position Y",100,-10,10);
    TH1F *hPx = new TH1F("hPx","momentum X",100, -10,10);
    TH1F *hPy = new TH1F("hPy","momentum Y",100,-10,10);
    TH1F *hPz = new TH1F("hPz","momentum Z",100,-10,10);

    simtree->SetBranchAddress("GeaneTrackFinal",&fTrackParFinal);
    simtree->SetBranchAddress("GeaneTrackPar",&fTrackParGeane);
    FairTrackParP *fTrkF;
    FairTrackParP *fTrkG;
    Int_t Nevents= simtree->GetEntriesFast();
    cout<<Nevents<<endl;
    for(Int_t i=0; i<Nevents; i++){
        simtree->GetEntry(i);
        for (Int_t k=0; k<fTrackParGeane->GetEntriesFast(); k++)	{
            fTrkF = (FairTrackParP *)fTrackParFinal->At(k);
            fTrkG = (FairTrackParP *)fTrackParGeane->At(k);
            if(fTrkF &&fTrkG ){
                if(fTrkG->GetDQp()) hQP->Fill((fTrkF->GetQp()-fTrkG->GetQp())/fTrkG->GetDQp());
                if(fTrkG->GetDX() ) hX ->Fill((fTrkF->GetX() -fTrkG->GetX()) /fTrkG->GetDX());
                if(fTrkG->GetDY() ) hY ->Fill((fTrkF->GetY() -fTrkG->GetY()) /fTrkG->GetDY());
                if(fTrkG->GetDPx()) hPx->Fill((fTrkF->GetPx()-fTrkG->GetPx())/fTrkG->GetDPx());
                if(fTrkG->GetDPy()) hPy->Fill((fTrkF->GetPy()-fTrkG->GetPy())/fTrkG->GetDPy());
                if(fTrkG->GetDPz()) hPz->Fill((fTrkF->GetPz()-fTrkG->GetPz())/fTrkG->GetDPz());
            }
        }
    }
    if ( drawHist ) {
        TCanvas *c=new TCanvas("c","c",900,600);
        c->Divide(3,2);
        c->cd(1);
        hQP->Draw();
        hQP-> Fit("gaus");
        c->cd(2);
        hX->Draw();
        hX-> Fit("gaus");
        c->cd(3);
        hY->Draw();
        hY-> Fit("gaus");
        c->cd(4);
        hPx->Draw();
        hPx-> Fit("gaus");
        c->cd(5);
        hPy->Draw();
        hPy-> Fit("gaus");
        c->cd(6);
        hPz->Draw();
        hPz-> Fit("gaus");
        
        c->cd();
    }

    TF1* fitX = new TF1("fitX","gaus",-5.,5.);
    hX->Fit("fitX","QN");

    if ( fitX->GetParameter(1) > -0.03 && fitX->GetParameter(1) < 0.03 && 
         fitX->GetParameter(2) >  0.   && fitX->GetParameter(1) < 1.5 )
        cout << "Macro finished successfully. Mean (" << fitX->GetParameter(1) << ") and sigma (" << fitX->GetParameter(2) << ") inside limits." << endl;
    else
        cout << "Macro failed. Mean (" << fitX->GetParameter(1) << ") or sigma (" << fitX->GetParameter(2) << ") too far off." << endl;

    return 0;
}
