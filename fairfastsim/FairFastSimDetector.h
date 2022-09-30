/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRFASTSIMDETECTOR_H
#define FAIRFASTSIMDETECTOR_H

#include "FairDetector.h"

#include <Rtypes.h>

class FairVolume;
class TClonesArray;
class TGeoMedium;

class FairFastSimDetector : public FairDetector
{
  public:
    FairFastSimDetector();

    FairFastSimDetector(const char* name, Int_t DetId = 0);

    ~FairFastSimDetector() override;

    void Initialize() override = 0;

    Bool_t ProcessHits(FairVolume* vol = 0) override final;

    void EndOfEvent() override {}

    void Register() override = 0;

    TClonesArray* GetCollection(Int_t iColl) const override = 0;

    void Reset() override = 0;

    void ConstructGeometry() override;

  protected:
    virtual void FastSimProcessParticle() = 0;

    TGeoMedium* fFastSimMedium;

    FairFastSimDetector(const FairFastSimDetector&);

    FairFastSimDetector& operator=(const FairFastSimDetector&);

    ClassDefOverride(FairFastSimDetector, 1);
};

#endif   //! FAIRFASTSIMDETECTOR_H
