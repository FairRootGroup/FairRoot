/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQExHistoServer.h"

#include "FairLogger.h"
#include "FairMQExHistoCanvasDrawer.h"
#include "RootSerializer.h"

#include <TH1.h>
#include <TObject.h>
#include <TString.h>
#include <chrono>
#include <mutex>

std::mutex mtx;

FairMQExHistoServer::FairMQExHistoServer()
    : fInputChannelName("histogram-in")
    , fArrayHisto()
    , fNMessages(0)
    , fServer("http:8080")
    , fCanvasDrawer(nullptr)
    , fStopThread(false)
{}

FairMQExHistoServer::~FairMQExHistoServer() {}

void FairMQExHistoServer::InitTask()
{
    OnData(fInputChannelName, &FairMQExHistoServer::ReceiveData);

    if (fCanvasDrawer) {
        fCanvasDrawer->CreateCanvases(fServer);
    }
}

bool FairMQExHistoServer::ReceiveData(FairMQMessagePtr& msg, int index)
{
    TObject* tempObject = nullptr;
    RootSerializer().Deserialize(*msg, tempObject);

    if (TString(tempObject->ClassName()).EqualTo("TObjArray")) {
        std::lock_guard<std::mutex> lk(mtx);
        TObjArray* arrayHisto = static_cast<TObjArray*>(tempObject);
        TH1* histogram_new;
        TH1* histogram_existing;
        for (int i = 0; i < arrayHisto->GetEntriesFast(); i++) {
            TObject* obj = arrayHisto->At(i);
            TH1* histogram = static_cast<TH1*>(obj);
            int index1 = FindHistogram(histogram->GetName());
            if (-1 == index1) {
                histogram_new = static_cast<TH1*>(histogram->Clone());
                fArrayHisto.Add(histogram_new);
                fServer.Register("Histograms", histogram_new);
            } else {
                histogram_existing = static_cast<TH1*>(fArrayHisto.At(index1));
                histogram_existing->Add(histogram);
            }
        }

        arrayHisto->Clear();
    }

    fNMessages += 1;

    delete tempObject;

    return true;
}

void FairMQExHistoServer::PreRun()
{
    fStopThread = false;
    fThread = std::thread(&FairMQExHistoServer::UpdateHttpServer, this);
}

void FairMQExHistoServer::UpdateHttpServer()
{
    while (!fStopThread) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lk(mtx);

        if (fCanvasDrawer) {
            fCanvasDrawer->DrawHistograms(fArrayHisto);
        }

        fServer.ProcessRequests();
    }
}

void FairMQExHistoServer::PostRun()
{
    fStopThread = true;
    fThread.join();
}

int FairMQExHistoServer::FindHistogram(const std::string& name)
{
    for (int i = 0; i < fArrayHisto.GetEntriesFast(); i++) {
        TObject* obj = fArrayHisto.At(i);
        if (TString(obj->GetName()).EqualTo(name)) {
            return i;
        }
    }
    return -1;
}
