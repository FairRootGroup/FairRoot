/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                        FairBoxSetDraw source file                  -----
// -----                  Created 03/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#include "FairBoxSetDraw.h"

#include "FairBoxSet.h"         // for FairBoxSet
#include "FairEventManager.h"   // for FairEventManager
#include "FairLogger.h"
#include "FairRootManager.h"   // for FairRootManager
#include "FairRunAna.h"        // for FairRunAna
#include "FairTCASource.h"
#include "FairTSBufferFunctional.h"   // for StopTime
#include "FairTimeStamp.h"            // for FairTimeStamp

#include <TClonesArray.h>   // for TClonesArray
#include <TEveBoxSet.h>
#include <TEveManager.h>   // for TEveManager, gEve
#include <TVector3.h>      // for TVector3
#include <iostream>        // for operator<<, basic_ostream, etc

FairBoxSet* fq;   //!
Double_t fX, fY, fZ;

FairBoxSetDraw::FairBoxSetDraw()
    : FairTask("FairBoxSetDraw", 0)
    , fVerbose(0)
{}

FairBoxSetDraw::FairBoxSetDraw(const char* name, FairDataSourceI* dataSource, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fVerbose(iVerbose)
    , fDataSource(dataSource)
{}

FairBoxSetDraw::FairBoxSetDraw(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fVerbose(iVerbose)
    , fDataSource(nullptr)
{}

InitStatus FairBoxSetDraw::Init()
{
    LOG(debug) << "FairBoxSetDraw::Init()";

    if (fDataSource == nullptr) {
        fDataSource = new FairTCASource(GetName());
    }

    if (fDataSource->Init() != kSUCCESS) {
        LOG(error) << "FairBoxSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
        return kERROR;
    }

    fEventManager = FairEventManager::Instance();

    fq = 0;

    return kSUCCESS;
}

void FairBoxSetDraw::Exec(Option_t* /*option*/)
{
    if (IsActive()) {
        TObject* p;
        Reset();
        //  cout<<  "FairBoxSetDraw::Init() Exec! " << fList->GetEntriesFast() << endl;
        CreateBoxSet();
        if (FairEventManager::Instance()->GetClearHandler()) {
            fDataSource->Reset();
        }
        fDataSource->RetrieveData(fEventManager->GetEvtTime());

        double tmin = -1.;
        double tmax = -1.;
        FairEventManager::Instance()->GetTimeLimits(tmin, tmax);
        bool checkTime = tmin < tmax;

        for (Int_t i = 0; i < fDataSource->GetNData(); ++i) {
            p = fDataSource->GetData(i);
            if (checkTime) {
                double time = fDataSource->GetTime(i);
                if (time + fTimeWindowMinus > 0) {
                    if (time + fTimeWindowMinus < tmin || time - fTimeWindowPlus > tmax) {
                        continue;
                    }
                }
            }
            AddBoxes(fq, p, i);
        }
        gEve->AddElement(fq, fEventManager);
        gEve->Redraw3D(kFALSE);
    }
}

void FairBoxSetDraw::AddBoxes(FairBoxSet* set, TObject* obj, Int_t i)
{
    TVector3 point = GetVector(obj);
    set->AddBox(point.X(), point.Y(), point.Z());
    set->DigitValue(GetValue(obj, i));
    LOG(debug2) << "FairBoxSetDraw::Init() Add point " << i << ": " << point.X() << " " << point.Y() << " " << point.Z()
                << " ";
}

Int_t FairBoxSetDraw::GetValue(TObject* /*obj*/, Int_t i) { return i; }

FairBoxSet* FairBoxSetDraw::CreateBoxSet()
{
    FairBoxSet* aBoxSet = new FairBoxSet(this, GetName());
    aBoxSet->Reset(FairBoxSet::kBT_AABoxFixedDim, kFALSE, 64);
    aBoxSet->SetDefWidth(fX);
    aBoxSet->SetDefHeight(fY);
    aBoxSet->SetDefDepth(fZ);
    fq = aBoxSet;

    return aBoxSet;
}

void FairBoxSetDraw::SetTimeWindowMinus(Double_t val) { fTimeWindowMinus = val; }

void FairBoxSetDraw::SetTimeWindowPlus(Double_t val) { fTimeWindowPlus = val; }

FairBoxSetDraw::~FairBoxSetDraw() {}

/** Action after each event**/
void FairBoxSetDraw::Finish() {}

void FairBoxSetDraw::Reset()
{
    if (fq != 0) {
        fq->Reset();
        gEve->RemoveElement(fq, fEventManager);
    }
}

ClassImp(FairBoxSetDraw);
