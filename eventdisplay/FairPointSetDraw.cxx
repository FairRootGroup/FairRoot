/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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

#include "FairDataSourceI.h"
#include "FairEventManager.h"   // for FairEventManager
#include "FairRootManager.h"    // for FairRootManager
#include "FairTCASource.h"

#include <TClonesArray.h>    // for TClonesArray
#include <TEveManager.h>     // for TEveManager, gEve
#include <TEvePointSet.h>    // for TEvePointSet
#include <TEveTreeTools.h>   // for TEvePointSelectorConsumer, etc
#include <TNamed.h>          // for TNamed
#include <TString.h>         // for Form
#include <TVector3.h>        // for TVector3
#include <iostream>          // for operator<<, basic_ostream, etc

class TObject;

FairPointSetDraw::FairPointSetDraw()
    : FairTask("FairPointSetDraw", 0)
    , fVerbose(0)
    , fq(nullptr)
    , fColor(0)
    , fStyle(0)
{}

FairPointSetDraw::FairPointSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fVerbose(iVerbose)
    , fq(nullptr)
    , fColor(color)
    , fStyle(mstyle)
{}

FairPointSetDraw::FairPointSetDraw(const char* name,
                                   FairDataSourceI* dataSource,
                                   Color_t color,
                                   Style_t mstyle,
                                   Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fVerbose(iVerbose)
    , fq(nullptr)
    , fColor(color)
    , fStyle(mstyle)
    , fDataSource(dataSource)
{}

InitStatus FairPointSetDraw::Init()
{
    LOG(info) << "FairPointSetDraw::Init()";
    fq = 0;

    if (fDataSource == nullptr) {
        fDataSource = new FairTCASource(GetName());
    }
    if (fDataSource->Init() != kSUCCESS) {
        LOG(error) << "FairPointSetDraw::Init() branch " << GetName() << " not found!";
        SetActive(kFALSE);
        return kERROR;
    }
    // gEve->AddElement(fq, fEventManager );
    return kSUCCESS;
}

void FairPointSetDraw::Exec(Option_t* /*option*/)
{
    Double_t timeOffset = 0.0;
    if (IsActive()) {
        if (FairEventManager::Instance()->GetClearHandler()) {
            fDataSource->Reset();
        }
        fDataSource->RetrieveData(FairEventManager::Instance()->GetEvtTime());
        Int_t npoints = fDataSource->GetNData();
        Reset();
        TEvePointSet* q = new TEvePointSet(GetName(), npoints, TEvePointSelectorConsumer::kTVT_XYZ);
        q->SetOwnIds(kTRUE);
        q->SetMarkerColor(fColor);
        q->SetMarkerSize(1.5);
        q->SetMarkerStyle(fStyle);
        double tmin, tmax;
        FairEventManager::Instance()->GetTimeLimits(tmin, tmax);
        bool checkTime = tmin < tmax;

        for (Int_t i = 0; i < npoints; ++i) {

            TVector3 vec(GetVector(fDataSource->GetData(i)));
            if (checkTime) {
                double time = fDataSource->GetTime(i);
                if (fUseTimeOffset && time > -1.0)
                    time += timeOffset;   ///< corrects a point time (with only time-of-flight) to event time +
                                          ///< ToF to match with TimeLimits tmin, tmax
                if (time > 0) {
                    if (time < tmin || time > tmax) {
                        continue;
                    }
                }
            }
            q->SetNextPoint(vec.X(), vec.Y(), vec.Z());
            // q->SetPointId(GetValue(p, i));
        }
        gEve->AddElement(q);
        gEve->Redraw3D(kFALSE);
        fq = q;
    }
}

// TObject* FairPointSetDraw::GetValue(TObject* /*obj*/, Int_t i) { return new TNamed(Form("Point %d", i), ""); }

FairPointSetDraw::~FairPointSetDraw() { delete (fDataSource); }

/** Action after each event**/
void FairPointSetDraw::Finish() {}

void FairPointSetDraw::Reset()
{
    if (fq != 0) {
        fq->Reset();
        gEve->RemoveElement(fq, FairEventManager::Instance());
    }
}

ClassImp(FairPointSetDraw);
