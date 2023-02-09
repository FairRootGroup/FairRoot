/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of DigiLoader::Exec() with pure binary transport data format

#include "Payload.h"

template<>
void DigiLoader<TestDetectorBin>::Exec(Option_t* /*opt*/)
{
    int numEntries = fInput->GetEntriesFast();
    size_t digisSize = numEntries * sizeof(Payload::Digi);

    fPayload = fTransportFactory->CreateMessage(digisSize);

    Payload::Digi* digiPayload = static_cast<Payload::Digi*>(fPayload->GetData());

    for (int i = 0; i < numEntries; ++i) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }
        new (&digiPayload[i]) Payload::Digi();
        digiPayload[i] = Payload::Digi();
        digiPayload[i].fX = digi->GetX();
        digiPayload[i].fY = digi->GetY();
        digiPayload[i].fZ = digi->GetZ();
        digiPayload[i].fTimeStamp = digi->GetTimeStamp();
        digiPayload[i].fTimeStampError = digi->GetTimeStampError();
    }
}
