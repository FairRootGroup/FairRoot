/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBPARSET_H
#define FAIRDBPARSET_H


#include "FairDbObjTableMap.h"


class FairDbParSet : public FairDbObjTableMap
{
  public:

    FairDbParSet();
    FairDbParSet(const char* name,const char* title,const char* context, Bool_t ownership=kFALSE)
     : FairDbObjTableMap(name,title,context,ownership) {} 

    FairDbParSet(const FairDbParSet& from);
    FairDbParSet& operator=(const FairDbParSet&);

    virtual ~FairDbParSet();

  protected:
   

    ClassDef(FairDbParSet,0)   // FairDbObjTableMap for a specific database table.

};


#endif  // FAIRDBPARSET_H
