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

FairHitPointSetDraw::FairHitPointSetDraw()
{
    // TODO Auto-generated constructor stub
}

FairHitPointSetDraw::~FairHitPointSetDraw()
{
    // TODO Auto-generated destructor stub
}

TVector3 FairHitPointSetDraw::GetVector(TObject* obj)
{
    FairHit* p = static_cast<FairHit*>(obj);
    LOG(debug) << "-I- FairHitPointSetDraw::GetVector: " << p->GetX() << " " << p->GetY() << " " << p->GetZ();

    return TVector3(p->GetX(), p->GetY(), p->GetZ());
}

ClassImp(FairHitPointSetDraw);
