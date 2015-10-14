
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
#include "BinaryBaseClassSerializer.h"
#include "BaseSerializationPolicy.h"
#include "BaseDeserializationPolicy.h"

// FairRoot - Tutorial7
#include "MyDigi.h"
#include "MyPodData.h"


// FairRoot - Tutorial3
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorPayload.h"

template <typename PodType,typename DigiType>
class MyDigiSerializerCrtp : public BaseSerializationPolicy < MyDigiSerializerCrtp<PodType,DigiType> >
{
public: 
    
    
    MyDigiSerializerCrtp() :  
          fPayload(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)

    {}

    virtual ~MyDigiSerializerCrtp()
    {}
    

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

        return fMessage;
    }
    
protected:

    PodType* fPayload;
    FairMQMessage* fMessage;
    int fNumInput;
};



template <typename PodType,typename DigiType>
class MyDigiDeserializerCrtp : public BaseDeserializationPolicy < MyDigiDeserializerCrtp<PodType,DigiType> >
{
public: 
    
    MyDigiDeserializerCrtp() : 
          fContainer(nullptr) 
        , fPayload(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    virtual ~MyDigiDeserializerCrtp()
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
                new ((*fContainer)[i]) DigiType(fPayload[i].fX, fPayload[i].fY, fPayload[i].fZ, fPayload[i].fTimeStamp);
            }
            
            if (fContainer->IsEmpty())
            {
                LOG(ERROR) << "MyDigiDeserializerCrtp::message(): No Output array!";
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
typedef MyDigiSerializerCrtp<MyPodData::Digi,MyDigi>        MyDigiSerializerCrtp_t;
typedef MyDigiDeserializerCrtp<MyPodData::Digi,MyDigi>      MyDigiDeserializerCrtp_t;
// for tuto 3 data
typedef MyDigiSerializerCrtp<TestDetectorPayload::Digi,FairTestDetectorDigi>    Tuto3DigiSerializer_t;
typedef MyDigiDeserializerCrtp<TestDetectorPayload::Digi,FairTestDetectorDigi>  Tuto3DigiDeSerializer_t;


#endif  /* MYDIGISERIALIZERCRTP_H */