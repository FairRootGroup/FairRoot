//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// FairGeoMagnet
//
// Class for the geometry of detector part Magnet
//
/////////////////////////////////////////////////////////////

#include "FairGeoMagnet.h"

ClassImp(FairGeoMagnet)

FairGeoMagnet::FairGeoMagnet()
  : FairGeoSet()
{
  // Constructor
  fName="magnet";
  maxSectors=0;
  maxModules=1;
  strcpy(modName,"m");
  strcpy(eleName,"m");
}
