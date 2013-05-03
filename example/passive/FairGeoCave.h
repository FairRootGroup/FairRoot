#ifndef PNDGEOCAVE_H
#define PNDGEOCAVE_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoCave::Class, Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoMedia;

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
