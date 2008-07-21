#ifndef CBMGEOTORUS_H
#define CBMGEOTORUS_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

class CbmGeoTorus : public CbmGeoBasicShape {
public:
  CbmGeoTorus();
  ~CbmGeoTorus();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
           const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream* pFile,CbmGeoVolume* volu);
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);

  ClassDef(CbmGeoTorus,0) // class for geometry shape TORUS
};

#endif  /* !CBMGEOTORUS_H */
