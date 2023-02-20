/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairHitDraw.cpp
 *
 *  Created on: Apr 16, 2009
 *      Author: stockman
 */

#include "FairHitDraw.h"

#include "FairHit.h"   // for FairHit

class TObject;

FairHitDraw::FairHitDraw() {}

FairHitDraw::FairHitDraw(const char* name, FairDataSourceI* dataSource, Int_t iVerbose)
    : FairBoxSetDraw(name, dataSource, iVerbose)
{}

FairHitDraw::FairHitDraw(const char* name, Int_t iVerbose)
    : FairBoxSetDraw(name, iVerbose)
{}

TVector3 FairHitDraw::GetVector(TObject* obj)
{
    FairHit* hit = static_cast<FairHit*>(obj);
    return TVector3(hit->GetX(), hit->GetY(), hit->GetZ());
}

ClassImp(FairHitDraw);
