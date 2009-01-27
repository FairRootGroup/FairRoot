#ifndef CBMGEOTUBS_H
#define CBMGEOTUBS_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

class FairGeoTubs : public FairGeoBasicShape {
public:
  FairGeoTubs();
  ~FairGeoTubs();
  TArrayD* calcVoluParam(FairGeoVolume*);
  void calcVoluPosition(FairGeoVolume*,
          const FairGeoTransform&,const FairGeoTransform&);
  Int_t readPoints(fstream*,FairGeoVolume*);   
  Bool_t writePoints(fstream*,FairGeoVolume*);   
  void printPoints(FairGeoVolume* volu);
  ClassDef(FairGeoTubs,0) // class for geometry shape TUBS
};

#endif  /* !CBMGEOTUBS_H */
