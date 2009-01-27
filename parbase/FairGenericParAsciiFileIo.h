#ifndef CBMGENERICPARASCIIFILEIO_H
#define CBMGENERICPARASCIIFILEIO_H

#include "FairDetParAsciiFileIo.h"

#include <fstream>

class FairParGenericSet;

class FairGenericParAsciiFileIo : public FairDetParAsciiFileIo {
public:
  FairGenericParAsciiFileIo(fstream* f=0);
  ~FairGenericParAsciiFileIo() {}
  Bool_t init(FairParSet*);
  Int_t write(FairParSet*);
private:
  Bool_t readGenericSet(FairParGenericSet* pPar);
  template <class type> UChar_t* readArray(type,const char*,Int_t&);
  Int_t writeGenericSet(FairParGenericSet* pPar);
  ClassDef(FairGenericParAsciiFileIo,0) // I/O from Ascii file for parameter containers derived from FairParGenericSet
};

#endif  /* !CBMGENERICPARASCIIFILEIO_H */
