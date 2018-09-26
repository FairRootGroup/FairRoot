/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairMQExHistoCanvasDrawerExample.h"

#include "TCanvas.h"
#include "THttpServer.h"
#include "TObjArray.h"
#include "TH1.h"

#include <cassert>

FairMQExHistoCanvasDrawerExample::FairMQExHistoCanvasDrawerExample()
    : fCanvas(nullptr)
{
}

FairMQExHistoCanvasDrawerExample::~FairMQExHistoCanvasDrawerExample() {}

void FairMQExHistoCanvasDrawerExample::CreateCanvases(THttpServer& server)
{
    assert(! fCanvas);
    fCanvas = std::unique_ptr<TCanvas, std::function<void(TCanvas*)>>
    (
        new TCanvas("c1", "", 10, 10, 1000, 1000),
        [&](TCanvas* p){server.Unregister(p);delete p;}
     );
    fCanvas->Divide(2, 2);
    server.Register("Canvases", fCanvas.get());
}

void FairMQExHistoCanvasDrawerExample::DrawHistograms(TObjArray& arrayHisto)
{
    for (int i = 0; i < arrayHisto.GetEntriesFast(); i++)
    {
        TObject* obj = arrayHisto.At(i);
        TH1* histogram = static_cast<TH1*>(obj);

        if (TString(histogram->GetName()).EqualTo("histo1"))
        {
            fCanvas->cd(1);
            histogram->Draw();
            fCanvas->cd(0);
            fCanvas->Modified();
            fCanvas->Update();
        }
        else if (TString(histogram->GetName()).EqualTo("histo2"))
        {
            fCanvas->cd(2);
            histogram->Draw();
            fCanvas->cd(0);
            fCanvas->Modified();
            fCanvas->Update();
        }
        else if (TString(histogram->GetName()).EqualTo("histo3"))
        {
            fCanvas->cd(3);
            histogram->Draw("COL");
            fCanvas->cd(0);
            fCanvas->Modified();
            fCanvas->Update();
        }
        else if (TString(histogram->GetName()).EqualTo("histo4"))
        {
            fCanvas->cd(4);
            histogram->Draw("COL");
            fCanvas->cd(0);
            fCanvas->Modified();
            fCanvas->Update();
        }
    }
}
