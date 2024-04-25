/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "PixelGeo.h"

PixelGeo::PixelGeo()
    : FairGeoSet()
{
    // Constructor
    // fName has to be the name used in the geometry for all volumes.
    // If there is a mismatch the geometry cannot be build.
    SetName("Pixel");
    setMaxModules(10);
}
