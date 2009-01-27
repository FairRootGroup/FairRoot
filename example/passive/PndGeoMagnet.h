#ifndef PNDGEOMAGNET_H
#define PNDGEOMAGNET_H

#include "CbmGeoSet.h"
#include "TString.h"

class  PndGeoMagnet : public CbmGeoSet {
protected:
  char modName[2];  // name of module
  char eleName[2];  // substring for elements in module
public:
  PndGeoMagnet();
  ~PndGeoMagnet() {}
  const char* getModuleName(Int_t) {return modName;}
  const char* getEleName(Int_t) {return eleName;}
  ClassDef(PndGeoMagnet,0) // Class for the geometry of Magnet
};

#endif  /* !CBMGEOMAGNET_H */
