/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4Hit.h"

FairTutorialDet4Hit::FairTutorialDet4Hit()
    : FairHit()
{}

FairTutorialDet4Hit::FairTutorialDet4Hit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{}

FairTutorialDet4Hit::~FairTutorialDet4Hit() {}
