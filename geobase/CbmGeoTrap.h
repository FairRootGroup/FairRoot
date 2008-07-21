#ifndef CBMGEOTRAP_H
#define CBMGEOTRAP_H

#include "CbmGeoBasicShape.h"
#include "CbmGeoRotation.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoTrap : public CbmGeoBasicShape {
private:
  CbmGeoRotation intrinsicRot;
public:
  CbmGeoTrap();
  ~CbmGeoTrap();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
            const CbmGeoTransform&,const CbmGeoTransform&);
  ClassDef(CbmGeoTrap,0) // class for geometry shape TRAP
};

#endif  /* !CBMGEOTRAP_H */
