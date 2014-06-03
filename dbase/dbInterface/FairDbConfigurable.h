/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCONFIGURABLE_H
#define FAIRDBCONFIGURABLE_H

#ifndef REGISTRY_H
#include "FairRegistry.h"               // for FairRegistry
#endif

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for FairDbConfigurable::Class, etc
#endif
#endif


class FairDbConfigNotice;

class FairDbConfigurable
{

  public:

    FairDbConfigurable();
    virtual ~FairDbConfigurable();

    virtual void            Config() = 0;

    virtual const FairRegistry& DefaultConfig() const;
    FairRegistry&               GetConfig();
    const FairRegistry&         GetConfig() const;

    int  Update();
    void Set(FairDbConfigNotice* d=0);
    void Set(const char* s);

  protected:
    virtual void CommitDefaultConfig(const FairRegistry& r);

  private:
    FairRegistry fDefConfig, fConfig;


    ClassDef(FairDbConfigurable,1)
};

#endif // FAIRDBCONFIGURABLE_H
