/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTUBS_H
#define FAIRGEOTUBS_H

#include "FairGeoBasicShape.h"   // for FairGeoBasicShape

#include <Rtypes.h>   // for FairGeoPcon::Class, Bool_t, etc
#include <iosfwd>     // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTubs : public FairGeoBasicShape
{
  public:
    FairGeoTubs();
    ~FairGeoTubs() override;
    TArrayD* calcVoluParam(FairGeoVolume*) override;
    void calcVoluPosition(FairGeoVolume*, const FairGeoTransform&, const FairGeoTransform&) override;
    Int_t readPoints(std::fstream*, FairGeoVolume*) override;
    Bool_t writePoints(std::fstream*, FairGeoVolume*) override;
    void printPoints(FairGeoVolume* volu) override;
    ClassDefOverride(FairGeoTubs, 0);   // class for geometry shape TUBS
};

#endif /* !FAIRGEOTUBS_H */
