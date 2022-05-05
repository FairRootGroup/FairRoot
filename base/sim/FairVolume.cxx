/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                      FairVolume source file                   -----
// -----          Created 12/01/04  by M. Al-Turany                    -----
// -------------------------------------------------------------------------

#include "FairVolume.h"

#include "FairDetector.h"

FairVolume::FairVolume()
    : TNamed()
{}

FairVolume::FairVolume(const TString& name, Int_t id, Int_t modId, FairModule* fMod)
    : TNamed(name, name)
    , fVolumeId(id)
    , fModId(modId)
    , fDetector(dynamic_cast<FairDetector*>(fMod))
    , fModule(fMod)
{}

FairVolume::~FairVolume() = default;

void FairVolume::SetModule(FairModule* mod)
{
    fModule = mod;
    fDetector = dynamic_cast<FairDetector*>(mod);
}

ClassImp(FairVolume);
