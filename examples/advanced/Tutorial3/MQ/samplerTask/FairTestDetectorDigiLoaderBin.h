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

// Implementation of FairTestDetectorDigiLoader::Exec() with pure binary transport data format
template<>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>::Exec(Option_t* /*opt*/)
{
    int numEntries = fInput->GetEntriesFast();
    size_t digisSize = numEntries * sizeof(TestDetectorPayload::Digi);

    fPayload = fTransportFactory->CreateMessage(digisSize);

    TestDetectorPayload::Digi* digiPayload = static_cast<TestDetectorPayload::Digi*>(fPayload->GetData());

    for (int i = 0; i < numEntries; ++i) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }
        new (&digiPayload[i]) TestDetectorPayload::Digi();
        digiPayload[i] = TestDetectorPayload::Digi();
        digiPayload[i].fX = digi->GetX();
        digiPayload[i].fY = digi->GetY();
        digiPayload[i].fZ = digi->GetZ();
        digiPayload[i].fTimeStamp = digi->GetTimeStamp();
        digiPayload[i].fTimeStampError = digi->GetTimeStampError();
    }
}
