/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "runExHistoServer.h"

#include "FairMQExHistoCanvasDrawerExample.h"

std::unique_ptr<FairMQExHistoCanvasDrawer> getCanvasDrawer()
{
    return std::unique_ptr<FairMQExHistoCanvasDrawer>{ new FairMQExHistoCanvasDrawerExample() };
}
