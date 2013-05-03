// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairUnpack                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRUNPACK_H
#define FAIRUNPACK_H

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TObject.h"


class FairUnpack : public TObject
{
  public:
    FairUnpack(Int_t type, Int_t subType);
    virtual ~FairUnpack();

    virtual Bool_t Init() = 0;
    virtual Bool_t DoUnpack(Int_t* data, Int_t size) = 0;
    virtual void   Reset() = 0;

    inline Int_t GetType()    const { return fType;    }
    inline Int_t GetSubType() const { return fSubType; }

  private:
    Int_t fType;
    Int_t fSubType;

  protected:
    virtual void Register() = 0;

  public:
    ClassDef(FairUnpack, 0)
};


#endif



