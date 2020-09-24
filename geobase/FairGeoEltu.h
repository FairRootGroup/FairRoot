/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOELTU_H
#define FAIRGEOELTU_H

#include <Rtypes.h>             // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>         // for Bool_t, Int_t
#include <iosfwd>               // for fstream

#include "FairGeoBasicShape.h"  // for FairGeoBasicShape

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
class TBuffer;
class TClass;
class TMemberInspector;

/**
 * class for geometry shape ELTU
 * @author Ilse  koenig
 */
class FairGeoEltu : public FairGeoBasicShape
{
  public:
    FairGeoEltu();
    ~FairGeoEltu();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*, const FairGeoTransform&, const FairGeoTransform&);
    Int_t readPoints(std::fstream*, FairGeoVolume*);
    Bool_t writePoints(std::fstream*, FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoEltu, 0);
};

#endif /* !FAIRGEOELTU_H */
