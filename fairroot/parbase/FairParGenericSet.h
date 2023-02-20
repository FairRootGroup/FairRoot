/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARGENERICSET_H
#define FAIRPARGENERICSET_H

#include "FairParSet.h"   // for FairParSet

#include <Rtypes.h>   // for Bool_t, etc

class FairParIo;
class FairParamList;

class FairParGenericSet : public FairParSet
{
  public:
    FairParGenericSet(const char* name, const char* title, const char* context, Bool_t ownership = kFALSE)
        : FairParSet(name, title, context, ownership)
    {}
    virtual ~FairParGenericSet() {}
    virtual void putParams(FairParamList*) = 0;
    virtual Bool_t getParams(FairParamList*) = 0;
    virtual void printParams();

    Bool_t init(FairParIo* inp) override;
    Int_t write(FairParIo* output) override;

  protected:
    FairParGenericSet()
        : FairParSet()
    {}
    ClassDefOverride(FairParGenericSet, 1);   // Base class for generic-style parameter containers
};

#endif /* !FAIRPARGENERICSET_H */
