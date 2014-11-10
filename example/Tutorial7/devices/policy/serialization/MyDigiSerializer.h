/* 
 * File:   MyDigiSerializer.h
 * Author: winckler
 *
 * Created on December 8, 2014, 1:16 PM
 */

#ifndef MYDIGISERIALIZER_H
#define	MYDIGISERIALIZER_H


// std
#include <vector>
#include <string>
#include <sstream>

// ROOT
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "TVector3.h"


// FairRoot - Tutorial7
#include "tuto7BinarySerializer.h"
#include "MyDigi.h"
#include "MyPodData.h"


// FairRoot - Tutorial3
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorPayload.h"

template <typename PodType,typename DigiType>
class MyDigiSerializer : public tuto7BinarySerializer<PodType>
{
public:
    
    MyDigiSerializer() : tuto7BinarySerializer<PodType>() {}
    ~MyDigiSerializer(){}
    // declare parent function and data members (not required when typed)
    using tuto7BinarySerializer<PodType>::fMessage;
    using tuto7BinarySerializer<PodType>::fContainer;
    using tuto7BinarySerializer<PodType>::GetPayload;
    using tuto7BinarySerializer<PodType>::fNumInput;
    using tuto7BinarySerializer<PodType>::fPayload;
    ////////////////////////////////////////////////////////////////////////////////////////
    // serialize
    
    virtual void DoSerialization(TClonesArray* array)
    {
        int nDigis = array->GetEntriesFast();
        int outputSize = nDigis * sizeof(PodType);
        fMessage->Rebuild(outputSize);
        PodType* digiptr = reinterpret_cast<PodType*>(fMessage->GetData());

        if (outputSize > 0)
        {
            for (int i = 0; i < nDigis; ++i)
            {
                DigiType* digi = reinterpret_cast<DigiType*>( array->At(i) );

                if (!digi)
                    continue;
                new (&digiptr[i]) PodType();
                digiptr[i] =  PodType();
                digiptr[i].fX = digi->GetX();
                digiptr[i].fY = digi->GetY();
                digiptr[i].fZ = digi->GetZ();
                digiptr[i].fTimeStamp = digi->GetTimeStamp();
                //digiptr[i].fTimeStampError = digi->GetTimeStampError();// commented as in tuto3
            }
        }
    }
    
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // deserialize

    virtual void DoDeSerialization(FairMQMessage* msg)
    {
        
        GetPayload(msg);
        if(fContainer)
        {
            fContainer->Delete();
            for (Int_t i = 0; i < fNumInput; ++i)
            {
                new ((*fContainer)[i]) DigiType(fPayload[i].fX, fPayload[i].fY, fPayload[i].fZ, fPayload[i].fTimeStamp);
            }
            
            if (fContainer->IsEmpty())
            {
                MQLOG(ERROR) << "MyDigiSerializer::message(): No Output array!";
            }
        }
    }


};



typedef MyDigiSerializer<MyPodData::Digi,MyDigi> MyDigiSerializer_t;
typedef MyDigiSerializer<TestDetectorPayload::Digi,FairTestDetectorDigi> Tuto3DigiSerializer_t;



#endif	/* MYDIGISERIALIZER_H */

