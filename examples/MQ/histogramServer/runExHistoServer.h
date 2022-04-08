/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQExHistoServer.h"
#include "FairRunFairMQDevice.h"

#include <memory>

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& /*options*/) {}

std::unique_ptr<FairMQExHistoCanvasDrawer> getCanvasDrawer();

std::unique_ptr<fair::mq::Device> fairGetDevice(const fair::mq::ProgOptions& /*config*/)
{
    auto histoServer = std::make_unique<FairMQExHistoServer>();

    histoServer->SetCanvasDrawer(getCanvasDrawer());

    return histoServer;
}
