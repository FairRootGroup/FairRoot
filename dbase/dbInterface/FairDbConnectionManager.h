#ifndef FAIRDBCONNECTIONMANAGER
#define FAIRDBCONNECTIONMANAGER

#include "Rtypes.h"                // for ClassDef

class FairDbConnectionPool;

class FairDbConnectionManager
{

  public:

    FairDbConnectionManager(FairDbConnectionPool* cascader = 0);
    virtual ~FairDbConnectionManager();

  private:

    FairDbConnectionPool* fConnectPool;

    FairDbConnectionManager(const FairDbConnectionManager&);
    FairDbConnectionManager operator=(const FairDbConnectionManager&);

    ClassDef(FairDbConnectionManager,0) // Class to manage connections

};


#endif // FAIRDBCONNECTIONMANAGER

