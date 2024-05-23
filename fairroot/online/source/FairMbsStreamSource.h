// -----------------------------------------------------------------------------
// ----- FairMbsStreamSource header file                                   -----
// -----                                                                   -----
// ----- created by C. Simon on 2014-09-12                                 -----
// -----                                                                   -----
// ----- based on FairLmdSource by D. Kresan                               -----
// -----                                                                   -----
// ----- revision 23363, 2013-12-26                                        -----
// -----------------------------------------------------------------------------

#ifndef FAIRMBSSTREAMSOURCE_H
#define FAIRMBSSTREAMSOURCE_H

extern "C"
{
#include "f_evt.h"
#include "s_bufhe_swap.h"
#include "s_filhe_swap.h"
}

#include "FairMbsSource.h"

#include <Rtypes.h>
#include <TString.h>

class FairMbsStreamSource : public FairMbsSource
{
  public:
    FairMbsStreamSource(TString tServerName);
    FairMbsStreamSource(const FairMbsStreamSource& source);
    ~FairMbsStreamSource() override = default;

    Bool_t Init() override;
    Int_t ReadEvent(UInt_t = 0) override;
    void Close() override;
    Bool_t SpecifyRunId() override
    {
        ReadEvent(0);
        return true;
    };

    const char* GetServerName() const { return fServerName.Data(); };

  private:
    Bool_t ConnectToServer();

    TString fServerName;

    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    Int_t* fxEventData;
    s_ves10_1* fxSubEvent;

    FairMbsStreamSource& operator=(const FairMbsStreamSource&);

  public:
    ClassDefOverride(FairMbsStreamSource, 0);
};

#endif
