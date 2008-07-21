#ifndef CBMGEOCONS_H
#define CBMGEOCONS_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape CONS
 * @author ilse koenig 
 */
class CbmGeoCons : public CbmGeoBasicShape {
public:
  CbmGeoCons();
  ~CbmGeoCons();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoCons,0) // 
};

#endif  /* !CBMGEOCONS_H */
