#ifndef CBMGEOVOLUME_H
#define CBMGEOVOLUME_H

#include "CbmGeoTransform.h"
#include "CbmGeoMedium.h"
#include "TNamed.h"
#include "TObjArray.h"

class CbmGeoVector;

/**
 * basic geometry parameters of a volume
 * @author Ilse koenig 
 */
class CbmGeoVolume : public TNamed {
private:
  CbmGeoVolume& operator= (const  CbmGeoVolume&) {return *this;}
protected:
  TString shape;              /**eant shape of the volume*/
  TString mother;            /** Name of the mother volume*/
  TObjArray* points;        /** array of points (type CbmGeoVector)*/
  CbmGeoTransform transform; /** transformation relative to the mother system */
  CbmGeoTransform fLabTransform; /** transformation to the LAB system; */
  CbmGeoMedium   fMedium;    /** medium properties */
  Int_t nPoints;             /** number of points */
  Int_t fHadFormat; //
  Int_t fgMCid;			/** Volume Id given by MC*/

public:
  inline CbmGeoVolume();
  CbmGeoVolume(CbmGeoVolume&);
  virtual ~CbmGeoVolume();
  const TString& getName() const { return fName; }
  const TString& getShape() const { return shape; }
  const TString& getMother() const { return mother; }
  CbmGeoTransform& getTransform() { return transform; }
  CbmGeoTransform& getLabTransform() { return fLabTransform;}
  CbmGeoMedium&    getMedium() { return fMedium;}
  Int_t getNumPoints() { return nPoints;}
  inline CbmGeoVector* getPoint(const Int_t n);
  inline void setName(const Text_t* s);
  void setVolumePar(CbmGeoVolume&);
  inline void setShape(const Text_t* s);
  inline void setMother(const Text_t* s);
  void createPoints(const Int_t);
  void setPoint(const Int_t,const Double_t,const Double_t,const Double_t);
  void setPoint(const Int_t,const CbmGeoVector&);
  virtual void clear();
  virtual void print();
  virtual void setHadFormat( Int_t i ) { fHadFormat=i;}
  Double_t getVolParameter( Int_t nPoint, Int_t pos );
  Int_t getMCid(){return fgMCid;}
  void setMCid(Int_t MCid){fgMCid=MCid;}

  ClassDef(CbmGeoVolume,1) // 
};

// -------------------- inlines --------------------------

inline CbmGeoVolume::CbmGeoVolume() 
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
}


inline CbmGeoVector* CbmGeoVolume::getPoint(const Int_t n) {
   if (points && n<nPoints) return (CbmGeoVector*)points->At(n);
   else return 0;
}

inline void CbmGeoVolume::setName(const Text_t* s) {
  fName=s;
  fName.ToUpper();
}

inline void CbmGeoVolume::setShape(const Text_t* s) {
  shape=s;
  shape.ToUpper();
}

inline void CbmGeoVolume::setMother(const Text_t* s) {
  mother=s;
  mother.ToUpper();
}

#endif /* !CBMGEOVOLUME_H */
