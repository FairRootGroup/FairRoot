#ifndef CBMGEOCONS_H
#define CBMGEOCONS_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

/**
 * class for geometry shape CONS
 * @author ilse koenig 
 */
class FairGeoCons : public FairGeoBasicShape {
public:
  FairGeoCons();
  ~FairGeoCons();
  TArrayD* calcVoluParam(FairGeoVolume*);
  void calcVoluPosition(FairGeoVolume*,
          const FairGeoTransform&,const FairGeoTransform&);
  Int_t readPoints(fstream*,FairGeoVolume*);   
  Bool_t writePoints(fstream*,FairGeoVolume*);   
  void printPoints(FairGeoVolume* volu);
  ClassDef(FairGeoCons,0) // 
};

#endif  /* !CBMGEOCONS_H */
