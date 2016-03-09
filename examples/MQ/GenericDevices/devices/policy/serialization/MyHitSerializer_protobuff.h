
#ifndef MYHITPROTOSERIALIZERPROTO_H
#define MYHITPROTOSERIALIZERPROTO_H


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
#include "MyHit.h"
#include "Tuto7Payload.pb.h"




/////////////////////////////////////////////////////////////////////////////////////////////////
// Serialization class
/////////////////////////////////////////////////////////////////////////////////////////////////

namespace hitproto
{
    // helper function to clean up the object holding the data after it is transported.
    void free_string(void* /*data*/, void* hint)
    {
        delete static_cast<std::string*>(hint);
    }
}

class MyHitProtoSerializer : public BaseSerializationPolicy < MyHitProtoSerializer >
{
  public:
    MyHitProtoSerializer() : fMessage(nullptr), fNumInput(0)
    {}

    MyHitProtoSerializer(const MyHitProtoSerializer&) = delete;
    MyHitProtoSerializer operator=(const MyHitProtoSerializer&) = delete;

    virtual ~MyHitProtoSerializer()
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
        Tuto7PayloadProto::HitPayload hit_array;
        for (int i = 0; i < numEntries; ++i)
        {
            MyHit* hit = static_cast<MyHit*>(array->At(i));
            if (!hit)
            {
                continue;
            }
            Tuto7PayloadProto::Hit* h = hit_array.add_hit();

            h->set_det_id(hit->GetDetectorID());
            h->set_mcindex(hit->GetRefIndex());
            h->set_posx(hit->GetX());
            h->set_posy(hit->GetY());
            h->set_posz(hit->GetZ());
            h->set_dposx(hit->GetDx());
            h->set_dposy(hit->GetDy());
            h->set_dposz(hit->GetDz());

            h->set_time_stamp(hit->GetTimeStamp());
            h->set_time_stamperror(hit->GetTimeStampError());
        }

        std::string* str = new std::string();
        hit_array.SerializeToString(str);

        fMessage->Rebuild(const_cast<char*>(str->c_str()), str->length(), hitproto::free_string, str);
        return fMessage;
    }

  protected:
    FairMQMessage* fMessage;
    int fNumInput;
};


/////////////////////////////////////////////////////////////////////////////////////////////////
// Deserialization class
/////////////////////////////////////////////////////////////////////////////////////////////////

class MyHitProtoDeserializer : public BaseDeserializationPolicy < MyHitProtoDeserializer >
{
  public:
    MyHitProtoDeserializer()
        : fContainer(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    MyHitProtoDeserializer(const MyHitProtoDeserializer&) = delete;
    MyHitProtoDeserializer operator=(const MyHitProtoDeserializer&) = delete;

    virtual ~MyHitProtoDeserializer()
    {
        if(fContainer)
            delete fContainer;
        fContainer=nullptr;
    }

    TClonesArray* DeserializeMsg(FairMQMessage* msg)
    {
        fContainer->Delete();
        Tuto7PayloadProto::HitPayload hit_array;
        hit_array.ParseFromArray(msg->GetData(), msg->GetSize());
        int numEntries = hit_array.hit_size();
        for (int i = 0; i < numEntries; ++i)
        {
            const Tuto7PayloadProto::Hit& hit = hit_array.hit(i);
            TVector3 pos(hit.posx(), hit.posy(), hit.posz());
            TVector3 dpos(hit.dposx(), hit.dposy(), hit.dposz());
            new ((*fContainer)[i]) MyHit(hit.det_id(), hit.mcindex(), pos, dpos, hit.time_stamp(), hit.time_stamperror());
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

#endif /* MYHITPROTOSERIALIZERPROTO_H */
