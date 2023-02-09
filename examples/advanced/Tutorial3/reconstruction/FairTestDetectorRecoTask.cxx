/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorRecoTask.h"

#include "FairLink.h"   // for FairLink
#include "FairLogger.h"
#include "FairRootManager.h"        // for FairRootManager
#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi
#include "FairTestDetectorHit.h"    // for FairTestDetectorHit

#include <TClonesArray.h>   // for TClonesArray
#include <TMath.h>          // for Sqrt
#include <TVector3.h>       // for TVector3

FairTestDetectorRecoTask::FairTestDetectorRecoTask()
    : FairTask()
    , fDigiArray(nullptr)
    , fHitArray(nullptr)
{}

FairTestDetectorRecoTask::FairTestDetectorRecoTask(Int_t verbose)
    : FairTask()
    , fDigiArray(nullptr)
    , fHitArray(nullptr)
{
    fVerbose = verbose;
}

FairTestDetectorRecoTask::~FairTestDetectorRecoTask() {}

InitStatus FairTestDetectorRecoTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(error) << "-E- FairTestDetectorRecoTask::Init: RootManager not instantiated!";
        return kFATAL;
    }

    fDigiArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorDigi"));
    if (!fDigiArray) {
        LOG(warn) << "-W- FairTestDetectorRecoTask::Init: No Point array!";
        return kERROR;
    }

    // Create and register output array
    fHitArray = new TClonesArray("FairTestDetectorHit");
    ioman->Register("FairTestDetectorHit", "FairTestDetector", fHitArray, kTRUE);

    return kSUCCESS;
}

void FairTestDetectorRecoTask::Exec(Option_t* /*opt*/)
{
    fHitArray->Clear();

    // fill the map
    for (int ipnt = 0; ipnt < fDigiArray->GetEntriesFast(); ipnt++) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fDigiArray->At(ipnt));
        if (!digi)
            continue;

        /*
        LOG(debug) << " x= "  << digi->GetX()
                   << " y= " << digi->GetY()
                   << " z= " << digi->GetZ()
                   << " t= " << digi->GetTimeStamp();
         // */

        TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
        TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));

        FairTestDetectorHit* hit = new ((*fHitArray)[ipnt]) FairTestDetectorHit(-1, -1, pos, dpos);
        if (!fStreamProcessing)
            hit->AddLink(FairLink(-1,
                                  FairRootManager::Instance()->GetEntryNr(),
                                  FairRootManager::Instance()->GetBranchId("FairTestDetectorDigi"),
                                  ipnt));
        hit->SetTimeStamp(digi->GetTimeStamp());
        hit->SetTimeStampError(digi->GetTimeStampError());
    }
}
