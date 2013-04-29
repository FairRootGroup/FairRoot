#ifndef PNDGEOTARGET_H
#define PNDGEOTARGET_H

#include "FairGeoSet.h"

class  FairGeoTarget : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoTarget();
    ~FairGeoTarget() {}
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    ClassDef(FairGeoTarget,0) // Class for geometry of Target
};

#endif  /* !PNDGEOTARGET_H */
