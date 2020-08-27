/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairMbsSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRONLINESOURCE_H
#define FAIRONLINESOURCE_H

#include "FairSource.h"
#include "FairUnpack.h"

#include <Rtypes.h>
#include <TObjArray.h>

class FairOnlineSource : public FairSource
{
  public:
    FairOnlineSource();
    FairOnlineSource(const FairOnlineSource& source);
    virtual ~FairOnlineSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }
    inline const TObjArray* GetUnpackers() const { return fUnpackers; }

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent(UInt_t = 0) = 0;
    virtual void Close() = 0;

    virtual void SetParUnpackers();

    virtual Bool_t InitUnpackers();

    virtual Bool_t ReInitUnpackers();

    void Reset();

    virtual Source_Type GetSourceType() { return kONLINE; }

    Bool_t SpecifyRunId()
    {
        ReadEvent(0);
        return true;
    };

  protected:
    TObjArray* fUnpackers;

  private:
    FairOnlineSource& operator=(const FairOnlineSource&);

    ClassDef(FairOnlineSource, 0);
};

#endif
