/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

