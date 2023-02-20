/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARASCIIFILEIO_H
#define FAIRGENERICPARASCIIFILEIO_H

#include "FairDetParAsciiFileIo.h"   // for FairDetParAsciiFileIo

#include <Rtypes.h>   // for Int_t, Bool_t, etc
#include <iosfwd>     // for fstream

class FairParGenericSet;
class FairParSet;
class TString;

class FairGenericParAsciiFileIo : public FairDetParAsciiFileIo
{
  public:
    FairGenericParAsciiFileIo(std::fstream* f = 0);
    ~FairGenericParAsciiFileIo() {}
    Bool_t init(FairParSet*) override;
    Int_t write(FairParSet*) override;

  private:
    ClassDefOverride(FairGenericParAsciiFileIo,
                     0)   // I/O from Ascii file for parameter containers derived from FairParGenericSet
        Bool_t readGenericSet(FairParGenericSet* pPar);
    Int_t writeGenericSet(FairParGenericSet* pPar);

    template<class type>
    const UChar_t* readData(type, const Char_t*, TString&, Int_t&);
    template<class type>
    void writeData(type*, Int_t);
};

#endif /* !FAIRGENERICPARASCIIFILEIO_H */
