/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorGeo.h"

#include <cstdio>   // for sprintf

FairTestDetectorGeo::FairTestDetectorGeo()
    : FairGeoSet()
{
    // Constructor
    // fName has to be the name used in the geometry for all volumes.
    // If there is a mismatch the geometry cannot be build.
    fName = "torino";
    strcpy(modName, "torino");
    strcpy(eleName, "torino");
    maxSectors = 0;
    maxModules = 10;
}

const char* FairTestDetectorGeo::getModuleName(Int_t m)
{
    /** Returns the module name of FairTestDetector number m
        Setting FairTestDetector here means that all modules names in the
        ASCII file should start with FairTestDetector otherwise they will
        not be constructed
    */
    sprintf(modName, "torino%i", m + 1);
    return modName;
}

const char* FairTestDetectorGeo::getEleName(Int_t m)
{
    /** Returns the element name of Det number m */
    sprintf(eleName, "torino%i", m + 1);
    return eleName;
}
