/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2GEO_H
#define FAIRTUTORIALDET2GEO_H

#include "FairGeoSet.h"

#include <Rtypes.h>

class FairTutorialDet2Geo : public FairGeoSet
{
  public:
    FairTutorialDet2Geo();
    ~FairTutorialDet2Geo() override = default;
    ClassDefOverride(FairTutorialDet2Geo, 1);
};

#endif /*  FAIRTUTORIALDETGEO_H */
