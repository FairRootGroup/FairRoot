#ifndef PNDGEOTARGET_H
#define PNDGEOTARGET_H

#include "CbmGeoSet.h"

class  PndGeoTarget : public CbmGeoSet {
protected:
  char modName[2];  // name of module
  char eleName[2];  // substring for elements in module
public:
  PndGeoTarget();
  ~PndGeoTarget() {}
  const char* getModuleName(Int_t) {return modName;}
  const char* getEleName(Int_t) {return eleName;}
  ClassDef(PndGeoTarget,0) // Class for geometry of Target
};

#endif  /* !PNDGEOTARGET_H */
