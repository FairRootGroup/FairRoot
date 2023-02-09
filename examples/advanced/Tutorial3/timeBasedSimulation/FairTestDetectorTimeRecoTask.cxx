/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorTimeRecoTask.h"

#include "FairLogger.h"
#include "FairRootManager.h"          // for FairRootManager
#include "FairRunAna.h"               // for FairRunAna
#include "FairTSBufferFunctional.h"   // for StopTime
#include "FairTestDetectorDigi.h"     // for FairTestDetectorDigi
#include "FairTestDetectorHit.h"      // for FairTestDetectorHit

#include <TClonesArray.h>   // for TClonesArray
#include <TMath.h>          // for Sqrt
#include <TVector3.h>       // for TVector3

FairTestDetectorTimeRecoTask::FairTestDetectorTimeRecoTask()
    : FairTask()
    , fDigiArray(nullptr)
    , fHitArray(nullptr)
    , fTime(0.)
    , fFunctor(nullptr)
{}

FairTestDetectorTimeRecoTask::FairTestDetectorTimeRecoTask(Int_t verbose)
    : FairTask()
    , fDigiArray(nullptr)
    , fHitArray(nullptr)
    , fTime(0.)
    , fFunctor(nullptr)
{
    fVerbose = verbose;
}

FairTestDetectorTimeRecoTask::~FairTestDetectorTimeRecoTask() {}

InitStatus FairTestDetectorTimeRecoTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(error) << "FairTestDetectorTimeRecoTask::Init: RootManager not instantiated!";
        return kFATAL;
    }

    fDigiArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorSortedDigi"));
    if (!fDigiArray) {
        LOG(warn) << "FairTestDetectorTimeRecoTask::Init: No Point array!";
        return kERROR;
    }

    fFunctor = new StopTime();

    // Create and register output array
    fHitArray = new TClonesArray("FairTestDetectorHit");
    ioman->Register("FairTestDetectorHit", "FairTestDetector", fHitArray, kTRUE);

    return kSUCCESS;
}

void FairTestDetectorTimeRecoTask::Exec(Option_t* /*opt*/)
{
    fHitArray->Delete();

    fTime += 200;
    if (FairRunAna::Instance()->IsTimeStamp()) {
        fDigiArray = FairRootManager::Instance()->GetData("FairTestDetectorSortedDigi", fFunctor, fTime);
        //    LOG(info) << "EventTime: " << FairRootManager::Instance()->GetEntryNr() << " " <<
        //    FairRootManager::Instance()->GetEventTime();
    }

    // fill the map
    // LOG(info) << "NDigis: " << fDigiArray->GetEntries();
    for (int ipnt = 0; ipnt < fDigiArray->GetEntries(); ipnt++) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fDigiArray->At(ipnt));
        if (!digi) {
            LOG(warn) << "No digi!";
            continue;
        }

        // Double_t timestamp = digi->GetTimeStamp();
        TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
        TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));

        FairTestDetectorHit* hit = new ((*fHitArray)[ipnt]) FairTestDetectorHit(-1, -1, pos, dpos);
        hit->SetTimeStamp(digi->GetTimeStamp());
        hit->SetTimeStampError(digi->GetTimeStampError());
        hit->AddLink(digi->GetEntryNr());
        hit->AddInterfaceData(digi);

        fHitArray->Sort();
    }

    fDigiArray->Delete();
}
