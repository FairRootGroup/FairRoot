// -----------------------------------------------------------------------------
// ----- FairMbsStreamSource source file                                   -----
// -----                                                                   -----
// ----- created by C. Simon on 2014-09-12                                 -----
// -----                                                                   -----
// ----- based on FairLmdSource by D. Kresan                               -----
// -----                                                                   -----
// ----- revision 24905, 2014-05-12                                        -----
// -----------------------------------------------------------------------------

#include "FairMbsStreamSource.h"

#include "FairLogger.h"

FairMbsStreamSource::FairMbsStreamSource(TString tServerName)
  : FairMbsSource(),
    fServerName(tServerName),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL)
{
}


FairMbsStreamSource::FairMbsStreamSource(const FairMbsStreamSource& source)
  : FairMbsSource(source),
    fServerName(source.GetServerName()),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL)
{
}


FairMbsStreamSource::~FairMbsStreamSource()
{
}


Bool_t FairMbsStreamSource::Init()
{
  if(! ConnectToServer()) {
    return kFALSE;
  }

  return kTRUE;
}


Bool_t FairMbsStreamSource::ConnectToServer()
{
  Int_t inputMode = GETEVT__STREAM;
  fxInputChannel = new s_evt_channel;
  s_filhe fxInfoHeader;
  void* headptr = &fxInfoHeader;
  INTS4 status;

  LOG(INFO) << "FairMbsStreamSource::ConnectToServer()"
		    << FairLogger::endl;
  LOG(INFO) << Form("- open connection to MBS stream server %s...", fServerName.Data())
		    << FairLogger::endl;

  status = f_evt_get_open(inputMode,
                          const_cast<char*>(fServerName.Data()),
                          fxInputChannel,
                          static_cast<Char_t**>(headptr),
                          1,
                          1);

  CHARS* sErrorString = NULL;
  f_evt_error(status, sErrorString , 0);

  if(GETEVT__SUCCESS != status) {
    return kFALSE;
  }

  LOG(INFO) << Form("- connection to MBS stream server %s established.", fServerName.Data())
		    << FairLogger::endl;

  return kTRUE;
}


Int_t FairMbsStreamSource::ReadEvent(UInt_t)
{
  void* evtptr = &fxEvent;
  void* buffptr = &fxBuffer;

  LOG(DEBUG2)<< "FairLmdSource::ReadEvent => New event "
             << FairLogger::endl;

  Int_t status = f_evt_get_event(fxInputChannel, static_cast<INTS4**>(evtptr),static_cast<INTS4**>(buffptr));

  LOG(DEBUG2)<< "FairLmdSource::ReadEvent => f_evt_get_event status: " << status
             << FairLogger::endl;

  if(GETEVT__SUCCESS != status) {
    LOG(INFO) << "FairMbsStreamSource::ReadEvent()"
              << FairLogger::endl;

    CHARS* sErrorString = NULL;
    f_evt_error(status, sErrorString , 0);

    return 1;
  }

  Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, NULL, NULL, NULL);

  Int_t sebuflength;
  Short_t setype;
  Short_t sesubtype;
  Short_t seprocid;
  Short_t sesubcrate;
  Short_t secontrol;

  LOG(DEBUG2)<< "FairLmdSource::ReadEvent => Found " << nrSubEvts << " Sub-event "
             << FairLogger::endl;

  for(Int_t i = 1; i <= nrSubEvts; i++) {
    void* SubEvtptr = &fxSubEvent;
    void* EvtDataptr = &fxEventData;
    Int_t nrlongwords;

    status = f_evt_get_subevent(fxEvent, i, static_cast<Int_t**>(SubEvtptr), static_cast<Int_t**>(EvtDataptr), &nrlongwords);

    sebuflength = nrlongwords;
    setype = fxSubEvent->i_type;
    sesubtype = fxSubEvent->i_subtype;
    seprocid = fxSubEvent->i_procid;
    sesubcrate = fxSubEvent->h_subcrate;
    secontrol = fxSubEvent->h_control;

    if(! Unpack(fxEventData, sebuflength,
                setype, sesubtype,
                seprocid, sesubcrate, secontrol)) {
      return 2;
    }
  }

  return 0;
}


void FairMbsStreamSource::Close()
{
  Int_t status = f_evt_get_close(fxInputChannel);

  LOG(INFO) << "FairMbsStreamSource::Close()"
  		    << FairLogger::endl;

  CHARS* sErrorString = NULL;
  f_evt_error(status, sErrorString , 0);
}


ClassImp(FairMbsStreamSource)


