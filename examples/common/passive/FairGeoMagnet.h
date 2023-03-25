/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMAGNET_H
#define FAIRGEOMAGNET_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for FairGeoMagnet::Class, Int_t, etc

class FairGeoMagnet : public FairGeoSet
{
  protected:
    char modName[2]{"m"};   // name of module
    char eleName[2]{"m"};   // substring for elements in module

  public:
    FairGeoMagnet();
    ~FairGeoMagnet() override = default;
    const char* getModuleName(Int_t) override { return modName; }
    const char* getEleName(Int_t) override { return eleName; }
    ClassDefOverride(FairGeoMagnet, 0);   // Class for the geometry of Magnet
};

#endif /* !FAIRGEOMAGNET_H */
