/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of DigiLoader::Exec() with Boost transport data format

#include "Payload.h"
#include "BoostSerializer.h"

template<>
void DigiLoader<TestDetectorBoost>::Exec(Option_t* /*opt*/)
{
    fPayload = fTransportFactory->CreateMessage();
    BoostSerializer<FairTestDetectorDigi>().Serialize(*fPayload, fInput);
}
