/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTOSERVER
#define FAIRMQEXHISTOSERVER

#include "FairMQ.h"                      // for fair::mq::Device, fair::mq::MessagePtr
#include "FairMQExHistoCanvasDrawer.h"   // for FairMQExHistoCanvasDrawer

#include <THttpServer.h>
#include <TObjArray.h>
#include <memory>
#include <string>
#include <thread>
#include <utility>

class FairMQExHistoServer : public fair::mq::Device
{
  public:
    FairMQExHistoServer();

    virtual ~FairMQExHistoServer();

    void UpdateHttpServer();

    void SetCanvasDrawer(std::unique_ptr<FairMQExHistoCanvasDrawer> canvasDrawer)
    {
        fCanvasDrawer = std::move(canvasDrawer);
    }

  protected:
    virtual void InitTask();

    bool ReceiveData(fair::mq::MessagePtr& msg, int index);

    virtual void PreRun();

    virtual void PostRun();

  private:
    std::string fInputChannelName;

    TObjArray fArrayHisto;

    int fNMessages;

    THttpServer fServer;

    std::unique_ptr<FairMQExHistoCanvasDrawer> fCanvasDrawer;

    std::thread fThread;
    bool fStopThread;

    int FindHistogram(const std::string& name);

    FairMQExHistoServer(const FairMQExHistoServer&);
    FairMQExHistoServer& operator=(const FairMQExHistoServer&);
};

#endif
