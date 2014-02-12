/* 
 * File:   FairMQDigiLoader.tpl
 * Author: winckler
 *
 * Created on February 7, 2014, 5:00 PM
 */

/// Implementation of the template class

template <typename T1, typename T2> FairMQDigiLoader<T1,T2>::FairMQDigiLoader() : 
FairMQSamplerTask("Load Data described by class T1 into the Payload class T2"),
        fPayloadPtr(NULL), fNDigis(0)
{ 
}
 
template <typename T1, typename T2> FairMQDigiLoader<T1,T2>::~FairMQDigiLoader() 
{ 
}

template <typename T1, typename T2> void FairMQDigiLoader<T1,T2>::Exec(Option_t* opt) 
{ 
}

template <typename T1, typename T2> 
void FairMQDigiLoader<T1,T2>::AllocateMsgStorage()
{
    fNDigis = fInput->GetEntriesFast();
    int size = fNDigis * sizeof(T2);
    fOutput = fTransportFactory->CreateMessage(size);
    fPayloadPtr = reinterpret_cast<T2*>(fOutput->GetData());
}

template <typename T1, typename T2> 
void FairMQDigiLoader<T1,T2>::LoadXYZTDigi()
{
    AllocateMsgStorage();
    for (Int_t i = 0; i < fNDigis; ++i) 
    {
        T1* digi = reinterpret_cast<T1*>(fInput->At(i));
        if (!digi) continue;
        // TO DO : make the part below generic.
        // in the following we need fx, fy etc. as attribute in payload class (T2)
        // and GetX(), GetY() etc. as method in digi class (T1))
        new(&fPayloadPtr[i]) T2();
        fPayloadPtr[i] = T2();
        fPayloadPtr[i].fX = digi->GetX();
        fPayloadPtr[i].fY = digi->GetY();
        fPayloadPtr[i].fZ = digi->GetZ();
        fPayloadPtr[i].fTimeStamp = digi->GetTimeStamp();
    }
}


