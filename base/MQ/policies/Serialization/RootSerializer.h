/* 
 * File:   RootSerializer.h
 * Author: winckler
 *
 * Created on January 14, 2015, 3:44 PM
 */

#ifndef ROOTSERIALIZER_H
#define ROOTSERIALIZER_H

#include <memory>

#include "TClonesArray.h"
#include "TMessage.h"

#include "FairMQMessage.h"

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

struct RootSerializer
{
    RootSerializer() = default;
    virtual ~RootSerializer() = default;

    template<typename T>
    void Serialize(FairMQMessage& msg, T* input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input);
        msg.Rebuild(tm->Buffer(),
                    tm->BufferSize(),
                    [](void*, void* tmsg){ delete static_cast<TMessage*>(tmsg); },
                    tm);
    }

    template<typename T>
    void Serialize(FairMQMessage& msg, const std::unique_ptr<T>& input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input.get());
        msg.Rebuild(tm->Buffer(),
                    tm->BufferSize(),
                    [](void*, void* tmsg){ delete static_cast<TMessage*>(tmsg); },
                    tm);
    }

    template<typename T>
    void Deserialize(FairMQMessage& msg, T*& output)
    {
        delete output;
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output = static_cast<T*>(tm.ReadObjectAny(tm.GetClass()));
    }

    template<typename T>
    void Deserialize(FairMQMessage& msg, std::unique_ptr<T>& output)
    {
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output.reset(static_cast<T*>(tm.ReadObjectAny(tm.GetClass())));
    }
};

#endif /* ROOTSERIALIZER_H */
