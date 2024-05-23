/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEO_H
#define CBMRUTHERFORDGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for Int_t, etc

class FairRutherfordGeo : public FairGeoSet
{
  public:
    FairRutherfordGeo();
    ~FairRutherfordGeo() override = default;
    ClassDefOverride(FairRutherfordGeo, 1);
};

#endif
