/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairTestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

// Default implementation of FairTestDetectorDigiLoader::Exec() with Boost transport data format

#include "BoostSerializer.h"

// example TOut: FairTestDetectorDigi
// example TPayloadOut: boost::archive::binary_oarchive
template<typename TOut, typename TPayloadOut>
void FairTestDetectorDigiLoader<TOut, TPayloadOut>::Exec(Option_t* /*opt*/)
{
    fPayload = fTransportFactory->CreateMessage();
    BoostSerializer<TOut>().Serialize(*fPayload, fInput);
}
