/*
 * File:   TestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

////////// Base template class <T1,T2>

template <typename T1, typename T2>
TestDetectorDigiLoader<T1, T2>::TestDetectorDigiLoader()
    : FairMQSamplerTask("Load class T1")
{
    fHasBoostSerialization = true;
#if __cplusplus >= 201103L
    fHasBoostSerialization = false;
    if (std::is_same<T2, boost::archive::binary_oarchive>::value || std::is_same<T2, boost::archive::text_oarchive>::value)
    {
        if (has_BoostSerialization<T1, void(T2&, const unsigned int)>::value == 1)
            fHasBoostSerialization = true;
    }
#endif
}

template <typename T1, typename T2>
TestDetectorDigiLoader<T1, T2>::~TestDetectorDigiLoader()
{
    if (fDigiVector.size() > 0)
        fDigiVector.clear();
}

// ----- Default implementation of TestDetectorDigiLoader::Exec() with Boost transport data format -----

template <typename T1, typename T2>
void TestDetectorDigiLoader<T1, T2>::Exec(Option_t* opt)
{

    // Default implementation of the base template Exec function using boost
    // the condition check if the input class has a function member with name
    // void serialize(T2 & ar, const unsigned int version) and if the payload are of boost type

    if (fHasBoostSerialization)
    {
        // LOG(INFO) <<" Boost Serialization ok ";

        std::ostringstream buffer;
        T2 OutputArchive(buffer);
        for (Int_t i = 0; i < fInput->GetEntriesFast(); ++i)
        {
            T1* digi = reinterpret_cast<T1*>(fInput->At(i));
            if (!digi)
                continue;
            fDigiVector.push_back(*digi);
        }

        OutputArchive << fDigiVector;
        int size = buffer.str().length();
        fOutput = fTransportFactory->CreateMessage(size);
        std::memcpy(fOutput->GetData(), buffer.str().c_str(), size);

        // delete the vector content
        if (fDigiVector.size() > 0)
            fDigiVector.clear();
    }
    else
    {
        LOG(ERROR) << " Boost Serialization not ok";
    }
}

// ----- Implementation of TestDetectorDigiLoader::Exec() with pure binary transport data format -----

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::Digi>::Exec(Option_t* opt)
{
     //<DB>  get the RID
    int rid = fEvtHeader->GetRunId();  
    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(TestDetectorPayload::Digi);
 

    fOutput = fTransportFactory->CreateMessage(sizeof(int)+size);
    int* iptr = reinterpret_cast<int*> (fOutput->GetData());
    new (&iptr[0]) int(rid);
    
    TestDetectorPayload::Digi* ptr = reinterpret_cast<TestDetectorPayload::Digi*>(&iptr[1]);

    for (Int_t i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
            continue;
        new (&ptr[i]) TestDetectorPayload::Digi();
        ptr[i] = TestDetectorPayload::Digi();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
}

// ----- Implementation of TestDetectorDigiLoader::Exec() with Root TMessage transport data format -----

// helper function to clean up the object holding the data after it is transported.
void free_tmessage (void *data, void *hint)
{
    delete (TMessage*)hint;
}

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TMessage>::Exec(Option_t* opt)
{
    TMessage* tm = new TMessage(kMESS_OBJECT);
    tm->WriteObject(fInput);
    fOutput = fTransportFactory->CreateMessage(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
}

// ----- Implementation of TestDetectorDigiLoader::Exec() with Google Protocol Buffers transport data format -----

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"

// helper function to clean up the object holding the data after it is transported.
void free_string (void *data, void *hint)
{
    delete (std::string*)hint;
}

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorProto::DigiPayload>::Exec(Option_t* opt)
{
    int nDigis = fInput->GetEntriesFast();

    TestDetectorProto::DigiPayload dp;

    for (int i = 0; i < nDigis; ++i)
    {
        FairTestDetectorDigi* digi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi)
        {
            continue;
        }
        TestDetectorProto::Digi* d = dp.add_digi();
        d->set_fx(digi->GetX());
        d->set_fy(digi->GetY());
        d->set_fz(digi->GetZ());
        d->set_ftimestamp(digi->GetTimeStamp());
    }

    std::string* str = new std::string();
    dp.SerializeToString(str);
    size_t size = str->length();

    fOutput = fTransportFactory->CreateMessage(const_cast<char*>(str->c_str()), size, free_string, str);
    // fOutput = fTransportFactory->CreateMessage(size);
    // memcpy(fOutput->GetData(), str.c_str(), size);
}

#endif /* PROTOBUF */
