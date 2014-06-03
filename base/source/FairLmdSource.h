/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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
#include "s_filhe_swap.h"
#include "s_bufhe_swap.h"
}

#include "TString.h"

#include "FairMbsSource.h"


class TList;


class FairLmdSource : public FairMbsSource
{
  public:
    FairLmdSource();
    FairLmdSource(const FairLmdSource& source);
    virtual ~FairLmdSource();

    void AddFile(TString fileName);
    inline const Int_t GetCurrentFile() const { return fCurrentFile; }
    inline const TList* GetFileNames() const { return fFileNames; }

    virtual Bool_t Init();
    virtual Int_t ReadEvent();
    virtual void Close();

  protected:
    Bool_t OpenNextFile(TString fileName);

    Int_t fCurrentFile;
    TList* fFileNames;
    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    Int_t* fxEventData;
    s_ves10_1* fxSubEvent;
	s_filhe* fxInfoHeader;

  public:
    ClassDef(FairLmdSource, 0)
};


#endif
