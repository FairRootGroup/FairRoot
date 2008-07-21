#ifndef CBMGEOVECTOR_H
#define CBMGEOVECTOR_H

#include "TObject.h"
#include "TMath.h"

#include <iostream>


class CbmGeoVector : public TObject {
protected:
  Double_t x;
  Double_t y;
  Double_t z;
  inline void round(Double_t d,Int_t n);
public:
  CbmGeoVector(Double_t dx=0,Double_t dy=0,Double_t dz=0) : x(dx),y(dy),z(dz) {}
  CbmGeoVector(const CbmGeoVector& v) : x(v.getX()), y(v.getY()), z(v.getZ()) {}
  ~CbmGeoVector() {}
  Double_t &X() {return x;}
  Double_t &Y() {return y;}
  Double_t &Z() {return z;}
  Double_t getX() const {return x;}
  Double_t getY() const {return y;}
  Double_t getZ() const {return z;}

  Double_t getValues(Int_t i ) {
    if ( i<0 || i>2 )
         std::cout << " -E- Vector index  is 0 1 2 only ! " << std::endl;
    if ( i == 0 ) return x;
    if ( i == 1 ) return y;
    if ( i == 2 ) return z;
   return -1;
  }

  void setXYZ(const Double_t xx,const Double_t yy,const Double_t zz) {
    x=xx; y=yy; z=zz;
  }
  void setX(const Double_t a) {x=a;}
  void setY(const Double_t a) {y=a;}
  void setZ(const Double_t a) {z=a;}
  inline void setVector(const Double_t* a);
  inline void setVector(const Float_t* a);
  inline Double_t operator() (const Int_t i) const;
  inline CbmGeoVector operator - () const;
  inline CbmGeoVector& operator = (const CbmGeoVector& v);
  inline Bool_t operator == (const CbmGeoVector& v) const;
  inline Bool_t operator != (const CbmGeoVector& v) const;
  inline Bool_t operator < (const Double_t a);
  inline Bool_t operator <= (const Double_t a);
  inline Bool_t operator > (const Double_t a);
  inline Bool_t operator >= (const Double_t a);
  inline CbmGeoVector& operator += (const Double_t a);
  inline CbmGeoVector& operator -= (const Double_t a);
  inline CbmGeoVector& operator *= (const Double_t a);
  inline CbmGeoVector& operator /= (const Double_t a);
  inline CbmGeoVector& operator += (const CbmGeoVector& v);
  inline CbmGeoVector& operator -= (const CbmGeoVector& v);
  inline CbmGeoVector operator + (const CbmGeoVector& v) const;
  inline CbmGeoVector operator - (const CbmGeoVector& v) const;
  inline CbmGeoVector& abs();
  inline Double_t scalarProduct(const CbmGeoVector& v) const;
  inline CbmGeoVector vectorProduct(const CbmGeoVector& v) const;
  Double_t length() const {return sqrt(x*x+y*y+z*z);}
  void clear() {x=y=z=0.;}
  void print() const {printf("%10.3f%10.3f%10.3f\n",x,y,z);}
  inline void round(Int_t n);
  inline friend ostream& operator << (ostream& put,const CbmGeoVector& v);
  inline friend istream& operator >> (istream& get,CbmGeoVector& v);
  ClassDef(CbmGeoVector,1) // vector with 3 components
};

// -------------------- inlines ---------------------------

inline void CbmGeoVector::setVector(const Double_t* a) {
  x=a[0];
  y=a[1];
  z=a[2];
}

inline void CbmGeoVector::setVector(const Float_t* a) {
  x=a[0];
  y=a[1];
  z=a[2];
}

inline Double_t CbmGeoVector::operator() (const Int_t i) const {
  switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: Error("operator()","bad index");
  }
  return 0;
}

inline CbmGeoVector CbmGeoVector::operator - () const {
  CbmGeoVector p(-x,-y,-z);
  return p;
}

inline CbmGeoVector& CbmGeoVector::operator = (const CbmGeoVector& v) {
  x=v.getX();
  y=v.getY();
  z=v.getZ();
  return *this;
}

