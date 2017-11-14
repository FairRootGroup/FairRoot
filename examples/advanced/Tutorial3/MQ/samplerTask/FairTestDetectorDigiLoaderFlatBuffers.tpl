// Implementation of FairTestDetectorDigiLoader::Exec() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "flatbuffers/flatbuffers.h"
#include "FairTestDetectorPayloadDigi_generated.h"

using namespace TestDetectorFlat;

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>::Exec(Option_t* /*opt*/)
{
    int nDigis = fInput->GetEntriesFast();

    flatbuffers::FlatBufferBuilder* builder = new flatbuffers::FlatBufferBuilder();
    flatbuffers::Offset<TestDetectorFlat::Digi>* digis = new flatbuffers::Offset<TestDetectorFlat::Digi>[nDigis];

    for (int i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }

        DigiBuilder db(*builder);
        db.add_x(digi->GetX()); // x:int
        db.add_y(digi->GetY()); // y:int
        db.add_z(digi->GetZ()); // z:int
        db.add_timestamp(digi->GetTimeStamp()); // timestamp:double
        db.add_timestampError(digi->GetTimeStampError()); // timestampError:double

        digis[i] = db.Finish();
        // LOG(INFO) << digi->GetX() << " " << digi->GetY() << " " << digi->GetZ() << " " << digi->GetTimeStamp() << " " << digi->GetTimeStampError();
    }

    auto dvector = builder->CreateVector(digis, nDigis);
    auto mloc = CreateDigiPayload(*builder, dvector);
    FinishDigiPayloadBuffer(*builder, mloc);

    delete [] digis;

    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage(builder->GetBufferPointer(),
                                                                 builder->GetSize(),
                                                                 [](void* /* data */, void* obj) { delete static_cast<flatbuffers::FlatBufferBuilder*>(obj); },
                                                                 builder));
}

#endif /* FLATBUFFERS */
