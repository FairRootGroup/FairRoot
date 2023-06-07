/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                FairParticleGenerator source file               -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------
#include "FairParticleGenerator.h"

#include "FairPrimaryGenerator.h"   // for FairPrimaryGenerator

#include <fairlogger/Logger.h>

FairParticleGenerator::FairParticleGenerator()
    : FairBaseMCGenerator()
    , fPx(0)
    , fPy(0)
    , fPz(0)
{
    SetPDGType(-1);
}

FairParticleGenerator::FairParticleGenerator(Int_t pdgid,
                                             Int_t mult,
                                             Double32_t px,
                                             Double32_t py,
                                             Double32_t pz,
                                             Double32_t vx,
                                             Double32_t vy,
                                             Double32_t vz)
    : FairBaseMCGenerator()
    , fPx(px)
    , fPy(py)
    , fPz(pz)
{
    SetPDGType(pdgid);
    SetMultiplicity(mult);
    SetVertex(vx, vy, vz);
}

void FairParticleGenerator::SetMomentum(Double32_t px, Double32_t py, Double32_t pz)
{
    fPx = px;
    fPy = py;
    fPz = pz;
}

Bool_t FairParticleGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    // Check for particle type
    GenerateEventParameters();
    if (GetPDGType() == -1) {
        LOG(fatal) << "FairParticleGenerator PDG code not defined";
    }

    // Generate particles
    for (Int_t k = 0; k < GetMultiplicity(); k++) {
        LOG(debug) << "FairParticleGenerator:  "
                   << Form("PDG %i p=(%.2f, %.2f, %.2f) GeV,", GetPDGType(), fPx, fPy, fPz);
        primGen->AddTrack(GetPDGType(), fPx, fPy, fPz, fX, fY, fZ);
    }

    return kTRUE;
}
