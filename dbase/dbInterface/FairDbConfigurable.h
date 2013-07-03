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


class FairDbConfDialog;

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
    void Set(FairDbConfDialog* d=0);
    void Set(const char* s);

  protected:
    virtual void CommitDefaultConfig(const FairRegistry& r);

  private:
    FairRegistry fDefConfig, fConfig;


    ClassDef(FairDbConfigurable,1)
};

#endif // FAIRDBCONFIGURABLE_H
