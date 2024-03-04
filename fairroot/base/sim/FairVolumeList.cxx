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

#include "FairLogger.h"   // for logging
#include "FairVolume.h"   // for FairVolume

FairVolume* FairVolumeList::getVolume(const TString& name)
{
    TObject* obj = findObject(name);

    if (obj) {
        LOG(info) << "FairVolume getVolume " << name << " found";
    }

    return static_cast<FairVolume*>(obj);
}

Int_t FairVolumeList::getVolumeId(const TString& name)
{
    FairVolume* vol = getVolume(name);

    if (!vol) {
        return fgkNotFound;
    }

    return vol->getVolumeId();
}

void FairVolumeList::addVolume(std::unique_ptr<FairVolume> vol)
{
    FairVolume* vol_found = findObject(vol->GetName());

    if (vol_found) {
        LOG(error) << "FairVolumeList element: " << vol->GetName() << " VolId : " << vol->getVolumeId()
                   << " already defined " << vol_found->getVolumeId();
    } else {
        fData.Add(vol.release());
    }
}
