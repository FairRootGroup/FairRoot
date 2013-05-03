// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           FairLmdSource                           -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------
#include "FairLmdSource.h"

#include <stddef.h>                     // for NULL
#include "s_filhe.h"                    // for s_filhe
#include "typedefs.h"                   // for INTS4

using namespace std;

FairLmdSource::FairLmdSource(char* fileName)
  : FairSource(),
    fFileName(fileName),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL)
{
}


FairLmdSource::~FairLmdSource()
{
}


Bool_t FairLmdSource::Init()
{
  if(! FairSource::Init()) {
    return kFALSE;
  }

  Int_t inputMode = 1;
  fxInputChannel = new s_evt_channel;
  s_filhe fxInfoHeader;
  void* headptr = &fxInfoHeader;
  INTS4 status;
  status = f_evt_get_open(inputMode,
                          const_cast<char*>(fFileName),
                          fxInputChannel,
                          (Char_t**)headptr,
                          1,
                          1);

  if(status) {
    return kFALSE;
  }

  return kTRUE;
}


Bool_t FairLmdSource::Read()
{
  void* evtptr = &fxEvent;
  void* buffptr = &fxBuffer;

  Int_t status = f_evt_get_event(fxInputChannel, (Int_t**)evtptr,(Int_t**) buffptr);
  Int_t fuEventCounter = fxEvent->l_count;
  Int_t fCurrentMbsEventNo = fuEventCounter;

  if(0 != status && 3 != status) {
    return kFALSE;
  }

  Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, NULL, NULL, NULL);
  Int_t sebuflength;
  Short_t setype;
  Short_t sesubtype;
  Char_t sesubcrate;
  Int_t* SubEventDataPtr = new Int_t;
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
    sesubcrate = fxSubEvent->h_subcrate;
    delete nrlongwords;


    if(! Unpack(fxEventData, sebuflength,
                setype, sesubtype)) {
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


