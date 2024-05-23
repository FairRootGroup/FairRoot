/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4GEO_H
#define FAIRTUTORIALDET4GEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>

class FairTutorialDet4Geo : public FairGeoSet
{
  public:
    FairTutorialDet4Geo();
    ~FairTutorialDet4Geo() override = default;
    ClassDefOverride(FairTutorialDet4Geo, 1);
};

#endif /*  FAIRTUTORIALDETGEO_H */
