//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// FairGeoTarget
//
// Class for geometry of Target
//
/////////////////////////////////////////////////////////////

#include "FairGeoTarget.h"

ClassImp(FairGeoTarget)

FairGeoTarget::FairGeoTarget()
  : FairGeoSet()
{
  // Constructor
  fName="target";
  strcpy(modName,"t");
  strcpy(eleName,"t");
  maxSectors=0;
  maxModules=1;
}
