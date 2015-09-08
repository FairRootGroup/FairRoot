/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTUT8UNPACK_H
#define FAIRTUT8UNPACK_H

#include "FairUnpack.h"

class TClonesArray;

class FairTut8Unpack : public FairUnpack
{
  public:
    // Constructor
    FairTut8Unpack(Short_t type = 94,
                   Short_t subType = 9400,
                   Short_t procId = 10,
                   Short_t subCrate = 1,
                   Short_t control = 3);

    // Destructor
    virtual ~FairTut8Unpack();

    // Fair specific
    virtual Bool_t Init();
    virtual Bool_t DoUnpack(Int_t* data, Int_t size);
    virtual void Reset();
    
    inline Int_t GetNHitsTotal() { return fNHitsTotal; }

  protected:
    virtual void Register();

  private:
    TClonesArray* fRawData;
    Int_t fNHits;
    Int_t fNHitsTotal;

  public:
    // Class definition
    ClassDef(FairTut8Unpack, 1)
};

#endif
