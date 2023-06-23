/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#if !defined(__CLING__) || defined(__ROOTCLING__)
#include "FairTrackParP.h"
#endif

#include <TCanvas.h>
#include <TClonesArray.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

int runPull(std::string propName = "rk", bool drawHist = false)
{
    if (propName != "geane" && propName != "rk") {
        cout << "Choose either \"geane\" or \"rk\"." << endl;
        return 1;
    }

    gROOT->Reset();
    gStyle->SetOptFit(1);

    std::unique_ptr<TFile> f{TFile::Open(Form("prop.%s.cal.root", propName.c_str()))};
    std::unique_ptr<TTree> simtree{f->Get<TTree>("cbmsim")};

    TClonesArray* fTrackParProp = new TClonesArray("FairTrackParP");
    TClonesArray* fTrackParFinal = new TClonesArray("FairTrackParP");

    Double_t maxDist = 0.1;
    TH1F* hQP = new TH1F("hQP", "charge over momentum", 200, -maxDist, maxDist);
    TH1F* hX = new TH1F("hX", "position X", 200, -maxDist, maxDist);
    TH1F* hY = new TH1F("hY", "position Y", 200, -maxDist, maxDist);
    TH1F* hPx = new TH1F("hPx", "momentum X", 200, -maxDist, maxDist);
    TH1F* hPy = new TH1F("hPy", "momentum Y", 200, -maxDist, maxDist);
    TH1F* hPz = new TH1F("hPz", "momentum Z", 200, -maxDist, maxDist);

    simtree->SetBranchAddress("PropTrackFinal", &fTrackParFinal);
    simtree->SetBranchAddress("PropTrackPar", &fTrackParProp);
    FairTrackParP* fTrkF;
    FairTrackParP* fTrkG;
    Int_t Nevents = simtree->GetEntriesFast();
    cout << Nevents << endl;
    for (Int_t i = 0; i < Nevents; i++) {
        simtree->GetEntry(i);
        for (Int_t k = 0; k < fTrackParProp->GetEntriesFast(); k++) {
            fTrkF = (FairTrackParP*)fTrackParFinal->At(k);
            fTrkG = (FairTrackParP*)fTrackParProp->At(k);
            if (fTrkF && fTrkG) {
                hQP->Fill(fTrkF->GetQp() - fTrkG->GetQp());
                hX->Fill(fTrkF->GetX() - fTrkG->GetX());
                hY->Fill(fTrkF->GetY() - fTrkG->GetY());
                hPx->Fill(fTrkF->GetPx() - fTrkG->GetPx());
                hPy->Fill(fTrkF->GetPy() - fTrkG->GetPy());
                hPz->Fill(fTrkF->GetPz() - fTrkG->GetPz());
                // if(fTrkG->GetDQp()) hQP->Fill((fTrkF->GetQp()-fTrkG->GetQp())/fTrkG->GetDQp());
                // if(fTrkG->GetDX() ) hX ->Fill((fTrkF->GetX() -fTrkG->GetX()) /fTrkG->GetDX());
                // if(fTrkG->GetDY() ) hY ->Fill((fTrkF->GetY() -fTrkG->GetY()) /fTrkG->GetDY());
                // if(fTrkG->GetDPx()) hPx->Fill((fTrkF->GetPx()-fTrkG->GetPx())/fTrkG->GetDPx());
                // if(fTrkG->GetDPy()) hPy->Fill((fTrkF->GetPy()-fTrkG->GetPy())/fTrkG->GetDPy());
                // if(fTrkG->GetDPz()) hPz->Fill((fTrkF->GetPz()-fTrkG->GetPz())/fTrkG->GetDPz());
            }
        }
    }
    if (drawHist) {
        TCanvas* c = new TCanvas("c", "c", 900, 600);
        c->Divide(3, 2);
        c->cd(1);
        hQP->Draw();
        hQP->Fit("gaus");
        c->cd(2);
        hX->Draw();
        hX->Fit("gaus");
        c->cd(3);
        hY->Draw();
        hY->Fit("gaus");
        c->cd(4);
        hPx->Draw();
        hPx->Fit("gaus");
        c->cd(5);
        hPy->Draw();
        hPy->Fit("gaus");
        c->cd(6);
        hPz->Draw();
        hPz->Fit("gaus");

        c->cd();
    }

    TF1* fitX = new TF1("fitX", "gaus", -5., 5.);
    hX->Fit("fitX", "QN");

    if (fitX->GetParameter(1) > -1.e-3 && fitX->GetParameter(1) < 1.e-3 && fitX->GetParameter(2) > 0.
        && fitX->GetParameter(2) < 1.e-2)
        cout << "Macro finished successfully. Mean (" << fitX->GetParameter(1) << ") and sigma ("
             << fitX->GetParameter(2) << ") inside limits." << endl;
    else
        cout << "Macro failed. Mean (" << fitX->GetParameter(1) << ") or sigma (" << fitX->GetParameter(2)
             << ") too far off." << endl;

    return 0;
}
