#ifndef CBMGEOPGON_H
#define CBMGEOPGON_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape PGON
 * @author Ilse koenig 
 */
class CbmGeoPgon : public CbmGeoBasicShape {
public:
  CbmGeoPgon();
  ~CbmGeoPgon();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoPgon,0) // 
};

#endif  /* !CBMGEOPGON_H */
