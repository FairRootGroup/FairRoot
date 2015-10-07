/*
 * File:   FairTestDetectorMQRecoTask.tpl
 * Author: winckler
 *
 * Created on March 11, 2014, 11:07 AM
 */

// Implementation of FairTestDetectorMQRecoTask::Exec() with Google Protocol Buffers transport data format

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"

// helper function to clean up the object holding the data after it is transported.
void free_string (void *data, void *hint)
{
    delete (string*)hint;
}

template <>
void FairTestDetectorMQRecoTask<FairTestDetectorDigi, FairTestDetectorHit, TestDetectorProto::DigiPayload, TestDetectorProto::HitPayload>::Exec(Option_t* opt)
{
    fRecoTask->fDigiArray->Delete();

    TestDetectorProto::DigiPayload dp;
    dp.ParseFromArray(fPayload->GetData(), fPayload->GetSize());

    int numEntries = dp.digi_size();

    for (int i = 0; i < numEntries; ++i)
    {
        const TestDetectorProto::Digi& digi = dp.digi(i);
        new ((*fRecoTask->fDigiArray)[i]) FairTestDetectorDigi(digi.fx(), digi.fy(), digi.fz(), digi.ftimestamp());
    }

    if (!fRecoTask->fDigiArray)
    {
        LOG(ERROR) << "FairTestDetectorMQRecoTask::Exec(): No Point array!";
    }

    fRecoTask->Exec(opt);

    TestDetectorProto::HitPayload hp;

    for (int i = 0; i < numEntries; ++i)
    {
        FairTestDetectorHit* hit = (FairTestDetectorHit*)fRecoTask->fHitArray->At(i);
        if (!hit)
        {
            continue;
        }
        TestDetectorProto::Hit* h = hp.add_hit();
        h->set_detid(hit->GetDetectorID());
        h->set_posx(hit->GetX());
        h->set_posy(hit->GetY());
        h->set_posz(hit->GetZ());
        h->set_dposx(hit->GetDx());
        h->set_dposy(hit->GetDy());
        h->set_dposz(hit->GetDz());
    }

    string* str = new string();
    hp.SerializeToString(str);
    size_t size = str->length();

    fPayload->Rebuild(const_cast<char*>(str->c_str()), size, free_string, str);
    // fPayload->Rebuild(size);
    // memcpy(fPayload->GetData(), str.c_str(), size);
}

#endif /* PROTOBUF */