inline Bool_t CbmGeoVector::operator == (const CbmGeoVector& v) const {
  return ((v.getX()!=x || v.getY()!=y || v.getZ()!=z) ? kFALSE : kTRUE); 
}

inline  Bool_t CbmGeoVector::operator != (const CbmGeoVector& v) const {
  return (v.getX()!=x || v.getY()!=y || v.getZ()!=z)  ? kTRUE : kFALSE; 
}
/// check with ilse
inline Bool_t CbmGeoVector::operator < (const Double_t a) {
  return (x>=a || y>=a || z>=a) ? kFALSE : kTRUE;
}

inline Bool_t CbmGeoVector::operator <= (const Double_t a) {
  return (x>a || y>a || z>a) ? kFALSE : kTRUE;
}

inline Bool_t CbmGeoVector::operator > (const Double_t a) {
  return (x<=a || y<=a || z<=a) ? kFALSE : kTRUE;
}

inline Bool_t CbmGeoVector::operator >= (const Double_t a) {
  return (x<a || y<a || z<a) ? kFALSE : kTRUE;
}

inline CbmGeoVector& CbmGeoVector::operator += (const Double_t a) {
  x+=a;
  y+=a;
  z+=a;
  return *this;
}

inline CbmGeoVector& CbmGeoVector::operator -= (const Double_t a) {
  x-=a;
  y-=a;
  z-=a;
  return *this;
}

inline CbmGeoVector& CbmGeoVector::operator *= (const Double_t a) {
  x*=a;
  y*=a;
  z*=a;
  return *this;
}

inline CbmGeoVector& CbmGeoVector::operator /= (const Double_t a) {
  x/=a;
  y/=a;
  z/=a;
  return *this;
}

inline CbmGeoVector& CbmGeoVector::operator += (const CbmGeoVector& v) {
  x+=v.getX();
  y+=v.getY();
  z+=v.getZ();
  return *this;
}

inline CbmGeoVector& CbmGeoVector::operator -= (const CbmGeoVector& v) {
  x-=v.getX();
  y-=v.getY();
  z-=v.getZ();
  return *this;
}

inline CbmGeoVector CbmGeoVector::operator + (const CbmGeoVector& v) const {
  CbmGeoVector p(*this);
  return p+=v;
}

inline CbmGeoVector CbmGeoVector::operator - (const CbmGeoVector& v) const {
  CbmGeoVector p(*this);
  return p-=v;
}

inline CbmGeoVector& CbmGeoVector::abs() {
  x=TMath::Abs(x);
  y=TMath::Abs(y);
  z=TMath::Abs(z);
  return *this;
}

inline Double_t CbmGeoVector::scalarProduct(const CbmGeoVector& v) const {
  return (x*v.getX()+y*v.getY()+z*v.getZ());
}

inline CbmGeoVector CbmGeoVector::vectorProduct(const CbmGeoVector& v) const {
  CbmGeoVector p(y*v.getZ()-z*v.getY(),z*v.getX()-x*v.getZ(),
                x*v.getY()-y*v.getX());
  return p;
}

inline void CbmGeoVector::round(Double_t d,Int_t n) {
  // rounds d to a precision with n digits
    if(d>0) d=floor(d*pow(10.,n)+0.5)/pow(10.,n);
  else d=-floor((-d)*pow(10.,n)+0.5)/pow(10.,n);
}

inline void CbmGeoVector::round(Int_t n) {
  // rounds every component to a precision with n digits
  round(x,n);
  round(y,n);
  round(z,n);
}

inline ostream& operator << (ostream& put,const CbmGeoVector& v) {
  return put<<v(0)<<"  "<<v(1)<<"  "<<v(2)<<'\n';
}

inline istream& operator >> (istream& get,CbmGeoVector& v) {
  Double_t x[3];
  get>>x[0]>>x[1]>>x[2];
  v.setVector(x);
  return get;
}

#endif /* !CBMGEOVECTOR_H */













