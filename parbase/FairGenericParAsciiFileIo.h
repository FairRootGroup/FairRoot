#ifndef FAIRGENERICPARASCIIFILEIO_H
#define FAIRGENERICPARASCIIFILEIO_H

#include "FairDetParAsciiFileIo.h"

#include <fstream>

class FairParGenericSet;

class FairGenericParAsciiFileIo : public FairDetParAsciiFileIo
{
  public:
    FairGenericParAsciiFileIo(fstream* f=0);
    ~FairGenericParAsciiFileIo() {}
    Bool_t init(FairParSet*);
    Int_t write(FairParSet*);
  private:

    ClassDef(FairGenericParAsciiFileIo,0) // I/O from Ascii file for parameter containers derived from FairParGenericSet
    Bool_t readGenericSet(FairParGenericSet* pPar);
    Int_t writeGenericSet(FairParGenericSet* pPar);

    template <class type> const UChar_t* readData(type,const Char_t*,TString&,Int_t&);
    template <class type> void writeData(type*,Int_t);
};

#endif  /* !FAIRGENERICPARASCIIFILEIO_H */
