#ifndef FAIRGEOPGON_H
#define FAIRGEOPGON_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

/**
 * class for geometry shape PGON
 * @author Ilse koenig
 */
class FairGeoPgon : public FairGeoBasicShape
{
  public:
    FairGeoPgon();
    ~FairGeoPgon();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(fstream*,FairGeoVolume*);
    Bool_t writePoints(fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoPgon,0) //
};

#endif  /* !FAIRGEOPGON_H */
