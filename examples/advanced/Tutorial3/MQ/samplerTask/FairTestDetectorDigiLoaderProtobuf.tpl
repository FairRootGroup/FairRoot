/**
 * File:   FairTestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

// Implementation of FairTestDetectorDigiLoader::Exec() with Google Protocol Buffers transport data format

#ifdef PROTOBUF

#include "FairTestDetectorPayload.pb.h"

// helper function to clean up the object holding the data after it is transported.
void free_string(void* /*data*/, void* hint)
{
    delete static_cast<std::string*>(hint);
}

template <>
void FairTestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>::Exec(Option_t* /*opt*/)
{
    int nDigis = fInput->GetEntriesFast();

    TestDetectorProto::DigiPayload dp;

    for (int i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        TestDetectorProto::Digi* d = dp.add_digi();
        d->set_fx(digi->GetX());
        d->set_fy(digi->GetY());
        d->set_fz(digi->GetZ());
        d->set_ftimestamp(digi->GetTimeStamp());
        d->set_ftimestamperror(digi->GetTimeStampError());
    }

    std::string* str = new std::string();
    dp.SerializeToString(str);

    fPayload = FairMQMessagePtr(fTransportFactory->CreateMessage(const_cast<char*>(str->c_str()), str->length(), free_string, str));
}

#endif /* PROTOBUF */
