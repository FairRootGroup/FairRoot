#ifndef PNDGEOMAGNET_H
#define PNDGEOMAGNET_H

#include "FairGeoSet.h"
#include "TString.h"

class  FairGeoMagnet : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoMagnet();
    ~FairGeoMagnet() {}
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    ClassDef(FairGeoMagnet,0) // Class for the geometry of Magnet
};

#endif  /* !FAIRGEOMAGNET_H */
