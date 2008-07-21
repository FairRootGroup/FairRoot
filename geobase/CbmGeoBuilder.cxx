//*-- AUTHOR : Ilse Koenig
//*-- Created : 11/11/03 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
// CbmGeoBuilder
//
// Base class for GEANT and ROOT builder classes to create the geometry
//
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoBuilder.h"

ClassImp(CbmGeoBuilder)

CbmGeoBuilder::CbmGeoBuilder() 
  :nRot(0),
   nMed(0)
{
  // Default constructor
}

CbmGeoBuilder::CbmGeoBuilder(const char* name,const char* title)
   : TNamed(name,title),
     nRot(0),
     nMed(0) 
{
  // Constructor
}

