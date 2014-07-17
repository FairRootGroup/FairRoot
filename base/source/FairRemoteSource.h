/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRREMOTESOURCE_H
#define FAIRREMOTESOURCE_H

#include "FairMbsSource.h"


class TSocket;
class MRevBuffer;
class REvent;


class FairRemoteSource : public FairMbsSource
{
  public:
    FairRemoteSource(char* node);
    FairRemoteSource(const FairRemoteSource& source);
    virtual ~FairRemoteSource();

    virtual Bool_t Init();
    virtual Int_t ReadEvent();
    virtual void Close();

    inline const char* GetNode() const { return fNode; }

  private:
    char* fNode;
    TSocket* fSocket;
    MRevBuffer* fBuffer;
    REvent* fREvent;

  public:
    ClassDef(FairRemoteSource, 0)
};


#endif
