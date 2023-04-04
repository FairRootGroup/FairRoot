/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           FairLmdSource                           -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRLMDSOURCE_H
#define FAIRLMDSOURCE_H

extern "C"
{
#include "f_evt.h"
#include "s_bufhe_swap.h"
#include "s_filhe_swap.h"
}

#include "FairMbsSource.h"

#include <Rtypes.h>
#include <TString.h>

class TList;

class FairLmdSource : public FairMbsSource
{
  public:
    FairLmdSource();
    FairLmdSource(const FairLmdSource& source);
    ~FairLmdSource() override;

    void AddFile(TString fileName);
    void AddPath(TString dir, TString wildCard);
    inline Int_t GetCurrentFile() const { return fCurrentFile; }
    inline const TList* GetFileNames() const { return fFileNames; }

    Bool_t Init() override;
    Int_t ReadEvent(UInt_t = 0) override;
    void Close() override;
    Bool_t SpecifyRunId() override
    {
        ReadEvent(0);
        return true;
    };

  protected:
    Bool_t OpenNextFile(TString fileName);

    Int_t fCurrentFile;
    Int_t fNEvent;
    Int_t fCurrentEvent;
    TList* fFileNames;
    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    Int_t* fxEventData;
    s_ves10_1* fxSubEvent;
    s_filhe* fxInfoHeader;

    FairLmdSource& operator=(const FairLmdSource&);

    ClassDefOverride(FairLmdSource, 0);
};

#endif
