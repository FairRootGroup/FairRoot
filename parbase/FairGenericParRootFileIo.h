/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARROOTFILEIO_H
#define FAIRGENERICPARROOTFILEIO_H

#include <Rtypes.h>                // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>            // for Bool_t

#include "FairDetParRootFileIo.h"  // for FairDetParRootFileIo

class FairParRootFile;
class FairParSet;
class TBuffer;
class TClass;
class TMemberInspector;

class FairGenericParRootFileIo : public FairDetParRootFileIo
{
  public:
    FairGenericParRootFileIo(FairParRootFile* f = 0);
    ~FairGenericParRootFileIo() {}
    Bool_t init(FairParSet*);
    ClassDef(FairGenericParRootFileIo,
             0)   // I/O from ROOT file for parameter containers derived from FairParGenericSet
};

#endif /* !FAIRGENERICPARROOTFILEIO_H */
