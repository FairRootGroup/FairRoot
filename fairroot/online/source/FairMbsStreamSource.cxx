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

#include <fairlogger/Logger.h>

FairMbsStreamSource::FairMbsStreamSource(TString tServerName)
    : FairMbsSource()
    , fServerName(tServerName)
    , fxInputChannel(nullptr)
    , fxEvent(nullptr)
    , fxBuffer(nullptr)
    , fxEventData(nullptr)
    , fxSubEvent(nullptr)
{
}

FairMbsStreamSource::FairMbsStreamSource(const FairMbsStreamSource& source)
    : FairMbsSource(source)
    , fServerName(source.GetServerName())
    , fxInputChannel(nullptr)
    , fxEvent(nullptr)
    , fxBuffer(nullptr)
    , fxEventData(nullptr)
    , fxSubEvent(nullptr)
{
}

Bool_t FairMbsStreamSource::Init()
{
    return ConnectToServer();
}

Bool_t FairMbsStreamSource::ConnectToServer()
{
    Int_t inputMode = GETEVT__STREAM;
    fxInputChannel = new s_evt_channel;
    s_filhe fxInfoHeader;
    void* headptr = &fxInfoHeader;
    INTS4 status;

    LOG(info) << "FairMbsStreamSource::ConnectToServer()";
    LOG(info) << Form("- open connection to MBS stream server %s...", fServerName.Data());

    status = f_evt_get_open(
        inputMode, const_cast<char*>(fServerName.Data()), fxInputChannel, static_cast<Char_t**>(headptr), 1, 1);

    CHARS* sErrorString = nullptr;
    f_evt_error(status, sErrorString, 0);

    if (GETEVT__SUCCESS != status) {
        return kFALSE;
    }

    LOG(info) << Form("- connection to MBS stream server %s established.", fServerName.Data());

    return kTRUE;
}

Int_t FairMbsStreamSource::ReadEvent(UInt_t)
{
    void* evtptr = &fxEvent;
    void* buffptr = &fxBuffer;

    LOG(debug2) << "FairLmdSource::ReadEvent => New event ";

    Int_t status = f_evt_get_event(fxInputChannel, static_cast<INTS4**>(evtptr), static_cast<INTS4**>(buffptr));

    LOG(debug2) << "FairLmdSource::ReadEvent => f_evt_get_event status: " << status;

    if (GETEVT__SUCCESS != status) {
        LOG(info) << "FairMbsStreamSource::ReadEvent()";

        CHARS* sErrorString = nullptr;
        f_evt_error(status, sErrorString, 0);

        return 1;
    }

    Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, nullptr, nullptr, nullptr);

    Int_t sebuflength;
    Short_t setype;
    Short_t sesubtype;
    Short_t seprocid;
    Short_t sesubcrate;
    Short_t secontrol;

    LOG(debug2) << "FairLmdSource::ReadEvent => Found " << nrSubEvts << " Sub-event ";

    for (Int_t i = 1; i <= nrSubEvts; i++) {
        void* SubEvtptr = &fxSubEvent;
        void* EvtDataptr = &fxEventData;
        Int_t nrlongwords;

        status = f_evt_get_subevent(
            fxEvent, i, static_cast<Int_t**>(SubEvtptr), static_cast<Int_t**>(EvtDataptr), &nrlongwords);

        sebuflength = nrlongwords;
        setype = fxSubEvent->i_type;
        sesubtype = fxSubEvent->i_subtype;
        seprocid = fxSubEvent->i_procid;
        sesubcrate = fxSubEvent->h_subcrate;
        secontrol = fxSubEvent->h_control;

        if (!Unpack(fxEventData, sebuflength, setype, sesubtype, seprocid, sesubcrate, secontrol)) {
            return 2;
        }
    }

    return 0;
}

void FairMbsStreamSource::Close()
{
    Int_t status = f_evt_get_close(fxInputChannel);

    LOG(info) << "FairMbsStreamSource::Close()";

    CHARS* sErrorString = nullptr;
    f_evt_error(status, sErrorString, 0);
}
