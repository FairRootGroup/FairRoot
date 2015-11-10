/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairRutherfordGeo.h"

#include <stdio.h>                      // for sprintf

ClassImp(FairRutherfordGeo)

// -----   Default constructor   -------------------------------------------
FairRutherfordGeo::FairRutherfordGeo()
  : FairGeoSet()
{
  // Constructor
  fName="rutherford";
  maxSectors=0;
  maxModules=10;
}

// -------------------------------------------------------------------------

const char* FairRutherfordGeo::getModuleName(Int_t m)
{
  /** Returns the module name of FairRutherford number m
      Setting MyDet here means that all modules names in the
      ASCII file should start with FairRutherford otherwise they will
      not be constructed
  */
  sprintf(modName,"rutherford%i",m+1);
  return modName;
}

const char* FairRutherfordGeo::getEleName(Int_t m)
{
  /** Returns the element name of Det number m */
  sprintf(eleName,"rutherford%i",m+1);
  return eleName;
}
