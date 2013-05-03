// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRREMOTESOURCE_H
#define FAIRREMOTESOURCE_H

#include "FairSource.h"                 // for FairSource

#include "Rtypes.h"                     // for Bool_t, etc

class MRevBuffer;
class REvent;
class TSocket;

class FairRemoteSource : public FairSource
{
  public:
    FairRemoteSource(char* node);
    virtual ~FairRemoteSource();

    virtual Bool_t Init();
    virtual Bool_t Read();
    virtual void Close();

  private:
    char* fNode;
    TSocket* fSocket;
    MRevBuffer* fBuffer;
    REvent* fREvent;

    FairRemoteSource(const FairRemoteSource&);
    FairRemoteSource& operator=(const FairRemoteSource&);

  public:
    ClassDef(FairRemoteSource, 0)
};


#endif
