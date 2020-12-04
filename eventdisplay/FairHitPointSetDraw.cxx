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

#include "FairHitPointSetDraw.h"

#include "FairHit.h"   // for FairHit

#include <TClonesArray.h>
#include <TObject.h>
#include <TVector3.h>   // for TVector3
#include <fairlogger/Logger.h>

using std::cout;
using std::endl;

FairHitPointSetDraw::FairHitPointSetDraw()
{
    // TODO Auto-generated constructor stub
}

FairHitPointSetDraw::~FairHitPointSetDraw()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairHitPointSetDraw::Init()
{
    FairRootManager* man = FairRootManager::Instance();
    fPointList = static_cast<TClonesArray*>(man->GetObject(GetName()));
    if (fPointList == 0) {
        LOG(warn) << "FairHitPointSetDraw::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
    }

    LOG(debug2) << "FairHitPointSetDraw::Init() get track list " << fPointList;

    FairPointSetDraw::Init();
    return kSUCCESS;
}

Int_t FairHitPointSetDraw::GetNPoints() { return fPointList->GetEntriesFast(); }

TVector3 FairHitPointSetDraw::GetVector(Int_t index)
{
    TObject* obj = fPointList->At(index);
    FairHit* p = static_cast<FairHit*>(obj);
    LOG(debug) << "-I- FairHitPointSetDraw::GetVector: " << p->GetX() << " " << p->GetY() << " " << p->GetZ();

    return TVector3(p->GetX(), p->GetY(), p->GetZ());
}

double FairHitPointSetDraw::GetTime(Int_t index)
{
    TObject* obj = fPointList->At(index);
    FairHit* p = static_cast<FairHit*>(obj);
    if (fVerbose > 1) {
        cout << "-I- FairHitPointSetDraw::GetTime: " << p->GetTimeStamp() << endl;
    }
    return p->GetTimeStamp();
}

ClassImp(FairHitPointSetDraw);
