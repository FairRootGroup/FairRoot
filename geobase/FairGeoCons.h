/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCONS_H
#define FAIRGEOCONS_H

#include "FairGeoBasicShape.h"   // for FairGeoBasicShape

#include <Rtypes.h>   // for FairGeoCons::Class, Bool_t, etc
#include <iosfwd>     // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
/**
 * class for geometry shape CONS
 * @author ilse koenig
 */
class FairGeoCons : public FairGeoBasicShape
{
  public:
    FairGeoCons();
    ~FairGeoCons();
    TArrayD* calcVoluParam(FairGeoVolume*) override;
    void calcVoluPosition(FairGeoVolume*, const FairGeoTransform&, const FairGeoTransform&) override;
    Int_t readPoints(std::fstream*, FairGeoVolume*) override;
    Bool_t writePoints(std::fstream*, FairGeoVolume*) override;
    void printPoints(FairGeoVolume* volu) override;

    ClassDefOverride(FairGeoCons, 0);
};

#endif /* !FAIRGEOCONS_H */
