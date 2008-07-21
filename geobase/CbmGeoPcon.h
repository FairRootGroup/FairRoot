#ifndef CBMGEOPCON_H
#define CBMGEOPCON_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape PCON
 * @author Ilse koenig 
 */
class CbmGeoPcon : public CbmGeoBasicShape {
public:
  CbmGeoPcon();
  ~CbmGeoPcon();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoPcon,0) //
};

#endif  /* !CBMGEOPCON_H */
