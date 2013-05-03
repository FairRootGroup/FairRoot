#ifndef FAIRGEOBRIK_H
#define FAIRGEOBRIK_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Rtypes.h"                     // for FairGeoBrik::Class, etc


class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

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
