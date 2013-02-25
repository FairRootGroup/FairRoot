#ifndef FAIRGEOELTU_H
#define FAIRGEOELTU_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

/**
 * class for geometry shape ELTU
 * @author Ilse  koenig
 */
class FairGeoEltu : public FairGeoBasicShape
{
  public:
    FairGeoEltu();
    ~FairGeoEltu();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(fstream*,FairGeoVolume*);
    Bool_t writePoints(fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoEltu,0) //
};

#endif  /* !FAIRGEOELTU_H */
