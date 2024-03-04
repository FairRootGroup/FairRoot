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

FairVolume* FairVolumeList::findObject(const TString& name)
{
    FairVolume* obj = nullptr;

    for (int i = 0; i < fData.GetEntriesFast(); i++) {
        obj = static_cast<FairVolume*>(fData.At(i));
        if (obj) {
            if (obj->GetName() == name) {
                return obj;
            }
        }
    }

    return nullptr;
}

void FairVolumeList::addVolume(FairVolume* elem)
{
    FairVolume* v = findObject(elem->GetName());

    if (v) {
        LOG(error) << "FairVolumeList element: " << elem->GetName() << " VolId : " << elem->getVolumeId()
                   << " already defined " << v->getVolumeId();
    } else {
        fData.Add(elem);
    }
}
