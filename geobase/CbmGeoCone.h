#ifndef CBMGEOCONE_H
#define CBMGEOCONE_H

#include "CbmGeoBasicShape.h"

class CbmGeoTransform;
class CbmGeoVolume;

/**
 * class for geometry shape CONE
 * @author ilse koenig 
 */
class CbmGeoCone : public CbmGeoBasicShape {
public:
  CbmGeoCone();
  ~CbmGeoCone();
  TArrayD* calcVoluParam(CbmGeoVolume*);
  void calcVoluPosition(CbmGeoVolume*,
          const CbmGeoTransform&,const CbmGeoTransform&);
  Int_t readPoints(fstream*,CbmGeoVolume*);   
  Bool_t writePoints(fstream*,CbmGeoVolume*);   
  void printPoints(CbmGeoVolume* volu);
  ClassDef(CbmGeoCone,0) // 
};

#endif  /* !CBMGEOCONE_H */
