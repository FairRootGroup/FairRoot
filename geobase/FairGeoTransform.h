#ifndef FAIRGEOTRANSFORM_H
#define FAIRGEOTRANSFORM_H

#include "FairGeoVector.h"
#include "FairGeoRotation.h"

/**
 * basic geometry transformation class
 * @author Ilse koenig*/
class FairGeoTransform : public TObject
{
  protected:
    FairGeoRotation rot;   /** rotation matrix, describing the orientation*/
    FairGeoVector trans;   /** translation vector, describing the position*/
    FairGeoVector trans_cm;   /** translation vector, describing the position in cm*/
  public:
    FairGeoTransform();
    inline FairGeoTransform(const FairGeoTransform& t);
    ~FairGeoTransform() {}
    FairGeoTransform& operator=(const FairGeoTransform& t);
    const FairGeoRotation& getRotMatrix() const { return rot; }
    const FairGeoVector& getTransVector() const { return trans; }
    void setRotMatrix(const FairGeoRotation& r) { rot=r; }
    void setRotMatrix(const Double_t* a) { rot.setMatrix(a); }
    void setRotMatrix(const Float_t* a) { rot.setMatrix(a); }
    void setTransVector(const FairGeoVector& t) { trans=t; }
    void setTransVector(const Double_t* a) { trans.setVector(a); }
    void setTransVector(const Float_t* a) { trans.setVector(a); }
    FairGeoVector transFrom(const FairGeoVector& p) const;
    FairGeoVector transTo(const FairGeoVector& p) const;
    void transFrom(const FairGeoTransform&);
    void transTo(const FairGeoTransform&);
    void invert(void);
    void clear();
    void print();
    const FairGeoVector& getTranslation()   {
      const double fac = 10.;
      trans_cm=trans;
      return (trans_cm/=fac);
    }

    const FairGeoRotation& getRotation() const { return rot; }

    inline void setTransform(const FairGeoTransform& t);
    ClassDef(FairGeoTransform,1) //
};

inline FairGeoTransform::FairGeoTransform(const FairGeoTransform& t)
  : rot(t.getRotMatrix()),
    trans(t.getTransVector()),
    trans_cm(FairGeoVector(0,0,0))
{

}


inline void FairGeoTransform::setTransform(const FairGeoTransform& t)
{
  rot=t.getRotMatrix();
  trans=t.getTransVector();
}

#endif /* !FAIRGEOTRANSFORM_H */
