/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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
#include "f_evt.h"     // for s_evt_channel
#include "s_bufhe.h"   // for s_bufhe
#include "s_bufhe_swap.h"
#include "s_filhe.h"   // for s_filhe
#include "s_filhe_swap.h"
#include "s_ve10_1.h"    // for s_ve10_1
#include "s_ves10_1.h"   // for s_ves10_1
}

#include "FairMbsSource.h"   // for FairMbsSource

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Int_t, Bool_t, UInt_t
#include <TString.h>      // for TString

class TList;
class TBuffer;
class TClass;
class TMemberInspector;

class FairLmdSource : public FairMbsSource
{
  public:
    FairLmdSource();
    FairLmdSource(const FairLmdSource& source);
    virtual ~FairLmdSource();

    void AddFile(TString fileName);
    void AddPath(TString dir, TString wildCard);
    inline Int_t GetCurrentFile() const { return fCurrentFile; }
    inline const TList* GetFileNames() const { return fFileNames; }

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t = 0);
    virtual void Close();
    Bool_t SpecifyRunId()
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

    ClassDef(FairLmdSource, 0);
};

#endif
