#ifndef CBMGEOTUBE_H
#define CBMGEOTUBE_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoTube : public CbmGeoBasicShape {
public:
  CbmGeoTube();
  ~CbmGeoTube();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoTube,0) // class for geometry shape TUBE
};

#endif  /* !CBMGEOTUBE_H */
