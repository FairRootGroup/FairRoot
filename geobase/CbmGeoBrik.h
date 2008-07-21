#ifndef CBMGEOBRIK_H
#define CBMGEOBRIK_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoBrik : public CbmGeoBasicShape {
public:
  CbmGeoBrik();
  ~CbmGeoBrik();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  ClassDef(CbmGeoBrik,0) // class for geometry shape BOX or BRIK
};

#endif  /* !CBMGEOBRIK_H */
