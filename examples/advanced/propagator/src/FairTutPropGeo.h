/********************************************************************************
 * Copyright (C) 2019-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPGEO_H
#define FAIRTUTPROPGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for FairTutPropGeo::Class, ClassDef, FairTutPropGeo::Streamer

class FairTutPropGeo : public FairGeoSet
{
  public:
    FairTutPropGeo();
    ~FairTutPropGeo() override = default;
    ClassDefOverride(FairTutPropGeo, 1);
};

#endif   // FAIRTUTPROPGEO_H
