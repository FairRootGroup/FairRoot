#ifndef PNDGEOPIPE_H
#define PNDGEOPIPE_H

#include "FairGeoSet.h"

class  FairGeoPipe : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoPipe();
    virtual ~FairGeoPipe();
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    Bool_t create(FairGeoBuilder*);
    ClassDef(FairGeoPipe,0) // Class for geometry of beam pipe
};

#endif  /* !PNDGEOPIPE_H */
