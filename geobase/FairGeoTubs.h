/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTUBS_H
#define FAIRGEOTUBS_H

#include "FairGeoBasicShape.h"   // for FairGeoBasicShape

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Bool_t, Int_t
#include <iosfwd>         // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
class TBuffer;
class TClass;
class TMemberInspector;

class FairGeoTubs : public FairGeoBasicShape
{
  public:
    FairGeoTubs();
    ~FairGeoTubs();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*, const FairGeoTransform&, const FairGeoTransform&);
    Int_t readPoints(std::fstream*, FairGeoVolume*);
    Bool_t writePoints(std::fstream*, FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoTubs, 0);   // class for geometry shape TUBS
};

#endif /* !FAIRGEOTUBS_H */
