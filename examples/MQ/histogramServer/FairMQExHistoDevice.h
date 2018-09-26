/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTODEVICE
#define FAIRMQEXHISTODEVICE

#include "FairMQDevice.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TRandom3.h"
#include "TObjArray.h"

class FairMQExHistoDevice : public FairMQDevice
{
  public:
    FairMQExHistoDevice();
    virtual ~FairMQExHistoDevice();

  protected:
    virtual void InitTask();
    virtual void PreRun();
    virtual void PostRun();
    virtual bool ConditionalRun();

  private:
    FairMQExHistoDevice(const FairMQExHistoDevice&);
    FairMQExHistoDevice& operator=(const FairMQExHistoDevice&);

    TRandom3 fRandom;

    TH1F fh_histo1;
    TH1F fh_histo2;
    TH2F fh_histo3;
    TH2F fh_histo4;

    TObjArray fArrayHisto;
};

#endif
