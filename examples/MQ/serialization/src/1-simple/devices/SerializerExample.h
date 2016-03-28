

#ifndef BASICSERIALIZEREXAMPLE_H
#define BASICSERIALIZEREXAMPLE_H

#include <memory>

#include "TMessage.h"
#include "TClonesArray.h"

#include "FairMQMessage.h"

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
void free_tmessage(void *data, void *hint)
{
    delete (TMessage*)hint;
}

struct MySerializer
{
    void Serialize(FairMQMessage& msg, TClonesArray* input)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(input);
        msg.Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }
};

struct MyDeserializer 
{
    void Deserialize(FairMQMessage& msg, TClonesArray*& output)
    {
        if(output) delete output;
        FairTMessage tm(msg.GetData(), msg.GetSize());
        output = static_cast<TClonesArray*>(tm.ReadObject(tm.GetClass()));
    }
};


#endif


