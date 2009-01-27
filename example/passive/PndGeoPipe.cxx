//*-- AUTHOR : Ilse Koenig
//*-- Created : 10/11/2003

/////////////////////////////////////////////////////////////
// PndGeoPipe
//
// Class for geometry of support structure
//
/////////////////////////////////////////////////////////////

#include "PndGeoPipe.h"
#include "CbmGeoLoader.h"
#include "CbmGeoInterface.h"
    
ClassImp(PndGeoPipe)

PndGeoPipe::PndGeoPipe() {
  // Constructor
  fName="pipe";
  strcpy(modName,"p");
  strcpy(eleName,"p");
  maxSectors=0;
  maxModules=1;
}
Bool_t  PndGeoPipe::create ( CbmGeoBuilder * build ) {
    Bool_t rc = CbmGeoSet::create( build );
    if ( rc ) {
	CbmGeoLoader *loader=CbmGeoLoader::Instance();
	CbmGeoInterface *GeoInterface =loader->getGeoInterface();
	
	GeoInterface->getMasterNodes()->Add( (TObject*)  getVolume("pipeCentral") );
    }
 return rc;
}

PndGeoPipe::~PndGeoPipe() {

}

