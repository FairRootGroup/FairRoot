/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet2Geo.h"

FairTutorialDet2Geo::FairTutorialDet2Geo()
    : FairGeoSet()
{
    // Constructor
    SetName("tutdet");
    setMaxModules(10);
}
