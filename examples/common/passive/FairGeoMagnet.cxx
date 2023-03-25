/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// FairGeoMagnet
//
// Class for the geometry of detector part Magnet
//
/////////////////////////////////////////////////////////////

#include "FairGeoMagnet.h"

FairGeoMagnet::FairGeoMagnet()
    : FairGeoSet()
{
    // Constructor
    fName = "magnet";
    maxModules = 1;
}
