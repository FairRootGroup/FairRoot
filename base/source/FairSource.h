// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRSOURCE_H
#define FAIRSOURCE_H

#include "TObject.h"
#include "TObjArray.h"

#include "FairUnpack.h"


class FairSource : public TObject
{
  public:
    FairSource();
    virtual ~FairSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }

    virtual Bool_t Init();
    virtual Bool_t ReadEvent() = 0;
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

