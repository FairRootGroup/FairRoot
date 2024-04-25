/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEO_H
#define PIXELGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

#include <Rtypes.h>   // for PixelGeo::Class, ClassDef, PixelGeo::Streamer

class PixelGeo : public FairGeoSet
{
  public:
    PixelGeo();
    ~PixelGeo() override = default;
    ClassDefOverride(PixelGeo, 1);
};

#endif
