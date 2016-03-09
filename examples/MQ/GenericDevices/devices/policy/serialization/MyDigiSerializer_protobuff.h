
#ifndef MYDIGIPROTOSERIALIZERPROTO_H
#define MYDIGIPROTOSERIALIZERPROTO_H


// std
#include <vector>
#include <string>
#include <sstream>

// ROOT
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "BaseSerializationPolicy.h"
#include "BaseDeserializationPolicy.h"

// FairRoot - Tutorial7
#include "MyDigi.h"
#include "Tuto7Payload.pb.h"




/////////////////////////////////////////////////////////////////////////////////////////////////
// Seserialization class
/////////////////////////////////////////////////////////////////////////////////////////////////
namespace digiproto
{

    // helper function to clean up the object holding the data after it is transported.
    void free_string(void* /*data*/, void* hint)
    {
        delete static_cast<std::string*>(hint);
    }

}

//template <typename PodType,typename DigiType>
class MyDigiProtoSerializer : public BaseSerializationPolicy < MyDigiProtoSerializer >
{
  public:
    MyDigiProtoSerializer() : fMessage(nullptr), fNumInput(0)
    {}

    MyDigiProtoSerializer(const MyDigiProtoSerializer&) = delete;
    MyDigiProtoSerializer operator=(const MyDigiProtoSerializer&) = delete;

    virtual ~MyDigiProtoSerializer()
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
        int numEntries=array->GetEntriesFast();
        Tuto7PayloadProto::DigiPayload digi_array;
        for (int i = 0; i < numEntries; ++i)
        {
            MyDigi* digi = static_cast<MyDigi*>(array->At(i));
            if (!digi)
            {
                continue;
            }
            Tuto7PayloadProto::Digi* d = digi_array.add_digi();

            d->set_x(digi->GetX());
            d->set_y(digi->GetY());
            d->set_z(digi->GetZ());

            d->set_time_stamp(digi->GetTimeStamp());
            d->set_time_stamperror(digi->GetTimeStampError());
        }

        std::string* str = new std::string();
        digi_array.SerializeToString(str);

        fMessage->Rebuild(const_cast<char*>(str->c_str()), str->length(), digiproto::free_string, str);
        return fMessage;
    }

  protected:
    FairMQMessage* fMessage;
    int fNumInput;

};


/////////////////////////////////////////////////////////////////////////////////////////////////
// Deserialization class
/////////////////////////////////////////////////////////////////////////////////////////////////

class MyDigiProtoDeserializer : public BaseDeserializationPolicy < MyDigiProtoDeserializer >
{
  public:
    MyDigiProtoDeserializer()
        : fContainer(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    MyDigiProtoDeserializer(const MyDigiProtoDeserializer&) = delete;
    MyDigiProtoDeserializer operator=(const MyDigiProtoDeserializer&) = delete;

    virtual ~MyDigiProtoDeserializer()
    {
        if(fContainer)
            delete fContainer;
        fContainer=nullptr;
    }

    TClonesArray* DeserializeMsg(FairMQMessage* msg)
    {
        fContainer->Delete();
        Tuto7PayloadProto::DigiPayload digi_array;
        digi_array.ParseFromArray(msg->GetData(), msg->GetSize());
        int numEntries = digi_array.digi_size();
        for (int i = 0; i < numEntries; ++i)
        {
            const Tuto7PayloadProto::Digi& digi = digi_array.digi(i);
            new ((*fContainer)[i]) MyDigi(digi.x(), digi.y(), digi.z(), digi.time_stamp(), digi.time_stamperror());
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
    FairMQMessage* fMessage;
    int fNumInput;
};

#endif /* MYDIGIPROTOSERIALIZERPROTO_H */
