//*-- AUTHOR : Ilse Koenig
//*-- Created : 11/11/03 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
// FairGeoBuilder
//
// Base class for GEANT and ROOT builder classes to create the geometry
//
///////////////////////////////////////////////////////////////////////////////

#include "FairGeoBuilder.h"

ClassImp(FairGeoBuilder)

FairGeoBuilder::FairGeoBuilder()
  :TNamed(),
   nRot(0),
   nMed(0)
{
  // Default constructor
}

FairGeoBuilder::FairGeoBuilder(const char* name,const char* title)
  : TNamed(name,title),
    nRot(0),
    nMed(0)
{
  // Constructor
}

