#ifndef FAIRGEOTORUS_H
#define FAIRGEOTORUS_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

class FairGeoTorus : public FairGeoBasicShape
{
  public:
    FairGeoTorus();
    ~FairGeoTorus();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(fstream* pFile,FairGeoVolume* volu);
    Bool_t writePoints(fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);

    ClassDef(FairGeoTorus,0) // class for geometry shape TORUS
};

#endif  /* !FAIRGEOTORUS_H */
