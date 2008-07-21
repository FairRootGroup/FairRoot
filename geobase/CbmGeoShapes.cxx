//*-- AUTHOR : Ilse Koenig
//*-- Modified : 22/06/2003 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
//
// CbmGeoShapes
//
// Class to manage the GEANT/ROOT geometry shapes
//
// The 3D geometry in ROOT uses the ROOT library geom.
//
// This class holds a list of shape classes (type CbmGeoBasicShape). They are
// used by all detectors when reading or writing geometry parameter containers
// to ascii files or to create an event display. This class is instantiated in
// the class HSpectrometer inside the function createDetGeomPar(Text_t* name).
// Every geometry parameter container gets a pointer to it.
//
// The individual shape classes are accessible with the selectShape(...)
// functions. The functions readPoints(...) and writePoints(...) use it
// internally.
//
// In the current version the following shapes are implemented:
//     BOX  TRAP  TRD1  PGON  PCON TUBE TUBS CONE CONS SPHE  ELTU
//     TORUS is added 06.11.06  m.al-turany
//
///////////////////////////////////////////////////////////////////////////////

#include"CbmGeoShapes.h"

#include "CbmGeoVolume.h"
#include "CbmGeoBasicShape.h"
#include "CbmGeoBrik.h"
#include "CbmGeoTrap.h"
#include "CbmGeoTrd1.h"
#include "CbmGeoPgon.h"
#include "CbmGeoPcon.h"
#include "CbmGeoTube.h"
#include "CbmGeoTubs.h"
#include "CbmGeoCone.h"
#include "CbmGeoCons.h"
#include "CbmGeoSphe.h"
#include "CbmGeoEltu.h"
#include "CbmGeoTorus.h"

#include "TList.h"

ClassImp(CbmGeoShapes) 

CbmGeoShapes::CbmGeoShapes() 
   : shapes(new TList())
{
  // constructor creates empty list of shapes
 
}


CbmGeoShapes::~CbmGeoShapes() {
  // destructor deletes all shapes
  shapes->Delete();
  delete shapes;
}


CbmGeoBasicShape* CbmGeoShapes::selectShape(CbmGeoVolume * volu) {
  // returns a pointer to the shape used in the given volume
  // calls internally selectShape(TString&) with the name of the shape
  // returns NULL if the corresponding shape class is not implemented 
  const TString& name(volu->getShape());
  return selectShape(name);
}


CbmGeoBasicShape* CbmGeoShapes::selectShape(const TString& name) {
  // returns a pointer to the shape given by name
  // creates a shape object and adds it to the list of shapes if
  // not existing
  // returns NULL if the corresponding shape class is not implemented 
  TString allShapes[12]={"BOX ","TRAP","TRD1","PGON","PCON","TUBE","TUBS",
                         "CONE","CONS","SPHE","ELTU","TORUS"};
  TString sName(name);
  if (sName.Length()==3) sName+=" ";
  CbmGeoBasicShape* s=(CbmGeoBasicShape*)shapes->FindObject(sName);
  if (s) return s;
  Int_t no=-1;
  for(Int_t i=0;i<12;i++) {if (sName.CompareTo(allShapes[i])==0) no=i;}
  switch(no) {
    case 0:  {s= new CbmGeoBrik();  break;}
    case 1:  {s= new CbmGeoTrap();  break;}
    case 2:  {s= new CbmGeoTrd1();  break;}
    case 3:  {s= new CbmGeoPgon();  break;}
    case 4:  {s= new CbmGeoPcon();  break;}
    case 5:  {s= new CbmGeoTube();  break;}
    case 6:  {s= new CbmGeoTubs();  break;}
    case 7:  {s= new CbmGeoCone();  break;}
    case 8:  {s= new CbmGeoCons();  break;}
    case 9:  {s= new CbmGeoSphe();  break;}
    case 10: {s= new CbmGeoEltu();  break;}
    case 11: {s= new CbmGeoTorus();  break;}
    default: {
      Error("selectShape","shape %s not implemented",name.Data());
    }
  }
  if (s) shapes->Add(s);
  return s;
}
 
 
Int_t CbmGeoShapes::readPoints(fstream* pFile,CbmGeoVolume* volu) {
  // reads the points of the given volume from the Ascii file
  // returns the number of points read
  // returns 0 if if the corresponding shape class is not implemented
  CbmGeoBasicShape* s=selectShape(volu);
  if (s) return s->readPoints(pFile,volu);
  else return 0;
}

  
Bool_t CbmGeoShapes::writePoints(fstream* pFile,CbmGeoVolume* volu) {
  // writes the points of the given volume to the Ascii file
  // return kFALSE if the corresponding shape class is not implemented
  CbmGeoBasicShape* s=selectShape(volu);
  if (s) return s->writePoints(pFile,volu);
  else return kFALSE;
}


void CbmGeoShapes::printPoints(CbmGeoVolume* volu) {
  // writes the points of the given volume to the Ascii file
  // return kFALSE if the corresponding shape class is not implemented
  CbmGeoBasicShape* s=selectShape(volu);
  if (s) return s->printPoints(volu);
}
