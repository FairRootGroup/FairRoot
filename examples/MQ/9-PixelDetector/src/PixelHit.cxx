/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelHit.h"

PixelHit::PixelHit()
    : FairHit()
{
}

PixelHit::PixelHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{
}

PixelHit::~PixelHit()
{
}

ClassImp(PixelHit)
