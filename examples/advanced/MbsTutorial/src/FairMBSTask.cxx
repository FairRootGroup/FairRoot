/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "TClonesArray.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFolder.h"

#include "FairRootManager.h"
#include "FairRunOnline.h"

#include "FairMBSRawItem.h"
#include "FairMBSTask.h"

FairMBSTask::FairMBSTask(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fRawData(NULL)
    , fhQdc(NULL)
    , fhTac(NULL)
    , fhClock(NULL)
    , fhTacCh(NULL)
{
}

FairMBSTask::~FairMBSTask()
{
}

InitStatus FairMBSTask::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
    {
        return kFATAL;
    }

    fRawData = static_cast<TClonesArray*>(mgr->GetObject("MBSRawItem"));
    if (NULL == fRawData)
    {
        return kERROR;
    }

    fhQdc = new TH1F("hQdc", "Raw QDC distribution", 400, 0., 4000.);
    fhTac = new TH1F("hTac", "Raw TAC distribution", 400, 0., 4000.);
    fhClock = new TH1F("hClock", "Raw Clock distribution", 64, 0., 64.);
    fhTacCh = new TH1F("hTacCh", "Raw TAC Channel distribution", 20, 0., 20.);

    FairRunOnline* run = FairRunOnline::Instance();
    if (NULL == run)
    {
        return kERROR;
    }

    run->AddObject(fhQdc);
    run->RegisterHttpCommand("/Reset_hQdc", "/hQdc/->Reset()");
    
    TCanvas *c1 = new TCanvas("c1", "", 10, 10, 500, 500);
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
    run->AddObject(c1);
    
    TFolder *folder = new TFolder("MbsDetFolder", "Example Folder");
    folder->Add(fhQdc);
    folder->Add(fhTac);
    folder->Add(fhClock);
    folder->Add(fhTacCh);
    run->AddObject(folder);

    return kSUCCESS;
}

void FairMBSTask::Exec(Option_t*)
{
    if (NULL == fRawData)
    {
        return;
    }
    Int_t nItems = fRawData->GetEntriesFast();
    FairMBSRawItem* item;
    for (Int_t i = 0; i < nItems; i++)
    {
        item = static_cast<FairMBSRawItem*>(fRawData->At(i));
        if (NULL == item)
        {
            continue;
        }
        fhQdc->Fill(item->GetQdcData());
        fhTac->Fill(item->GetTacData());
        fhClock->Fill(item->GetClock());
        fhTacCh->Fill(item->GetTacCh());
    }
}

void FairMBSTask::FinishEvent()
{
}

void FairMBSTask::FinishTask()
{
}

ClassImp(FairMBSTask)
