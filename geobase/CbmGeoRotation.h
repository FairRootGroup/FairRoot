#ifndef CBMGEOROTATION_H
#define CBMGEOROTATION_H

#include "TObject.h"

#include "CbmGeoVector.h"

#include "TRotMatrix.h"

#include <iostream>


/**
 * rotation matrix
 * @author Ilse koenig 
 */
class CbmGeoRotation : public TObject {
protected:
  Double_t rot[9];
public:
  inline CbmGeoRotation();
  inline CbmGeoRotation(const CbmGeoRotation&);
  inline CbmGeoRotation(const Double_t*);
  CbmGeoRotation(const Double_t,const Double_t,const Double_t);
  ~CbmGeoRotation() {}
  inline void setMatrix(const Double_t*);
  inline void setMatrix(const Float_t*);
  void setEulerAngles(const Double_t,const Double_t,const Double_t);
  inline void setElement(const Double_t,const Int_t);
  inline Double_t operator () (Int_t) const;
  inline CbmGeoRotation& operator = (const CbmGeoRotation&);
  inline Bool_t operator == (const CbmGeoRotation&);
  inline Bool_t operator != (const CbmGeoRotation&);
  inline CbmGeoVector operator * (const CbmGeoVector&) const;
  inline CbmGeoRotation operator * (const CbmGeoRotation&) const;
  inline CbmGeoRotation& operator *= (const CbmGeoRotation&);
  inline CbmGeoRotation& transform(const CbmGeoRotation&);
  inline Bool_t isUnitMatrix();
  inline CbmGeoRotation inverse() const;
  inline CbmGeoRotation& invert();
  inline Double_t determinant() const;
  Double_t diff2(const CbmGeoRotation&) const;
  inline Double_t getElement(Int_t i,Int_t j) const;
  inline void setUnitMatrix();
  inline void setZero();
  inline void print() const;
  TRotMatrix* createTRotMatrix(Text_t* name="",Text_t* title="");

  ClassDef(CbmGeoRotation,1) // 
};

// -------------------- inlines ---------------------------

inline CbmGeoRotation::CbmGeoRotation() {
  rot[0]=rot[4]=rot[8]=1.;
  rot[1]=rot[2]=rot[3]=rot[5]=rot[6]=rot[7]=0.;
}

inline Double_t CbmGeoRotation::operator () (Int_t i) const {
  if (i>=0 && i<9) return rot[i];
  Error("operator()","bad index");
  return 0;
}

inline CbmGeoRotation::CbmGeoRotation(const CbmGeoRotation& r) {
  for(Int_t i=0;i<9;i++) rot[i]=r(i);
}

inline CbmGeoRotation::CbmGeoRotation(const Double_t* a) {
  for(Int_t i=0;i<9;i++) rot[i]=a[i];
}
  
inline void CbmGeoRotation::setMatrix(const Double_t* a) {
  for(Int_t i=0;i<9;i++) rot[i]=a[i];
}
  
inline void CbmGeoRotation::setMatrix(const Float_t* a) {
  for(Int_t i=0;i<9;i++) rot[i]=a[i];
}
  
inline void CbmGeoRotation::setElement(const Double_t a, const Int_t i) {
  if (i<9) rot[i]=a;
}

inline Double_t CbmGeoRotation::getElement(Int_t i,Int_t j) const {
  return rot[i*3+j];
}

inline CbmGeoRotation& CbmGeoRotation::operator = (const CbmGeoRotation& r) {
  for(Int_t i=0;i<9;i++) rot[i]=r(i);
  return *this;
}

inline Bool_t CbmGeoRotation::operator == (const CbmGeoRotation& r) {
  Int_t i=0;
  while (i<9) {
    if (rot[i]!=r(i)) return kFALSE;
    i++;
  }
  return kTRUE;
}

inline Bool_t CbmGeoRotation::operator != (const CbmGeoRotation& r) {
  Int_t i=0;
  while (i<9) {
    if (rot[i]!=r(i)) return kTRUE;
    i++;
  }
  return kFALSE;
}
 
inline CbmGeoVector CbmGeoRotation::operator * (const CbmGeoVector& v) const {
  return CbmGeoVector(rot[0]*v(0)+rot[1]*v(1)+rot[2]*v(2),
                     rot[3]*v(0)+rot[4]*v(1)+rot[5]*v(2),
                     rot[6]*v(0)+rot[7]*v(1)+rot[8]*v(2));
}

inline CbmGeoRotation CbmGeoRotation::operator * (const CbmGeoRotation& r) const {
  Double_t a[9];
  for(Int_t kk=0;kk<9;kk++) a[kk]=0;
  for(Int_t i=0;i<3;i++) {
    for(Int_t j=0;j<3;j++) {
      Int_t n=3*i+j;
      for(Int_t k=0;k<3;k++) a[n]+=rot[3*i+k]*r(3*k+j);
    }
  }
  return CbmGeoRotation(&a[0]);
}

inline CbmGeoRotation& CbmGeoRotation::operator *= (const CbmGeoRotation& r) {
  return *this=operator * (r);  
}

inline   CbmGeoRotation& CbmGeoRotation::transform(const CbmGeoRotation& r) {
  return *this=r*(*this);
}

inline Bool_t CbmGeoRotation::isUnitMatrix() {
  return (rot[0]==1. && rot[1]==0. && rot[2]==0. &&
          rot[3]==0. && rot[4]==1. && rot[5]==0. &&
          rot[6]==0. && rot[7]==0. && rot[8]==1.)  ? kTRUE : kFALSE;
}

inline CbmGeoRotation CbmGeoRotation::inverse() const {
  Double_t a[9];
  for(Int_t i=0;i<3;i++) {
    for(Int_t j=0;j<3;j++) a[j+3*i]=rot[i+3*j];
  }
  return CbmGeoRotation(a); 
}

inline CbmGeoRotation& CbmGeoRotation::invert() {
  return *this=inverse();
}

inline Double_t CbmGeoRotation::determinant() const {
  return rot[0]*(rot[4]*rot[8]-rot[7]*rot[5])
        -rot[3]*(rot[1]*rot[8]-rot[7]*rot[2])
        +rot[6]*(rot[1]*rot[5]-rot[4]*rot[2]);
}

inline void CbmGeoRotation::setUnitMatrix(){
  rot[0]=rot[4]=rot[8]=1.;
  rot[1]=rot[2]=rot[3]=rot[5]=rot[6]=rot[7]=0.;
}

inline void CbmGeoRotation::setZero(){
  for(Int_t i=0;i<9;i++) rot[i]=0.;
}

inline void CbmGeoRotation::print() const {
  for(Int_t i=0;i<9;i++) std::cout<<rot[i]<<"  ";
  std::cout<<'\n';
}

#endif /* !CBMGEOROTATION_H */
