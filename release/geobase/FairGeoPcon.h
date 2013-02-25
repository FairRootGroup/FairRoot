#ifndef FAIRGEOPCON_H
#define FAIRGEOPCON_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

/**
 * class for geometry shape PCON
 * @author Ilse koenig
 */
class FairGeoPcon : public FairGeoBasicShape
{
  public:
    FairGeoPcon();
    ~FairGeoPcon();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(fstream*,FairGeoVolume*);
    Bool_t writePoints(fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoPcon,0) //
};

#endif  /* !FAIRGEOPCON_H */
