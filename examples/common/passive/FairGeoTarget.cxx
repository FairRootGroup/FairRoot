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

FairGeoTarget::FairGeoTarget()
    : FairGeoSet()
{
    // Constructor
    fName = "target";
    maxModules = 1;
}
