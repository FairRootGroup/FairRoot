/* 
 * File:   MyHitSerializer.h
 * Author: winckler
 *
 * Created on October 14, 2014, 5:32 PM
 */


#ifndef MYHITSERIALIZERCRTP_H
#define	MYHITSERIALIZERCRTP_H

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
#include "BaseSerializationPolicy.h"
#include "BaseDeserializationPolicy.h"

// FairRoot - Tutorial7
#include "MyHit.h"
#include "MyPodData.h"

// FairRoot - Tutorial3
#include "FairTestDetectorHit.h"
#include "FairTestDetectorPayload.h"



////////////////////////////////////////////////////////////////////////////////////////
// serialize
template <typename PodType, typename HitType>
class MyHitSerializer : public BaseSerializationPolicy<MyHitSerializer<PodType,HitType> >
{
  public:
    MyHitSerializer() : BaseSerializationPolicy<MyHitSerializer<PodType,HitType> >(),
        fPayload(nullptr),
        fMessage(nullptr),
        fNumInput(0)
    {}

    MyHitSerializer(const MyHitSerializer&) = delete;
    MyHitSerializer operator=(const MyHitSerializer&) = delete;

    virtual ~MyHitSerializer(){}

    void SetMessage(FairMQMessage* msg)
    {
        fMessage = msg;
    }

    FairMQMessage* GetMessage()
    {
        return fMessage;
    }

    FairMQMessage* SerializeMsg(TClonesArray* array)
    {
        int numOutput = array->GetEntriesFast();
        int outputSize = numOutput * sizeof(PodType);
        fMessage->Rebuild(outputSize);
        PodType* output = reinterpret_cast<PodType*>(fMessage->GetData());

        if (outputSize > 0)
        {
            for (int i = 0; i < numOutput; ++i)
            {
                HitType* hit = static_cast<HitType*>(array->At(i));

                output[i].detID = hit->GetDetectorID();
                output[i].posX = hit->GetX();
                output[i].posY = hit->GetY();
                output[i].posZ = hit->GetZ();
                output[i].dposX = hit->GetDx();
                output[i].dposY = hit->GetDy();
                output[i].dposZ = hit->GetDz();
            }
        }
        return fMessage;
    }

  protected:
    PodType* fPayload;
    FairMQMessage* fMessage;
    int fNumInput;

};




////////////////////////////////////////////////////////////////////////////////////////
// deserialize

template <typename PodType, typename HitType>
class MyHitDeserializer : public BaseDeserializationPolicy<MyHitDeserializer<PodType,HitType> >
{
  public:
    MyHitDeserializer() : BaseDeserializationPolicy<MyHitDeserializer<PodType,HitType>>(),
        fContainer(nullptr),
        fPayload(nullptr),
        fMessage(nullptr),
        fNumInput(0)
    {}

    MyHitDeserializer(const MyHitDeserializer&) = delete;
    MyHitDeserializer operator=(const MyHitDeserializer&) = delete;

    virtual ~MyHitDeserializer()
    {
        if(fContainer)
            delete fContainer;
        fContainer=nullptr;
    }

    TClonesArray* DeserializeMsg(FairMQMessage* msg)
    {
        int inputSize = msg->GetSize();
        if (inputSize > 0)
        {
            fNumInput = inputSize / sizeof(PodType);
        }
        fPayload = static_cast<PodType*>(msg->GetData());
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
                MQLOG(DEBUG) << "MyHitDeserializer::DeSerializeMsg(): No Output array!";
            }
        }
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
    PodType* fPayload;
    FairMQMessage* fMessage;
    int fNumInput;
};


// for tuto 7 data
typedef MyHitSerializer<MyPodData::Hit,MyHit>   MyHitSerializer_t;
typedef MyHitDeserializer<MyPodData::Hit,MyHit> MyHitDeserializer_t;
// for tuto 3 data
typedef MyHitSerializer<TestDetectorPayload::Hit,FairTestDetectorHit>   Tuto3HitSerializer_t;
typedef MyHitDeserializer<TestDetectorPayload::Hit,FairTestDetectorHit> Tuto3HitDeserializer_t;


#endif /* MYHITSERIALIZERCRTP_H */

