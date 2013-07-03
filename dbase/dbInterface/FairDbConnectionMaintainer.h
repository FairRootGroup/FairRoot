#ifndef FAIRDBCONNECTIONMAINTAINER
#define FAIRDBCONNECTIONMAINTAINER

#include "Rtypes.h"                // for ClassDef

class FairDbMultConnector;

class FairDbConnectionMaintainer
{

  public:

    FairDbConnectionMaintainer(FairDbMultConnector* cascader = 0);
    virtual ~FairDbConnectionMaintainer();

  private:

    FairDbMultConnector* fCascader;

    FairDbConnectionMaintainer(const FairDbConnectionMaintainer&);
    FairDbConnectionMaintainer operator=(const FairDbConnectionMaintainer&);

    ClassDef(FairDbConnectionMaintainer,0) // Object to hold open connections

};


#endif // FAIRDBCONNECTIONMAINTAINER

