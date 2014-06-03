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
#include <iostream>
using namespace std;

#include "TList.h"
#include "TObjString.h"

#include "FairLmdSource.h"


FairLmdSource::FairLmdSource()
  : FairMbsSource(),
    fCurrentFile(0),
    fFileNames(new TList()),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL),
    fxInfoHeader(NULL)
{
}


FairLmdSource::FairLmdSource(const FairLmdSource& source)
  : FairMbsSource(source),
    fCurrentFile(source.GetCurrentFile()),
    fFileNames(new TList()),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL),
    fxInfoHeader(NULL)
{
}


FairLmdSource::~FairLmdSource()
{
  fFileNames->Delete();
  delete fFileNames;
}


void FairLmdSource::AddFile(TString fileName)
{
  TObjString* str = new TObjString(fileName);
  fFileNames->Add(str);
}


Bool_t FairLmdSource::Init()
{
  if(! FairMbsSource::Init()) {
    return kFALSE;
  }

  if(fFileNames->GetSize() == 0) {
    return kFALSE;
  }

  TString name = ((TObjString*)fFileNames->At(fCurrentFile))->GetString();
  if(! OpenNextFile(name)) {
    return kFALSE;
  }

  fCurrentFile += 1;

  return kTRUE;
}


Bool_t FairLmdSource::OpenNextFile(TString fileName)
{
  Int_t inputMode = 1;
  fxInputChannel = new s_evt_channel;  
  void* headptr = &fxInfoHeader;
  INTS4 status;
  status = f_evt_get_open(inputMode,
                          const_cast<char*>(fileName.Data()),
                          fxInputChannel,
                          (Char_t**)headptr,
                          1,
                          1);

  if(status) {
    return kFALSE;
  }

  cout << "-I- FairLmdSource::OpenNextFile : file "
       << fileName << " opened." << endl;

  return kTRUE;
}


Int_t FairLmdSource::ReadEvent()
{
  void* evtptr = &fxEvent;
  void* buffptr = &fxBuffer;

  Int_t status = f_evt_get_event(fxInputChannel, (INTS4**)evtptr,(INTS4**) buffptr);
  //Int_t fuEventCounter = fxEvent->l_count;
  //Int_t fCurrentMbsEventNo = fuEventCounter;

  if(GETEVT__SUCCESS != status) {
    if(fCurrentFile >= fFileNames->GetSize()) {
      return 1;
    }

    if(GETEVT__NOMORE == status) {
      Close();
    }

    TString name = ((TObjString*)fFileNames->At(fCurrentFile))->GetString();
    if(! OpenNextFile(name)) {
      return 1;
    } else {
      fCurrentFile += 1;
      return ReadEvent();
    }
  }

  // Decode event header
  Bool_t result = Unpack((Int_t*)fxEvent, sizeof(s_ve10_1), -2, -2, -2, -2, -2);

  Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, NULL, NULL, NULL);
  Int_t sebuflength;
  Short_t setype;
  Short_t sesubtype;
  Short_t seprocid;
  Short_t sesubcrate;
  Short_t secontrol;
//  Int_t* SubEventDataPtr = new Int_t;
  for(Int_t i = 1; i <= nrSubEvts; i++) {
    void* SubEvtptr = &fxSubEvent;
    void* EvtDataptr = &fxEventData;
    Int_t nrlongwords;
    status = f_evt_get_subevent(fxEvent, i, (Int_t**)SubEvtptr, (Int_t**)EvtDataptr, &nrlongwords);
    if(status) {
      return 1;
    }
    sebuflength = nrlongwords;
    setype = fxSubEvent->i_type;
    sesubtype = fxSubEvent->i_subtype;
    seprocid = fxSubEvent->i_procid;
    sesubcrate = fxSubEvent->h_subcrate;
    secontrol = fxSubEvent->h_control;

    if(Unpack(fxEventData, sebuflength,
              setype, sesubtype,
              seprocid, sesubcrate, secontrol)) {
      result = kTRUE;
    }
  }

  if(! result)
  {
    return 2;
  }

  return 0;
}


void FairLmdSource::Close()
{
  f_evt_get_close(fxInputChannel);
}


ClassImp(FairLmdSource)


