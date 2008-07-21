//*-- AUTHOR : Ilse Koenig
//*-- Modified : 16/06/99

///////////////////////////////////////////////////////////////////////////////
//
// CbmGeoVector
//
// This class defines a vector with 3 Double_t components.
// Instantiations of this class are e.g geometry points and
// translation vectors in the geometry transformations.
//
// All functions and operators are defined inline.
//
// Constructors:
//   CbmGeoVector(Double_t dx=0,Double_t dy=0,Double_t dz=0)
//   CbmGeoVector(const CbmGeoVector& v)
//
// Access to the components:
//   void setVector(const Double_t* a);
//   void setX(const Double_t a)
//   void setY(const Double_t a)
//   void setZ(const Double_t a)
//   Double_t getX() const
//   Double_t getY() const
//   Double_t getZ() const
//   Double_t operator() (const Int_t i) const;
//
// Check for the size of all components: 
//   Bool_t operator < (const Double_t a)
//   Bool_t operator <= (const Double_t a)
//   Bool_t operator > (const Double_t a)
//   Bool_t operator >= (const Double_t a)
//
// Check for equality/inequality;
//   Bool_t operator == (const CbmGeoVector& v) const
//   Bool_t operator != (const CbmGeoVector& v) const
//
// Addition/Substraction of a vector;
//   CbmGeoVector& operator += (const Double_t a)
//   CbmGeoVector& operator -= (const Double_t a)
//
// Addition/Substraction of two vectors;
//   CbmGeoVector operator + (const CbmGeoVector& v) const
//   CbmGeoVector operator - (const CbmGeoVector& v) const
//
// Multiplication/Division of each components with/by a factor
//   CbmGeoVector& operator *= (const Double_t a)
//   CbmGeoVector& operator /= (const Double_t a)
//
//
// CbmGeoVector operator - () const
//      changes the sign of all components
//
// CbmGeoVector& operator = (const CbmGeoVector& v)
//      assignment
//
// CbmGeoVector& abs()
//      builds absolute value of each components  
//
// Double_t scalarProduct(const CbmGeoVector& v) const;
//      returns the scalar product
//
// CbmGeoVector vectorProduct(const CbmGeoVector& v) const;
//      returns the vector product
//
// Double_t length() const {return sqrt(x*x+y*y+z*z);}
//      returns the length
//
//  void clear()
//      sets all components to 0.0
//
// void print()
//      prints the components
//
// void round(Int_t n)
//      rounds all components to a precision with n digits
//
// friend ostream& operator << (ostream& put,const CbmGeoVector& v);
//      output to stream
//
// friend istream& operator >> (istream& get,CbmGeoVector& v);
//      input from stream
//
///////////////////////////////////////////////////////////////////////////////

#include "CbmGeoVector.h"

ClassImp(CbmGeoVector)
