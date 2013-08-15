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
  : FairSource()
{
  fCurrentFile = 0;
  fFileNames = new TList();
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
  if(! FairSource::Init()) {
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
  s_filhe fxInfoHeader;
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


Bool_t FairLmdSource::ReadEvent()
{
  void* evtptr = &fxEvent;
  void* buffptr = &fxBuffer;

  Int_t status = f_evt_get_event(fxInputChannel, (Int_t**)evtptr,(Int_t**) buffptr);
  //Int_t fuEventCounter = fxEvent->l_count;
  //Int_t fCurrentMbsEventNo = fuEventCounter;

  if(0 != status) {
    if(fCurrentFile >= fFileNames->GetSize()) {
      return kFALSE;
    }

    TString name = ((TObjString*)fFileNames->At(fCurrentFile))->GetString();
    if(! OpenNextFile(name)) {
      return kFALSE;
    } else {
      fCurrentFile += 1;
      return ReadEvent();
    }

    return kFALSE;
  }

  Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, NULL, NULL, NULL);
  Int_t sebuflength;
  Short_t setype;
  Short_t sesubtype;
  Short_t seprocid;
  Short_t sesubcrate;
  Short_t secontrol;
  //Int_t* SubEventDataPtr = new Int_t;
  for(Int_t i = 1; i <= nrSubEvts; i++) {
    void* SubEvtptr = &fxSubEvent;
    void* EvtDataptr = &fxEventData;
    Int_t* nrlongwords = new Int_t;
    status = f_evt_get_subevent(fxEvent, i, (Int_t**)SubEvtptr, (Int_t**)EvtDataptr, nrlongwords);
    if(status) {
      return kFALSE;
    }
    sebuflength = fxSubEvent->l_dlen;
    setype = fxSubEvent->i_type;
    sesubtype = fxSubEvent->i_subtype;
    seprocid = fxSubEvent->i_procid;
    sesubcrate = fxSubEvent->h_subcrate;
    secontrol = fxSubEvent->h_control;
    delete nrlongwords;

    if(! Unpack(fxEventData, sebuflength,
                setype, sesubtype,
                seprocid, sesubcrate, secontrol)) {
      return kFALSE;
    }
  }

  return kTRUE;
}


void FairLmdSource::Close()
{
  f_evt_get_close(fxInputChannel);
}


ClassImp(FairLmdSource)


