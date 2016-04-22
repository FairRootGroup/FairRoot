// Implementation of FairTestDetectorDigiLoader::Exec() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "flatbuffers/flatbuffers.h"
#include "FairTestDetectorPayloadDigi_generated.h"

using namespace TestDetectorFlat;

// helper function to clean up the object holding the data after it is transported.
void free_builder(void *data, void *hint)
{
    delete static_cast<flatbuffers::FlatBufferBuilder*>(hint);
}

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorFlat::DigiPayload>::Exec(Option_t* opt)
{
    int nDigis = fInput->GetEntriesFast();

    flatbuffers::FlatBufferBuilder* builder = new flatbuffers::FlatBufferBuilder();
    flatbuffers::Offset<TestDetectorFlat::Digi>* digis = new flatbuffers::Offset<TestDetectorFlat::Digi>[nDigis];

    // Write some data to check it on the receiver side
    // (*fBigBuffer)[7] = 'c';

    // unsigned char *inv_buf = nullptr;
    // auto bigBuffer = builder->CreateUninitializedVector<unsigned char>(sizeof(*fBigBuffer), &inv_buf);
    // memcpy(inv_buf, fBigBuffer->data(), sizeof(*fBigBuffer));

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
    auto mloc = CreateDigiPayload(*builder, dvector); // digis:[Digi]
    // auto mloc = CreateDigiPayload(*builder, dvector, bigBuffer); // digis:[Digi], bigBuffer:[ubyte]
    FinishDigiPayloadBuffer(*builder, mloc);

    delete [] digis;

    fOutput = fTransportFactory->CreateMessage(builder->GetBufferPointer(), builder->GetSize(), free_builder, builder);
}

#endif /* FLATBUFFERS */
