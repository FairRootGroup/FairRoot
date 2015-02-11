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
#include "BinaryBaseClassSerializer.h"

// FairRoot - Tutorial7
#include "MyDigi.h"
#include "MyPodData.h"


// FairRoot - Tutorial3
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorPayload.h"

template <typename PodType,typename DigiType>
class MyDigiSerializer : public BinaryBaseClassSerializer<PodType>
{
public: 
    
    using BinaryBaseClassSerializer<PodType>::fMessage;
    
    MyDigiSerializer() : BinaryBaseClassSerializer<PodType>() {}
    ~MyDigiSerializer(){}
    
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
    
    virtual FairMQMessage* SerializeMsg(TClonesArray* array)
    {
        DoSerialization(array);
        return fMessage;
    }
    
};



template <typename PodType,typename DigiType>
class MyDigiDeSerializer : public BinaryBaseClassSerializer<PodType>
{
public: 
    
    using BinaryBaseClassSerializer<PodType>::fMessage;
    using BinaryBaseClassSerializer<PodType>::GetPayload;
    using BinaryBaseClassSerializer<PodType>::fNumInput;
    using BinaryBaseClassSerializer<PodType>::fPayload;
    
    MyDigiDeSerializer() : BinaryBaseClassSerializer<PodType>(), fContainer(nullptr) {}
    ~MyDigiDeSerializer()
    { 
        if(fContainer) 
            delete fContainer; 
        fContainer=nullptr;
    }
    
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
                MQLOG(ERROR) << "MyDigiDeSerializer::message(): No Output array!";
            }
        }
    }
    
    virtual TClonesArray* DeSerializeMsg(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        return fContainer;
    }
    
    
    void InitContainer(const std::string &ClassName)
    {
        fContainer = new TClonesArray(ClassName.c_str());
    }
    
    void InitContainer(TClonesArray* array)
    {
        fContainer = array;
    }
    
    protected:
    
    TClonesArray* fContainer;
    
};



// for tuto 7 data
typedef MyDigiSerializer<MyPodData::Digi,MyDigi>        MyDigiSerializer_t;
typedef MyDigiDeSerializer<MyPodData::Digi,MyDigi>      MyDigiDeSerializer_t;
// for tuto 3 data
typedef MyDigiSerializer<TestDetectorPayload::Digi,FairTestDetectorDigi>    Tuto3DigiSerializer_t;
typedef MyDigiDeSerializer<TestDetectorPayload::Digi,FairTestDetectorDigi>  Tuto3DigiDeSerializer_t;


#endif	/* MYDIGISERIALIZER_H */

