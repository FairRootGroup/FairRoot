//*-- AUTHOR : Ilse Koenig
//*-- Modified : 11/11/2003 by Ilse Koenig
//*-- Modified : 28/06/99 by Ilse Koenig

///////////////////////////////////////////////////////////////////////////////
//
// CbmGeoCone
//
// class for the GEANT shape CONE
// 
// The size of a CONE is defined by 4 'points'.
//   point 0:   origin of starting circle of the cone;
//   point 1:   inner radius of starting circle,
//              outer radius of starting circle;
//              (z-component not used)
//   point 2:   origin of ending circle of the cone;
//   point 3:   inner radius of ending circle,
//              outer radius of ending circle;
//              (z-component not used)
// Warning: The x- and y-values of point 0 and 2 have to be the same!!!!
//          A rotation has to be desribed via the rotation matrix.
//
// The intrinsic coordinate system of a CONE, which sits in the CAVE and is
// not rotated, is identical with the laboratory system.
//
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoCone.h"

#include "CbmGeoVolume.h"
#include "CbmGeoVector.h"

#include "TArrayD.h"

ClassImp(CbmGeoCone)

CbmGeoCone::CbmGeoCone() {
  // constructor
  fName="CONE";
  nPoints=4;
  nParam=5;
  param=new TArrayD(nParam);
}


CbmGeoCone::~CbmGeoCone() {
  // default destructor
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


Int_t CbmGeoCone::readPoints(fstream* pFile,CbmGeoVolume* volu) {
  // reads the 4 'points' decribed above from ascii file
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
    i++;
    pFile->getline(buf,maxbuf);
    sscanf(buf,"%lf%lf",&x,&y);
    volu->setPoint(i,x,y,0.0);
  }
  return nPoints;
}


Bool_t CbmGeoCone::writePoints(fstream* pFile,CbmGeoVolume* volu) {
  // writes the 4 'points' decribed above to ascii file
  if (!pFile) return kFALSE;  
  Text_t buf[155];
  for(Int_t i=0;i<nPoints;i++) {
    CbmGeoVector& v=*(volu->getPoint(i));
    if (i==0 || i==2) sprintf(buf,"%9.3f%10.3f%10.3f\n",v(0),v(1),v(2));
    else sprintf(buf,"%9.3f%10.3f\n",v(0),v(1));
    pFile->write(buf,strlen(buf));
  }
  return kTRUE;
}


void CbmGeoCone::printPoints(CbmGeoVolume* volu) {
  // prints volume points to screen
  for(Int_t i=0;i<nPoints;i++) {
    CbmGeoVector& v=*(volu->getPoint(i));
    if (i==0 || i==2) printf("%9.3f%10.3f%10.3f\n",v(0),v(1),v(2));
    else printf("%9.3f%10.3f\n",v(0),v(1));
  }
}


TArrayD* CbmGeoCone::calcVoluParam(CbmGeoVolume* volu) {
  // calculates the parameters needed to create the shape CONE 
  Double_t fac=10.;
  CbmGeoVector v=*(volu->getPoint(2)) - *(volu->getPoint(0));
  param->AddAt(TMath::Abs(v(2))/fac/2.,0);
  CbmGeoVector& v1=*(volu->getPoint(1));
  param->AddAt(v1(0)/fac,1);
  param->AddAt(v1(1)/fac,2);
  CbmGeoVector& v3=*(volu->getPoint(3));
  param->AddAt(v3(0)/fac,3);
  param->AddAt(v3(1)/fac,4);
  return param;
} 


void CbmGeoCone::calcVoluPosition(CbmGeoVolume* volu,
          const CbmGeoTransform& dTC,const CbmGeoTransform& mTR) {
  // calculates the position of the center of the volume in the intrinsic
  // coordinate system and stores it in the data element 'center'
  // calls the function posInMother(...) to calculate the position of the
  // volume in its mother 
  Double_t t[3]={0.,0.,0.};
  CbmGeoVector v=*(volu->getPoint(2)) + *(volu->getPoint(0));
  t[2]=v(2)/2.;  
  center->clear();
  center->setTransVector(t);
  posInMother(dTC,mTR);
}

