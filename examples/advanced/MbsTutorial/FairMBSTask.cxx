/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMBSTask.h"

#include "FairMBSRawItem.h"
#include "FairRootManager.h"

#include <TCanvas.h>
#include <TFolder.h>

InitStatus FairMBSTask::Init()
{
    FairRootManager& mgr = fRunOnline.GetRootManager();

    fRawData = static_cast<TClonesArray*>(mgr.GetObject("MBSRawItem"));
    if (nullptr == fRawData) {
        return kERROR;
    }

    fhQdc = new TH1F("hQdc", "Raw QDC distribution", 400, 0., 4000.);
    fhTac = new TH1F("hTac", "Raw TAC distribution", 400, 0., 4000.);
    fhClock = new TH1F("hClock", "Raw Clock distribution", 64, 0., 64.);
    fhTacCh = new TH1F("hTacCh", "Raw TAC Channel distribution", 20, 0., 20.);

    fRunOnline.AddObject(fhQdc);
    fRunOnline.RegisterHttpCommand("/Reset_hQdc", "/hQdc/->Reset()");

    auto c1 = new TCanvas("c1", "", 10, 10, 500, 500);
    c1->Divide(2, 2);
    c1->cd(1);
    fhQdc->Draw();
    c1->cd(2);
    fhTac->Draw();
    c1->cd(3);
    fhClock->Draw();
    c1->cd(4);
    fhTacCh->Draw();
    c1->cd(0);
    fRunOnline.AddObject(c1);

    auto folder = new TFolder("MbsDetFolder", "Example Folder");
    folder->Add(fhQdc);
    folder->Add(fhTac);
    folder->Add(fhClock);
    folder->Add(fhTacCh);
    fRunOnline.AddObject(folder);

    return kSUCCESS;
}

void FairMBSTask::Exec(Option_t*)
{
    if (nullptr == fRawData) {
        return;
    }
    Int_t nItems = fRawData->GetEntriesFast();
    for (Int_t i = 0; i < nItems; i++) {
        auto item = static_cast<FairMBSRawItem const*>(fRawData->At(i));
        if (nullptr == item) {
            continue;
        }
        fhQdc->Fill(item->GetQdcData());
        fhTac->Fill(item->GetTacData());
        fhClock->Fill(item->GetClock());
        fhTacCh->Fill(item->GetTacCh());
    }
}
