/********************************************************************************
 *                  Copyright (C) 2026 Jagiellonian University                  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairShapeSetDraw.h"

#include "FairEventManager.h"   // for FairEventManager
#include "FairLogger.h"
#include "FairRootManager.h"   // for FairRootManager
#include "FairRunAna.h"        // for FairRunAna
#include "FairShapeSet.h"      // for FairShapeSet
#include "FairTCASource.h"
#include "FairTSBufferFunctional.h"   // for StopTime
#include "FairTimeStamp.h"            // for FairTimeStamp

#include <Math/Point3D.h>
#include <TClonesArray.h>   // for TClonesArray
#include <TEveBoxSet.h>
#include <TEveManager.h>   // for TEveManager, gEve
#include <TVector3.h>      // for TVector3
#include <iostream>        // for operator<<, basic_ostream, etc

FairShapeSetDraw::FairShapeSetDraw()
    : FairTask("FairShapeSetDraw", 0)
{}

FairShapeSetDraw::FairShapeSetDraw(const char* name,
                                   FairDataSourceI* dataSource,
                                   Color_t color,
                                   Style_t mstyle,
                                   Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fColor{color}
    , fStyle{mstyle}
    , fVerbose{iVerbose}
    , fDataSource{dataSource}
{}

FairShapeSetDraw::FairShapeSetDraw(const char* name, Color_t color, Style_t mstyle, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fColor{color}
    , fStyle{mstyle}
    , fVerbose{iVerbose}
{}

InitStatus FairShapeSetDraw::Init()
{
    LOG(debug) << "FairShapeSetDraw::Init()";

    if (!fDataSource) {
        fDataSource = new FairTCASource(GetName());
    }

    if (fDataSource->Init() != kSUCCESS) {
        LOG(error) << "FairShapeSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
        return kERROR;
    }

    fEventManager = FairEventManager::Instance();

    fq = 0;

    return kSUCCESS;
}

void FairShapeSetDraw::Exec(Option_t* /*option*/)
{
    if (IsActive()) {
        Reset();
        //  cout<<  "FairShapeSetDraw::Init() Exec! " << fList->GetEntriesFast() << endl;
        CreateShapeSet();
        if (FairEventManager::Instance()->GetClearHandler()) {
            fDataSource->Reset();
        }
        fDataSource->RetrieveData(fEventManager->GetEvtTime());

        double tmin = -1.;
        double tmax = -1.;
        FairEventManager::Instance()->GetTimeLimits(tmin, tmax);
        bool checkTime = tmin < tmax;

        for (Int_t i = 0; i < fDataSource->GetNData(); ++i) {
            auto p = fDataSource->GetData(i);
            if (checkTime) {
                double time = fDataSource->GetTime(i);
                if (time + fTimeWindowMinus > 0) {
                    if (time + fTimeWindowMinus < tmin || time - fTimeWindowPlus > tmax) {
                        continue;
                    }
                }
            }
            AddShapes(fq, p, i);
        }
        gEve->AddElement(fq, fEventManager);
        gEve->Redraw3D(kFALSE);
    }
}

void FairShapeSetDraw::AddShapes(FairShapeSet* set, TObject* obj, Int_t i)
{
    auto shape = GetShape(obj);

    set->AddBox(shape.data());
    set->DigitValue(GetValue(obj, i));
    LOG(debug2) << "FairShapeSetDraw::Init() Add shape for " << obj << " ";
}

Int_t FairShapeSetDraw::GetValue(TObject* /*obj*/, Int_t i)
{
    return i;
}

FairShapeSet* FairShapeSetDraw::CreateShapeSet()
{
    auto aShapeSet = new FairShapeSet(this, GetName());
    aShapeSet->Reset(FairShapeSet::kBT_FreeBox, kFALSE, 64);
    fq = aShapeSet;

    return aShapeSet;
}

void FairShapeSetDraw::SetTimeWindowMinus(Double_t val)
{
    fTimeWindowMinus = val;
}

void FairShapeSetDraw::SetTimeWindowPlus(Double_t val)
{
    fTimeWindowPlus = val;
}

/** Action after each event**/
void FairShapeSetDraw::Finish() {}

void FairShapeSetDraw::Reset()
{
    if (fq != 0) {
        fq->Reset();
        gEve->RemoveElement(fq, fEventManager);
    }
}
