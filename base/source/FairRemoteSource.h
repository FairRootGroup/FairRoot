/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRREMOTESOURCE_H
#define FAIRREMOTESOURCE_H

#include "FairMbsSource.h"   // for FairMbsSource

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Bool_t, Int_t, UInt_t

class MRevBuffer;
class REvent;
class TSocket;
class TBuffer;
class TClass;
class TMemberInspector;

class FairRemoteSource : public FairMbsSource
{
  public:
    FairRemoteSource(char* node);
    FairRemoteSource(const FairRemoteSource& source);
    virtual ~FairRemoteSource();

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t = 0);
    virtual void Close();

    inline const char* GetNode() const { return fNode; }

  private:
    char* fNode;
    TSocket* fSocket;
    MRevBuffer* fBuffer;
    REvent* fREvent;

    FairRemoteSource& operator=(const FairRemoteSource&);

  public:
    ClassDef(FairRemoteSource, 0);
};

#endif
