/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTODEVICE
#define FAIRMQEXHISTODEVICE

#include "FairMQ.h"   // for fair::mq::Device

#include <TH1.h>   // for TH1F
#include <TH2.h>   // for TH2F
#include <TObjArray.h>
#include <TRandom3.h>

class FairMQExHistoDevice : public fair::mq::Device
{
  public:
    FairMQExHistoDevice();
    ~FairMQExHistoDevice() override;

  protected:
    void InitTask() override;
    void PreRun() override;
    void PostRun() override;
    bool ConditionalRun() override;

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
