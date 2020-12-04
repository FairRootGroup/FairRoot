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

InitStatus FairPointSetDraw::Init()
{
    LOG(info) << "FairPointSetDraw::Init()";
    fq = 0;

    // gEve->AddElement(fq, fEventManager );
    return kSUCCESS;
}

void FairPointSetDraw::Exec(Option_t* /*option*/)
{
    Double_t timeOffset = 0.0;
    if (IsActive()) {
        GetData();
        Int_t npoints = GetNPoints();
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

            TVector3 vec(GetVector(i));
            if (checkTime) {
                double time = GetTime(i);
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
            // q->SetPointId(GetValue(p, i));
        }
        gEve->AddElement(q);
        gEve->Redraw3D(kFALSE);
        fq = q;
    }
}

// TObject* FairPointSetDraw::GetValue(TObject* /*obj*/, Int_t i) { return new TNamed(Form("Point %d", i), ""); }

FairPointSetDraw::~FairPointSetDraw() {}

void FairPointSetDraw::SetParContainers() {}

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
