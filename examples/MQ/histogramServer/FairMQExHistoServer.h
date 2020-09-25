/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXHISTOSERVER
#define FAIRMQEXHISTOSERVER

#include "FairMQExHistoCanvasDrawer.h"   // for FairMQExHistoCanvasDrawer

#include <FairMQDevice.h>    // for FairMQDevice
#include <FairMQMessage.h>   // for FairMQMessagePtr
#include <THttpServer.h>     // for THttpServer
#include <TObjArray.h>       // for TObjArray
#include <iosfwd>            // for string
#include <memory>            // for unique_ptr
#include <string>
#include <thread>   // for thread
#include <utility>
#include <utility>   // for move

class FairMQExHistoServer : public FairMQDevice
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

    bool ReceiveData(FairMQMessagePtr& msg, int index);

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
