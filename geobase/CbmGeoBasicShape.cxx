//*-- AUTHOR : Ilse Koenig
//*-- Modified : 11/11/2003 by Ilse Koenig
//*-- Modified : 29/06/99 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
//
// CbmGeoBasicShape
//
// Base class of the all shapes
//
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoBasicShape.h"

#include "CbmGeoVolume.h"
#include "CbmGeoVector.h"

#include "TArrayD.h"

#include <iostream>

using std::cout;

ClassImp(CbmGeoBasicShape)

CbmGeoBasicShape::CbmGeoBasicShape() 
  : nPoints(0),
    nParam(0),
    param(0),
    center(new CbmGeoTransform()),
    position(new CbmGeoTransform())
{
  // default constructor
 
}


CbmGeoBasicShape::~CbmGeoBasicShape() {
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


Int_t CbmGeoBasicShape::readPoints(fstream* pFile,CbmGeoVolume* volu) {
  // reads nPoints with 3 components from Ascii file
  // if the array of points is not existing in the volume it is created and
  // the values are stored inside
  // returns the number of points
  if (!pFile) return 0;
  if (volu->getNumPoints()!=nPoints) volu->createPoints(nPoints);
  Double_t x,y,z;
  const Int_t maxbuf=155;
  Text_t buf[maxbuf];
  for(Int_t i=0;i<nPoints;i++) {
    pFile->getline(buf,maxbuf);
    sscanf(buf,"%lf%lf%lf",&x,&y,&z);
    volu->setPoint(i,x,y,z);
  }  
  return nPoints;
}
   

Bool_t CbmGeoBasicShape::writePoints(fstream* pFile,CbmGeoVolume* volu) {
  // writes nPoints with 3 components to Ascii file
  if (!pFile) return kFALSE;  
  Text_t buf[155];
  for(Int_t i=0;i<volu->getNumPoints();i++) {
    CbmGeoVector& v=*(volu->getPoint(i));
    sprintf(buf,"%9.3f%10.3f%10.3f\n",v(0),v(1),v(2));
    pFile->write(buf,strlen(buf));
  }
  return kTRUE;
}


void CbmGeoBasicShape::printPoints(CbmGeoVolume* volu) {
  // prints nPoints with 3 components to screen
  for(Int_t i=0;i<volu->getNumPoints();i++) {
    CbmGeoVector& v=*(volu->getPoint(i));
    printf("%9.3f%10.3f%10.3f\n",v(0),v(1),v(2));
  }
}


void CbmGeoBasicShape::calcVoluPosition(CbmGeoVolume* volu,
                                       const CbmGeoTransform& mTR) {
  // calculates the relevant information to position the corresponding volume
  // in its mother and to position later other components inside this volume.
  // The transformation mTR describes the position and orientation of the
  // mother volume (center) relative to the physical coordinate system of
  // the volume from which it was created.   
  CbmGeoTransform& dTC=volu->getTransform();
  calcVoluPosition(volu,dTC,mTR);
}


void CbmGeoBasicShape::posInMother(const CbmGeoTransform& dTC,
                                  const CbmGeoTransform& mTR) {
  // calculates the position of the volume inside its mother
  // dTC is the coordinate system of the ROOT volume relative to its physical
  // coordinate system
  // mTR is the coordinate system of the mother volume relative to its
  // physical coordinate system
  position->setRotMatrix(center->getRotMatrix());
  position->setTransVector(center->getTransVector());
  position->transFrom(dTC);
  position->transTo(mTR);
  CbmGeoVector t(position->getTransVector());
  position->setTransVector(t*=0.1);
}


void CbmGeoBasicShape::printParam() {
  // prints the parameters of the ROOT shape 
  if (param) {
    for (Int_t i=0;i<nParam;i++) cout<<param->At(i)<<" ";
    cout<<'\n';
  }
}




