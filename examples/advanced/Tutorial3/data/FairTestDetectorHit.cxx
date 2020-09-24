/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorHit.h"

#include <TGenericClassInfo.h>  // for TGenericClassInfo
#include <TVector3.h>           // for TVector3

FairTestDetectorHit::FairTestDetectorHit()
    : FairHit()
{}

FairTestDetectorHit::FairTestDetectorHit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{}

FairTestDetectorHit::~FairTestDetectorHit() {}

ClassImp(FairTestDetectorHit);
