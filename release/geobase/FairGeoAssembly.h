#ifndef FAIRGEOASSEMBLY_H
#define FAIRGEOASSEMBLY_H

#include "FairGeoBasicShape.h"

class FairGeoTransform;
class FairGeoVolume;

class FairGeoAssembly : public FairGeoBasicShape
{
  public:
    FairGeoAssembly();
    ~FairGeoAssembly();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(fstream* pFile,FairGeoVolume* volu);
    Bool_t writePoints(fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);

    ClassDef(FairGeoAssembly,0) // class for geometry shape ASSEMBLY
};

#endif  /* !FAIRGEOASSEMBLY_H */


