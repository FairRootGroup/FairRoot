/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <memory>

#include "runFairMQDevice.h"

#include "FairMQExHistoServer.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& /*options*/)
{
}

std::unique_ptr<FairMQExHistoCanvasDrawer> getCanvasDrawer();

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    FairMQExHistoServer* histoServer = new FairMQExHistoServer();

    histoServer->SetCanvasDrawer(getCanvasDrawer());

    return histoServer;
}

