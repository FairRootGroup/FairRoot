#ifndef CBMGENERICPARASCIIFILEIO_H
#define CBMGENERICPARASCIIFILEIO_H

#include "CbmDetParAsciiFileIo.h"

#include <fstream>

class CbmParGenericSet;

class CbmGenericParAsciiFileIo : public CbmDetParAsciiFileIo {
public:
  CbmGenericParAsciiFileIo(fstream* f=0);
  ~CbmGenericParAsciiFileIo() {}
  Bool_t init(CbmParSet*);
  Int_t write(CbmParSet*);
private:
  Bool_t readGenericSet(CbmParGenericSet* pPar);
  template <class type> UChar_t* readArray(type,const char*,Int_t&);
  Int_t writeGenericSet(CbmParGenericSet* pPar);
  ClassDef(CbmGenericParAsciiFileIo,0) // I/O from Ascii file for parameter containers derived from CbmParGenericSet
};

#endif  /* !CBMGENERICPARASCIIFILEIO_H */
