#ifndef CBMGEOTRD1_H
#define CBMGEOTRD1_H

#include "CbmGeoBasicShape.h"
#include "CbmGeoRotation.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoTrd1 : public CbmGeoBasicShape {
private:
  CbmGeoRotation intrinsicRot;
public:
  CbmGeoTrd1();
  ~CbmGeoTrd1();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
           const CbmGeoTransform&,const CbmGeoTransform&);
  ClassDef(CbmGeoTrd1,0) // class for geometry shape TRD1
};

#endif  /* !CBMGEOTRD1_H */
