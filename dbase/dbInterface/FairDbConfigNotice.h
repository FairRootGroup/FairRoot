/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRCONFIGNOTICE_H
#define FAIRCONFIGNOTICE_H

#ifndef REGISTRY_H
#include "FairRegistry.h"
#endif

class FairDbConfigNotice
{
  public:
    FairDbConfigNotice();
    FairDbConfigNotice(const FairRegistry& current, const FairRegistry& deflt);
    virtual ~FairDbConfigNotice();

    virtual FairRegistry& Query();

    void SetCurrent(const FairRegistry& r);
    void SetDefault(const FairRegistry& r);

  protected:
    FairRegistry fCurrent;
    FairRegistry fDefault;
    FairRegistry fResult;
};


#endif

