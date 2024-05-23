/***************************************************************************
 * Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                         *
 *            This software is distributed under the terms of the          *
 *            GNU Lesser General Public Licence (LGPL) version 3,          *
 *                copied verbatim in the file "LICENSE"                    *
 ***************************************************************************/
#ifndef FAIRTESTGEO_H
#define FAIRTESTGEO_H

#include "FairGeoSet.h"   // for FairGeoSet

class FairTestGeo : public FairGeoSet
{
  public:
    FairTestGeo();
    ~FairTestGeo() override = default;
};

#endif
