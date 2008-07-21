//*-- AUTHOR : Ilse Koenig
//*-- Modified : 11/11/2003 by Ilse Koenig
//*-- Modified : 14/05/99 by Ilse Koenig

/////////////////////////////////////////////////////////////
//
// CbmGeoBrik
//
// class for the GEANT shape BOX
// 
// The intrisic coordinate system of a BOX in GEANT/ROOT has the
// same orientation as the volume described by its 8 points
// in the technical coordinate system 
// 
/////////////////////////////////////////////////////////////

#include "CbmGeoBrik.h"

#include "CbmGeoVolume.h"
#include "CbmGeoVector.h"

#include "TArrayD.h"

ClassImp(CbmGeoBrik)

CbmGeoBrik::CbmGeoBrik() {
  // constructor
  fName="BOX ";
  nPoints=8;
  nParam=3;
  param=new TArrayD(nParam);
}


CbmGeoBrik::~CbmGeoBrik() {
  // destructor
  if (param) {
    delete param;
    param=0;
  }
  if (center) {
    delete center;
    center=0;
  }
  if (position) {
    delete position;
    position=0;
  }
}


TArrayD* CbmGeoBrik::calcVoluParam(CbmGeoVolume* volu) {
  // calculates the parameters needed to create the shape 
  if (!volu) return 0;
  CbmGeoVector v=*(volu->getPoint(5)) - *(volu->getPoint(3));
  v.abs();
  v*=(1/20.);
  for(Int_t i=0;i<nParam;i++) param->AddAt(v(i),i);
  return param;
} 


void CbmGeoBrik::calcVoluPosition(CbmGeoVolume* volu,
          const CbmGeoTransform& dTC,const CbmGeoTransform& mTR) {
  // calls the function posInMother(...) to calculate the position of the
  // volume in its mother 
  CbmGeoVector trans=*(volu->getPoint(5)) + *(volu->getPoint(3));
  trans*=0.5;
  center->clear();
  center->setTransVector(trans);
  posInMother(dTC,mTR);
}





