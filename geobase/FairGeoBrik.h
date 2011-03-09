#ifndef FAIRGEOBRIK_H
#define FAIRGEOBRIK_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

class FairGeoBrik : public FairGeoBasicShape
{
  public:
    FairGeoBrik();
    ~FairGeoBrik();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    ClassDef(FairGeoBrik,0) // class for geometry shape BOX or BRIK
};

#endif  /* !FAIRGEOBRIK_H */
