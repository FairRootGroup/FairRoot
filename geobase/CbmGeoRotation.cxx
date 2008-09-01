//*-- AUTHOR : Ilse Koenig
//*-- Modified : 16/06/99

///////////////////////////////////////////////////////////////////////////////
// CbmGeoRotation
//
// This class defines a 3x3 rotation matrix.
// The data are stored in a linear array with 9 Double_t
// components.
//
// Inline functions:
//
// Constructors:
//   CbmGeoRotation()
//   CbmGeoRotation(const CbmGeoRotation& r)
//   CbmGeoRotation(const Double_t* a)
//
// Access to components:
//   Double_t operator () (Int_t) const
//   void setElement(const Double_t,const Int_t)
//
// Check for equality/inequality
//   Bool_t operator == (const CbmGeoRotation&)
//   Bool_t operator != (const CbmGeoRotation&)
//
// CbmGeoRotation& operator = (const CbmGeoRotation&);
//      assignment
//
// void setUnitMatrix()
//      sets identity matrix
//
// void setZero()
//      sets all components to 0.0
//
// Bool_t isUnitMatrix()
//      checks unity
//
// CbmGeoRotation& invert()
//      inverts the matrix
//
// CbmGeoRotation inverse()
//      copies the matrix and returns the inverse of the copy
//
// Double_t determinant() const;
//      returns determinate
//
// CbmGeoRotation& operator *= (const CbmGeoRotation&);
//      multiplies with the given rotation matrix from the right
//
// CbmGeoRotation& transform(const CbmGeoRotation&);
//      multiplies with the given rotation matrix from the left
//
// CbmGeoVector operator * (const CbmGeoVector&) const;
//      rotates a vector
//
// CbmGeoRotation operator * (const CbmGeoRotation&) const;
//      rotates the given rotation
//  
// void print()
//      shows the matrix
//
//
// Euler Angles:
//   1. angle:  rotation around z-axis   --> x1, y1, z1=z
//   2. angle:  rotation around y1-axis  --> x2, y2=y1, z2
//   3. angle:  rotation around z2-axis  --> x3, y3, z3=z2
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoRotation.h"

ClassImp(CbmGeoRotation)


CbmGeoRotation::CbmGeoRotation(const Double_t a,const Double_t b,
                             const Double_t c) {
  // constructor taking three Euler angles
  setEulerAngles(a,b,c);
}


void CbmGeoRotation::setEulerAngles(const Double_t a,const Double_t b,
                                   const Double_t c) {
  // sets the matrix calculating the values from the given Euler angles
  const double deg2rad=0.01745329252; 
  Double_t s0=TMath::Sin(a*deg2rad);
  Double_t c0=TMath::Cos(a*deg2rad);
  Double_t s1=TMath::Sin(b*deg2rad);
  Double_t c1=TMath::Cos(b*deg2rad);
  Double_t s2=TMath::Sin(c*deg2rad);
  Double_t c2=TMath::Cos(c*deg2rad);
  rot[0]=c0*c1*c2 - s0*s2;
  rot[1]=-c0*c1*s2 - s0*c2;
  rot[2]=c0*s1;
  rot[3]=s0*c1*c2 + c0*s2;
  rot[4]=c0*c2 - s0*c1*s2;
  rot[5]=s0*s1;
  rot[6]=-s1*c2;
  rot[7]=s1*s2;
  rot[8]=c1;
}


Double_t CbmGeoRotation::diff2(const CbmGeoRotation& r) const {
  // calculates the square of the difference between 2 matrices
  Double_t s=0;
  for(Int_t i=0;i<9;i++) {
    Double_t d=rot[i]-r(i);
    s+=d*d;
  }
  return s;
}


TRotMatrix* CbmGeoRotation::createTRotMatrix(const Text_t* name,const Text_t* title) {
  // creates a TRotMatrix
  // (uses a new() operator and the user has to take care to free the memory)
  TRotMatrix* t=0;
  if (isUnitMatrix()==kTRUE) return t;
  Double_t a[9];
  for(Int_t i=0;i<3;i++) {
    for(Int_t j=0;j<3;j++) a[j+3*i]=rot[i+3*j];
  }
  t=new TRotMatrix(name,title,a);
  return t;
}

