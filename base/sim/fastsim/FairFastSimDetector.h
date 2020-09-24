/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRFASTSIMDETECTOR_H
#define FAIRFASTSIMDETECTOR_H

#include <Rtypes.h>        // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>    // for Int_t, Bool_t

#include "FairDetector.h"  // for FairDetector

class FairVolume;
class TClonesArray;
class TGeoMedium;
class TBuffer;
class TClass;
class TMemberInspector;

class FairFastSimDetector : public FairDetector
{
  public:
    FairFastSimDetector();

    FairFastSimDetector(const char* name, Int_t DetId = 0);

    virtual ~FairFastSimDetector();

    virtual void Initialize() = 0;

    virtual Bool_t ProcessHits(FairVolume* vol = 0) final;

    virtual void EndOfEvent() {}

    virtual void Register() = 0;

    virtual TClonesArray* GetCollection(Int_t iColl) const = 0;

    virtual void Reset() = 0;

    virtual void ConstructGeometry();

  protected:
    virtual void FastSimProcessParticle() = 0;

    TGeoMedium* fFastSimMedium;

    FairFastSimDetector(const FairFastSimDetector&);

    FairFastSimDetector& operator=(const FairFastSimDetector&);

    ClassDef(FairFastSimDetector, 1);
};

#endif   //! FAIRFASTSIMDETECTOR_H
