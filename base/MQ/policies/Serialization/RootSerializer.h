/* 
 * File:   RootSerializer.h
 * Author: winckler
 *
 * Created on January 14, 2015, 3:44 PM
 */

#ifndef ROOTBASECLASSSERIALIZER_H
#define	ROOTBASECLASSSERIALIZER_H

//std
#include <iostream>
//Root
#include "TClonesArray.h"
#include "TMessage.h"
//FairRoot
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

// helper function to clean up the object holding the data after it is transported.
void free_tmessage(void *data, void *hint)
{
    delete (TMessage*)hint;
}

//template <typename TPayload>
class RootSerializer
{
  public:
    RootSerializer()
        : fContainer(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    RootSerializer(const RootSerializer&) = delete;
    RootSerializer operator=(const RootSerializer&) = delete;

    ~RootSerializer()
    {}

    void InitContainer(const std::string &ClassName)
    {
        fContainer = new TClonesArray(ClassName.c_str());
    }

    void InitContainer(TClonesArray* array)
    {
        fContainer = array;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // serialize

    void DoSerialization(TClonesArray* array)
    {
        TMessage* tm = new TMessage(kMESS_OBJECT);
        tm->WriteObject(array);
        // fMessage = fTransportFactory->CreateMessage(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
        fMessage->Rebuild(tm->Buffer(), tm->BufferSize(), free_tmessage, tm);
    }

    FairMQMessage* SerializeMsg(TClonesArray* array)
    {
        DoSerialization(array);
        return fMessage;
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage=msg;
    }

    FairMQMessage* GetMessage()
    {
        return fMessage;
    }

  protected:
    // TPayload* fPayload;
    TClonesArray* fContainer;
    FairMQMessage* fMessage;
    int fNumInput;
};

class RootDeSerializer
{
  public:
    RootDeSerializer()
        : fContainer(nullptr)
        , fMessage(nullptr)
        , fNumInput(0)
    {}

    RootDeSerializer(const RootDeSerializer&) = delete;
    RootDeSerializer operator=(const RootDeSerializer&) = delete;

    ~RootDeSerializer()
    {}

    void InitContainer(const std::string &ClassName)
    {
        fContainer = new TClonesArray(ClassName.c_str());
    }

    void InitContainer(TClonesArray* array)
    {
        fContainer = array;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // deserialize

    void DoDeSerialization(FairMQMessage* msg)
    {
        FairTMessage tm(msg->GetData(), msg->GetSize());
        fContainer  = (TClonesArray*)(tm.ReadObject(tm.GetClass()));
    }

    TClonesArray* DeserializeMsg(FairMQMessage* msg)
    {
        DoDeSerialization(msg);
        return fContainer;
    }

    void SetMessage(FairMQMessage* msg)
    {
        fMessage=msg;
    }

    FairMQMessage* GetMessage()
    {
        return fMessage;
    }

  protected:
    // TPayload* fPayload;
    TClonesArray* fContainer;
    FairMQMessage* fMessage;
    int fNumInput;
};

#endif /* ROOTBASECLASSSERIALIZER_H */
