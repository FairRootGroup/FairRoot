/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_VOLUMELIST_H
#define FAIR_VOLUMELIST_H

#include "FairVolume.h"

#include <Rtypes.h>      // for Int_t, etc
#include <TObjArray.h>   // for TObjArray
#include <TObject.h>     // for TObject
#include <TString.h>     // for TString

/**
 * This Object is only used for internal book keeping!
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairVolumeList : public TObject
{
  private:
    TObjArray* fData;
    FairVolumeList(const FairVolumeList&);
    FairVolumeList& operator=(const FairVolumeList&);

  public:
    FairVolumeList();
    ~FairVolumeList() override;

    FairVolume* getVolume(TString* name);
    Int_t getVolumeId(TString* name);

    FairVolume* findObject(TString name);
    void addVolume(FairVolume* elem);

    Int_t getEntries() { return fData->GetEntries(); }
    FairVolume* At(Int_t pos) { return (dynamic_cast<FairVolume*>(fData->At(pos))); }

    ClassDefOverride(FairVolumeList, 1);
};

#endif   // FAIR_VOLUMELIST_H
