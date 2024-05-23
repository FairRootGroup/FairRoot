/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropHit.h"

FairTutPropHit::FairTutPropHit()
    : FairHit()
    , fTrackID(-1)
    , fPx(0.)
    , fPy(0.)
    , fPz(0.)
    , fDPx(0.)
    , fDPy(0.)
    , fDPz(0.)
{}

FairTutPropHit::FairTutPropHit(int detID,
                               int mcindex,
                               const TVector3& pos,
                               const TVector3& dpos,
                               int trackID,
                               int pdgCode,
                               double charge,
                               const TVector3& mom,
                               const TVector3& dmom)
    : FairHit(detID, pos, dpos, mcindex)
    , fTrackID(trackID)
    , fPdgCode(pdgCode)
    , fCharge(charge)
    , fPx(mom.X())
    , fPy(mom.Y())
    , fPz(mom.Z())
    , fDPx(dmom.X())
    , fDPy(dmom.Y())
    , fDPz(dmom.Z())
{}

FairTutPropHit::~FairTutPropHit() {}
