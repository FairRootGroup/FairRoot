#ifndef FAIRGENERICPARROOTFILEIO_H
#define FAIRGENERICPARROOTFILEIO_H

#include "FairDetParRootFileIo.h"

class FairParRootFile;

class FairGenericParRootFileIo : public FairDetParRootFileIo
{
  public:
    FairGenericParRootFileIo(FairParRootFile* f=0);
    ~FairGenericParRootFileIo() {}
    Bool_t init(FairParSet*);
    ClassDef(FairGenericParRootFileIo,0) // I/O from ROOT file for parameter containers derived from FairParGenericSet
};

#endif  /* !FAIRGENERICPARROOTFILEIO_H */
