#ifndef CBMGEOTUBS_H
#define CBMGEOTUBS_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoTubs : public CbmGeoBasicShape {
public:
  CbmGeoTubs();
  ~CbmGeoTubs();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoTubs,0) // class for geometry shape TUBS
};

#endif  /* !CBMGEOTUBS_H */
