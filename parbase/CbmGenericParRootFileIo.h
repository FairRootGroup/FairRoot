#ifndef CBMGENERICPARROOTFILEIO_H
#define CBMGENERICPARROOTFILEIO_H

#include "CbmDetParRootFileIo.h"

class CbmParRootFile;

class CbmGenericParRootFileIo : public CbmDetParRootFileIo {
public:
  CbmGenericParRootFileIo(CbmParRootFile* f=0);
  ~CbmGenericParRootFileIo() {}
  Bool_t init(CbmParSet*);
  ClassDef(CbmGenericParRootFileIo,0) // I/O from ROOT file for parameter containers derived from CbmParGenericSet
};

#endif  /* !CBMGENERICPARROOTFILEIO_H */
