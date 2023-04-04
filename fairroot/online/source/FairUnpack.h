/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairUnpack                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRUNPACK_H
#define FAIRUNPACK_H

#include <Rtypes.h>   // for Int_t, Bool_t, etc
#include <TObject.h>

class FairUnpack : public TObject
{
  public:
    FairUnpack(Short_t type, Short_t subType, Short_t procId, Short_t subCrate, Short_t control);
    ~FairUnpack() override = default;

    virtual Bool_t Init() = 0;
    virtual Bool_t ReInit() { return kTRUE; }
    virtual Bool_t DoUnpack(Int_t* data, Int_t size) = 0;
    virtual void Reset() = 0;
    virtual void SetParContainers(){};

    inline Short_t GetType() const { return fType; }
    inline Short_t GetSubType() const { return fSubType; }
    inline Short_t GetProcId() const { return fProcId; }
    inline Short_t GetSubCrate() const { return fSubCrate; }
    inline Short_t GetControl() const { return fControl; }

  private:
    Short_t fType;
    Short_t fSubType;
    Short_t fProcId;
    Short_t fSubCrate;
    Short_t fControl;

  protected:
    virtual void Register() = 0;

  public:
    ClassDefOverride(FairUnpack, 0);
};

#endif
