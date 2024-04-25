/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4Geo.h"

FairTutorialDet4Geo::FairTutorialDet4Geo()
    : FairGeoSet()
{
    // Constructor
    SetName("tutdet");
    setMaxModules(100);
}
