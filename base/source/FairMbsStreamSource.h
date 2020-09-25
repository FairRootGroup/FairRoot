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
#include "f_evt.h"     // for s_evt_channel
#include "s_bufhe.h"   // for s_bufhe
#include "s_bufhe_swap.h"
#include "s_filhe_swap.h"
#include "s_ve10_1.h"    // for s_ve10_1
#include "s_ves10_1.h"   // for s_ves10_1
}

#include "FairMbsSource.h"   // for FairMbsSource

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Bool_t, Int_t, UInt_t
#include <TString.h>      // for TString

class TBuffer;
class TClass;
class TMemberInspector;

class FairMbsStreamSource : public FairMbsSource
{
  public:
    FairMbsStreamSource(TString tServerName);
    FairMbsStreamSource(const FairMbsStreamSource& source);
    virtual ~FairMbsStreamSource();

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t = 0);
    virtual void Close();
    Bool_t SpecifyRunId()
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
    ClassDef(FairMbsStreamSource, 0);
};

#endif
