/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairMQExHistoCanvasDrawerExample.h"
#include "runExHistoServer.h"

#include <memory>

std::unique_ptr<FairMQExHistoCanvasDrawer> getCanvasDrawer()
{
    return std::make_unique<FairMQExHistoCanvasDrawerExample>();
}
