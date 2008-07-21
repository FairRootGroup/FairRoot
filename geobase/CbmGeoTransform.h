#ifndef CBMGEOTRANSFORM_H
#define CBMGEOTRANSFORM_H

#include "CbmGeoVector.h"
#include "CbmGeoRotation.h"

/**
 * basic geometry transformation class
 * @author Ilse koenig*/
class CbmGeoTransform : public TObject {
protected:
  CbmGeoRotation rot;   /** rotation matrix, describing the orientation*/
  CbmGeoVector trans;   /** translation vector, describing the position*/
  CbmGeoVector trans_cm;   /** translation vector, describing the position in cm*/
public:
  CbmGeoTransform();
  inline CbmGeoTransform(const CbmGeoTransform& t);
  ~CbmGeoTransform() {}
  CbmGeoTransform& operator=(const CbmGeoTransform& t);
  const CbmGeoRotation& getRotMatrix() const { return rot; }
  const CbmGeoVector& getTransVector() const { return trans; } 
  void setRotMatrix(const CbmGeoRotation& r) { rot=r; }
  void setRotMatrix(const Double_t* a) { rot.setMatrix(a); }
  void setRotMatrix(const Float_t* a) { rot.setMatrix(a); }
  void setTransVector(const CbmGeoVector& t) { trans=t; }
  void setTransVector(const Double_t* a) { trans.setVector(a); }
  void setTransVector(const Float_t* a) { trans.setVector(a); }
  CbmGeoVector transFrom(const CbmGeoVector& p) const;
  CbmGeoVector transTo(const CbmGeoVector& p) const;
  void transFrom(const CbmGeoTransform&);
  void transTo(const CbmGeoTransform&);
  void invert(void);
  void clear();
  void print();
  const CbmGeoVector& getTranslation()   {
      const double fac = 10.;
      trans_cm=trans;
      return (trans_cm/=fac);}
      
  const CbmGeoRotation& getRotation() const { return rot; }

  inline void setTransform(const CbmGeoTransform& t);
  ClassDef(CbmGeoTransform,1) //
};

inline CbmGeoTransform::CbmGeoTransform(const CbmGeoTransform& t) 
: rot(t.getRotMatrix()),
  trans(t.getTransVector()),
  trans_cm(CbmGeoVector(0,0,0)) 
{
  
}


inline void CbmGeoTransform::setTransform(const CbmGeoTransform& t) 
{
  rot=t.getRotMatrix();
  trans=t.getTransVector();
}

#endif /* !CBMGEOTRANSFORM_H */
