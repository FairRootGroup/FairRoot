/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCPointsDraw.cpp
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#include "FairTimebasedMCHitDraw.h"

#include "FairEventManager.h"
#include "FairMCPoint.h"   // for FairMCPoint
#include "FairRootManager.h"

#include <TClonesArray.h>
#include <TObject.h>
#include <TVector3.h>   // for TVector3

FairTimebasedMCHitDraw::FairTimebasedMCHitDraw()
{
    // TODO Auto-generated constructor stub
}

FairTimebasedMCHitDraw::~FairTimebasedMCHitDraw()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairTimebasedMCHitDraw::Init()
{
    FairRootManager* man = FairRootManager::Instance();
    fPointList = static_cast<TClonesArray*>(man->GetObject(GetName()));
    if (fPointList == nullptr) {
        LOG(warn) << "FairMCPoint::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
    }

    fEventTime = man->InitObjectAs<std::vector<double> const*>("EventTimes");
    fBranch = man->GetInTree()->GetBranch(GetName());

    if (fEventTime == nullptr) {
        LOG(error) << "FairTimebasedMCHitDraw::Init no EventTimes vector";
        return kERROR;
    }

    LOG(debug2) << "FairTimebasedMCHitDraw::Init() get track list " << fPointList;

    FairPointSetDraw::Init();
    return kSUCCESS;
}

void FairTimebasedMCHitDraw::GetData()
{
    Double_t simTime = FairEventManager::Instance()->GetEvtTime();
    auto lower = std::lower_bound(fEventTime->begin(), fEventTime->end(), simTime + 0.01);
    int evtIndex = std::distance(fEventTime->begin(), lower) - 1;
    if (evtIndex > -1) {
        LOG(debug) << "FairTimebasedMCHitDraw::GetData " << simTime << " lower " << *lower << " at index "
                   << evtIndex + 1;
        LOG(debug) << "GetEvent " << evtIndex << " time: " << fEventTime->at(evtIndex) << std::endl;
    }
    if (evtIndex < 0) {
        fPointList->Clear();
    } else {
        fBranch->GetEvent(evtIndex);
        fCurrentEventTime = fEventTime->at(evtIndex);
    }
    if (FairEventManager::Instance()->GetClearHandler() == kTRUE) {
        fDataHandler.Reset();
    }
    if (evtIndex > -1)
        fDataHandler.FillTClonesArray(fPointList, evtIndex, fCurrentEventTime, simTime);
}

Int_t FairTimebasedMCHitDraw::GetNPoints() { return fDataHandler.GetData().size(); }

TVector3 FairTimebasedMCHitDraw::GetVector(Int_t index)
{
    FairHit* p = fDataHandler.GetData()[index].first;
    return TVector3(p->GetX(), p->GetY(), p->GetZ());
}

Double_t FairTimebasedMCHitDraw::GetTime(Int_t index)
{
    return fDataHandler.GetData()[index].first->GetTimeStamp()
           + fDataHandler.GetData()[index].second;   // Flight time + event time
}

ClassImp(FairTimebasedMCHitDraw);
