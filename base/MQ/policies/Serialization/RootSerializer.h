/* 
 * File:   RootSerializer.h
 * Author: winckler
 *
 * Created on January 14, 2015, 3:44 PM
 */

#ifndef ROOTBASECLASSSERIALIZER_H
#define ROOTBASECLASSSERIALIZER_H

//std
#include <iostream>
#include <type_traits>
#include <memory>

//Root
#include "TClonesArray.h"
#include "TMessage.h"
//FairRoot
#include "FairMQMessage.h"

 #include "MQPolicyDef.h"

// special class to expose protected TMessage constructor
class FairTMessage : public TMessage
{
  public:
    FairTMessage(void* buf, Int_t len)
        : TMessage(buf, len)
    {
        ResetBit(kIsOwner);
    }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void* /*data*/, void* hint)
{
    delete static_cast<TMessage*>(hint);
}


struct RootSerializer
{
    RootSerializer() = default;
    ~RootSerializer() = default;
    template<typename T>
    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, T* input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input);
        msg->Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }

    template<typename T>
    void serialize_impl(std::unique_ptr<FairMQMessage>& msg, const std::unique_ptr<T>& input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input.get());
        msg->Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }
};

struct RootDeserializer 
{
    RootDeserializer() = default;
    ~RootDeserializer() = default;
    template<typename T>
    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, T*& output)
    {
        if(output) delete output;
        FairTMessage tm(msg->GetData(), msg->GetSize());
        output = static_cast<T*>(tm.ReadObject(tm.GetClass()));
    }

    template<typename T>
    void deserialize_impl(const std::unique_ptr<FairMQMessage>& msg, std::unique_ptr<T>& output)
    {
        FairTMessage tm(msg->GetData(), msg->GetSize());
        output.reset(static_cast<T*>(tm.ReadObject(tm.GetClass())));
    }
};



using RootDefaultInputPolicy = RawPtrDefaultInputPolicy<RootDeserializer,TClonesArray>;
using RootDefaultOutputPolicy = RawPtrDefaultOutputPolicy<RootSerializer,TClonesArray>;


#endif /* ROOTBASECLASSSERIALIZER_H */
