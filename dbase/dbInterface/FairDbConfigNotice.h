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

