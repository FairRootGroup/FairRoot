/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Implementation of FairTestDetectorDigiLoader::Exec() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "FairTestDetectorPayloadDigi_generated.h"
#include "flatbuffers/flatbuffers.h"

using namespace TestDetectorFlat;

template<>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>::Exec(Option_t* /*opt*/)
{
    int nDigis = fInput->GetEntriesFast();

    flatbuffers::FlatBufferBuilder* builder = new flatbuffers::FlatBufferBuilder();
    flatbuffers::Offset<TestDetectorFlat::Digi>* digis = new flatbuffers::Offset<TestDetectorFlat::Digi>[nDigis];

    for (int i = 0; i < nDigis; ++i) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }

        DigiBuilder db(*builder);
        db.add_x(digi->GetX());                             // x:int
        db.add_y(digi->GetY());                             // y:int
        db.add_z(digi->GetZ());                             // z:int
        db.add_timestamp(digi->GetTimeStamp());             // timestamp:double
        db.add_timestampError(digi->GetTimeStampError());   // timestampError:double

        digis[i] = db.Finish();
        // LOG(info) << digi->GetX() << " " << digi->GetY() << " " << digi->GetZ() << " " << digi->GetTimeStamp() << " "
        // << digi->GetTimeStampError();
    }

    auto dvector = builder->CreateVector(digis, nDigis);
    auto mloc = CreateDigiPayload(*builder, dvector);
    FinishDigiPayloadBuffer(*builder, mloc);

    delete[] digis;

    fPayload = fTransportFactory->CreateMessage(
        builder->GetBufferPointer(),
        builder->GetSize(),
        [](void* /* data */, void* obj) { delete static_cast<flatbuffers::FlatBufferBuilder*>(obj); },
        builder);
}

#endif /* FLATBUFFERS */
