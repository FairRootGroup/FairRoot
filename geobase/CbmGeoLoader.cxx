/***************************************************************************
                          CbmGeoLoader.cxx  -  description
                             -------------------
    begin                : Thu Jun 17 2004
    copyright            : (C) 2004 by ilse koenig , M. Al-turany
    email                : m.al-turany@gsi.de
 ***************************************************************************/

#include "CbmGeoLoader.h"

#include "CbmGeoInterface.h"
#include "CbmGeoRootBuilder.h"
#include "CbmGeoG3Builder.h"

#include "TGeoManager.h"

#include <iostream>

using std::cout;
using std::endl;

CbmGeoLoader *CbmGeoLoader::fgInstance=0;
//_____________________________________________________________________________
CbmGeoLoader* CbmGeoLoader::Instance()
{
	return fgInstance;
}
//_____________________________________________________________________________
CbmGeoLoader::CbmGeoLoader()
 :fInterface(0),
  fGeoBuilder(0)
{
	fgInstance=this;
}
//_____________________________________________________________________________
CbmGeoLoader::CbmGeoLoader(const char *Name, const char *title)
	:TNamed(Name,title),
     fInterface(0),
     fGeoBuilder(0)
{
	if (fgInstance) {
	    Fatal("CbmGeoLoader", "Singleton instance already exists.");
	    return;
	}  
	fgInstance = this;
	fInterface= new CbmGeoInterface;
        if ( strncmp(Name,"TGeo",4) == 0 ){
          TGeoManager* geom = new TGeoManager("CBMGeom", "CBM geometry");
	  fGeoBuilder=new CbmGeoRootBuilder("TGeo builder","geometry builder");
	  ((CbmGeoRootBuilder*)fGeoBuilder)->setGeoManager(geom);
        }else if ( strncmp(Name,"G3Native",8) == 0) {
            cout << "-I- CbmGeoLoader() : Native G3 Geometry is used" << endl;
          gGeoManager = NULL;
          fGeoBuilder=new CbmGeoG3Builder("G3 builder","geometry builder");
        }

        fInterface->setGeomBuilder(fGeoBuilder);
		
}
//_____________________________________________________________________________
CbmGeoLoader::~CbmGeoLoader()
{
	delete fInterface;

}
//_____________________________________________________________________________

ClassImp(CbmGeoLoader)
