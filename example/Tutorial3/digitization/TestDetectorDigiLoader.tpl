/* 
 * File:   TestDetectorDigiLoader.tpl
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 *
 */

/// Implementation of the template class

template <typename T1, typename T2> TestDetectorDigiLoader<T1,T2>::TestDetectorDigiLoader() : 
FairMQSamplerTask("Load Data described by class T1 into the Payload class T2")
{ 
}
 
template <typename T1, typename T2> TestDetectorDigiLoader<T1,T2>::~TestDetectorDigiLoader() 
{ 
}

template <typename T1, typename T2> void TestDetectorDigiLoader<T1,T2>::Exec(Option_t* opt) 
{ 
    /*
    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(T2);

    fOutput = fTransportFactory->CreateMessage(size);
    T2* ptr = reinterpret_cast<T2*>(fOutput->GetData());

    for (Int_t i = 0; i < nDigis; ++i) 
    {
        T1* digi = reinterpret_cast<T1*>(fInput->At(i));
        if (!digi) continue;
        // TO DO : make the part below generic.
        new(&ptr[i]) T2();
        ptr[i] = T2();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
    // */
}

////////// Specialization <FairMQDigi, FairMQPayload::TestDetectorDigi>
template <> 
void TestDetectorDigiLoader<FairMQDigi, FairMQPayload::TestDetectorDigi>::Exec(Option_t* opt) 
{ 
    int nDigis = fInput->GetEntriesFast();
    int size = nDigis * sizeof(FairMQPayload::TestDetectorDigi);

    fOutput = fTransportFactory->CreateMessage(size);
    FairMQPayload::TestDetectorDigi* ptr = reinterpret_cast<FairMQPayload::TestDetectorDigi*>(fOutput->GetData());

    for (Int_t i = 0; i < nDigis; ++i) 
    {
        FairMQDigi* digi = reinterpret_cast<FairMQDigi*>(fInput->At(i));
        if (!digi) continue;
        new(&ptr[i]) FairMQPayload::TestDetectorDigi();
        ptr[i] = FairMQPayload::TestDetectorDigi();
        ptr[i].fX = digi->GetX();
        ptr[i].fY = digi->GetY();
        ptr[i].fZ = digi->GetZ();
        ptr[i].fTimeStamp = digi->GetTimeStamp();
    }
    
}



////////// Specialization <FairTestDetectorDigi, TestDetectorPayload::TestDetectorDigi>

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

