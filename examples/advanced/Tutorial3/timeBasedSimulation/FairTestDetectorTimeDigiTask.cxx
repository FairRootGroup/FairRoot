/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorTimeDigiTask.h"

#include "FairLink.h"   // for FairLink
#include "FairLogger.h"
#include "FairRootManager.h"        // for FairRootManager
#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi
#include "FairTestDetectorDigiWriteoutBuffer.h"
#include "FairTestDetectorPoint.h"   // for FairTestDetectorPoint

#include <TClonesArray.h>   // for TClonesArray
#include <TMath.h>          // for Sqrt
#include <TRandom.h>        // for TRandom, gRandom
#include <TString.h>        // for TString

FairTestDetectorTimeDigiTask::FairTestDetectorTimeDigiTask()
    : FairTask()
    , fTimeResolution(100.)
    , fPointArray(nullptr)
    , fDigiArray(nullptr)
    , fDataBuffer(nullptr)
    , fTimeOrderedDigi(kFALSE)
{}

FairTestDetectorTimeDigiTask::~FairTestDetectorTimeDigiTask() {}

InitStatus FairTestDetectorTimeDigiTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman) {
        LOG(error) << "FairTestDetectorTimeDigiTask::Init: RootManager not instantiated!";
        return kFATAL;
    }

    fPointArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorPoint"));
    if (!fPointArray) {
        LOG(warn) << "FairTestDetectorTimeDigiTask::Init: No Point array!";
        return kERROR;
    }

    // Create and register output array
    fDataBuffer = new FairTestDetectorDigiWriteoutBuffer("FairTestDetectorDigi", "TOY", kTRUE);
    fDataBuffer = static_cast<FairTestDetectorDigiWriteoutBuffer*>(
        ioman->RegisterWriteoutBuffer("FairTestDetectorDigi", fDataBuffer));
    fDataBuffer->ActivateBuffering(fTimeOrderedDigi);

    return kSUCCESS;
}

void FairTestDetectorTimeDigiTask::Exec(Option_t* /*opt*/)
{
    // fDigiArray->Delete();

    // fill the map
    LOG(info) << "EventTime: " << FairRootManager::Instance()->GetEventTime();

    for (int ipnt = 0; ipnt < fPointArray->GetEntries(); ipnt++) {
        FairTestDetectorPoint* point = static_cast<FairTestDetectorPoint*>(fPointArray->At(ipnt));
        if (!point) {
            continue;
        }

        Int_t xPad = CalcPad(point->GetX(), point->GetXOut());
        Int_t yPad = CalcPad(point->GetY(), point->GetYOut());
        Int_t zPad = CalcPad(point->GetZ(), point->GetZOut());

        Double_t timestamp = CalcTimeStamp(point->GetTime());

        FairTestDetectorDigi* digi = new FairTestDetectorDigi(xPad, yPad, zPad, timestamp);
        if (fTimeResolution > 0) {
            digi->SetTimeStampError(fTimeResolution / TMath::Sqrt(fTimeResolution));
        } else {
            digi->SetTimeStampError(0);
        }

        digi->SetLink(FairLink(-1, FairRootManager::Instance()->GetEntryNr(), "FairTestDetectorPoint", ipnt));

        Double_t timeOfFlight = point->GetTime();
        Double_t eventTime = FairRootManager::Instance()->GetEventTime();

        fDataBuffer->FillNewData(digi, timeOfFlight + eventTime, digi->GetTimeStamp() + 10);
    }
}

Int_t FairTestDetectorTimeDigiTask::CalcPad(Double_t posIn, Double_t posOut)
{
    Int_t result = static_cast<Int_t>(posIn + posOut) / 2;
    return result;
}

Double_t FairTestDetectorTimeDigiTask::CalcTimeStamp(Double_t timeOfFlight)
{
    Double_t eventTime = FairRootManager::Instance()->GetEventTime();
    Double_t detectionTime = gRandom->Gaus(0, fTimeResolution);

    Double_t result = eventTime + timeOfFlight + detectionTime;

    if (result < 0) {
        return 0;
    } else {
        return result;
    }
}
