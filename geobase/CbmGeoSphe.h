#ifndef CBMGEOSPHE_H
#define CBMGEOSPHE_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape SPHE
 * @author Ilse koenig 
 */
class CbmGeoSphe : public CbmGeoBasicShape {
public:
  CbmGeoSphe();
  ~CbmGeoSphe();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoSphe,0) //
};

#endif  /* !CBMGEOSPHE_H */
