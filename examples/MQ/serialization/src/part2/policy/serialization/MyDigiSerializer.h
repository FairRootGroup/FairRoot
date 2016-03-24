
#ifndef MYDIGISERIALIZERCRTP_H
#define MYDIGISERIALIZERCRTP_H


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
#include "MyDigi.h"
#include "MyPodData.h"

// FairRoot - Tutorial3
//#include "FairTestDetectorDigi.h"
//#include "FairTestDetectorPayload.h"


template <typename PodType,typename DigiType>
class MyDigiSerializer
{
  public:
    MyDigiSerializer() 
    {}

    MyDigiSerializer(const MyDigiSerializer&) = delete;
    MyDigiSerializer operator=(const MyDigiSerializer&) = delete;

    virtual ~MyDigiSerializer()
    {}


    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        int nDigis = input->GetEntriesFast();
        int outputSize = nDigis * sizeof(PodType);
        msg->Rebuild(outputSize);
        PodType* digiptr = reinterpret_cast<PodType*>(msg->GetData());

        if (outputSize > 0)
        {
            for (int i = 0; i < nDigis; ++i)
            {
                DigiType* digi = reinterpret_cast<DigiType*>( input->At(i) );

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

};








template <typename PodType,typename DigiType>
class MyDigiDeserializer 
{
  public:
    MyDigiDeserializer()
    {}
    virtual ~MyDigiDeserializer()
    {}

    MyDigiDeserializer(const MyDigiDeserializer&) = delete;
    MyDigiDeserializer operator=(const MyDigiDeserializer&) = delete;


    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        int inputSize = msg->GetSize();
        int numInput=0;
        if (inputSize > 0)
        {
            numInput = inputSize / sizeof(PodType);
        }
        PodType* payload = static_cast<PodType*>(msg->GetData());
        if(input)
        {
            input->Delete();
            for (Int_t i = 0; i < numInput; ++i)
            {
                new ((*input)[i]) DigiType(payload[i].fX, payload[i].fY, payload[i].fZ, payload[i].fTimeStamp);
            }
            
            if (input->IsEmpty())
            {
                LOG(ERROR) << "MyDigiDeserializer::deserialize_impl(): No Output array!";
            }
        }
    }

};





// for tuto 7 data
typedef MyDigiSerializer<MyPodData::Digi,MyDigi>        MyDigiSerializer_t;
typedef MyDigiDeserializer<MyPodData::Digi,MyDigi>      MyDigiDeserializer_t;
// for tuto 3 data
//typedef MyDigiSerializer<TestDetectorPayload::Digi,FairTestDetectorDigi>    Tuto3DigiSerializer_t;
//typedef MyDigiDeserializer<TestDetectorPayload::Digi,FairTestDetectorDigi>  Tuto3DigiDeSerializer_t;


#endif /* MYDIGISERIALIZERCRTP_H */
