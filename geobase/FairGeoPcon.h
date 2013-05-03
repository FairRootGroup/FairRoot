#ifndef FAIRGEOPCON_H
#define FAIRGEOPCON_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

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
