/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "TClonesArray.h"
#include "TH1F.h"

#include "FairRootManager.h"
#include "FairRunOnline.h"

#include "FairTut8RawItem.h"
#include "FairTut8Task.h"

FairTut8Task::FairTut8Task(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fRawData(NULL)
    , fhQdc(NULL)
{
}

FairTut8Task::~FairTut8Task()
{
}

InitStatus FairTut8Task::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    if (NULL == mgr)
    {
        return kFATAL;
    }

    fRawData = static_cast<TClonesArray*>(mgr->GetObject("Tut8RawItem"));
    if (NULL == fRawData)
    {
        return kERROR;
    }

    fhQdc = new TH1F("hQdc", "Raw QDC distribution", 400, 0., 4000.);

    FairRunOnline* run = FairRunOnline::Instance();
    if (NULL == run)
    {
        return kERROR;
    }

    run->AddObject(fhQdc);
    run->RegisterHttpCommand("/Reset_hQdc", "/hQdc/->Reset()");

    return kSUCCESS;
}

void FairTut8Task::Exec(Option_t*)
{
    if (NULL == fRawData)
    {
        return;
    }
    Int_t nItems = fRawData->GetEntriesFast();
    FairTut8RawItem* item;
    for (Int_t i = 0; i < nItems; i++)
    {
        item = static_cast<FairTut8RawItem*>(fRawData->At(i));
        if (NULL == item)
        {
            continue;
        }
        fhQdc->Fill(item->GetQdcData());
    }
}

void FairTut8Task::FinishEvent()
{
}

void FairTut8Task::FinishTask()
{
}

ClassImp(FairTut8Task)
