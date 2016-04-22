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

// FairRoot - Tutorial7
#include "MyHit.h"
#include "MyPodData.h"

// FairRoot - Tutorial3
//#include "FairTestDetectorHit.h"
//#include "FairTestDetectorPayload.h"




template <typename PodType, typename HitType>
class MyHitSerializer 
{
  public:
    MyHitSerializer() 
    {}

    MyHitSerializer(const MyHitSerializer&) = delete;
    MyHitSerializer operator=(const MyHitSerializer&) = delete;

    virtual ~MyHitSerializer(){}

    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        int numOutput = input->GetEntriesFast();
        int outputSize = numOutput * sizeof(PodType);
        msg->Rebuild(outputSize);
        PodType* output = reinterpret_cast<PodType*>(msg->GetData());

        if (outputSize > 0)
        {
            for (int i = 0; i < numOutput; ++i)
            {
                HitType* hit = (HitType*)input->At(i);

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


};


////////////////////////////////////////////////////////////////////////////////////////
// deserialize

template <typename PodType, typename HitType>
class MyHitDeserializer 
{
  public:
    MyHitDeserializer() 
    {}

    MyHitDeserializer(const MyHitDeserializer&) = delete;
    MyHitDeserializer operator=(const MyHitDeserializer&) = delete;

    virtual ~MyHitDeserializer()
    {
    }

    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        int inputSize = msg->GetSize();
        int numInput=0;
        if (inputSize > 0)
        {
            numInput = inputSize / sizeof(PodType);
        }
        PodType* fPayload = static_cast<PodType*>(msg->GetData());
        if(input)
        {
            input->Delete();
            for (Int_t i = 0; i < numInput; ++i)
            {
                TVector3 pos(fPayload[i].posX, fPayload[i].posY, fPayload[i].posZ);
                TVector3 dpos(fPayload[i].dposX, fPayload[i].dposY, fPayload[i].dposZ);
                new ((*input)[i]) HitType(fPayload[i].detID, fPayload[i].mcindex, pos, dpos);
            }
            
            if (input->IsEmpty())
            {
                LOG(DEBUG) << "MyHitDeserializer::DeSerializeMsg(): No Output array!";
            }
        }
    }

};

// for tuto 7 data
typedef MyHitSerializer<MyPodData::Hit,MyHit>   MyHitSerializer_t;
typedef MyHitDeserializer<MyPodData::Hit,MyHit> MyHitDeserializer_t;

// for tuto 3 data
//typedef MyHitSerializer<TestDetectorPayload::Hit,FairTestDetectorHit>   Tuto3HitSerializer_t;
//typedef MyHitDeserializer<TestDetectorPayload::Hit,FairTestDetectorHit> Tuto3HitDeserializer_t;


#endif /* MYHITSERIALIZERCRTP_H */

