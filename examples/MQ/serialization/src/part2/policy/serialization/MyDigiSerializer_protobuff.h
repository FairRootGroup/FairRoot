
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

class MyDigiProtoSerializer
{
  public:
    MyDigiProtoSerializer()
    {}

    MyDigiProtoSerializer(const MyDigiProtoSerializer&) = delete;
    MyDigiProtoSerializer operator=(const MyDigiProtoSerializer&) = delete;

    virtual ~MyDigiProtoSerializer()
    {}

    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        int numEntries=input->GetEntriesFast();
        Tuto7PayloadProto::DigiPayload digi_array;
        for (int i = 0; i < numEntries; ++i)
        {
            MyDigi* digi = (MyDigi*)input->At(i);
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

        msg->Rebuild(const_cast<char*>(str->c_str()), str->length(), digiproto::free_string, str);
    }


};

/////////////////////////////////////////////////////////////////////////////////////////////////
// Deserialization class
/////////////////////////////////////////////////////////////////////////////////////////////////


class MyDigiProtoDeserializer
{
  public:
    MyDigiProtoDeserializer()
    {}

    MyDigiProtoDeserializer(const MyDigiProtoDeserializer&) = delete;
    MyDigiProtoDeserializer operator=(const MyDigiProtoDeserializer&) = delete;

    virtual ~MyDigiProtoDeserializer()
    {
    }

    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, TClonesArray* input)
    {
        input->Delete();
        Tuto7PayloadProto::DigiPayload digi_array;
        digi_array.ParseFromArray(msg->GetData(), msg->GetSize());
        int numEntries = digi_array.digi_size();
        for (int i = 0; i < numEntries; ++i)
        {
            const Tuto7PayloadProto::Digi& digi = digi_array.digi(i);
            new ((*input)[i]) MyDigi(digi.x(), digi.y(), digi.z(), digi.time_stamp(), digi.time_stamperror());
        }
    }
};

#endif /* MYDIGIPROTOSERIALIZERPROTO_H */
