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
    FairSource(const FairSource& source);
    virtual ~FairSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }
    inline const TObjArray* GetUnpackers() const { return fUnpackers; }

    virtual Bool_t Init();
    virtual Int_t ReadEvent() = 0;
    virtual void Close() = 0;

    void Reset();

  protected:
    Bool_t Unpack(Int_t* data, Int_t size,
                  Short_t type, Short_t subType,
                  Short_t procId, Short_t subCrate, Short_t control);

  private:
    TObjArray* fUnpackers;

  public:
    ClassDef(FairSource, 0)
};


#endif
