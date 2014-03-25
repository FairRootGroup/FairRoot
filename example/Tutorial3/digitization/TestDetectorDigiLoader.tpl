/* 
 * File:   TestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

////////// Base template class <T1,T2>


template <typename T1, typename T2> 
void TestDetectorDigiLoader<T1,T2>::Exec(Option_t* opt) 
{ 
    std::ostringstream buffer;
    T2 OutputArchive(buffer);
    for (Int_t i = 0; i < fInput->GetEntriesFast(); ++i) 
    {
        T1* digi = reinterpret_cast<T1*>(fInput->At(i));
        if (!digi) continue;
        fDigiVector.push_back(*digi); 
    }
    
    OutputArchive << fDigiVector;
    int size=buffer.str().length();
    fOutput = fTransportFactory->CreateMessage(size);
    std::memcpy(fOutput->GetData(), buffer.str().c_str(), size);
    
    // delete the vector content
    if(fDigiVector.size()>0) fDigiVector.clear();

}



////////// Partial Specialization <T1,boost::archive::text_oarchive>

template <typename T1> void TestDetectorDigiLoader<T1,boost::archive::text_oarchive>::Exec(Option_t* opt) 
{ 
    std::ostringstream buffer;
    boost::archive::text_oarchive OutputArchive(buffer);
    for (Int_t i = 0; i < fInput->GetEntriesFast(); ++i) 
    {
        T1* digi = reinterpret_cast<T1*>(fInput->At(i));
        if (!digi) continue;
        fDigiVector.push_back(*digi);
        
    }
    
    OutputArchive << fDigiVector;
    int size=buffer.str().length();
    fOutput = fTransportFactory->CreateMessage(size);
    std::memcpy(fOutput->GetData(), buffer.str().c_str(), size);
    
    if(fDigiVector.size()>0) fDigiVector.clear();
    
}

////////// FULL Specialization 

template <>
void TestDetectorDigiLoader<FairTestDetectorDigi, TestDetectorPayload::TestDetectorDigi>::Exec(Option_t* opt)
{ 
    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(TestDetectorPayload::TestDetectorDigi);

    fOutput = fTransportFactory->CreateMessage(size);
    TestDetectorPayload::TestDetectorDigi* ptr = reinterpret_cast<TestDetectorPayload::TestDetectorDigi*>(fOutput->GetData());

    for (Int_t i = 0; i < nDigis; ++i) 
    {
        FairTestDetectorDigi* digi = reinterpret_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) continue;
        new(&ptr[i]) TestDetectorPayload::TestDetectorDigi();
        ptr[i] = TestDetectorPayload::TestDetectorDigi();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
}

#ifdef PROTOBUF
#include "FairTestDetectorPayload.pb.h"
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

