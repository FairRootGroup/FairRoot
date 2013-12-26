// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRSOURCE_H
#define FAIRSOURCE_H

#include "TObject.h"

class FairSource : public TObject
{
  public:
    FairSource();
    FairSource(const FairSource& source);
    virtual ~FairSource();

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent() = 0;
    virtual void Close() = 0;

    virtual void Reset() = 0;

  public:
    ClassDef(FairSource, 0)
};


#endif
