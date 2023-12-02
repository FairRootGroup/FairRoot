/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
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
    ~FairOnlineSource() override;

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }
    inline const TObjArray* GetUnpackers() const { return fUnpackers; }

    Bool_t Init() override = 0;
    Int_t ReadEvent(UInt_t = 0) override = 0;

    void SetParUnpackers() override;

    Bool_t InitUnpackers() override;

    Bool_t ReInitUnpackers() override;

    void Reset() override;

    Source_Type GetSourceType() override { return kONLINE; }

    Bool_t SpecifyRunId() override
    {
        ReadEvent(0);
        return true;
    };

  protected:
    TObjArray* fUnpackers;

  private:
    FairOnlineSource& operator=(const FairOnlineSource&);

    ClassDefOverride(FairOnlineSource, 0);
};

#endif
