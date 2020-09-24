/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelHit.h"

#include <TGenericClassInfo.h>  // for TGenericClassInfo
#include <TVector3.h>           // for TVector3

PixelHit::PixelHit()
    : FairHit()
{}

PixelHit::PixelHit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{}

PixelHit::~PixelHit() {}

ClassImp(PixelHit);
