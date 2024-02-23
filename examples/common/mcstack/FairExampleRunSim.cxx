/********************************************************************************
 * Copyright (C) 2023-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairExampleRunSim.h"

FairExampleRunSim::FairExampleRunSim(const char* mcEngine)
    : FairRunSim()
{
    SetName(mcEngine);
}
