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

// FairRoot - Tutorial7
#include "tuto7BinarySerializer.h"
#include "MyHit.h"
#include "MyPodData.h"

// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"


//typedef FairTestDetectorHit DigiDataType;
//typedef TestDetectorPayload::Hit DigiPodDataType;

template <typename PodType, typename HitType>
class MyHitSerializer : public tuto7BinarySerializer<PodType>
{
public:
    
    MyHitSerializer() : tuto7BinarySerializer<PodType>() {}
    ~MyHitSerializer(){}
    
    using tuto7BinarySerializer<PodType>::fMessage;
    using tuto7BinarySerializer<PodType>::fContainer;
    using tuto7BinarySerializer<PodType>::GetPayload;
    using tuto7BinarySerializer<PodType>::fNumInput;
    using tuto7BinarySerializer<PodType>::fPayload;
    
    ////////////////////////////////////////////////////////////////////////////////////////
    // serialize
    
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
                TVector3 pos(fPayload[i].posX, fPayload[i].posY, fPayload[i].posZ);
                TVector3 dpos(fPayload[i].dposX, fPayload[i].dposY, fPayload[i].dposZ);
                new ((*fContainer)[i]) HitType(fPayload[i].detID, fPayload[i].mcindex, pos, dpos);
            }
            
            if (fContainer->IsEmpty())
            {
                MQLOG(ERROR) << "MyHitSerializer::message(): No Output array!";
            }
        }
    }
    

};


typedef MyHitSerializer<MyPodData::Hit,MyHit> MyHitSerializer_t;
typedef MyHitSerializer<TestDetectorPayload::Hit,FairTestDetectorHit> Tuto3HitSerializer_t;

#endif	/* MYHITSERIALIER_H */

