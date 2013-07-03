#ifndef FAIRCONFDIALOG_H
#define FAIRCONFDIALOG_H

#ifndef REGISTRY_H
#include "FairRegistry.h"
#endif

class FairDbConfDialog
{
  public:
    FairDbConfDialog();
    FairDbConfDialog(const FairRegistry& current, const FairRegistry& deflt);
    virtual ~FairDbConfDialog();

    virtual FairRegistry& Query();

    void SetCurrent(const FairRegistry& r);
    void SetDefault(const FairRegistry& r);

  protected:
    FairRegistry fCurrent;
    FairRegistry fDefault;
    FairRegistry fResult;
};


#endif

