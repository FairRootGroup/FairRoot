/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRSOURCE_H
#define FAIRSOURCE_H

#include "TObject.h"

#include <iostream>

class FairEventHeader;

class FairSource : public TObject
{
  public:
    FairSource();
    FairSource(const FairSource& source);
    virtual ~FairSource();

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent(UInt_t=0) = 0;
    virtual void Close() = 0;

    virtual void Reset() = 0;
    
    virtual Bool_t   ActivateObject(TObject**, const char*)  { return kFALSE; }
    
    /**Check the maximum event number we can run to*/
    virtual Int_t  CheckMaxEventNo(Int_t=0) {return -1;}
    /**Read the tree entry on one branch**/
    virtual void   ReadBranchEvent(const char* ) {return;}
    virtual void   ReadBranchEvent(const char*, Int_t) {return;}
    virtual void FillEventHeader(FairEventHeader*) { return; } 

  public:
    ClassDef(FairSource, 1)
};


#endif
