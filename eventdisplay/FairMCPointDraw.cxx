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

#include "FairMCPointDraw.h"

#include "FairMCPoint.h"   // for FairMCPoint

#include <TClonesArray.h>
#include <TObject.h>
#include <TVector3.h>   // for TVector3

FairMCPointDraw::FairMCPointDraw()
{
    // TODO Auto-generated constructor stub
}

FairMCPointDraw::~FairMCPointDraw()
{
    // TODO Auto-generated destructor stub
}

InitStatus FairMCPointDraw::Init()
{
    FairRootManager* man = FairRootManager::Instance();
    fPointList = static_cast<TClonesArray*>(man->GetObject(GetName()));
    if (fPointList == 0) {
        LOG(warn) << "FairMCPoint::Init()  branch " << GetName() << " Not found! Task will be deactivated ";
        SetActive(kFALSE);
    }

    LOG(debug2) << "FairPointSetDraw::Init() get track list " << fPointList;

    FairPointSetDraw::Init();
    return kSUCCESS;
}

Int_t FairMCPointDraw::GetNPoints() { return fPointList->GetEntriesFast(); }

TVector3 FairMCPointDraw::GetVector(Int_t index)
{
    TObject* obj = fPointList->At(index);
    FairMCPoint* p = static_cast<FairMCPoint*>(obj);
    return TVector3(p->GetX(), p->GetY(), p->GetZ());
}

ClassImp(FairMCPointDraw);
