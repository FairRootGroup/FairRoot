#ifndef CBMGEOELTU_H
#define CBMGEOELTU_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape ELTU
 * @author Ilse  koenig 
 */
class CbmGeoEltu : public CbmGeoBasicShape {
public:
  CbmGeoEltu();
  ~CbmGeoEltu();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoEltu,0) //
};

#endif  /* !CBMGEOELTU_H */
