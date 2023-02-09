/********************************************************************************
 * Copyright (C) 2019-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutPropGeo.h"

#include <stdio.h>   // for sprintf

// -----   Default constructor   -------------------------------------------
FairTutPropGeo::FairTutPropGeo()
    : FairGeoSet()
{
    // Constructor
    // fName has to be the name used in the geometry for all volumes.
    // If there is a mismatch the geometry cannot be build.
    fName = "Pixel";
    strcpy(modName, "Pixel");
    strcpy(eleName, "Pixel");
    maxSectors = 0;
    maxModules = 10;
}

// -------------------------------------------------------------------------

const char* FairTutPropGeo::getModuleName(Int_t m)
{
    /** Returns the module name of Pixel number m
      Setting Pixel here means that all modules names in the
      ASCII file should start with Pixel otherwise they will
      not be constructed
  */
    sprintf(modName, "Pixel%i", m + 1);
    return modName;
}

const char* FairTutPropGeo::getEleName(Int_t m)
{
    /** Returns the element name of Det number m */
    sprintf(eleName, "Pixel%i", m + 1);
    return eleName;
}
