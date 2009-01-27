#ifndef PNDGEOCAVE_H
#define PNDGEOCAVE_H

#include "CbmGeoSet.h"
#include "TString.h"
#include "CbmGeoMedia.h"
#include <fstream>
class  PndGeoCave : public CbmGeoSet {
protected:
  TString name;
public:
  PndGeoCave();
  ~PndGeoCave() {}
  const char* getModuleName(Int_t) {return name.Data();}  
  Bool_t read(fstream&,CbmGeoMedia*);
  void addRefNodes();
  void write(fstream&);
  void print();
  ClassDef(PndGeoCave,0) // Class for the geometry of CAVE
};

#endif  /* !PNDGEOCAVE_H */
