/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of DigiLoader::Exec() with Boost transport data format

#ifndef FAIR_TESTDETECTOR_DIGILOADER_BOOST_H
#define FAIR_TESTDETECTOR_DIGILOADER_BOOST_H

#include "BoostSerializer.h"
#include "Payload.h"

template<>
void DigiLoader<TestDetectorBoost>::Exec(Option_t* /*opt*/)
{
    fPayload = fTransportFactory->CreateMessage();
    BoostSerializer<FairTestDetectorDigi>().Serialize(*fPayload, fInput);
}

#endif   // FAIR_TESTDETECTOR_DIGILOADER_BOOST_H
