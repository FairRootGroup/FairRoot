#ifndef FAIRGEOPGON_H
#define FAIRGEOPGON_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

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
