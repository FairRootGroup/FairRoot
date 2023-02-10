/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of DigiLoader::Exec() with Root TMessage transport data format

#include "Payload.h"
#include "RootSerializer.h"

template<>
void DigiLoader<TestDetectorTMessage>::Exec(Option_t* /*opt*/)
{
    fPayload = fTransportFactory->CreateMessage();
    RootSerializer().Serialize(*fPayload, fInput);
}
