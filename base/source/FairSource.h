// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRSOURCE_H
#define FAIRSOURCE_H

#include "TObject.h"                    // for TObject

#include "FairUnpack.h"                 // for FairUnpack

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TObjArray.h"                  // for TObjArray

class FairSource : public TObject
{
  public:
    FairSource();
    virtual ~FairSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }

    virtual Bool_t Init();
    virtual Bool_t Read() = 0;
    virtual void Close() = 0;

  protected:
    Bool_t Unpack(Int_t* data, Int_t size,
                  Int_t type, Int_t subType);
    void Reset();

  private:
    TObjArray* fUnpackers;

  public:
    ClassDef(FairSource, 0)
};


#endif

