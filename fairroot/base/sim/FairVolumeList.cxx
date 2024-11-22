/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 FairVolumeList  source file                   -----
// -----          Created 12/01/04  by M. Al-Turany                    -----
// -------------------------------------------------------------------------

#include "FairVolumeList.h"

#include "FairDetector.h"
#include "FairVolume.h"

FairVolume* FairVolumeList::getVolume(const TString& name)
{
    auto obj = findObject(name);

    if (obj) {
        LOG(info) << "FairVolume getVolume " << name << " found";
    }

    return static_cast<FairVolume*>(obj);
}

Int_t FairVolumeList::getVolumeId(const TString& name)
{
    auto vol = getVolume(name);

    return vol ? vol->getVolumeId() : fgkNotFound;
}

FairVolume* FairVolumeList::addVolume(std::unique_ptr<FairVolume> vol)
{
    auto vol_found = findObject(vol->GetName());

    if (vol_found) {
        // FATAL: The same volume name for different detectors
        if (vol->GetDetector() != vol_found->GetDetector()) {
            LOG(fatal) << "FairVolumeList Trying to register element: " << vol->GetName()
                       << " (VolId=" << vol->getVolumeId() << ") for detector " << vol->GetDetector()->GetName()
                       << ", but it was already defined (VolId=" << vol_found->getVolumeId() << ") for detector "
                       << vol_found->GetDetector()->GetName();
        }
        return nullptr;
    }

    auto vol_added = vol.get();
    fData.Add(vol.release());
    return vol_added;
}
