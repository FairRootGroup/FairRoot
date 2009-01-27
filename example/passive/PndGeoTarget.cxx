//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// PndGeoTarget
//
// Class for geometry of Target
//
/////////////////////////////////////////////////////////////

#include "PndGeoTarget.h"

ClassImp(PndGeoTarget)

PndGeoTarget::PndGeoTarget() {
  // Constructor
  fName="target";
  strcpy(modName,"t");
  strcpy(eleName,"t");
  maxSectors=0;
  maxModules=1;
}
