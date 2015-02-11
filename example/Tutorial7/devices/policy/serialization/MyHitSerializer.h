/* 
 * File:   MyHitSerializer.h
 * Author: winckler
 *
 * Created on October 14, 2014, 5:32 PM
 */


#ifndef MYHITSERIALIER_H
#define	MYHITSERIALIER_H

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
#include "MyHit.h"
#include "MyPodData.h"

// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"






////////////////////////////////////////////////////////////////////////////////////////
// serialize
template <typename PodType, typename HitType>
class MyHitSerializer : public BinaryBaseClassSerializer<PodType>
{
public:
    
    MyHitSerializer() : BinaryBaseClassSerializer<PodType>() {}
    virtual ~MyHitSerializer(){}
    
    using BinaryBaseClassSerializer<PodType>::fMessage;
    
    virtual void DoSerialization(TClonesArray* array)
    {
        int numOutput = array->GetEntriesFast();
        int outputSize = numOutput * sizeof(PodType);
        fMessage->Rebuild(outputSize);
        PodType* output = reinterpret_cast<PodType*>(fMessage->GetData());

        if (outputSize > 0)
        {
            for (int i = 0; i < numOutput; ++i)
            {
                HitType* hit = (HitType*)array->At(i);

                output[i].detID = hit->GetDetectorID();
                output[i].posX = hit->GetX();
                output[i].posY = hit->GetY();
                output[i].posZ = hit->GetZ();
                output[i].dposX = hit->GetDx();
                output[i].dposY = hit->GetDy();
                output[i].dposZ = hit->GetDz();
            }
        }
    }
    
   
    virtual FairMQMessage* SerializeMsg(TClonesArray* array)
    {
        DoSerialization(array);
        return fMessage;
    }
    

};




////////////////////////////////////////////////////////////////////////////////////////
// deserialize
    

template <typename PodType, typename HitType>
class MyHitDeSerializer : public BinaryBaseClassSerializer<PodType>
{
public:
    
    using BinaryBaseClassSerializer<PodType>::fMessage;
    using BinaryBaseClassSerializer<PodType>::GetPayload;
    using BinaryBaseClassSerializer<PodType>::fNumInput;
    using BinaryBaseClassSerializer<PodType>::fPayload;
    
    MyHitDeSerializer() : BinaryBaseClassSerializer<PodType>(), fContainer(nullptr) {}
    virtual ~MyHitDeSerializer() 
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
                TVector3 pos(fPayload[i].posX, fPayload[i].posY, fPayload[i].posZ);
                TVector3 dpos(fPayload[i].dposX, fPayload[i].dposY, fPayload[i].dposZ);
                new ((*fContainer)[i]) HitType(fPayload[i].detID, fPayload[i].mcindex, pos, dpos);
            }
            
            if (fContainer->IsEmpty())
            {
                MQLOG(ERROR) << "MyHitDeSerializer::DeSerializeMsg(): No Output array!";
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
typedef MyHitSerializer<MyPodData::Hit,MyHit>   MyHitSerializer_t;
typedef MyHitDeSerializer<MyPodData::Hit,MyHit> MyHitDeSerializer_t;
// for tuto 3 data
typedef MyHitSerializer<TestDetectorPayload::Hit,FairTestDetectorHit>   Tuto3HitSerializer_t;
typedef MyHitDeSerializer<TestDetectorPayload::Hit,FairTestDetectorHit> Tuto3HitDeSerializer_t;


#endif	/* MYHITSERIALIER_H */

