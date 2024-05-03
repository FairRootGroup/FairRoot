/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRutherfordGeo.h"

FairRutherfordGeo::FairRutherfordGeo()
    : FairGeoSet()
{
    // Constructor
    SetName("rutherford");
    setMaxModules(10);
}
