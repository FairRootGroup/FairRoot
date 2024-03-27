/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "PixelGeo.h"

#include <fairlogger/Logger.h>

#include <stdio.h>   // for sprintf

PixelGeo::PixelGeo()
    : FairGeoSet()
{
    // Constructor
    // fName has to be the name used in the geometry for all volumes.
    // If there is a mismatch the geometry cannot be build.
    fName = "Pixel";
    maxModules = 10;
}

const char* PixelGeo::getModuleName(Int_t m)
{
    /** Returns the module name of Pixel number m
      Setting Pixel here means that all modules names in the
      ASCII file should start with Pixel otherwise they will
      not be constructed
  */
    int result_length = snprintf(modName, maxbuf-1, "Pixel%i", m + 1);
    if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
      LOG(fatal) << "Buffer overrun in snprintf.";
    }
    return modName;
}

const char* PixelGeo::getEleName(Int_t m)
{
    /** Returns the element name of Det number m */
    int result_length = snprintf(eleName, maxbuf-1, "Pixel%i", m + 1);
    if (!(result_length > 0 && result_length < static_cast<int>(maxbuf))) {
      LOG(fatal) << "Buffer overrun in snprintf.";
    }
    return eleName;
}
