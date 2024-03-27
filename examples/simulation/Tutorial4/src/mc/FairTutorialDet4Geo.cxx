/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTutorialDet4Geo.h"

#include <fairlogger/Logger.h>
#include <stdio.h>   // for sprintf

FairTutorialDet4Geo::FairTutorialDet4Geo()
    : FairGeoSet()
{
    // Constructor
    fName = "tutdet";
    maxModules = 100;
}

const char* FairTutorialDet4Geo::getModuleName(Int_t m)
{
    /** Returns the module name of TutorialDet number m
      Setting MyDet here means that all modules names in the
      ASCII file should start with TutorialDet otherwise they will
      not be constructed
  */
    int result_length = snprintf(modName, maxbuf - 1, "tutdet%i", m + 1);
    if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
        LOG(fatal) << "Buffer overrun in snprintf.";
    }
    return modName;
}

const char* FairTutorialDet4Geo::getEleName(Int_t m)
{
    /** Returns the element name of Det number m */
    int result_length = snprintf(eleName, maxbuf - 1, "tutdet%i", m + 1);
    if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
        LOG(fatal) << "Buffer overrun in snprintf.";
    }
    return eleName;
}
