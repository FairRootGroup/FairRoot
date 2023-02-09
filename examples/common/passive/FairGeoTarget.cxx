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
// FairGeoTarget
//
// Class for geometry of Target
//
/////////////////////////////////////////////////////////////

#include "FairGeoTarget.h"

#include <TString.h>   // for TString
#include <string.h>    // for strcpy

FairGeoTarget::FairGeoTarget()
    : FairGeoSet()
{
    // Constructor
    fName = "target";
    strcpy(modName, "t");
    strcpy(eleName, "t");
    maxSectors = 0;
    maxModules = 1;
}
