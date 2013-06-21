// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRREMOTESOURCE_H
#define FAIRREMOTESOURCE_H

#include "FairSource.h"


class TSocket;
class MRevBuffer;
class REvent;


class FairRemoteSource : public FairSource
{
  public:
    FairRemoteSource(char* node);
    virtual ~FairRemoteSource();

    virtual Bool_t Init();
    virtual Bool_t ReadEvent();
    virtual void Close();

  private:
    char* fNode;
    TSocket* fSocket;
    MRevBuffer* fBuffer;
    REvent* fREvent;

  public:
    ClassDef(FairRemoteSource, 0)
};


#endif
