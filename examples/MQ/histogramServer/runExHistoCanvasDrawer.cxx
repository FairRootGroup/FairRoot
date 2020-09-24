/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <memory>                              // for unique_ptr

#include "FairMQExHistoCanvasDrawerExample.h"  // for FairMQExHistoCanvasDra...
#include "runExHistoServer.h"                  // for getCanvasDrawer
#include "FairMQExHistoCanvasDrawer.h"         // for FairMQExHistoCanvasDrawer

std::unique_ptr<FairMQExHistoCanvasDrawer> getCanvasDrawer()
{
    return std::unique_ptr<FairMQExHistoCanvasDrawer>{new FairMQExHistoCanvasDrawerExample()};
}
