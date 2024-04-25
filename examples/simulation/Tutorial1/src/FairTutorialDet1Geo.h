/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1GEO_H
#define FAIRTUTORIALDET1GEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for Int_t, etc

class FairTutorialDet1Geo : public FairGeoSet
{
  public:
    FairTutorialDet1Geo();
    ~FairTutorialDet1Geo() override = default;
    ClassDefOverride(FairTutorialDet1Geo, 1);
};

#endif