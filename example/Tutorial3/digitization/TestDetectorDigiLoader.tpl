/**
 * File:   TestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#include <iostream>

#include "FairTestDetectorPayload.h"

#ifdef PROTOBUF
  #include "FairTestDetectorPayload.pb.h"
#endif

template <typename T1, typename T2>
TestDetectorDigiLoader<T1,T2>::TestDetectorDigiLoader() :
FairMQSamplerTask("Load Data described by class T1 into the Payload class T2")
{
}

template <typename T1, typename T2>
TestDetectorDigiLoader<T1,T2>::~TestDetectorDigiLoader()
{
}

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::TestDetectorDigi>::Exec(Option_t* opt)
{ 
    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(TestDetectorPayload::TestDetectorDigi);

    fOutput = fTransportFactory->CreateMessage(size);
    TestDetectorPayload::TestDetectorDigi* ptr = reinterpret_cast<TestDetectorPayload::TestDetectorDigi*>(fOutput->GetData());

    for (Int_t i = 0; i < nDigis; ++i) {
        FairTestDetectorDigi* digi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }
        new(&ptr[i]) TestDetectorPayload::TestDetectorDigi();
        ptr[i] = TestDetectorPayload::TestDetectorDigi();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
}

#ifdef PROTOBUF

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>::Exec(Option_t* opt)
{
    int nDigis = fInput->GetEntriesFast();

    TestDetectorProto::DigiPayload dp;

    for (int i = 0; i < nDigis; ++i) {
        FairTestDetectorDigi* digi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }
        TestDetectorProto::Digi* d = dp.add_digi();
        d->set_fx(digi->GetX());
        d->set_fy(digi->GetY());
        d->set_fz(digi->GetZ());
        d->set_ftimestamp(digi->GetTimeStamp());
    }

    std::string str;
    dp.SerializeToString(&str);
    size_t size = str.length();

    fOutput = fTransportFactory->CreateMessage(size);
    memcpy(fOutput->GetData(), str.c_str(), size);
}

#endif /* PROTOBUF */
