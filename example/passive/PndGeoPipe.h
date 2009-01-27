#ifndef PNDGEOPIPE_H
#define PNDGEOPIPE_H

#include "CbmGeoSet.h"

class  PndGeoPipe : public CbmGeoSet {
protected:
  char modName[2];  // name of module
  char eleName[2];  // substring for elements in module
public:
  PndGeoPipe();
  virtual ~PndGeoPipe();
  const char* getModuleName(Int_t) {return modName;}
  const char* getEleName(Int_t) {return eleName;}
  Bool_t create(CbmGeoBuilder*);
  ClassDef(PndGeoPipe,0) // Class for geometry of beam pipe
};

#endif  /* !PNDGEOPIPE_H */
