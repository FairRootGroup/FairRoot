/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQExHistoDevice.h"

#include "RootSerializer.h"

#include <TMath.h>
#include <chrono>
#include <thread>

FairMQExHistoDevice::FairMQExHistoDevice()
    : FairMQDevice()
    , fRandom(0)
    , fArrayHisto()
{}

FairMQExHistoDevice::~FairMQExHistoDevice() {}

void FairMQExHistoDevice::InitTask()
{
    fh_histo1 = TH1F("histo1", "", 200, -0.5, 1.5);
    fh_histo2 = TH1F("histo2", "", 1000, -5., 5.);
    fh_histo3 = TH2F("histo3", "", 40, -2., 2., 40, -2., 2.);
    fh_histo4 = TH2F("histo4", "", 40, -2., 2., 40, -2., 2.);

    fArrayHisto.Add(&fh_histo1);
    fArrayHisto.Add(&fh_histo2);
    fArrayHisto.Add(&fh_histo3);
    fArrayHisto.Add(&fh_histo4);
}

void FairMQExHistoDevice::PreRun() {}

void FairMQExHistoDevice::PostRun() {}

bool FairMQExHistoDevice::ConditionalRun()
{
    fh_histo1.Fill(fRandom.Uniform(0., 1.));
    fh_histo2.Fill(fRandom.Gaus(0., 1.));
    double x = fRandom.Uniform(0., 1.);
    double y = fRandom.Uniform(x, 1.);
    fh_histo3.Fill(x, y);
    double r = fRandom.Uniform(0., 1.);
    double phi = TMath::DegToRad() * fRandom.Uniform(0., 360.);
    x = r * TMath::Cos(phi);
    y = r * TMath::Sin(phi);
    fh_histo4.Fill(x, y);

    auto message(NewMessage());
    RootSerializer().Serialize(*message, &fArrayHisto);

    for (auto& channel : fChannels) {
        Send(message, channel.first.data());
    }

    fh_histo1.Reset();
    fh_histo2.Reset();
    fh_histo3.Reset();
    fh_histo4.Reset();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    return true;
}
