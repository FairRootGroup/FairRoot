//*-- AUTHOR : Ilse Koenig
//*-- Modified : 27/05/99

/////////////////////////////////////////////////////////////
// CbmGeoVolume
//
// Class to hold the basic geometry properties of a volume
// Each volume has a name, a pointer to a reference volume and
// a lab transformation.
// The reference volume defines the shape, the mother, the size
// and the transformation relative to the mother volume which
// is either the cave (for modules) or the detector (for the
// inner parts). 
// As an example:
// The Mdc modules built at GSI (plane 1 type) are all identical
// independent where the sit in the cave. This module type has a
// fixed coordinate system. The first layers in all these modules
// are identical and they have the same position in the module
// coordinate system.   
//
/////////////////////////////////////////////////////////////
#include "CbmGeoVolume.h"

#include <iostream>

using std::cout;
using std::endl;

ClassImp(CbmGeoVolume)

CbmGeoVolume::CbmGeoVolume(CbmGeoVolume& r) 
  : shape(""),
	mother(""),
    points(0),
    transform(CbmGeoTransform()), 
    fLabTransform(CbmGeoTransform()),
    fMedium(0),
    nPoints(0),
    fHadFormat(0),
    fgMCid(0)
{
  // copy constructor
  fName=r.GetName();
  setVolumePar(r);
}

void CbmGeoVolume::setVolumePar(CbmGeoVolume& r) {
  // copies all volume parameters except the name
  shape=r.getShape();
  mother=r.getMother();
  Int_t n=r.getNumPoints();
  createPoints(n);
  for (Int_t i=0;i<nPoints;i++) setPoint(i,*(r.getPoint(i)));
  transform=r.getTransform();
}

void CbmGeoVolume::createPoints(const Int_t n) {
  // Creates n Points (objects of class CbmGeoVector).
  // If the array exists already and the size is different from n it is
  // deleted and recreated with the new size n.
  // If n==0 the points are deleted.
  if (n!=nPoints) {
    nPoints=n;
    if (n>0) {
      if (points!=0) {
        points->Delete();
        delete points;
      }
      points=new TObjArray(n);
      for(Int_t i=0;i<n;i++) points->AddAt(new CbmGeoVector(),i);
    }
    else {
      if (points) points->Delete();
      delete points;
      points=0;
    }
  }
}

void CbmGeoVolume::setPoint(const Int_t n,const Double_t x,
                           const Double_t y,const Double_t z) {
  // set the 3 values of the point with index n
  if (points && n<nPoints) {
    CbmGeoVector* v=(CbmGeoVector*)points->At(n);
    v->setX(x);
    v->setY(y);
    v->setZ(z);
  }
}

void CbmGeoVolume::setPoint(const Int_t n,const CbmGeoVector& p) {
  // sets point with index n by copying the 3 components of point p 
  if (points && n<nPoints) {
    CbmGeoVector& v=*((CbmGeoVector*)points->At(n));
    v=p;
  }
}

void CbmGeoVolume::clear() {
  // clears the volume
  // deletes the points
  shape="";
  mother="";
  if (points) points->Delete();
  delete points;
  points=0;
  nPoints=0;
  transform.clear();
}

void CbmGeoVolume::print() {
  // prints all parameters of a volume
    cout<<"Volume: " <<((const char*)fName)<<"  Shape: "<<((const char*)shape)<<"  Mother: "
      <<((const char*)mother)<<'\n';
  cout << "Points definition " << endl;
  if (points) {
    for (Int_t i=0;i<nPoints;i++)
        cout<<(*((CbmGeoVector*)points->At(i)));
  }
  cout << "Lab Transform " << endl;
  fLabTransform.print();
  cout<<'\n';
}

Double_t CbmGeoVolume::getVolParameter( Int_t nPoint, Int_t pos ){
  CbmGeoVector *vec = (CbmGeoVector*) points->At( nPoint );
  if ( vec ) return vec->getValues( pos );
  else return -1;
}


CbmGeoVolume::~CbmGeoVolume() {
  if (points) {
    points->Delete();
    delete points;
    points=0;
  }
}

