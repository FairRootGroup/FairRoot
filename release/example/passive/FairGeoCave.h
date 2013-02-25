#ifndef PNDGEOCAVE_H
#define PNDGEOCAVE_H

#include "FairGeoSet.h"
#include "TString.h"
#include "FairGeoMedia.h"
#include <fstream>
class  FairGeoCave : public FairGeoSet
{
  protected:
    TString name;
  public:
    FairGeoCave();
    ~FairGeoCave() {}
    const char* getModuleName(Int_t) {return name.Data();}
    Bool_t read(fstream&,FairGeoMedia*);
    void addRefNodes();
    void write(fstream&);
    void print();
    ClassDef(FairGeoCave,0) // Class for the geometry of CAVE
};

#endif  /* !PNDGEOCAVE_H */
