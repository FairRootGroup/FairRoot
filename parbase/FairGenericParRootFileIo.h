/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARROOTFILEIO_H
#define FAIRGENERICPARROOTFILEIO_H

#include "FairDetParRootFileIo.h"   // for FairDetParRootFileIo

#include <Rtypes.h>   // for ClassDef macro

class FairParRootFile;
class FairParSet;

class FairGenericParRootFileIo : public FairDetParRootFileIo
{
  public:
    FairGenericParRootFileIo(FairParRootFile* f = 0);
    ~FairGenericParRootFileIo() {}
    Bool_t init(FairParSet*) override;
    ClassDefOverride(FairGenericParRootFileIo,
                     0)   // I/O from ROOT file for parameter containers derived from FairParGenericSet
};

#endif /* !FAIRGENERICPARROOTFILEIO_H */
