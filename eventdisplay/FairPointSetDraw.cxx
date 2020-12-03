/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                        FairPointSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#include "FairPointSetDraw.h"

#include "FairEventManager.h"   // for FairEventManager
#include "FairRootManager.h"    // for FairRootManager

#include <TClonesArray.h>    // for TClonesArray
#include <TEveManager.h>     // for TEveManager, gEve
#include <TEvePointSet.h>    // for TEvePointSet
#include <TEveTreeTools.h>   // for TEvePointSelectorConsumer, etc
#include <TNamed.h>          // for TNamed
#include <TString.h>         // for Form
#include <TVector3.h>        // for TVector3
#include <iostream>          // for operator<<, basic_ostream, etc

class TObject;

using std::cout;
using std::endl;

FairPointSetDraw::FairPointSetDraw()
    : FairTask("FairPointSetDraw", 0)
    , fVerbose(0)
    , fPointList(nullptr)
    , fEventManager(nullptr)
    , fq(nullptr)
    , fColor(0)
    , fStyle(0)
    , fBranch(nullptr)
{}

FairPointSetDraw::FairPointSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fVerbose(iVerbose)
    , fPointList(nullptr)
    , fEventManager(nullptr)
    , fq(nullptr)
    , fColor(color)
    , fStyle(mstyle)
    , fBranch(nullptr)
{}

InitStatus FairPointSetDraw::Init()
{
    LOG(info) << "FairPointSetDraw::Init()";

    FairRootManager* fManager = FairRootManager::Instance();
    fBranch = fManager->GetInTree()->GetBranch(GetName());
    fEventTime = fManager->InitObjectAs<std::vector<double> const*>("EventTimes");

    fPointList = static_cast<TClonesArray*>(fManager->GetObject(GetName()));
    if (fPointList == 0) {
        LOG(warn) << "FairPointSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
    }

    LOG(debug2) << "FairPointSetDraw::Init() get track list " << fPointList;
    fEventManager = FairEventManager::Instance();
    fq = 0;

    // gEve->AddElement(fq, fEventManager );
    return kSUCCESS;
}

void FairPointSetDraw::Exec(Option_t* /*option*/)
{
    Double_t timeOffset = 0.0;
    if (IsActive()) {
        if (FairRunAna::Instance()->IsTimeStamp() && fEventTime != nullptr
            && fEventTime->size() > 0) {   ///< find the matching event to a given time if timebased simulation is on
            Double_t simTime = fEventManager->GetEvtTime();
            auto lower = std::lower_bound(fEventTime->begin(), fEventTime->end(), simTime + 0.01);
            int currentEvent = std::distance(fEventTime->begin(), lower) - 1;
            if (currentEvent == -1) {
                fPointList->Delete();
            } else {
                fBranch->GetEvent(currentEvent);
                timeOffset = fEventTime->at(currentEvent);
            }
        }
        Int_t npoints = fPointList->GetEntriesFast();
        Reset();
        TEvePointSet* q = new TEvePointSet(GetName(), npoints, TEvePointSelectorConsumer::kTVT_XYZ);
        q->SetOwnIds(kTRUE);
        q->SetMarkerColor(fColor);
        q->SetMarkerSize(1.5);
        q->SetMarkerStyle(fStyle);
        double tmin, tmax;
        FairEventManager::Instance()->GetTimeLimits(tmin, tmax);
        bool checkTime = tmin < tmax;
        // std::cout << "FairPointSetDraw::Exec time offset " << timeOffset << " tmin " << tmin << " tmax " << tmax
        //                  << std::endl;
        for (Int_t i = 0; i < npoints; ++i) {
            TObject* p = static_cast<TObject*>(fPointList->At(i));
            if (p != 0) {
                TVector3 vec(GetVector(p));
                if (checkTime) {
                    double time = GetTime(p);
                    if (fUseTimeOffset == kTRUE)
                        time += timeOffset;   ///< corrects a point time (with only time-of-flight) to event time +
                                              ///< ToF to match with TimeLimits tmin, tmax
                    // std::cout << i << " time: " << time;
                    if (time > 0) {
                        if (time < tmin || time > tmax) {
                            // std::cout << " no match" << std::endl;
                            continue;
                        }
                    }
                    // std::cout << " match" << std::endl;
                }
                q->SetNextPoint(vec.X(), vec.Y(), vec.Z());
                q->SetPointId(GetValue(p, i));
            }
        }
        gEve->AddElement(q);
        gEve->Redraw3D(kFALSE);
        fq = q;
    }
}

TObject* FairPointSetDraw::GetValue(TObject* /*obj*/, Int_t i) { return new TNamed(Form("Point %d", i), ""); }

FairPointSetDraw::~FairPointSetDraw() {}

void FairPointSetDraw::SetParContainers() {}

/** Action after each event**/
void FairPointSetDraw::Finish() {}

void FairPointSetDraw::Reset()
{
    if (fq != 0) {
        fq->Reset();
        gEve->RemoveElement(fq, fEventManager);
    }
}

ClassImp(FairPointSetDraw);
