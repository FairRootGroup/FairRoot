//*-- AUTHOR : Ilse Koenig
//*-- Modified : 16/06/1999
//*-- Modified : 21/06/2005 D.Bertini

///////////////////////////////////////////////////////////////////////////////
//
// CbmGeoTransform
//
// Class to hold the orientation (rotation matrix) and the position
// (translation vector) of a coordinate system (system 2) relative to a
// reference coordinate system (system 1)
// It provides member functions to transform a vector or a point and an other
// coordinate system from its own coordinate system into the reference
// coordinate system and vice versa.
// Instances of this class can e.g. hold the lab or detector transformation of
// a geometry volume (see class CbmGeoVolume)
//
// Inline functions:
//
// CbmGeoTransform()
//    The default constructor creates an identity transformation  
// CbmGeoTransform(CbmGeoTransform& t)
//    copy constructor
// void setTransform(const CbmGeoTransform& t)
//    copies the given transformation
// void setRotMatrix(const CbmGeoRotation& r)
//    copies the given rotation matrix
// void setRotMatrix(const Double_t* a)
//    creates a rotation matrix taking an Double_t array with 9 components 
// void setTransVector(const CbmGeoVector& t)
//    copies the given translation vector
// void setTransVector(const Double_t* a)
//    creates a translation vector taking an Double_t array with 6 components
// const CbmGeoRotation& getRotMatrix() const
//    returns the rotation matrix
// const CbmGeoVector& getTransVector() const
//    returns the  translation vector
//
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoTransform.h"

//#include <iostream>
//#include <iomanip>
//#include "math.h"

ClassImp(CbmGeoTransform)
CbmGeoTransform::CbmGeoTransform()
: rot(CbmGeoRotation(0,0,0)),  
  trans(CbmGeoVector(0,0,0)),
  trans_cm(CbmGeoVector(0,0,0))
{
 
}
CbmGeoTransform& CbmGeoTransform::operator=(const CbmGeoTransform& t)  {
  rot=t.getRotMatrix();
  trans=t.getTransVector();

  return *this;
}


CbmGeoVector CbmGeoTransform::transFrom(const CbmGeoVector& p) const {
  // Transforms a vector (point) given in its own coordinate
  // system (2) into the reference coordinate system (1)
  // e.g. v2 is a vector (point) in the detector coordinate system;
  // it can be transformed to a vector v2 the lab system with
  //    CbmGeoVector v2=mo.transFrom(v1)
  // where mo is the coordinate system of the mother
  return rot*p+trans;
}

CbmGeoVector CbmGeoTransform::transTo(const CbmGeoVector& p) const {
  // Transforms a vector (point) given in the reference system (1)
  // into the local coordinate system (2)
  // e.g. v1 is a vector (point) in the lab system; it can be transformed to
  // a vector v2 the detector coordinate system with
  //    CbmGeoVector v2=mo.transTo(v1)
  // where mo is the coordinate system of the mother
  return rot.inverse()*(p-trans);
}

void CbmGeoTransform::transTo(const CbmGeoTransform& s) {
  // Transforms the coordinate system into the coordinate system
  // described by s. Both transformations must have the same reference
  // system e.g. the lab system
  // This function is e.g. used to transform a daughter coordinate system
  // with a transformation relative to the lab into the detector coordinate
  // system.
  const CbmGeoRotation& rm=s.getRotMatrix();
  CbmGeoRotation rt(rm.inverse());
  if (rm.diff2(rot)<0.000001) rot.setUnitMatrix();
  else rot.transform(rt);
  trans-=s.getTransVector();
  trans=rt*trans;
  //  trans.round(3); // rounds to 3 digits (precision 1 micrometer)
}

void CbmGeoTransform::transFrom(const CbmGeoTransform& s) {
  // Transforms the coordinate system described by s into the local
  // coordinate system
  // This function is e.g. used to transform a daughter coordinate system
  // with a transformation relative to its mother into the lab system.
  // e.g. daughterDetTransform.transFrom(motherLabTransform)
  const CbmGeoRotation& r=s.getRotMatrix();
  rot.transform(r);
  trans=r*trans;
  trans+=s.getTransVector();
}

void CbmGeoTransform::clear() {
  trans.clear();
  rot.setUnitMatrix();
}

void CbmGeoTransform::print() {
  rot.print();
  trans.print();
}

void CbmGeoTransform::invert(void) {
  rot.invert();
  trans = rot*trans;
  trans *= -1.;
}
