/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "NewDetectorGeo.h"

#include "FairGeoNode.h"

// -----   Default constructor   -------------------------------------------
NewDetectorGeo::NewDetectorGeo()
    : FairGeoSet("newdetector", 10)
{}

// -------------------------------------------------------------------------

const char* NewDetectorGeo::getModuleName(Int_t m)
{
    /** Returns the module name of NewDetector number m
      Setting NewDetector here means that all modules names in the
      ASCII file should start with NewDetector otherwise they will
      not be constructed
  */
    sprintf(modName, "NewDetector%i", m + 1);
    return modName;
}

const char* NewDetectorGeo::getEleName(Int_t m)
{
    /** Returns the element name of Det number m */
    sprintf(eleName, "NewDetector%i", m + 1);
    return eleName;
}
