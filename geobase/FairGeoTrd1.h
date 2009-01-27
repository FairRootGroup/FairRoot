#ifndef CBMGEOTRD1_H
#define CBMGEOTRD1_H

#include "FairGeoBasicShape.h"
#include "FairGeoRotation.h"

class FairGeoTransform;
class FairGeoVolume;

class FairGeoTrd1 : public FairGeoBasicShape {
private:
  FairGeoRotation intrinsicRot;
public:
  FairGeoTrd1();
  ~FairGeoTrd1();
  TArrayD* calcVoluParam(FairGeoVolume*);
  void calcVoluPosition(FairGeoVolume*,
           const FairGeoTransform&,const FairGeoTransform&);
  ClassDef(FairGeoTrd1,0) // class for geometry shape TRD1
};

#endif  /* !CBMGEOTRD1_H */
