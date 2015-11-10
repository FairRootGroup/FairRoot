/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorHit.h"

FairTestDetectorHit::FairTestDetectorHit()
    : FairHit()
{
}

FairTestDetectorHit::FairTestDetectorHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{
}

FairTestDetectorHit::~FairTestDetectorHit()
{
}

ClassImp(FairTestDetectorHit)
