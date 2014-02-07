/* 
 * File:   FairMQDigiLoader.tpl
 * Author: winckler
 *
 * Created on February 7, 2014, 5:00 PM
 */

/// Implementation of the template class

template <typename T1, typename T2> FairMQDigiLoader<T1,T2>::FairMQDigiLoader() : 
FairMQSamplerTask("Load Data described by class T1 into the Payload class T2")
{ 
}
 
template <typename T1, typename T2> FairMQDigiLoader<T1,T2>::~FairMQDigiLoader() 
{ 
}

template <typename T1, typename T2> void FairMQDigiLoader<T1,T2>::Exec(Option_t* opt) 
{ 
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
    
}





