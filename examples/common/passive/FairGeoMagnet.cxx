/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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

#include <TString.h>   // for TString
#include <string.h>    // for strcpy

ClassImp(FairGeoMagnet);

FairGeoMagnet::FairGeoMagnet()
    : FairGeoSet()
{
    // Constructor
    fName = "magnet";
    maxSectors = 0;
    maxModules = 1;
    strcpy(modName, "m");
    strcpy(eleName, "m");
}
