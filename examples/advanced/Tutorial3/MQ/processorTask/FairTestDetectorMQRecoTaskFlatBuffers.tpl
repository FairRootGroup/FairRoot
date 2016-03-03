// Implementation of FairTestDetectorMQRecoTask::Exec() with Google FlatBuffers transport data format

#ifdef FLATBUFFERS

#include "flatbuffers/flatbuffers.h"
#include "FairTestDetectorPayloadDigi_generated.h"
#include "FairTestDetectorPayloadHit_generated.h"

using namespace TestDetectorFlat;

// helper function to clean up the object holding the data after it is transported.
void free_builder(void *data, void *hint)
{
    delete static_cast<flatbuffers::FlatBufferBuilder*>(hint);
}

template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorFlat::DigiPayload, TestDetectorFlat::HitPayload>::Exec(Option_t* opt)
{
    fRecoTask->fDigiArray->Clear();

    auto digiPayload = GetDigiPayload(fPayload->GetData());
    auto digis = digiPayload->digis();
    // auto rbigBuffer = digiPayload->bigBuffer();
    // memcpy(fBigBuffer->data(), rbigBuffer->Data(), sizeof(*fBigBuffer));

    // Check if the data is the same as on the sender
    // LOG(WARN) << (*fBigBuffer)[7];

    int numEntries = digis->size();

    for (auto it = digis->begin(); it != digis->end(); ++it)
    {
        new ((*fRecoTask->fDigiArray)[it - digis->begin()]) FairTestDetectorDigi((*it)->x(), (*it)->y(), (*it)->z(), (*it)->timestamp());
        static_cast<FairTestDetectorDigi*>(((*fRecoTask->fDigiArray)[it - digis->begin()]))->SetTimeStampError((*it)->timestampError());
        // LOG(INFO) << (*it)->x() << " " << (*it)->y() << " " << (*it)->z() << " " << (*it)->timestamp() << " " << (*it)->timestampError();
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    flatbuffers::FlatBufferBuilder* builder = new flatbuffers::FlatBufferBuilder();
    flatbuffers::Offset<TestDetectorFlat::Hit> hits[numEntries];

    // unsigned char *inv_buf = nullptr;
    // auto bigBuffer = builder->CreateUninitializedVector<unsigned char>(sizeof(*fBigBuffer), &inv_buf);
    // memcpy(inv_buf, fBigBuffer->data(), sizeof(*fBigBuffer));

    for (int i = 0; i < numEntries; ++i)
    {
        FairTestDetectorHit* hit = (FairTestDetectorHit*)fRecoTask->fHitArray->At(i);
        if (!hit)
        {
            continue;
        }
        // LOG(WARN) << " " << hit->GetDetectorID() << " " << hit->GetX() << " " << hit->GetY() << " " << hit->GetZ() << " " << hit->GetDx() << " " << hit->GetDy() << " " << hit->GetDz();
        HitBuilder hb(*builder);
        hb.add_detID(hit->GetDetectorID()); // detID:int
        hb.add_mcIndex(hit->GetRefIndex()); // GetRefIndex:int
        hb.add_x(hit->GetX()); // x:double
        hb.add_y(hit->GetY()); // y:double
        hb.add_z(hit->GetZ()); // z:double
        hb.add_dx(hit->GetDx()); // dx:double
        hb.add_dy(hit->GetDy()); // dy:double
        hb.add_dz(hit->GetDz()); // dz:double
        hb.add_timestamp(hit->GetTimeStamp()); // timestamp:double
        hb.add_timestampError(hit->GetTimeStampError()); // timestampError:double
        hits[i] = hb.Finish();
    }
    auto hvector = builder->CreateVector(hits, numEntries);
    auto mloc = CreateHitPayload(*builder, hvector); // hits:[Hit]
    // auto mloc = CreateHitPayload(*builder, hvector, bigBuffer); // hits:[Hit], bigBuffer:[ubyte]
    FinishHitPayloadBuffer(*builder, mloc);

    fPayload->Rebuild(builder->GetBufferPointer(), builder->GetSize(), free_builder, builder);
}

#endif /* FLATBUFFERS */
